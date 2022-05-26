
/*
freqCount
输入 时钟clk 监测信号in
输出 BCD格式频率 out
*/


module freqCount(input clk, input in, output [31:0] out); 
	
	parameter MAX_CLK = 10 - 1; // 最大计数,应等于频率
	reg [31:0] clk_count;
	reg [7:0] freq_count1,freq_count10,freq_count100,freq_count1000;
	reg [31:0] out_lock; // 输出锁存
	reg rst_bcd; //同步清零bcd计数器
	wire inc1,inc10,inc100,inc1000;

	assign inc1 = in; // 个位+1信号
	assign inc10 = (freq_count1 >= 9); // 十位+1信号
	assign inc100 = (freq_count10 >= 9);
	assign inc1000 = (freq_count100 >= 9);

	initial begin 
		rst_bcd = 0;
		clk_count = 0;
	end
	
	// clk_count, out_lock
	always@(posedge clk) begin
		clk_count <= (clk_count==MAX_CLK)?0:(clk_count+1); //clk_count 状态转移

		if(clk_count == MAX_CLK) begin
			out_lock <= {freq_count1000,freq_count100,freq_count10,freq_count1}; //锁住
			rst_bcd <= 1; //清零
		end
		else
			rst_bcd <= 0;
		
	end

	// bcd计数器
	always @(posedge inc1) begin
		freq_count1 <= (freq_count1 >= 9 || rst_bcd == 1)? 0 : (freq_count1 + 1);
	end
	always @(posedge inc10) begin
		freq_count10 <= (freq_count10 >= 9 || rst_bcd == 1)? 0 : (freq_count10 + 1);
	end
	always @(posedge inc100) begin
		freq_count100 <= (freq_count100 >= 9 || rst_bcd == 1)? 0 : (freq_count100 + 1);
	end
	always @(posedge inc1000) begin
		freq_count1000 <= (freq_count1000 >= 9 || rst_bcd == 1)? 0 : (freq_count1000 + 1);
	end
	

	assign out = out_lock;

endmodule

//将一位bcd化为数码管显示
module bcd2tube(input [3:0] bcd, output [7:0] tube);
reg [7:0] rtube;
assign tube = rtube; 

always@* begin
	case (bcd) // case 只能用在always中,编译器优化掉
        0 : rtube = 8'h3f;
        1 : rtube = 8'h06;
        2 : rtube = 8'h5b;
        3 : rtube = 8'h4f;
        4 : rtube = 8'h66;
        5 : rtube = 8'h6d;
        6 : rtube = 8'h7d;
        7 : rtube = 8'h07;
        8 : rtube = 8'h7f;
        9 : rtube = 8'h6f;
        4'b1010 : rtube = 8'h77;
        4'b1011 : rtube = 8'h7c;
        4'b1100 : rtube = 8'h39;
        4'b1101 : rtube = 8'h5e;
        4'b1110 : rtube = 8'h79;
        4'b1111 : rtube = 8'h71;
		
      endcase
end
endmodule


module bcd2time_tubes(input clk, input [3:0] bcd1,input [3:0] bcd10,input [3:0] bcd100,input [3:0] bcd1000, output [15:0] out);
	reg [8:0] tube_select;
	reg [8:0] tube_content;
	reg [2:0] clk_count;
	
	wire [7:0] tube1;
	wire [7:0] tube10;
	wire [7:0] tube100;
	wire [7:0] tube1000;

	bcd2tube b1(bcd1, tube1);
	bcd2tube b10(bcd10, tube10);
	bcd2tube b100(bcd100, tube100);
	bcd2tube b1000(bcd1000, tube1000);

	assign out = {tube_select, tube_content};
	initial begin
		clk_count <= 0;
	end
	always @(posedge clk) begin
		clk_count <= clk_count+1;
		case (clk_count)
			0 : begin tube_select <= 8'b0000_0001; tube_content<=tube1; end
			1 : begin tube_select <= 8'b0000_0010; tube_content<=tube10; end
			2 : begin tube_select <= 8'b0000_0100; tube_content<=tube100; end
			3 : begin tube_select <= 8'b0000_1000; tube_content<=tube1000; end // 补上 4-7
			4 : begin tube_select <= 8'b0001_0000; tube_content<=0; end
			5 : begin tube_select <= 8'b0010_0000; tube_content<=0; end
			6 : begin tube_select <= 8'b0100_0000; tube_content<=0; end
			7 : begin tube_select <= 8'b1000_0000; tube_content<=0; end
		endcase
	end

endmodule

module main(input clk, input in, output [15:0] out, output [31:0] outBCD);
	
	freqCount freq(clk, in, outBCD);
	bcd2time_tubes tube(clk, outBCD[3:0], outBCD[7:4],outBCD[11:8],outBCD[15:12], out);
endmodule