%coding: GBK

function AIO 
clc;

x=2005:1:2035;
t = x - 2004
S = 120 

% Logistic
AL = 0.341
BL = 2.861
yL  = S ./ (1 + BL * exp(-AL * t))

% Gompertz
BG = -0.275
AG = 1.554
yG  = S * exp(-AG*exp(BG*t)) 



% 观测
y_r = [35.4, 45.1, 60, 70.8, 79.0, 91.4, 101.8, 103.73, 104.5, 105.18] 

hold on

% 画图
plot(x,yL, '--')
plot(x,yG, '-')
plot(2005:1:2014, y_r, 'rx')

% 美化
xlabel('时间(t)','fontsize',8);
ylabel('普及率','fontsize',8);
legend('Logistic','Gompertz','观测')
grid on
title('Gompertz-Logistic-观测')
text(2030,yG(2030-2004) + 5,'S=120')

% ------------- 200

S = 200 

% Logistic
AL = 0.341
BL = 2.861
yL  = S ./ (1 + BL * exp(-AL * t))

% Gompertz
BG = -0.275
AG = 1.554
yG  = S * exp(-AG*exp(BG*t)) 
plot(x,yL, '--')
plot(x,yG, '-')
plot(2005:1:2014, y_r, 'rx')
text(2030,yG(2030-2004) - 5,'S=200')
% ------------- 240 

hold off
end

