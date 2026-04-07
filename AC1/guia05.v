


module guia0501 (output s, input a, b);
  wire nota, notb;
  assign nota = ~(a | a);  
  assign notb = ~(b | b);  
  assign s = ~(nota | b);  
endmodule
module test_guia0501;
  reg a, b;
  wire s;
  guia0501 uut (s, a, b);
  initial begin
    $display("a b | s");
    $display("-------");
    a = 0; b = 0; #1 $display("%b %b | %b", a, b, s);
    a = 0; b = 1; #1 $display("%b %b | %b", a, b, s);
    a = 1; b = 0; #1 $display("%b %b | %b", a, b, s);
    a = 1; b = 1; #1 $display("%b %b | %b", a, b, s);
  end
endmodule



module guia0502 (output s, input a, b);
  wire nota, notb;
  assign nota = ~(a & a);  
  assign notb = ~(b & b); 
  assign s = ~(nota & notb);
endmodule
module test_guia0502;
  reg a, b;
  wire s;
  guia0502 uut (s, a, b);
  initial begin
    $display("a b | s");
    $display("-------");
    a = 0; b = 0; #1 $display("%b %b | %b", a, b, s);
    a = 0; b = 1; #1 $display("%b %b | %b", a, b, s);
    a = 1; b = 0; #1 $display("%b %b | %b", a, b, s);
    a = 1; b = 1; #1 $display("%b %b | %b", a, b, s);
  end
endmodule



module guia0503 (output s, input a, b);
  wire notb;
  assign notb = ~(b | b);   
  assign s = ~(a | notb);    
endmodule
module test_guia0503;
  reg a, b;
  wire s;
  guia0503 uut (s, a, b);
  initial begin
    $display("a b | s");
    $display("-------");
    a = 0; b = 0; #1 $display("%b %b | %b", a, b, s);
    a = 0; b = 1; #1 $display("%b %b | %b", a, b, s);
    a = 1; b = 0; #1 $display("%b %b | %b", a, b, s);
    a = 1; b = 1; #1 $display("%b %b | %b", a, b, s);
  end
endmodule




module guia0504 (output s, input a, b);
  wire notb;
  assign notb = ~(b & b);     
  assign s = ~(a & notb);     
endmodule
module test_guia0504;
  reg a, b;
  wire s;
  guia0504 uut (s, a, b);
  initial begin
    $display("a b | s");
    $display("-------");
    a = 0; b = 0; #1 $display("%b %b | %b", a, b, s);
    a = 0; b = 1; #1 $display("%b %b | %b", a, b, s);
    a = 1; b = 0; #1 $display("%b %b | %b", a, b, s);
    a = 1; b = 1; #1 $display("%b %b | %b", a, b, s);
  end
endmodule




module guia0505 (output s, input a, b);
  wire nota, notb;
  wire a_and_notb, not_a_and_b;
  assign nota = ~(a | a);           
  assign notb = ~(b | b);          
  assign a_and_notb   = ~(nota | b);   
  assign not_a_and_b  = ~(a | notb);   
  assign s = ~(a_and_notb | not_a_and_b); 
endmodule
module test_guia0505;
  reg a, b;
  wire s;
  guia0505 uut (s, a, b);
  initial begin
    $display("a b | s");
    $display("-------");
    a = 0; b = 0; #1 $display("%b %b | %b", a, b, s);
    a = 0; b = 1; #1 $display("%b %b | %b", a, b, s);
    a = 1; b = 0; #1 $display("%b %b | %b", a, b, s);
    a = 1; b = 1; #1 $display("%b %b | %b", a, b, s);
  end
endmodule




module guia0506 (output s, input a, b);
  wire t1, t2, t3, t4, t5;
  assign t1 = ~(a & b);      
  assign t2 = ~(a & a);       
  assign t3 = ~(b & b);      
  assign t4 = ~(t1 & t1);     
  assign t5 = ~(t2 & t3);     
  assign s = ~(t4 & t5);      
endmodule
module test_guia0506;
  reg a, b;
  wire s;
  guia0506 uut (s, a, b);
  initial begin
    $display("a b | s");
    $display("-------");
    a = 0; b = 0; #1 $display("%b %b | %b", a, b, s);
    a = 0; b = 1; #1 $display("%b %b | %b", a, b, s);
    a = 1; b = 0; #1 $display("%b %b | %b", a, b, s);
    a = 1; b = 1; #1 $display("%b %b | %b", a, b, s);
  end
endmodule
