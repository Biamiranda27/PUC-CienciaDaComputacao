


module imul (
    input [7:0] A,
    input [7:0] B,
    output reg [15:0] PROD
);
    integer i;
    always @(*) begin
        PROD = 0;
        for (i = 0; i < B; i = i + 1) begin
            PROD = PROD + A;
        end
    end
endmodule


module idiv (
    input [7:0] A,
    input [7:0] B,
    output reg [7:0] QUOT
);
    integer count;
    reg [15:0] temp;

    always @(*) begin
        temp = A;
        QUOT = 0;
        while (temp >= B) begin
            temp = temp - B;
            QUOT = QUOT + 1;
        end
    end
endmodule


module imod (
    input [7:0] A,
    input [7:0] B,
    output reg [7:0] REM
);
    reg [15:0] temp;

    always @(*) begin
        temp = A;
        while (temp >= B) begin
            temp = temp - B;
        end
        REM = temp;
    end
endmodule


module max_array (
    input [7:0] arr [0:7], // vetor de 8 elementos
    output reg [7:0] max
);
    integer i;
    always @(*) begin
        max = arr[0];
        for (i = 1; i < 8; i = i + 1) begin
            if (arr[i] > max)
                max = arr[i];
        end
    end
endmodule


module bcd_to_hex (
    input [7:0] BCD,
    output reg [7:0] HEX
);
    reg [3:0] high, low;
    always @(*) begin
        high = BCD[7:4]; // parte alta do BCD
        low  = BCD[3:0]; // parte baixa
        HEX = (high * 4'd10) + low;
    end
endmodule

