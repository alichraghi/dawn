[[group(1), binding(0)]] var arg_0 : texture_storage_2d_array<rgba8uint, write>;

fn textureStore_22d955() {
  textureStore(arg_0, vec2<i32>(), 1, vec4<u32>());
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureStore_22d955();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureStore_22d955();
}

[[stage(compute)]]
fn compute_main() {
  textureStore_22d955();
}
