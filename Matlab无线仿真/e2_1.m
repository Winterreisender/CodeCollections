m1=[1 0 0 0 0 1 0 0 1 0 1 1 0 0 1 1 1 1 1 0 0 0 1 1 0 1 1 1 0 1 0];
m2=[1 1 1 1 1 0 1 1 1 0 0 0 1 0 1 0 1 1 0 1 0 0 0 0 1 1 0 0 1 0 0];
%%
% （1）仿真出gold 序列，并选2个序列画出波形图，自相关和互相关图形（画五个周期）。
R11 = circorr(m1,m1);
R22 = circorr(m2,m2);
R12 = circorr(m1,m2);

gold1 = xor(m1,circshift(m2,0));
gold2 = xor(m1,circshift(m2,3));

Rg11 = circorr(gold1,gold1);
Rg22 = circorr(gold2,gold2);
Rg12 = circorr(gold1,gold2);

% 绘图

figure

subplot(5,1,1);
stem(m1)
title('m1时域波形');

subplot(5,1,2);
stem(m2)
title('m2时域波形');

subplot(5,1,3);
plot(R11);
ylim([-20 40]); % ylim([-50 50]); ?
title('m1自相关波形');

subplot(5,1,4);
plot(R22);
ylim([-20 40]);
title('m2自相关波形');

subplot(5,1,5);
plot(R12);
ylim([-50 50]);
title('m1和m2互相关波形');



figure

% stem(gold1)
% title("Gold1")

% stem(gold2)
% title("Gold2")

subplot(3,1,1);
plot(Rg11);
ylim([-50 50]);
title('Gold1自相关序列');

subplot(3,1,2);
plot(Rg22);
ylim([-50 50]);
title('Gold2自相关序列');

subplot(3,1,3);
plot(Rg12);
ylim([-50 50]);
title('Gold1,2互相关序列');
%%
N=400000;
fg11=linspace(-1,1,N);
Pg11 = fft(Rg11,N);

figure
plot(fg11,abs(Pg11)./max(abs(Pg11)));
title('Gold功率谱');
xlabel("频率")
ylabel("幅值")
xlim([0.5 0.6]);
%% BPSK波形部分

L = 10; % 原信号比特数
ExpandNum = 10;

Fs = 50; % 采样频率
Ts = 1 / Fs; % 采样周期

N = L * ExpandNum; % 数字时长
n = 1:N; % 数字时间

T = Ts * N; % 模拟时长
MTI = Ts / 100 %最小时间间隔
t = 0:MTI:(T-MTI); % 模拟时间

Ns = length(t); % 采样点数
f = ((0:Ns-1)/Ns)*Fs; % 模拟频率
%%
fc = 200;

% 原信号
src = [1 0 1 1 1 1 0 1 1 1]; % randi([0 1],1,L);
srcOrigin = src;


src_exp = expandN(src,ExpandNum);

% stem(n,src)
% title("原信号")
% xlabel("时间 n")
% ylabel("f(n)")

% bpsk
bpskOrigin = [];

for i=n
    t2 = 0:MTI:(Ts-MTI);
    bpskOrigin = [bpskOrigin sin(2*pi*fc*t2 + pi*src_exp(i))];
end

P_bpskOrigin = fft(bpskOrigin);

%%
% 扩频
rnd_seq = goldrnd(N); % 0,1-> -1,1
srcExp = src_exp .* rnd_seq; % 乘以高频PN序列

% bpsk
bpsk = [];
for i=n
    t2 = 0:MTI:(Ts-MTI);
    bpsk = [bpsk sin(2*pi*fc*t2 + 0.5*pi*srcExp(i))];
end
P_bpsk = fft(bpsk);
%%
figure

subplot(3,1,1);
stem(src)
title("原信号")
xlabel("时间 n")
ylabel("f(n)")

subplot(3,1,2);
plot(t,bpskOrigin);
title("原BPSK信号")
xlabel("时间 t")
ylabel("f(t)")
xlim([0 0.3]);

subplot(3,1,3);
plot(t,bpsk)
xlim([0 0.3]);
title("扩频BPSK信号")
xlabel("时间 t")
ylabel("f(t)")


figure
subplot(2,1,1);
plot(f,abs(P_bpskOrigin));
title("原BPSK信号频谱")
xlabel("频率 (Hz)")
ylabel("幅度")
xlim([0 8]);

subplot(2,1,2);
plot(f,abs(P_bpsk));
xlim([0 8]);
title("扩频BPSK信号频谱")
xlabel("频率 (Hz)")
ylabel("幅值")

%%

%%
function [r] = mseq(g)
    n = length(g);
    N = 2^n - 1;

    reg = [zeros(1,n-1) 1];
    r(1) = reg(1);

    for i = 2:N
        newReg(1) = mod(sum(g.*reg),2);
        for j = 2:n
            newReg(j) = reg(j-1);
        end
        reg = newReg;
        r(i) = reg(n);
    end
end

% 多项式生成gold序列
function [r] = goldseq(g1,g2)
    m1 = mseq(g1);
    m2 = mseq(g2);
    r = mod(m1+m2,2);
end

% 任意长Gold序列
function [r] = goldrnd(L) % [+1 -1]
rnd = goldseq([0 1 0 0 1 0 1 0 0 0 1 0 0 1 0 0 1 1 0 1],[1 0 1 0 0 1 1 0 1 1 0 1 0 0 1 1 0 1 0 1]);
r = 1-2.*rnd(1525+1:1525+L); % 自带PN
end

function [output] =  circorr(m,n)
L=length(m);
m1=m;
 for i=1:L*5 % 画五个周期
   output(i)=sum((1-2*m1).*(1-2*n));
   m1=circshift(m1',1)';
 end
end

function [r] = expandN(x,N)
    L = length(x);
    r = [];

    for i=x
        r = [r ones(1,N).*i];
    end
end