[[group(1), binding(0)]] var arg_0 : texture_storage_2d_array<rgba8sint, write>;

fn textureStore_fbf53f() {
  textureStore(arg_0, vec2<i32>(), 1, vec4<i32>());
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureStore_fbf53f();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureStore_fbf53f();
}

[[stage(compute)]]
fn compute_main() {
  textureStore_fbf53f();
}
