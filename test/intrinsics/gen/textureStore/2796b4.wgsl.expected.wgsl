[[group(1), binding(0)]] var arg_0 : texture_storage_3d<rg32sint, write>;

fn textureStore_2796b4() {
  textureStore(arg_0, vec3<i32>(), vec4<i32>());
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureStore_2796b4();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureStore_2796b4();
}

[[stage(compute)]]
fn compute_main() {
  textureStore_2796b4();
}
