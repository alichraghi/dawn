// Copyright 2022 The Tint Authors.
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

////////////////////////////////////////////////////////////////////////////////
// File generated by tools/src/cmd/gen
// using the template:
//   src/tint/lang/core/builtin/builtin_test.cc.tmpl
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/tint/lang/core/builtin/builtin.h"

#include <string>

#include "gtest/gtest.h"

#include "src/tint/utils/text/string.h"

namespace tint::builtin {
namespace {

namespace parse_print_tests {

struct Case {
    const char* string;
    Builtin value;
};

inline std::ostream& operator<<(std::ostream& out, Case c) {
    return out << "'" << std::string(c.string) << "'";
}

static constexpr Case kValidCases[] = {
    {"__atomic_compare_exchange_result_i32", Builtin::kAtomicCompareExchangeResultI32},
    {"__atomic_compare_exchange_result_u32", Builtin::kAtomicCompareExchangeResultU32},
    {"__frexp_result_abstract", Builtin::kFrexpResultAbstract},
    {"__frexp_result_f16", Builtin::kFrexpResultF16},
    {"__frexp_result_f32", Builtin::kFrexpResultF32},
    {"__frexp_result_vec2_abstract", Builtin::kFrexpResultVec2Abstract},
    {"__frexp_result_vec2_f16", Builtin::kFrexpResultVec2F16},
    {"__frexp_result_vec2_f32", Builtin::kFrexpResultVec2F32},
    {"__frexp_result_vec3_abstract", Builtin::kFrexpResultVec3Abstract},
    {"__frexp_result_vec3_f16", Builtin::kFrexpResultVec3F16},
    {"__frexp_result_vec3_f32", Builtin::kFrexpResultVec3F32},
    {"__frexp_result_vec4_abstract", Builtin::kFrexpResultVec4Abstract},
    {"__frexp_result_vec4_f16", Builtin::kFrexpResultVec4F16},
    {"__frexp_result_vec4_f32", Builtin::kFrexpResultVec4F32},
    {"__modf_result_abstract", Builtin::kModfResultAbstract},
    {"__modf_result_f16", Builtin::kModfResultF16},
    {"__modf_result_f32", Builtin::kModfResultF32},
    {"__modf_result_vec2_abstract", Builtin::kModfResultVec2Abstract},
    {"__modf_result_vec2_f16", Builtin::kModfResultVec2F16},
    {"__modf_result_vec2_f32", Builtin::kModfResultVec2F32},
    {"__modf_result_vec3_abstract", Builtin::kModfResultVec3Abstract},
    {"__modf_result_vec3_f16", Builtin::kModfResultVec3F16},
    {"__modf_result_vec3_f32", Builtin::kModfResultVec3F32},
    {"__modf_result_vec4_abstract", Builtin::kModfResultVec4Abstract},
    {"__modf_result_vec4_f16", Builtin::kModfResultVec4F16},
    {"__modf_result_vec4_f32", Builtin::kModfResultVec4F32},
    {"__packed_vec3", Builtin::kPackedVec3},
    {"array", Builtin::kArray},
    {"atomic", Builtin::kAtomic},
    {"bool", Builtin::kBool},
    {"f16", Builtin::kF16},
    {"f32", Builtin::kF32},
    {"i32", Builtin::kI32},
    {"mat2x2", Builtin::kMat2X2},
    {"mat2x2f", Builtin::kMat2X2F},
    {"mat2x2h", Builtin::kMat2X2H},
    {"mat2x3", Builtin::kMat2X3},
    {"mat2x3f", Builtin::kMat2X3F},
    {"mat2x3h", Builtin::kMat2X3H},
    {"mat2x4", Builtin::kMat2X4},
    {"mat2x4f", Builtin::kMat2X4F},
    {"mat2x4h", Builtin::kMat2X4H},
    {"mat3x2", Builtin::kMat3X2},
    {"mat3x2f", Builtin::kMat3X2F},
    {"mat3x2h", Builtin::kMat3X2H},
    {"mat3x3", Builtin::kMat3X3},
    {"mat3x3f", Builtin::kMat3X3F},
    {"mat3x3h", Builtin::kMat3X3H},
    {"mat3x4", Builtin::kMat3X4},
    {"mat3x4f", Builtin::kMat3X4F},
    {"mat3x4h", Builtin::kMat3X4H},
    {"mat4x2", Builtin::kMat4X2},
    {"mat4x2f", Builtin::kMat4X2F},
    {"mat4x2h", Builtin::kMat4X2H},
    {"mat4x3", Builtin::kMat4X3},
    {"mat4x3f", Builtin::kMat4X3F},
    {"mat4x3h", Builtin::kMat4X3H},
    {"mat4x4", Builtin::kMat4X4},
    {"mat4x4f", Builtin::kMat4X4F},
    {"mat4x4h", Builtin::kMat4X4H},
    {"ptr", Builtin::kPtr},
    {"sampler", Builtin::kSampler},
    {"sampler_comparison", Builtin::kSamplerComparison},
    {"texture_1d", Builtin::kTexture1D},
    {"texture_2d", Builtin::kTexture2D},
    {"texture_2d_array", Builtin::kTexture2DArray},
    {"texture_3d", Builtin::kTexture3D},
    {"texture_cube", Builtin::kTextureCube},
    {"texture_cube_array", Builtin::kTextureCubeArray},
    {"texture_depth_2d", Builtin::kTextureDepth2D},
    {"texture_depth_2d_array", Builtin::kTextureDepth2DArray},
    {"texture_depth_cube", Builtin::kTextureDepthCube},
    {"texture_depth_cube_array", Builtin::kTextureDepthCubeArray},
    {"texture_depth_multisampled_2d", Builtin::kTextureDepthMultisampled2D},
    {"texture_external", Builtin::kTextureExternal},
    {"texture_multisampled_2d", Builtin::kTextureMultisampled2D},
    {"texture_storage_1d", Builtin::kTextureStorage1D},
    {"texture_storage_2d", Builtin::kTextureStorage2D},
    {"texture_storage_2d_array", Builtin::kTextureStorage2DArray},
    {"texture_storage_3d", Builtin::kTextureStorage3D},
    {"u32", Builtin::kU32},
    {"vec2", Builtin::kVec2},
    {"vec2f", Builtin::kVec2F},
    {"vec2h", Builtin::kVec2H},
    {"vec2i", Builtin::kVec2I},
    {"vec2u", Builtin::kVec2U},
    {"vec3", Builtin::kVec3},
    {"vec3f", Builtin::kVec3F},
    {"vec3h", Builtin::kVec3H},
    {"vec3i", Builtin::kVec3I},
    {"vec3u", Builtin::kVec3U},
    {"vec4", Builtin::kVec4},
    {"vec4f", Builtin::kVec4F},
    {"vec4h", Builtin::kVec4H},
    {"vec4i", Builtin::kVec4I},
    {"vec4u", Builtin::kVec4U},
};

static constexpr Case kInvalidCases[] = {
    {"__atomic_compareexchangeccresult_i32", Builtin::kUndefined},
    {"__atoml3_compare_exchane_resulti2", Builtin::kUndefined},
    {"__atomic_compare_Vxchange_result_i32", Builtin::kUndefined},
    {"__atomic_com1are_exchange_result_u32", Builtin::kUndefined},
    {"__atomic_qqompare_exchage_resulJ_u32", Builtin::kUndefined},
    {"__atllmic_compare_exchange_result_u377", Builtin::kUndefined},
    {"qpp_frexp_resultHHbstract", Builtin::kUndefined},
    {"__fep_esulv_abstract", Builtin::kUndefined},
    {"__Gbexp_resul_abstract", Builtin::kUndefined},
    {"_vfrexp_resiilt_f16", Builtin::kUndefined},
    {"__fr8xp_resultWWf16", Builtin::kUndefined},
    {"__frxp_result_fMxx", Builtin::kUndefined},
    {"gg_fXexp_reslt_f32", Builtin::kUndefined},
    {"__frXxpresul_V32", Builtin::kUndefined},
    {"__frexp_r3sult_f32", Builtin::kUndefined},
    {"__frexpEresult_vec2_abstract", Builtin::kUndefined},
    {"__frex_rPPsult_vTTc2_abstract", Builtin::kUndefined},
    {"__frexp_resuddt_ec2_xxbstract", Builtin::kUndefined},
    {"__frexp_result_ve442_f16", Builtin::kUndefined},
    {"_SSfrexp_resulVV_vec2_f16", Builtin::kUndefined},
    {"__fRxpRr22sult_vec2_f16", Builtin::kUndefined},
    {"__frexp_res9lt_vec_fF2", Builtin::kUndefined},
    {"__frexp_result_ve2_f32", Builtin::kUndefined},
    {"_OOfrexp_result_VeHRRf32", Builtin::kUndefined},
    {"__frexp_reyult_vec3_absract", Builtin::kUndefined},
    {"__frexp_re77ulll_vecG_arrnstract", Builtin::kUndefined},
    {"__4rexp_result_vec3_00bstract", Builtin::kUndefined},
    {"__oorxp_result_vec316", Builtin::kUndefined},
    {"zz_frexp_esult_ec3_f16", Builtin::kUndefined},
    {"__iirex11_result_vp3_f16", Builtin::kUndefined},
    {"__frXXxp_result_vec3_f32", Builtin::kUndefined},
    {"__fnnexp99resIIlt_vec3_f355", Builtin::kUndefined},
    {"__faSSerrp_result_vHHc3_fY2", Builtin::kUndefined},
    {"__freHp_resutve4_abstkkact", Builtin::kUndefined},
    {"jfrexpgresult_veRR4_abstrac", Builtin::kUndefined},
    {"__frexp_resul_vec4_absbrac", Builtin::kUndefined},
    {"_jfrexp_result_vec4_f16", Builtin::kUndefined},
    {"__frexp_resultvec4_f16", Builtin::kUndefined},
    {"__freqpresultvec4_f16", Builtin::kUndefined},
    {"__frexNN_result_vec_f32", Builtin::kUndefined},
    {"__frexp_resvvlt_vc4_f3", Builtin::kUndefined},
    {"__frexp_esult_vec4_f3QQ", Builtin::kUndefined},
    {"rmodf_reffultabstract", Builtin::kUndefined},
    {"__jodf_result_abstract", Builtin::kUndefined},
    {"_mNNwdf_r2sult8abstract", Builtin::kUndefined},
    {"__mdf_result_f16", Builtin::kUndefined},
    {"__modrr_result_f16", Builtin::kUndefined},
    {"__mGdf_result_f16", Builtin::kUndefined},
    {"__modf_resulFF_f32", Builtin::kUndefined},
    {"__modf_eult_E3", Builtin::kUndefined},
    {"__odf_resurrt_f32", Builtin::kUndefined},
    {"__modf_reslt_vec_abstract", Builtin::kUndefined},
    {"__modfJJresuDt_Xc2_abstract", Builtin::kUndefined},
    {"_modf_reslt_vec28abstrct", Builtin::kUndefined},
    {"__odf_reult_vkc211f1", Builtin::kUndefined},
    {"__mdf_result_vec2_f16", Builtin::kUndefined},
    {"__modf_resuJt_vec2_f6", Builtin::kUndefined},
    {"__modf_result_vec2cf32", Builtin::kUndefined},
    {"__modf_result_vec2_fO2", Builtin::kUndefined},
    {"KK_movvf_result_vec2_ftt__", Builtin::kUndefined},
    {"xx_modf_r8sult_vec3_abtr5ct", Builtin::kUndefined},
    {"__modf_resuFt_vec3_aqt__act", Builtin::kUndefined},
    {"__modf_result_vec3_aqqstrac", Builtin::kUndefined},
    {"__odf_33esult_vec3_f1O6", Builtin::kUndefined},
    {"_ttm6df_resQQlt_ooec9_f16", Builtin::kUndefined},
    {"_modf_resu66t_vec3_f16", Builtin::kUndefined},
    {"__mdf_resultOvxc3_f36zz", Builtin::kUndefined},
    {"__modf_resuyyt_vec3_f32", Builtin::kUndefined},
    {"__mod_resul_vecZHHf32", Builtin::kUndefined},
    {"__modf_reqult_44ec4WWbstract", Builtin::kUndefined},
    {"__mof_result_vec4_abstrOOct", Builtin::kUndefined},
    {"__modYooresult_vh4_bstract", Builtin::kUndefined},
    {"__modf_relt_ve4_f16", Builtin::kUndefined},
    {"__modf_result_ve4Ff16", Builtin::kUndefined},
    {"__modf_result_wec4_f1", Builtin::kUndefined},
    {"__Kdff_rGsult_vec4_f2", Builtin::kUndefined},
    {"__modf_reKKulq_vec4_f32", Builtin::kUndefined},
    {"__modf_resummt3vec4_f3F", Builtin::kUndefined},
    {"__packed_ec3", Builtin::kUndefined},
    {"__packed_ecq", Builtin::kUndefined},
    {"_backed_bbec3", Builtin::kUndefined},
    {"iira", Builtin::kUndefined},
    {"aqOOy", Builtin::kUndefined},
    {"arvvTTy", Builtin::kUndefined},
    {"atomFFc", Builtin::kUndefined},
    {"aoQ00P", Builtin::kUndefined},
    {"atPmic", Builtin::kUndefined},
    {"bos77", Builtin::kUndefined},
    {"CoRbbl", Builtin::kUndefined},
    {"booXX", Builtin::kUndefined},
    {"qOOO6", Builtin::kUndefined},
    {"fs", Builtin::kUndefined},
    {"f1X", Builtin::kUndefined},
    {"f3", Builtin::kUndefined},
    {"q", Builtin::kUndefined},
    {"f322", Builtin::kUndefined},
    {"0yz2", Builtin::kUndefined},
    {"iVP", Builtin::kUndefined},
    {"Cnn", Builtin::kUndefined},
    {"AtqqHH2", Builtin::kUndefined},
    {"at2x2", Builtin::kUndefined},
    {"mafKK", Builtin::kUndefined},
    {"ltgg2f", Builtin::kUndefined},
    {"mat2xf", Builtin::kUndefined},
    {"NTTtcx4f", Builtin::kUndefined},
    {"ma7ppl2h", Builtin::kUndefined},
    {"mNNt2xg", Builtin::kUndefined},
    {"uub2XX2h", Builtin::kUndefined},
    {"mt2x3", Builtin::kUndefined},
    {"m88xK", Builtin::kUndefined},
    {"maqx3", Builtin::kUndefined},
    {"m11t2x3f", Builtin::kUndefined},
    {"22at2iif", Builtin::kUndefined},
    {"at2x377", Builtin::kUndefined},
    {"m2t2xNh", Builtin::kUndefined},
    {"mVVt2x3h", Builtin::kUndefined},
    {"FaWW2w11h", Builtin::kUndefined},
    {"matww4", Builtin::kUndefined},
    {"mat2D4", Builtin::kUndefined},
    {"maKx4", Builtin::kUndefined},
    {"mat21PPhf", Builtin::kUndefined},
    {"mat24f", Builtin::kUndefined},
    {"mYYt2x4f", Builtin::kUndefined},
    {"mttHH4kk", Builtin::kUndefined},
    {"mat2rr4h", Builtin::kUndefined},
    {"WWas2x4h", Builtin::kUndefined},
    {"maYx2", Builtin::kUndefined},
    {"mq3f2", Builtin::kUndefined},
    {"vvafu222", Builtin::kUndefined},
    {"t3x2f", Builtin::kUndefined},
    {"YYat3f", Builtin::kUndefined},
    {"may3x2EYY", Builtin::kUndefined},
    {"da3xMoh", Builtin::kUndefined},
    {"matMMx2", Builtin::kUndefined},
    {"mat3x55h", Builtin::kUndefined},
    {"maN3", Builtin::kUndefined},
    {"ma33x3", Builtin::kUndefined},
    {"mt3x3", Builtin::kUndefined},
    {"mm66Issf", Builtin::kUndefined},
    {"mat3x1f", Builtin::kUndefined},
    {"Xt3x3", Builtin::kUndefined},
    {"LatIx3h", Builtin::kUndefined},
    {"at3fh", Builtin::kUndefined},
    {"mYtURD3", Builtin::kUndefined},
    {"mah3x4", Builtin::kUndefined},
    {"muqII4", Builtin::kUndefined},
    {"mat3xH", Builtin::kUndefined},
    {"at3QQvv", Builtin::kUndefined},
    {"at66ef", Builtin::kUndefined},
    {"ma7O4f", Builtin::kUndefined},
    {"m55t3x0DD", Builtin::kUndefined},
    {"maH3x4II", Builtin::kUndefined},
    {"at3x4", Builtin::kUndefined},
    {"ma994x2", Builtin::kUndefined},
    {"mWWt4Gt2", Builtin::kUndefined},
    {"ay42", Builtin::kUndefined},
    {"mt4x2f", Builtin::kUndefined},
    {"IIaBB4x2f", Builtin::kUndefined},
    {"TTat4x833", Builtin::kUndefined},
    {"ddUUnntYYx2h", Builtin::kUndefined},
    {"m5CCxxdZ", Builtin::kUndefined},
    {"matkkq2h", Builtin::kUndefined},
    {"5iitp00", Builtin::kUndefined},
    {"mnntIIx3", Builtin::kUndefined},
    {"ccaKx", Builtin::kUndefined},
    {"m43KK", Builtin::kUndefined},
    {"mat66x3f", Builtin::kUndefined},
    {"Et4PP3K", Builtin::kUndefined},
    {"xxatx3h", Builtin::kUndefined},
    {"qat4x3h", Builtin::kUndefined},
    {"MMayySrxh", Builtin::kUndefined},
    {"uat4", Builtin::kUndefined},
    {"tx4", Builtin::kUndefined},
    {"ma54FF4", Builtin::kUndefined},
    {"rra444z4f", Builtin::kUndefined},
    {"matWW", Builtin::kUndefined},
    {"CatZJXx4f", Builtin::kUndefined},
    {"maPPx4h", Builtin::kUndefined},
    {"mat4c4h", Builtin::kUndefined},
    {"matPPll6h", Builtin::kUndefined},
    {"9tyy", Builtin::kUndefined},
    {"ptKK", Builtin::kUndefined},
    {"x_", Builtin::kUndefined},
    {"ayKer", Builtin::kUndefined},
    {"szmpVek", Builtin::kUndefined},
    {"sampqeK", Builtin::kUndefined},
    {"sampler_comparisn", Builtin::kUndefined},
    {"sapler_comparisVVn", Builtin::kUndefined},
    {"samplerIcompaAUison", Builtin::kUndefined},
    {"jexurbRd", Builtin::kUndefined},
    {"exure_YYd", Builtin::kUndefined},
    {"exture_1d", Builtin::kUndefined},
    {"texxxur_1d", Builtin::kUndefined},
    {"tJxucce_2d", Builtin::kUndefined},
    {"texure_JJd", Builtin::kUndefined},
    {"lDexture_fCC_arraU", Builtin::kUndefined},
    {"tegture_2d_array", Builtin::kUndefined},
    {"teCCure2d_arra", Builtin::kUndefined},
    {"textue_3d", Builtin::kUndefined},
    {"tIx__ure_3d", Builtin::kUndefined},
    {"texurettPP", Builtin::kUndefined},
    {"tddx3ure_cube", Builtin::kUndefined},
    {"teKyyur_cube", Builtin::kUndefined},
    {"teturecub", Builtin::kUndefined},
    {"textinne_c03e_array", Builtin::kUndefined},
    {"nextCCruuvcubK_array", Builtin::kUndefined},
    {"tXxturellcbe_array", Builtin::kUndefined},
    {"tppxture_depth_2d", Builtin::kUndefined},
    {"txture_deptww_2d", Builtin::kUndefined},
    {"gexturedemmthuu2", Builtin::kUndefined},
    {"texmmre_depthaa2daray", Builtin::kUndefined},
    {"texture_RRepth_Td_ccZray", Builtin::kUndefined},
    {"text88re_depthTOd_array", Builtin::kUndefined},
    {"texture_depth_cm00e", Builtin::kUndefined},
    {"texture_Bmepth_cube", Builtin::kUndefined},
    {"Mextre_ppeph_cube", Builtin::kUndefined},
    {"texturOO_depth_cub_array", Builtin::kUndefined},
    {"GeGGture_depthcube_array", Builtin::kUndefined},
    {"texture11Hdepth_cube_array", Builtin::kUndefined},
    {"textu6e_FFepth_multiameeled_2d", Builtin::kUndefined},
    {"texture_epth_mltisampled_2d", Builtin::kUndefined},
    {"texture_depth_mullKsaiipled_2d", Builtin::kUndefined},
    {"texture_extenal", Builtin::kUndefined},
    {"IIext99reexvvernal", Builtin::kUndefined},
    {"texture_externl", Builtin::kUndefined},
    {"texture_mhltisampled_2d", Builtin::kUndefined},
    {"texturemPllltisampzzed_2d", Builtin::kUndefined},
    {"exture_mltisamed_2d", Builtin::kUndefined},
    {"texture_qqtoragff_1", Builtin::kUndefined},
    {"textre_JJddorage_1W", Builtin::kUndefined},
    {"XXrxture_storae1zz", Builtin::kUndefined},
    {"texturestorag2_2d", Builtin::kUndefined},
    {"yyNxture_storage_2d", Builtin::kUndefined},
    {"etue_storage_2OO", Builtin::kUndefined},
    {"reutuPe_storZgeE2d_array", Builtin::kUndefined},
    {"texlure_storddeee_d_22rray", Builtin::kUndefined},
    {"texture_mtorage_2V_a9ra", Builtin::kUndefined},
    {"teII1re_storage_3d", Builtin::kUndefined},
    {"texture_storagb_3d", Builtin::kUndefined},
    {"texizrestorge73d", Builtin::kUndefined},
    {"u3oi", Builtin::kUndefined},
    {"3", Builtin::kUndefined},
    {"S2", Builtin::kUndefined},
    {"e22", Builtin::kUndefined},
    {"1eC2", Builtin::kUndefined},
    {"vf8c2", Builtin::kUndefined},
    {"c2f", Builtin::kUndefined},
    {"JJecSSf", Builtin::kUndefined},
    {"92f", Builtin::kUndefined},
    {"vbbJJ2TT", Builtin::kUndefined},
    {"e66h", Builtin::kUndefined},
    {"u662h", Builtin::kUndefined},
    {"vW2i", Builtin::kUndefined},
    {"v2i", Builtin::kUndefined},
    {"veci", Builtin::kUndefined},
    {"rec2u", Builtin::kUndefined},
    {"2ec2B", Builtin::kUndefined},
    {"vcBBu", Builtin::kUndefined},
    {"veRR", Builtin::kUndefined},
    {"VLL0", Builtin::kUndefined},
    {"KOe3", Builtin::kUndefined},
    {"vgwcf", Builtin::kUndefined},
    {"vLphf", Builtin::kUndefined},
    {"eiiEf", Builtin::kUndefined},
    {"ec3h", Builtin::kUndefined},
    {"UU883", Builtin::kUndefined},
    {"rrecvvh", Builtin::kUndefined},
    {"ecmm", Builtin::kUndefined},
    {"vec4j", Builtin::kUndefined},
    {"vec3X", Builtin::kUndefined},
    {"vec38", Builtin::kUndefined},
    {"vecvEE", Builtin::kUndefined},
    {"z99ci", Builtin::kUndefined},
    {"JJGeQQ4", Builtin::kUndefined},
    {"ssec4", Builtin::kUndefined},
    {"PecK", Builtin::kUndefined},
    {"tpc4f", Builtin::kUndefined},
    {"vec", Builtin::kUndefined},
    {"MMec4f", Builtin::kUndefined},
    {"vJJc40", Builtin::kUndefined},
    {"8c", Builtin::kUndefined},
    {"vecggKh", Builtin::kUndefined},
    {"vecfi", Builtin::kUndefined},
    {"vec47Q", Builtin::kUndefined},
    {"veY4i", Builtin::kUndefined},
    {"keSu", Builtin::kUndefined},
    {"n422", Builtin::kUndefined},
    {"vFFu", Builtin::kUndefined},
};

using BuiltinParseTest = testing::TestWithParam<Case>;

TEST_P(BuiltinParseTest, Parse) {
    const char* string = GetParam().string;
    Builtin expect = GetParam().value;
    EXPECT_EQ(expect, ParseBuiltin(string));
}

INSTANTIATE_TEST_SUITE_P(ValidCases, BuiltinParseTest, testing::ValuesIn(kValidCases));
INSTANTIATE_TEST_SUITE_P(InvalidCases, BuiltinParseTest, testing::ValuesIn(kInvalidCases));

using BuiltinPrintTest = testing::TestWithParam<Case>;

TEST_P(BuiltinPrintTest, Print) {
    Builtin value = GetParam().value;
    const char* expect = GetParam().string;
    EXPECT_EQ(expect, tint::ToString(value));
}

INSTANTIATE_TEST_SUITE_P(ValidCases, BuiltinPrintTest, testing::ValuesIn(kValidCases));

}  // namespace parse_print_tests

}  // namespace
}  // namespace tint::builtin
