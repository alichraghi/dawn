[[group(1), binding(0)]] var arg_0 : texture_storage_3d<rgba32float, write>;

fn textureDimensions_8fca0f() {
  var res : vec3<i32> = textureDimensions(arg_0);
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureDimensions_8fca0f();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureDimensions_8fca0f();
}

[[stage(compute)]]
fn compute_main() {
  textureDimensions_8fca0f();
}
