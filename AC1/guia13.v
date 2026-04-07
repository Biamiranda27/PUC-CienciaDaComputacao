

module contador_assincrono_decrescente_6b (
    input clk,
    input clear,
    output [5:0] Q
);
    wire [5:0] J, K;
    wire [5:0] Qn;

    assign J = 6'b111111;
    assign K = 6'b111111;

    jkff ff0 (Q[0], Qn[0], J[0], K[0], clk, 1'b0, clear);
    jkff ff1 (Q[1], Qn[1], J[1], K[1], Q[0], 1'b0, clear);
    jkff ff2 (Q[2], Qn[2], J[2], K[2], Q[1], 1'b0, clear);
    jkff ff3 (Q[3], Qn[3], J[3], K[3], Q[2], 1'b0, clear);
    jkff ff4 (Q[4], Qn[4], J[4], K[4], Q[3], 1'b0, clear);
    jkff ff5 (Q[5], Qn[5], J[5], K[5], Q[4], 1'b0, clear);
endmodule


module contador_assincrono_crescente_6b (
    input clk,
    input clear,
    output [5:0] Q
);
    wire [5:0] J, K;
    wire [5:0] Qn;

    assign J = 6'b111111;
    assign K = 6'b111111;

    jkff ff0 (Q[0], Qn[0], J[0], K[0], clk, 1'b0, clear);
    jkff ff1 (Q[1], Qn[1], J[1], K[1], Qn[0], 1'b0, clear);
    jkff ff2 (Q[2], Qn[2], J[2], K[2], Qn[1], 1'b0, clear);
    jkff ff3 (Q[3], Qn[3], J[3], K[3], Qn[2], 1'b0, clear);
    jkff ff4 (Q[4], Qn[4], J[4], K[4], Qn[3], 1'b0, clear);
    jkff ff5 (Q[5], Qn[5], J[5], K[5], Qn[4], 1'b0, clear);
endmodule


module contador_assincrono_decadico_crescente (
    input clk,
    input clear,
    output reg [4:0] Q
);
    always @(posedge clk or posedge clear) begin
        if (clear)
            Q <= 0;
        else if (Q == 9)
            Q <= 0;
        else
            Q <= Q + 1;
    end
endmodule


module contador_assincrono_decadico_decrescente (
    input clk,
    input clear,
    output reg [4:0] Q
);
    always @(posedge clk or posedge clear) begin
        if (clear)
            Q <= 9;
        else if (Q == 0)
            Q <= 9;
        else
            Q <= Q - 1;
    end
endmodule


module contador_sincrono_mod7 (
    input clk,
    input clear,
    output reg [2:0] Q
);
    always @(posedge clk or posedge clear) begin
        if (clear)
            Q <= 0;
        else if (Q == 6)
            Q <= 0;
        else
            Q <= Q + 1;
    end
endmodule
