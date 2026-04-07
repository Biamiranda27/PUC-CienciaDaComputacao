
module guia0701(output s, output s_and, output s_nand, input a, b, sel);
  wire and_out, nand_out, nsel, and_sel, nand_sel;
  assign and_out = a & b;
  assign nand_out = ~(a & b);
  assign s_and = and_out;
  assign s_nand = nand_out;
  assign nsel = ~sel;               
  assign and_sel = and_out & nsel;   
  assign nand_sel = nand_out & sel;  
  assign s = and_sel | nand_sel;     
endmodule
module test_guia0701;
  reg a, b, sel;
  wire s, s_and, s_nand;
  guia0701 uut (s, s_and, s_nand, a, b, sel);
  initial begin
    $display("a b sel | AND NAND | S");
    $display("------------------------");
    a=0; b=0; sel=0; #1 $display("%b %b  %b  |  %b    %b   | %b", a, b, sel, s_and, s_nand, s);
    a=0; b=1; sel=0; #1 $display("%b %b  %b  |  %b    %b   | %b", a, b, sel, s_and, s_nand, s);
    a=1; b=0; sel=0; #1 $display("%b %b  %b  |  %b    %b   | %b", a, b, sel, s_and, s_nand, s);
    a=1; b=1; sel=0; #1 $display("%b %b  %b  |  %b    %b   | %b", a, b, sel, s_and, s_nand, s);
    
    a=0; b=0; sel=1; #1 $display("%b %b  %b  |  %b    %b   | %b", a, b, sel, s_and, s_nand, s);
    a=0; b=1; sel=1; #1 $display("%b %b  %b  |  %b    %b   | %b", a, b, sel, s_and, s_nand, s);
    a=1; b=0; sel=1; #1 $display("%b %b  %b  |  %b    %b   | %b", a, b, sel, s_and, s_nand, s);
    a=1; b=1; sel=1; #1 $display("%b %b  %b  |  %b    %b   | %b", a, b, sel, s_and, s_nand, s);
  end
endmodule



module guia0702(output s, input a, b, sel);
  wire or_out, nor_out, nsel, or_sel, nor_sel;
  assign or_out = a | b;
  assign nor_out = ~(a | b);
  assign nsel = ~sel;           
  assign or_sel = or_out & nsel;   
  assign nor_sel = nor_out & sel;  
  assign s = or_sel | nor_sel;     
endmodule
module test_guia0702;
  reg a, b, sel;
  wire s;
  guia0702 uut (s, a, b, sel);
  initial begin
    $display("a b sel | s (saida)");
    $display("------------------");
    a=0; b=0; sel=0; #1 $display("%b %b  %b  | %b", a, b, sel, s);
    a=0; b=1; sel=0; #1 $display("%b %b  %b  | %b", a, b, sel, s);
    a=1; b=0; sel=0; #1 $display("%b %b  %b  | %b", a, b, sel, s);
    a=1; b=1; sel=0; #1 $display("%b %b  %b  | %b", a, b, sel, s);

    a=0; b=0; sel=1; #1 $display("%b %b  %b  | %b", a, b, sel, s);
    a=0; b=1; sel=1; #1 $display("%b %b  %b  | %b", a, b, sel, s);
    a=1; b=0; sel=1; #1 $display("%b %b  %b  | %b", a, b, sel, s);
    a=1; b=1; sel=1; #1 $display("%b %b  %b  | %b", a, b, sel, s);
  end
endmodule



module guia0703(output s, input a, b, sel_op, sel_grp);
  wire and_out, nand_out, or_out, nor_out;
  wire and_sel, nand_sel, or_sel, nor_sel;
  wire not_sel_op, not_sel_grp;
  wire grupo_andnand, grupo_ornor;
  assign and_out = a & b;
  assign nand_out = ~(a & b);
  assign or_out = a | b;
  assign nor_out = ~(a | b);
  assign not_sel_op = ~sel_op;
  assign not_sel_grp = ~sel_grp;
  assign and_sel  = and_out  & not_sel_op & sel_grp;     
  assign nand_sel = nand_out & sel_op      & sel_grp;   
  assign or_sel   = or_out   & not_sel_op & not_sel_grp;
  assign nor_sel  = nor_out  & sel_op      & not_sel_grp; 
  assign s = and_sel | nand_sel | or_sel | nor_sel;
endmodule
module test_guia0703;
  reg a, b, sel_op, sel_grp;
  wire s;
  guia0703 uut (s, a, b, sel_op, sel_grp);
  initial begin
    $display("a b sel_op sel_grp | s");
    $display("------------------------");
    sel_grp = 0;
    sel_op = 0; a = 0; b = 0; #1 $display("%b %b   %b       %b     | %b", a, b, sel_op, sel_grp, s); // OR
    sel_op = 1; a = 0; b = 0; #1 $display("%b %b   %b       %b     | %b", a, b, sel_op, sel_grp, s); // NOR
    sel_op = 0; a = 1; b = 1; #1 $display("%b %b   %b       %b     | %b", a, b, sel_op, sel_grp, s);
    sel_op = 1; a = 1; b = 0; #1 $display("%b %b   %b       %b     | %b", a, b, sel_op, sel_grp, s);
    sel_grp = 1;
    sel_op = 0; a = 0; b = 0; #1 $display("%b %b   %b       %b     | %b", a, b, sel_op, sel_grp, s); // AND
    sel_op = 1; a = 0; b = 0; #1 $display("%b %b   %b       %b     | %b", a, b, sel_op, sel_grp, s); // NAND
    sel_op = 0; a = 1; b = 1; #1 $display("%b %b   %b       %b     | %b", a, b, sel_op, sel_grp, s);
    sel_op = 1; a = 1; b = 0; #1 $display("%b %b   %b       %b     | %b", a, b, sel_op, sel_grp, s);
  end
endmodule



module guia0704(output s, input a, b, input [1:0] sel);
  wire xor_out, xnor_out, or_out, nor_out;
  wire nsel0, nsel1;
  wire xor_sel, xnor_sel, or_sel, nor_sel;
  assign xor_out  = a ^ b;
  assign xnor_out = ~(a ^ b);
  assign or_out   = a | b;
  assign nor_out  = ~(a | b);
  assign nsel0 = ~sel[0];
  assign nsel1 = ~sel[1];
  assign xnor_sel = xnor_out & nsel1 & nsel0;  
  assign xor_sel  = xor_out  & nsel1 & sel[0]; 
  assign or_sel   = or_out   & sel[1] & nsel0; 
  assign nor_sel  = nor_out  & sel[1] & sel[0];
  assign s = xnor_sel | xor_sel | or_sel | nor_sel;
endmodule
module test_guia0704;
  reg a, b;
  reg [1:0] sel;
  wire s;
  guia0704 uut (s, a, b, sel);
  initial begin
    $display("a b sel | s");
    $display("-------------");
    a = 0; b = 0;
    sel = 2'b00; #1 $display("%b %b  %b%b  | %b", a, b, sel[1], sel[0], s); 
    sel = 2'b01; #1 $display("%b %b  %b%b  | %b", a, b, sel[1], sel[0], s); 
    sel = 2'b10; #1 $display("%b %b  %b%b  | %b", a, b, sel[1], sel[0], s); 
    sel = 2'b11; #1 $display("%b %b  %b%b  | %b", a, b, sel[1], sel[0], s); 
    a = 1; b = 0;
    sel = 2'b00; #1 $display("%b %b  %b%b  | %b", a, b, sel[1], sel[0], s);
    sel = 2'b01; #1 $display("%b %b  %b%b  | %b", a, b, sel[1], sel[0], s);
    sel = 2'b10; #1 $display("%b %b  %b%b  | %b", a, b, sel[1], sel[0], s);
    sel = 2'b11; #1 $display("%b %b  %b%b  | %b", a, b, sel[1], sel[0], s);
    a = 1; b = 1;
    sel = 2'b00; #1 $display("%b %b  %b%b  | %b", a, b, sel[1], sel[0], s);
    sel = 2'b01; #1 $display("%b %b  %b%b  | %b", a, b, sel[1], sel[0], s);
    sel = 2'b10; #1 $display("%b %b  %b%b  | %b", a, b, sel[1], sel[0], s);
    sel = 2'b11; #1 $display("%b %b  %b%b  | %b", a, b, sel[1], sel[0], s);
  end
endmodule



module guia0705(output s, input a, b, input [2:0] sel, input neg);
  wire not_out, and_out, nand_out, or_out, nor_out, xor_out, xnor_out;
  wire b_mod;
  wire [6:0] sel_mask;
  wire [6:0] ops_out;
  assign b_mod = neg ? ~b : b;
  assign not_out  = ~a;
  assign and_out  = a & b_mod;
  assign nand_out = ~(a & b_mod);
  assign or_out   = a | b_mod;
  assign nor_out  = ~(a | b_mod);
  assign xor_out  = a ^ b_mod;
  assign xnor_out = ~(a ^ b_mod);
  assign sel_mask[0] = ~sel[2] & ~sel[1] & ~sel[0];
  assign sel_mask[1] = ~sel[2] & ~sel[1] &  sel[0]; 
  assign sel_mask[2] = ~sel[2] &  sel[1] & ~sel[0]; 
  assign sel_mask[3] = ~sel[2] &  sel[1] &  sel[0]; 
  assign sel_mask[4] =  sel[2] & ~sel[1] & ~sel[0]; 
  assign sel_mask[5] =  sel[2] & ~sel[1] &  sel[0]; 
  assign sel_mask[6] =  sel[2] &  sel[1] & ~sel[0]; 
  assign ops_out[0] = not_out  & sel_mask[0];
  assign ops_out[1] = and_out  & sel_mask[1];
  assign ops_out[2] = nand_out & sel_mask[2];
  assign ops_out[3] = or_out   & sel_mask[3];
  assign ops_out[4] = nor_out  & sel_mask[4];
  assign ops_out[5] = xor_out  & sel_mask[5];
  assign ops_out[6] = xnor_out & sel_mask[6];
  assign s = ops_out[0] | ops_out[1] | ops_out[2] |
             ops_out[3] | ops_out[4] | ops_out[5] | ops_out[6];
endmodule
module test_guia0705;
  reg a, b, neg;
  reg [2:0] sel;
  wire s;
  guia0705 uut (s, a, b, sel, neg);
  initial begin
    $display("a b neg sel | s");
    $display("---------------");
    a = 1; b = 0; neg = 0;
    sel = 3'b000; #1 $display("%b %b  %b  %b%b%b | %b", a, b, neg, sel[2], sel[1], sel[0], s); 
    sel = 3'b001; #1 $display("%b %b  %b  %b%b%b | %b", a, b, neg, sel[2], sel[1], sel[0], s);
    sel = 3'b010; #1 $display("%b %b  %b  %b%b%b | %b", a, b, neg, sel[2], sel[1], sel[0], s); 
    sel = 3'b011; #1 $display("%b %b  %b  %b%b%b | %b", a, b, neg, sel[2], sel[1], sel[0], s); 
    sel = 3'b100; #1 $display("%b %b  %b  %b%b%b | %b", a, b, neg, sel[2], sel[1], sel[0], s); 
    sel = 3'b101; #1 $display("%b %b  %b  %b%b%b | %b", a, b, neg, sel[2], sel[1], sel[0], s); 
    sel = 3'b110; #1 $display("%b %b  %b  %b%b%b | %b", a, b, neg, sel[2], sel[1], sel[0], s); 
    a = 1; b = 1; neg = 1; sel = 3'b001; #1 $display("Com neg: %b %b  %b  %b%b%b | %b", a, b, neg, sel[2], sel[1], sel[0], s); 
  end
endmodule
