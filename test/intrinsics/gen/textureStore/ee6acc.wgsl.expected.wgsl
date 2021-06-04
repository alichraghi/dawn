[[group(1), binding(0)]] var arg_0 : texture_storage_3d<rg32float, write>;

fn textureStore_ee6acc() {
  textureStore(arg_0, vec3<i32>(), vec4<f32>());
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureStore_ee6acc();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureStore_ee6acc();
}

[[stage(compute)]]
fn compute_main() {
  textureStore_ee6acc();
}
