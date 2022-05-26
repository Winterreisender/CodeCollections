function [] = my3_iir()
    % 设计一个巴特沃思数字低通滤波器
    figure(1)
    [n,Wn] = buttord(0.2,0.35,3,15);
    [b,a] = butter(n,Wn);
    % freqz(butter(n,Wn)) % 幅度特性和相位特性
    fvtool(b,a)
    
    
    N = 128;
    [H,w]=freqz(b,a,N); % H幅频,w相频
    [h,t] = impz(b,a);
    
    figure(2)
    f = 0.1;
    x = cos(2*pi*f*t);
    
    subplot(3,2,1)
    stem(abs(fft(x)))

    subplot(3,2,2)
    stem(abs(fft(conv(x,h))))
    ylim([-5 15])
    
    %---------------
    subplot(3,2,3)
    f = 0.3;
    x = cos(2*pi*f*t);
    stem(abs(fft(x)))

    subplot(3,2,4)
    stem(abs(fft(conv(x,h))))
    ylim([-5 15])

    %---------------
    subplot(3,2,5)
    f = 0.45;
    x = cos(2*pi*f*t);
    stem(abs(fft(x)))

    subplot(3,2,6)
    stem(abs(fft(conv(x,h))))
    ylim([-5 15])

end

