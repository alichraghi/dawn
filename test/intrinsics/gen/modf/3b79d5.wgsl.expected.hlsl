intrinsics/gen/modf/3b79d5.wgsl:29:24 warning: use of deprecated intrinsic
  var res: vec3<f32> = modf(vec3<f32>(), &arg_1);
                       ^^^^

void modf_3b79d5() {
  float3 arg_1 = float3(0.0f, 0.0f, 0.0f);
  float3 res = modf(float3(0.0f, 0.0f, 0.0f), arg_1);
}

struct tint_symbol {
  float4 value : SV_Position;
};

float4 vertex_main_inner() {
  modf_3b79d5();
  return float4(0.0f, 0.0f, 0.0f, 0.0f);
}

tint_symbol vertex_main() {
  const float4 inner_result = vertex_main_inner();
  tint_symbol wrapper_result = (tint_symbol)0;
  wrapper_result.value = inner_result;
  return wrapper_result;
}

void fragment_main() {
  modf_3b79d5();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  modf_3b79d5();
  return;
}
