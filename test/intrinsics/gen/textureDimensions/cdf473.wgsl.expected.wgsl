[[group(1), binding(0)]] var arg_0 : texture_storage_2d_array<rgba16sint, write>;

fn textureDimensions_cdf473() {
  var res : vec2<i32> = textureDimensions(arg_0);
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureDimensions_cdf473();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureDimensions_cdf473();
}

[[stage(compute)]]
fn compute_main() {
  textureDimensions_cdf473();
}
