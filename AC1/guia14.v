

module shift_left_load1bit (
    input clk, input clear,
    input load,
    output [4:0] q
);
    wire [4:0] qn;

    dff f0(q[0], qn[0], q[1], clk, load, clear);
    dff f1(q[1], qn[1], q[2], clk, 1'b0, clear);
    dff f2(q[2], qn[2], q[3], clk, 1'b0, clear);
    dff f3(q[3], qn[3], q[4], clk, 1'b0, clear);
    dff f4(q[4], qn[4], 1'b0, clk, 1'b0, clear);
endmodule


module shift_left_load_all (
    input clk, input clear,
    input load,
    output [4:0] q
);
    wire [4:0] qn;
    wire d4 = 1'b0; // Entrada final nula

    dff f0(q[0], qn[0], q[1], clk, load, clear);
    dff f1(q[1], qn[1], q[2], clk, load, clear);
    dff f2(q[2], qn[2], q[3], clk, load, clear);
    dff f3(q[3], qn[3], q[4], clk, load, clear);
    dff f4(q[4], qn[4], d4,    clk, load, clear);
endmodule


module ring_right (
    input clk, input clear,
    input load,
    output [4:0] q
);
    wire [4:0] qn;

    dff f0(q[0], qn[0], q[4], clk, load, clear);
    dff f1(q[1], qn[1], q[0], clk, 1'b0, clear);
    dff f2(q[2], qn[2], q[1], clk, 1'b0, clear);
    dff f3(q[3], qn[3], q[2], clk, 1'b0, clear);
    dff f4(q[4], qn[4], q[3], clk, 1'b0, clear);
endmodule


module twisted_ring_left (
    input clk, input clear,
    input load,
    output [4:0] q
);
    wire [4:0] qn;

    dff f0(q[0], qn[0], ~q[4], clk, load, clear);
    dff f1(q[1], qn[1], q[0], clk, 1'b0, clear);
    dff f2(q[2], qn[2], q[1], clk, 1'b0, clear);
    dff f3(q[3], qn[3], q[2], clk, 1'b0, clear);
    dff f4(q[4], qn[4], q[3], clk, 1'b0, clear);
endmodule


module paralelo_serie (
    input clk, input clear, input load,
    input [4:0] data_in,
    output bit_out
);
    reg [4:0] shift_reg;

    always @(posedge clk or posedge clear) begin
        if (clear)
            shift_reg <= 5'b0;
        else if (load)
            shift_reg <= data_in;
        else
            shift_reg <= shift_reg << 1;
    end

    assign bit_out = shift_reg[4]; // MSB sai primeiro
endmodule
