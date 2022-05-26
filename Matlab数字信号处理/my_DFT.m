function [X] = my_DFT(x) % 和fft相比,误差小于1e-10
    N = length(x);
    
    X = (1:N) * 0;
    for k=1:N
        for n=1:N
            % n-1,k-1: matlab数组从1开始留下的大坑
            X(k) = X(k) + x(n) * exp(-1i * (2*pi / N) * (n-1) * (k-1) );
        end
    end

    % X = abs(X);
    % figure(1)
    % stem(x)
    % figure(2)
    % stem(X)
end

