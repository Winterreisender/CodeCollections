%% 
% 

OkumuraHata = @(f_c, h_te, h_re, d, alpha, C_cell, C_terrain) (69.55 + 26.16.*log10(f_c) - 13.82.*log10(h_te) - alpha + (44.9-6.55.*log10(h_te)).*log10(d) + C_cell + C_terrain);

C_cell_city = @(f_c) 0;
C_cell_suburban = @(f_c) -2.*(log10(f_c./28)).^2 - 5.4;
C_cell_rural = @(f_c) -4.78.*(log10(f_c)).^2 + 18.33.*log10(f_c) - 40.98;

alpha_smallcity = @(f_c, h_re) (1.11.*log10(f_c) - 0.7).*h_re - (1.56.*log(f_c) - 0.8);
%%
h_te = 30;
h_re = 1.5;
d = linspace(1,10,10);
C_terrain = 0;
alpha = alpha_large(f_c,h_re);


% 绘图 f_c = 500;
clc; figure; hold on;
f_c = 500;
C_cell = C_cell_city(f_c);
L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);
plot(d,L,'r-','DisplayName',"市区 f_c="+num2str(f_c));

C_cell = C_cell_suburban(f_c);
L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);
plot(d,L,'g-','DisplayName',"郊区 f_c="+num2str(f_c));

C_cell = C_cell_rural(f_c);
L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);
plot(d,L,'b-','DisplayName',"乡村 f_c="+num2str(f_c));


% 绘图 f_c = 900;
f_c = 900;
C_cell = C_cell_city(f_c);
L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);
plot(d,L,'r--','DisplayName',"市区 f_c="+num2str(f_c));

C_cell = C_cell_suburban(f_c);
L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);
plot(d,L,'g--','DisplayName',"郊区 f_c="+num2str(f_c));

C_cell = C_cell_rural(f_c);
L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);
plot(d,L,'b--','DisplayName',"乡村 f_c="+num2str(f_c));


xlim([0, 12]);
grid on;
xlabel('距离 d (km)');
ylabel('损耗中值(dB)');
title("学号 姓名");
legend('show');
legend('Location','northwest');
hold off;
%%
function [alpha] = alpha_large(f_c, h_re)
    fc=f_c;
    if(fc < 300)
        alpha = 8.29*(log10(1.54*h_re))^2 - 1.1;
    else
        alpha = 3.2*(log10(11.75*h_re))^2 - 4.97;
    end
end