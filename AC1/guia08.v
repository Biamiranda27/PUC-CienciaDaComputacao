

module and_com_nand (
    input a,
    input b,
    output y
);
    wire nand_ab;

    nand(nand_ab, a, b);   
    nand(y, nand_ab, nand_ab); 
endmodule



module or_com_nand (
    input a,
    input b,
    output y
);
    wire nota, notb;

    nand(nota, a, a); 
    nand(notb, b, b);
    nand(y, nota, notb); 
endmodule



module and_com_nor (
    input a,
    input b,
    output y
);
    wire nota, notb, orab;

    nor(nota, a, a); 
    nor(notb, b, b); 
    nor(y, nota, notb); 
endmodule



module or_com_nor (
    input a,
    input b,
    output y
);
    wire nor_ab;

    nor(nor_ab, a, b); 
    nor(y, nor_ab, nor_ab);
endmodule



module xor_com_nand (
    input a,
    input b,
    output y
);
    wire nand1, nand2, nand3, nand4;

    nand(nand1, a, b);        
    nand(nand2, a, nand1);    
    nand(nand3, b, nand1);    
    nand(y, nand2, nand3);    
endmodule
