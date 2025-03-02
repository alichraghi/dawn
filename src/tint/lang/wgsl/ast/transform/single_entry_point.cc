// Copyright 2021 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/tint/lang/wgsl/ast/transform/single_entry_point.h"

#include <unordered_set>
#include <utility>

#include "src/tint/lang/wgsl/program/clone_context.h"
#include "src/tint/lang/wgsl/program/program_builder.h"
#include "src/tint/lang/wgsl/resolver/resolve.h"
#include "src/tint/lang/wgsl/sem/function.h"
#include "src/tint/lang/wgsl/sem/variable.h"
#include "src/tint/utils/rtti/switch.h"

TINT_INSTANTIATE_TYPEINFO(tint::ast::transform::SingleEntryPoint);
TINT_INSTANTIATE_TYPEINFO(tint::ast::transform::SingleEntryPoint::Config);

namespace tint::ast::transform {

SingleEntryPoint::SingleEntryPoint() = default;

SingleEntryPoint::~SingleEntryPoint() = default;

Transform::ApplyResult SingleEntryPoint::Apply(const Program* src,
                                               const DataMap& inputs,
                                               DataMap&) const {
    ProgramBuilder b;
    program::CloneContext ctx{&b, src, /* auto_clone_symbols */ true};

    auto* cfg = inputs.Get<Config>();
    if (cfg == nullptr) {
        b.Diagnostics().add_error(diag::System::Transform,
                                  "missing transform data for " + std::string(TypeInfo().name));
        return resolver::Resolve(b);
    }

    // Find the target entry point.
    const Function* entry_point = nullptr;
    for (auto* f : src->AST().Functions()) {
        if (!f->IsEntryPoint()) {
            continue;
        }
        if (f->name->symbol.Name() == cfg->entry_point_name) {
            entry_point = f;
            break;
        }
    }
    if (entry_point == nullptr) {
        b.Diagnostics().add_error(diag::System::Transform,
                                  "entry point '" + cfg->entry_point_name + "' not found");
        return resolver::Resolve(b);
    }

    auto& sem = src->Sem();
    auto& referenced_vars = sem.Get(entry_point)->TransitivelyReferencedGlobals();

    // Clone any module-scope variables, types, and functions that are statically referenced by the
    // target entry point.
    for (auto* decl : src->AST().GlobalDeclarations()) {
        Switch(
            decl,  //
            [&](const TypeDecl* ty) {
                // Strip aliases that reference unused override declarations.
                if (auto* arr = sem.Get(ty)->As<type::Array>()) {
                    auto* refs = sem.TransitivelyReferencedOverrides(arr);
                    if (refs) {
                        for (auto* o : *refs) {
                            if (!referenced_vars.Contains(o)) {
                                return;
                            }
                        }
                    }
                }

                // TODO(jrprice): Strip other unused types.
                b.AST().AddTypeDecl(ctx.Clone(ty));
            },
            [&](const Override* override) {
                if (referenced_vars.Contains(sem.Get(override))) {
                    if (!HasAttribute<IdAttribute>(override->attributes)) {
                        // If the override doesn't already have an @id() attribute, add one
                        // so that its allocated ID so that it won't be affected by other
                        // stripped away overrides
                        auto* global = sem.Get(override);
                        const auto* id = b.Id(global->OverrideId());
                        ctx.InsertFront(override->attributes, id);
                    }
                    b.AST().AddGlobalVariable(ctx.Clone(override));
                }
            },
            [&](const Var* var) {
                if (referenced_vars.Contains(sem.Get<sem::GlobalVariable>(var))) {
                    b.AST().AddGlobalVariable(ctx.Clone(var));
                }
            },
            [&](const Const* c) {
                // Always keep 'const' declarations, as these can be used by attributes and array
                // sizes, which are not tracked as transitively used by functions. They also don't
                // typically get emitted by the backend unless they're actually used.
                b.AST().AddGlobalVariable(ctx.Clone(c));
            },
            [&](const Function* func) {
                if (sem.Get(func)->HasAncestorEntryPoint(entry_point->name->symbol)) {
                    b.AST().AddFunction(ctx.Clone(func));
                }
            },
            [&](const Enable* ext) { b.AST().AddEnable(ctx.Clone(ext)); },
            [&](const DiagnosticDirective* d) { b.AST().AddDiagnosticDirective(ctx.Clone(d)); },
            [&](Default) {
                TINT_UNREACHABLE() << "unhandled global declaration: " << decl->TypeInfo().name;
            });
    }

    // Clone the entry point.
    b.AST().AddFunction(ctx.Clone(entry_point));

    return resolver::Resolve(b);
}

SingleEntryPoint::Config::Config(std::string entry_point) : entry_point_name(entry_point) {}

SingleEntryPoint::Config::Config(const Config&) = default;
SingleEntryPoint::Config::~Config() = default;
SingleEntryPoint::Config& SingleEntryPoint::Config::operator=(const Config&) = default;

}  // namespace tint::ast::transform
