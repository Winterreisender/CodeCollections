function [] = my_cos_fft
    F = 50;
    N = 32;
    T = 0.000625;

    x = cos(2*pi*F .* (0:T:(T*(N-1))) );

    subplot(2,1,1)
    stem(x)
    subplot(2,1,2)
    stem(abs(my_DFT(x)))
end