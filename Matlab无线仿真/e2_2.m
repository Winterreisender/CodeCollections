A2dB = @(A)  10*log10(A);
dB2A = @(dB) 10.^(dB/10);

EbN0= 0:0.5:10;                 % dB
%%
% 误码率

L = 40000;
error_rate_unexp = [];

for i = EbN0
    % 原信号
    origin=randi([0,1],1,L);
    
    % 模拟BPSK
    bpsk=1-2.*origin;

    % 噪声
    Eb = norm(bpsk)^2/L; % 信号功率/bit
    N0 = Eb / dB2A(i);
    sigma = sqrt(N0 / 2); % N0 单边
    noise = sigma*(randn(1,L));
    
    % "BPSK"信号通过信道、解码
    recv = bpsk + noise; 
    recv = round((recv < 0)); % -1 +1 -> 1 0

    [~,er] = symerr(origin,recv); %误码率 [数量,比率] 
    error_rate_unexp = [error_rate_unexp er];
end


%%
original_length = 8000;    
expand_num = 16;
total_length = original_length * expand_num; %总长

gold = goldrnd(total_length);

error_rate_sum = EbN0 .* 0;
LOOP_TIMES = 10;
for j = 1:LOOP_TIMES
error_rate = [];
for i = EbN0
    % 原信号
    origin=randi([0,1],1,original_length);
    origin=1-2.*origin;

    % 扩频+"BPSK"信号 已经提前生成优化
    % gold = randi([-1 +1],1,total_length);
    exp_freq = expandN(origin,expand_num) .* gold;

    % 噪声
    Eb = norm(origin).^2/original_length;
    N0 = Eb / dB2A(i);
    sigma = sqrt(N0/2); % 单边
    noise = sigma.*(randn(1,total_length));
    

    % "BPSK"信号通过
    recv = exp_freq + noise; 
    recv = collapseN(gold .* recv,expand_num); % 判决

    [~,er] = symerr(origin,recv);%误码率 [数量,比率] 
    error_rate = [error_rate er];
end
error_rate_sum = error_rate_sum + error_rate; 
end

error_rate_exp = error_rate_sum ./ LOOP_TIMES


%%
clf;
figure;

hold on;
error_theory = qfunc(sqrt(2.*dB2A(EbN0))); % 理论误码率

plot(EbN0,A2dB(error_rate_unexp),'-b*','DisplayName','未扩频误码率');
plot(EbN0,A2dB(error_theory),'-rx','DisplayName','理论误码率曲线');

plot(EbN0,A2dB(error_rate_exp),'black-o','DisplayName',"扩频误码率");

title('BPSK误码率');
xlabel('Eb/N0 (dB)');
ylabel('误码率');
yticks((-60):10:(-10))
yticklabels(dB2A((-60):10:(-10)))
legend('show');
hold off;
%% 
% 
% 
% 

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
rnd = goldseq([0     1     0     0     1     0     1     0     0     0     1     0     0     1     0     0     1     1     0     1],[1     0     1     0     0     1     1     0     1     1     0     1     0     0     1     1     0     1     0     1]);
r = 1-2.*rnd(1:L);
end

function [output] =  circorr(m,n)
L=length(m);
m1=m;
 for i=1:L*5 % 画五个周期
   output(i)=sum((1-2*m1).*(1-2*n));
   m1=circshift(m1',1)';
 end
end

function [r] = expandN(x,N) % N: 扩频倍数 
    L = length(x);
    r = [];

    for i=x
        r = [r ones(1,N).*i];
    end
end

function [r] = collapseN(X,N) % N: 扩频倍数 
    M = round(length(X) / N); % M即未扩频信号长 = 扩频信号长度 / 扩频倍数
    X = reshape(X,N,M)' ; % 变为矩阵便于运算
    coll = round((X*ones(N,1))./N); % 每行求和 / N 得到每行均值
    r = reshape(coll,1,M);
end

% function [r] = collapse(X)
%     N = round(sqrt(length(X)));
%     X = reshape(X,N,N)' ;
%     coll = round((X*ones(N,1))./N);
% 
%     r = reshape(coll,1,N);
% end
% 
% function [r] = expand(x)
%     L = length(x);
%     r = reshape(ones(L,1)*x,1,L^2); % 扩长度 [1,2,3] -> [1,1,1,2,2,2,3,3,3]
% end