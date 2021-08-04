intrinsics/gen/frexp/6efa09.wgsl:29:24 warning: use of deprecated intrinsic
  var res: vec3<f32> = frexp(vec3<f32>(), &arg_1);
                       ^^^^^

float3 tint_frexp(float3 param_0, inout int3 param_1) {
  float3 float_exp;
  float3 significand = frexp(param_0, float_exp);
  param_1 = int3(float_exp);
  return significand;
}

static int3 arg_1 = int3(0, 0, 0);

void frexp_6efa09() {
  float3 res = tint_frexp(float3(0.0f, 0.0f, 0.0f), arg_1);
}

struct tint_symbol {
  float4 value : SV_Position;
};

float4 vertex_main_inner() {
  frexp_6efa09();
  return float4(0.0f, 0.0f, 0.0f, 0.0f);
}

tint_symbol vertex_main() {
  const float4 inner_result = vertex_main_inner();
  tint_symbol wrapper_result = (tint_symbol)0;
  wrapper_result.value = inner_result;
  return wrapper_result;
}

void fragment_main() {
  frexp_6efa09();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  frexp_6efa09();
  return;
}
