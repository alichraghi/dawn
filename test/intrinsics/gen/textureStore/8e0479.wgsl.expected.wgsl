[[group(1), binding(0)]] var arg_0 : texture_storage_2d_array<rgba32uint, write>;

fn textureStore_8e0479() {
  textureStore(arg_0, vec2<i32>(), 1, vec4<u32>());
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureStore_8e0479();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureStore_8e0479();
}

[[stage(compute)]]
fn compute_main() {
  textureStore_8e0479();
}
