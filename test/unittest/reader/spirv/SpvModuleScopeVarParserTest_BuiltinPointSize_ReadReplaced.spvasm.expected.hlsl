static float x_900 = 0.0f;
static float4 gl_Position = float4(0.0f, 0.0f, 0.0f, 0.0f);

void main_1() {
  x_900 = 1.0f;
  return;
}

struct main_out {
  float4 gl_Position;
};
struct tint_symbol {
  float4 gl_Position : SV_Position;
};

main_out main_inner() {
  main_1();
  const main_out tint_symbol_1 = {gl_Position};
  return tint_symbol_1;
}

tint_symbol main() {
  const main_out inner_result = main_inner();
  tint_symbol wrapper_result = (tint_symbol)0;
  wrapper_result.gl_Position = inner_result.gl_Position;
  return wrapper_result;
}
