%% 
% 

OkumuraHata = @(f_c, h_te, h_re, d, alpha, C_cell, C_terrain) (69.55 + 26.16.*log10(f_c) - 13.82.*log10(h_te) - alpha + (44.9-6.55.*log10(h_te)).*log10(d) + C_cell + C_terrain);

C_cell_city = @(f_c) 0;
C_cell_suburban = @(f_c) -2.*(log10(f_c./28)).^2 - 5.4;
C_cell_rural = @(f_c) -4.78.*(log10(f_c)).^2 + 18.33.*log10(f_c) - 40.98;

alpha_smallcity = @(f_c, h_re) (1.11.*log10(f_c) - 0.7).*h_re - (1.56.*log(f_c) - 0.8);
%%
f_c = linspace(300,1500,12);
h_te = 30;
h_re = 1.5;
d = 5;
C_terrain = 0;
x = 1111.1; % 打点
f = x;

% 绘图 d=5
clc; figure; hold on;
alpha = alpha_large(f_c,h_re);
C_cell = C_cell_city(f_c);
L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);
plot(f_c,L,'b--o','DisplayName',"市区 d=" + num2str(d) + "km");
y = OkumuraHata(1412.7, h_te, h_re, d, alpha_large(x,h_re), C_cell_city(x), C_terrain);
text(x,y,['O (' , num2str(x),',',num2str(y), ')']);

alpha = alpha_large(f_c,h_re);
C_cell = C_cell_suburban(f_c);
L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);
plot(f_c,L,'b--s','DisplayName',"郊区 d=" + num2str(d) + "km");
y = OkumuraHata(1412.7, h_te, h_re, d, alpha_large(x,h_re), C_cell_suburban(x), C_terrain);
text(x,y,['O (' , num2str(x),',',num2str(y), ')']);

alpha = alpha_large(f_c,h_re);
C_cell = C_cell_rural(f_c);
L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);
plot(f_c,L,'b--*','DisplayName',"乡村 d=" + num2str(d) + "km");
y = OkumuraHata(1412.7, h_te, h_re, d, alpha_large(f,h_re), C_cell_rural(f), C_terrain);
text(x,y,['O (' , num2str(x),',',num2str(y), ')']);


% d = 2
d = 2;

alpha = alpha_large(f_c,h_re);
C_cell = C_cell_city(f_c);
L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);
plot(f_c,L,'b-o','DisplayName',"市区 d=" + num2str(d) + "km");
y = OkumuraHata(1412.7, h_te, h_re, d, alpha_large(f,h_re), C_cell_city(f), C_terrain);
text(x,y,['O (' , num2str(x),',',num2str(y), ')']);

alpha = alpha_large(f_c,h_re);
C_cell = C_cell_suburban(f_c);
L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);
plot(f_c,L,'b-s','DisplayName',"郊区 d=" + num2str(d) + "km");
y = OkumuraHata(1412.7, h_te, h_re, d, alpha_large(f,h_re), C_cell_suburban(f), C_terrain);
text(x,y,['O (' , num2str(x),',',num2str(y), ')']);

alpha = alpha_large(f_c,h_re);
C_cell = C_cell_rural(f_c);
L = OkumuraHata(f_c, h_te, h_re, d, alpha, C_cell, C_terrain);
plot(f_c,L,'b-*','DisplayName',"乡村 d=" + num2str(d) + "km");
y = OkumuraHata(1412.7, h_te, h_re, d, alpha_large(f,h_re), C_cell_rural(f), C_terrain);
text(x,y,['O (' , num2str(x),',',num2str(y), ')']);


xlim([0, 1500]);
ylim([90 170]);
grid on;
xlabel('频率(MHz)');
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