intrinsics/gen/modf/3d00e2.wgsl:29:24 warning: use of deprecated intrinsic
  var res: vec4<f32> = modf(vec4<f32>(), &arg_1);
                       ^^^^

static float4 arg_1 = float4(0.0f, 0.0f, 0.0f, 0.0f);

void modf_3d00e2() {
  float4 res = modf(float4(0.0f, 0.0f, 0.0f, 0.0f), arg_1);
}

struct tint_symbol {
  float4 value : SV_Position;
};

float4 vertex_main_inner() {
  modf_3d00e2();
  return float4(0.0f, 0.0f, 0.0f, 0.0f);
}

tint_symbol vertex_main() {
  const float4 inner_result = vertex_main_inner();
  tint_symbol wrapper_result = (tint_symbol)0;
  wrapper_result.value = inner_result;
  return wrapper_result;
}

void fragment_main() {
  modf_3d00e2();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  modf_3d00e2();
  return;
}
