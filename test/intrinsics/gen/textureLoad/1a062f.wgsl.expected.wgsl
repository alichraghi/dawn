[[group(1), binding(0)]] var arg_0 : texture_storage_2d_array<rgba16float, read>;

fn textureLoad_1a062f() {
  var res : vec4<f32> = textureLoad(arg_0, vec2<i32>(), 1);
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureLoad_1a062f();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureLoad_1a062f();
}

[[stage(compute)]]
fn compute_main() {
  textureLoad_1a062f();
}
