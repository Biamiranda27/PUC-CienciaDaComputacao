// 845860 - Beatriz Miranda Paiva

module Guia_0301;
    reg [5:0] a = 6'b1011;
    reg [7:0] b = 8'b1100;
    reg [5:0] c = 6'b100011;
    reg [6:0] d = 7'b101001;
    reg [7:0] e = 8'b111010;
    
    initial begin
        $display("Exercício 01");
        $display("C1,6(%b) = %b", a, ~a);
        $display("C1,8(%b) = %b", b, ~b);
        $display("C2,6(%b) = %b", c, ~c + 1);
        $display("C2,7(%b) = %b", d, ~d + 1);
        $display("C2,8(%b) = %b", e, ~e + 1);
    end
endmodule

module Guia_0302;
    reg [5:0] a = 6'o123;
    reg [7:0] b = 8'hC4;
    reg [5:0] c = 6'o312;
    reg [9:0] d = 10'o153;
    reg [7:0] e = 8'h7D;
    
    initial begin
        $display("Exercício 02");
        $display("C1,6(%o) = %b", a, ~a);
        $display("C1,8(%h) = %b", b, ~b);
        $display("C2,6(%o) = %b", c, ~c + 1);
        $display("C2,10(%o) = %b", d, ~d + 1);
        $display("C2,8(%h) = %b", e, ~e + 1);
    end
endmodule

module Guia_0303;
    reg [4:0] a = 5'b10101;
    reg [5:0] b = 6'b110101;
    reg [5:0] c = 6'b100110;
    reg [6:0] d = 7'b1010111;
    reg [7:0] e = 8'b1110101;
    
    initial begin
        $display("Exercício 03");
        $display("%b = %d", a, -((~a + 1)));
        $display("%b = %d", b, -((~b + 1)));
        $display("%b = %d", c, -((~c + 1)));
        $display("%b = %d", d, -((~d + 1)));
        $display("%b = %d", e, -((~e + 1)));
    end
endmodule

module Guia_0304;
    reg signed [5:0] a = 6'b11101;
    reg signed [5:0] b = 6'b01101;
    reg signed [6:0] c = 7'b1011001;
    reg signed [4:0] d = 5'b10011;
    reg signed [8:0] e = 9'h6A2;
    reg signed [8:0] f = 9'hC14;
    
    initial begin
        $display("Exercício 04");
        $display("%b - %b = %b", a, b, a - b);
        $display("%b - %b = %b", c, d, c - d);
        $display("%h - %h = %h", e, f, e - f);
    end
endmodule

//nao consegui fazer a 5
