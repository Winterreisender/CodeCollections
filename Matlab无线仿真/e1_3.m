%% 
% 

OkumuraHata = @(f_c, h_te, h_re, d, alpha, C_cell, C_terrain) (69.55 + 26.16.*log10(f_c) - 13.82.*log10(h_te) - alpha + (44.9-6.55.*log10(h_te)).*log10(d) + C_cell + C_terrain);

C_cell_city = @(f_c) 0;
C_cell_suburban = @(f_c) -2.*(log10(f_c./28)).^2 - 5.4;
C_cell_rural = @(f_c) -4.78.*(log10(f_c)).^2 + 18.33.*log10(f_c) - 40.98;

alpha_smallcity = @(f_c, h_re) (1.11.*log10(f_c) - 0.7).*h_re - (1.56.*log(f_c) - 0.8);
%%
h_re = 1.5;
d = 3;
C_terrain = 0;
f_c = 600;
C_cell = C_cell_city(f_c);
alpha = alpha_large(f_c,h_re);



h_te = linspace(20,80,10)

L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);

clc; figure; hold on;

plot(h_te, L,'r-o',DisplayName="预测天线高度");

grid on;
xlabel('天线高度  h_{te} (m)');
ylabel('损耗中值(dB)');
title("学号 姓名");
legend('show');
legend('Location','northwest');
hold off;
%%
function [alpha] = alpha_large(f_c, h_re)
    alpha = [];
    for fc=f_c
    if(fc < 300)
        alpha = [alpha, 8.29*(log10(1.54*h_re))^2 - 1.1];
    else
        alpha = [alpha, 3.2*(log10(11.75*h_re))^2 - 4.97];
    end
    end
end