[[group(1), binding(0)]] var arg_0 : texture_storage_1d<rg32uint, read>;

fn textureLoad_5bb7fb() {
  var res : vec4<u32> = textureLoad(arg_0, 1);
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureLoad_5bb7fb();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureLoad_5bb7fb();
}

[[stage(compute)]]
fn compute_main() {
  textureLoad_5bb7fb();
}
