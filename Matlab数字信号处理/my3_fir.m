
% 设计数字滤波器
fir_min = designfilt('lowpassfir', ...
    'PassbandFrequency',0.2,'StopbandFrequency',0.35, ...
    'PassbandRipple',1,'StopbandAttenuation',15); % 10



fir_20 = designfilt('lowpassfir', ...
    'FilterOrder',20,'PassbandFrequency',0.2, ...
    'StopbandFrequency',0.35);


fir = fir_min;

disp('当前阶数为:');
disp(filtord(fir));
% 幅值和相位响应可视化
% freqz(fir.Coefficients)


[h,t] = fir.impz;
b = fir.Coefficients;
a = 1;

t = 0:63;

fvtool(fir)

%%
figure(11)
f = 0.1;
x = cos(2*pi*f*t);
y = filter(fir,x);

subplot(2,1,1);
hold on 
plot(t,x,'b')
plot(t,y,'r')
hold off

subplot(2,1,2);
hold on 
plot(abs(fft(x)),'b')
plot(abs(fft(y)),'r')
hold off
%%
figure(12)
f = 0.25;
x = cos(2*pi*f*t);
y = filter(fir,x);

subplot(2,1,1);
hold on 
plot(t,x,'b')
plot(t,y,'r')
hold off

subplot(2,1,2);
hold on 
plot(abs(fft(x)),'b')
plot(abs(fft(y)),'r')
hold off
%%
figure(13)
f = 0.543;
x = cos(2*pi*f*t);
y = filter(fir,x);

subplot(2,1,1);
hold on 
plot(t,x,'b')
plot(t,y,'r')
hold off

subplot(2,1,2);
hold on 
plot(abs(fft(x)),'b')
plot(abs(fft(y)),'r')
hold off