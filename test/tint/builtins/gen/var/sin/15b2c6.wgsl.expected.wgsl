fn sin_15b2c6() {
  const arg_0 = vec4(1.57079632679);
  var res = sin(arg_0);
}

@vertex
fn vertex_main() -> @builtin(position) vec4<f32> {
  sin_15b2c6();
  return vec4<f32>();
}

@fragment
fn fragment_main() {
  sin_15b2c6();
}

@compute @workgroup_size(1)
fn compute_main() {
  sin_15b2c6();
}
