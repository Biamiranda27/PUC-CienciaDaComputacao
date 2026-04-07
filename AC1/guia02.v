

module Guia_0201;
   real x = 0;
   real power2 = 1.0;
   integer y = 7;
   reg [7:0] b = 8'b10100000;

   initial begin
      $display("Guia_0201");
      $display("b = 0.%8b", b);
      while (y >= 0) begin
         power2 = power2 / 2.0;
         if (b[y] == 1) x = x + power2;
         y = y - 1;
      end
      $display("Decimal: x = %f", x);
   end
endmodule

module Guia_0202;
   real x = 0.75;
   integer y = 7;
   reg [7:0] b = 0;

   initial begin
      $display("Guia_0202");
      while (x > 0 && y >= 0) begin
         if (x * 2 >= 1) begin
            b[y] = 1;
            x = x * 2.0 - 1.0;
         end else begin
            b[y] = 0;
            x = x * 2.0;
         end
         y = y - 1;
      end
      $display("Binário: b = 0.%8b", b);
   end
endmodule

module Guia_0203;
   reg [7:0] bin = 8'b01101000;
   reg [3:0] base4, base8, base16;

   initial begin
      $display("Guia_0203");
      base4 = bin[7:6] * 4 + bin[5:4];
      base8 = bin[7:5] * 8 + bin[4:2];
      base16 = bin[7:4];
      $display("Base 4: %d", base4);
      $display("Base 8: %d", base8);
      $display("Base 16: %h", base16);
   end
endmodule

module Guia_0204;
   reg [7:0] base4 = 8'b10110101;
   reg [7:0] bin;

   initial begin
      $display("Guia_0204");
      bin = (base4[7:6] << 6) | (base4[5:4] << 4) | (base4[3:2] << 2) | base4[1:0];
      $display("Binário: %8b", bin);
   end
endmodule

module Guia_0205;
   reg [7:0] a = 8'b10101010;
   reg [7:0] b = 8'b01010101;
   reg [7:0] c;

   initial begin
      $display("Guia_0205");
      c = a + b;
      $display("Soma: %8b", c);
      c = a - b;
      $display("Subtração: %8b", c);
      c = a * b;
      $display("Multiplicação: %8b", c);
      c = a / b;
      $display("Divisão: %8b", c);
   end
endmodule
