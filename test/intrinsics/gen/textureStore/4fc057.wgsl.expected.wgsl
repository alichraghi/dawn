[[group(1), binding(0)]] var arg_0 : texture_storage_2d_array<rgba8snorm, write>;

fn textureStore_4fc057() {
  textureStore(arg_0, vec2<i32>(), 1, vec4<f32>());
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureStore_4fc057();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureStore_4fc057();
}

[[stage(compute)]]
fn compute_main() {
  textureStore_4fc057();
}
