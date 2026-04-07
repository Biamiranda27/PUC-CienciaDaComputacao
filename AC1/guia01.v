

module Guia_0101;
  integer x;
  reg [9:0] b;
  initial begin
    $display("Guia_0101");
    x = 27;    b = x;    $display("%d = %b", x, b);
    x = 51;    b = x;    $display("%d = %b", x, b);
    x = 725;   b = x;    $display("%d = %b", x, b);
    x = 132;   b = x;    $display("%d = %b", x, b);
    x = 360;   b = x;    $display("%d = %b", x, b);
  end
endmodule

module Guia_0102;
  integer x;
  reg [7:0] b;
  initial begin
    $display("Guia_0102");
    b = 8'b10011;   x = b;    $display("%b = %d", b, x);
    b = 8'b10101;   x = b;    $display("%b = %d", b, x);
    b = 8'b10110;   x = b;    $display("%b = %d", b, x);
    b = 8'b110010;  x = b;    $display("%b = %d", b, x);
    b = 8'b111011;  x = b;    $display("%b = %d", b, x);
  end
endmodule

module Guia_0103;
  integer x;
  initial begin
    $display("Guia_0103");
    x = 54;   $display("%d = %o (8) = %x (16)", x, x, x);
    x = 67;   $display("%d = %o (8) = %x (16)", x, x, x);
    x = 76;   $display("%d = %o (8) = %x (16)", x, x, x);
    x = 157;  $display("%d = %o (8) = %x (16)", x, x, x);
    x = 731;  $display("%d = %o (8) = %x (16)", x, x, x);
  end
endmodule

module Guia_0104;
  reg [7:0] b;
  initial begin
    $display("Guia_0104");
    b = 8'b10110;    $display("%b = %o (8)", b, b);
    b = 8'b11011;    $display("%b = %o (8)", b, b);
    b = 8'b100100;   $display("%b = %x (16)", b, b);
    b = 8'b101011;   $display("%b = %o (8)", b, b);
    b = 8'b101100;   $display("%b = %o (8)", b, b);
  end
endmodule

module Guia_0105;
  reg [7:0] s [0:15];
  initial begin
    $display("Guia_0105");
    s = "PUC-Minas";   $display("%s", s);
    s = "2025-01";     $display("%s", s);
    s = "Belo Horizonte - M.G.";  $display("%s", s);
    s = "156 157 151 164 145";  $display("%s", s);
    s = "4D 61 6E 68 61";  $display("%s", s);
  end
endmodule
