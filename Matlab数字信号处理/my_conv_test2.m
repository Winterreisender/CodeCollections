function [] = my_conv_test2()
    x = [(0:14)*0 + 1,(15:29)*0];
    h = [0.8 .^ (0:14),(15:29)*0];


        function [y] = my_conv(a,b)
        assert(length(a) == length(b),"数组长度都不相等卷个锤子");
        y = zeros(1,length(a)); %1 x len(a)
        for n = 1:length(b) %什么奇怪的数组起点问题
            for i = 1:n % 保证不越界+全覆盖就行
                y(n) = y(n) + a(i)*b(n-i+1); % 你matlab连+=都没有吗????        因为起点是1
            end
        end
        end

    subplot(3,1,1)
    stem(x)
    subplot(3,1,2)
    stem(h)
    subplot(3,1,3)
    stem(my_conv(x,h))
end

