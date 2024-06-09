`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/05/2024 05:27:16 PM
// Design Name: 
// Module Name: deserializer
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
//              1st byte - x coord, 2nd byte - y coord, 3rd byte - color
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////



module deserializer(
    input logic [7:0] DATA_IN,
    input WRITE_EN,
    input RST,
    input WRITE_TO_VGA,
    
    output logic [7:0] COLOR,
    output logic [12:0] ADDRESS,
    output logic VGA_WRITE,
    output logic [1:0] INPUT_COUNT
    );
    
    
    logic [7:0] buffer [3]; // Buffer for storing input values  
    logic [1:0] input_count;    // Number of bytes we've read
    
    always_ff @(posedge WRITE_EN or posedge RST) begin   
         
        if(RST) begin 
            buffer[2] <= 0;
            buffer[1] <= 0;
            buffer[0] <= 0;
            input_count <= 0;
        end else begin
        
        buffer[2] <= buffer[1];
        buffer[1] <= buffer[0];
        buffer[0] <= DATA_IN;
        
            
            if(input_count < 3) begin
                input_count <= input_count + 1;
            end else begin
                input_count <= 1;
            end
        
        end
        
    end
    
    always_comb begin
        VGA_WRITE = WRITE_TO_VGA;
        
        COLOR = buffer[0];
        ADDRESS = {buffer[1][5:0], buffer[2][6:0]};
        INPUT_COUNT = input_count;
    end
    
    
    
endmodule
