[[group(1), binding(0)]] var arg_0 : texture_storage_2d<rgba16float, write>;

fn textureStore_be6e30() {
  textureStore(arg_0, vec2<i32>(), vec4<f32>());
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureStore_be6e30();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureStore_be6e30();
}

[[stage(compute)]]
fn compute_main() {
  textureStore_be6e30();
}
