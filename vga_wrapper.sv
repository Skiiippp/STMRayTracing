`timescale 1ns / 1ps


module vga_wrapper(
    
    input CLK_100MHz,
    input [7:0] DES_DATA_IN,
    input DES_WRITE_EN,
    input DES_RST,
    input DES_WRITE_TO_VGA,
    
    output logic [7:0] VGA_RGB,
    output VGA_HS,
    output VGA_VS,
    
    output [1:0] INPUT_COUNT
    );
    
    logic CLK_50MHz = 0;
    logic [12:0] address;
    logic [7:0] color;
    logic vga_write;
    
    logic [7:0] rd;
    logic [2:0] r_out;
    logic [2:0] g_out;
    logic [1:0] b_out;
    
    // Generate 50MHZ clock for vga driver
    always_ff @(posedge CLK_100MHz) begin
        CLK_50MHz <= ~CLK_50MHz;
    end
    
    // Wire up output colors
    always_comb begin
        VGA_RGB[7:5] = r_out;
        VGA_RGB[4:2] = g_out;
        VGA_RGB[1:0] = b_out;
    end
    
    deserializer des(DES_DATA_IN, DES_WRITE_EN, DES_RST, DES_WRITE_TO_VGA, color, address, vga_write, INPUT_COUNT);
    
    vga_fb_driver_80x60 vga(CLK_50MHz, address, color, vga_write, rd, r_out, g_out, b_out, VGA_HS, VGA_VS);
    
    
endmodule
