static float4 x_GLF_color = float4(0.0f, 0.0f, 0.0f, 0.0f);

float f_() {
  int i = 0;
  i = 1;
  {
    for(; (i < 10); i = (i + 1)) {
      if ((float(i) >= 1.0f)) {
        return 1.0f;
      } else {
        continue;
      }
    }
  }
  return 1.0f;
}

void main_1() {
  float4 c = float4(0.0f, 0.0f, 0.0f, 0.0f);
  int i_1 = 0;
  c = float4(1.0f, 0.0f, 0.0f, 1.0f);
  i_1 = 0;
  while (true) {
    if ((i_1 < 1)) {
    } else {
      break;
    }
    {
      const float x_39 = f_();
      c.x = x_39;
      i_1 = (i_1 + 1);
    }
  }
  x_GLF_color = c;
  return;
}

struct main_out {
  float4 x_GLF_color_1;
};
struct tint_symbol {
  float4 x_GLF_color_1 : SV_Target0;
};

main_out main_inner() {
  main_1();
  const main_out tint_symbol_1 = {x_GLF_color};
  return tint_symbol_1;
}

tint_symbol main() {
  const main_out inner_result = main_inner();
  tint_symbol wrapper_result = (tint_symbol)0;
  wrapper_result.x_GLF_color_1 = inner_result.x_GLF_color_1;
  return wrapper_result;
}
