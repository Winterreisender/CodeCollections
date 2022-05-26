function [] = my_conv_test()
    function [y] = my_conv(a,b)
        assert(length(a) == length(b),"数组长度都不相等卷个锤子");
        y = zeros(1,length(a)); %1 x len(a)
        for n = 1:length(b) %什么奇怪的数组起点问题
            for i = 1:n % 保证不越界+全覆盖就行
                y(n) = y(n) + a(i)*b(n-i+1); % 你matlab连+=都没有吗????        因为起点是1
            end
        end
    end

    stem(my_conv([0.0181,0.0543,0.0543,0.0181],[1.000,-1.76,1.1829,-0.2781]));
end