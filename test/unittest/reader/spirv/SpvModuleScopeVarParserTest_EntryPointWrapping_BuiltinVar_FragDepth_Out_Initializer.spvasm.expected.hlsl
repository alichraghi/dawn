static float x_1 = 0.0f;

void main_1() {
  return;
}

struct main_out {
  float x_1_1;
};
struct tint_symbol {
  float x_1_1 : SV_Depth;
};

main_out main_inner() {
  main_1();
  const main_out tint_symbol_1 = {x_1};
  return tint_symbol_1;
}

tint_symbol main() {
  const main_out inner_result = main_inner();
  tint_symbol wrapper_result = (tint_symbol)0;
  wrapper_result.x_1_1 = inner_result.x_1_1;
  return wrapper_result;
}
