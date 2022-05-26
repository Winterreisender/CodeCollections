function [y] = my_conv(a,b)
        assert(length(a) == length(b),"数组长度都不相等卷个锤子");
        y = zeros(1,length(a));       % 1 x len(a)
        for n = 1:length(b)           %奇怪的数组起点问题,因为起点是1
            for i = 1:n               % 保证不越界+全覆盖就行
                y(n) = y(n) + a(i)*b(n-i+1); % 你matlab连+=都没有吗????
            end
        end
    end