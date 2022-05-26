function [] = my_triangle()
    x_c = [1,2,3,4,4,3,2,1]; % 正三角
    x_d = [4,3,2,1,1,2,3,4]; % 反三角
    figure(1)
    subplot(2,1,1)
    stem(x_c)
    subplot(2,1,2)
    stem(abs(my_DFT(x_c)))

    figure(2)
    subplot(2,1,1)
    stem(x_d)
    subplot(2,1,2)
    stem(abs(my_DFT(x_d)))
end

