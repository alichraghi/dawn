[[group(1), binding(0)]] var arg_0 : texture_storage_3d<rgba16uint, read>;

fn textureLoad_f56e6f() {
  var res : vec4<u32> = textureLoad(arg_0, vec3<i32>());
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureLoad_f56e6f();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureLoad_f56e6f();
}

[[stage(compute)]]
fn compute_main() {
  textureLoad_f56e6f();
}
