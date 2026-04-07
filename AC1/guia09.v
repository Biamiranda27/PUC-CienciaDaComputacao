

module questao1 (
    input A, B, C, D,
    output F
);
    assign F = (~A & ~B & ~C & ~D) |  
               (~A & ~B &  C & ~D) |  
               (~A &  B & ~C &  D) | 
               (~A &  B &  C & ~D) |  
               (~A &  B &  C &  D)  | 
               ( A & ~B & ~C & ~D) | 
               ( A & ~B &  C & ~D) |  
               ( A &  B &  C &  D);   
endmodule

module questao2 (
    input A, B, C, D,
    output F
);
    assign F = (A | B | C | D) & 
               (A | B | C | ~D) & 
               (A | ~B | C | D) & 
               (A | ~B | C | ~D) & 
               (A | ~B | ~C | ~D) & 
               (~A | B | ~C | D) & 
               (~A | B | ~C | ~D) & 
               (~A | ~B | ~C | D);
endmodule

module questao3 (
    input A, B, C,
    output F
);
    assign F = (~A & ~C) | (~A & B) | (A & ~B & C);
endmodule

module questao4 (
    input A, B, C, D,
    output F
);
    assign F = (A | D) & (A | B | ~C) & (~B | ~C | D);
endmodule

