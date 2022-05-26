% 离散时间系统的单位脉冲响应
% 什么垃圾语法!正常人能设计出一个函数一个文件这种**规则?

function [] = my_resp_calc(x,y_0) % 连默认参数都没有吗?WTF
    % 方程是 y(t) - y(t-1) = x(t) => y(t) = y(t-1) + x(t)
    x = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1];
    y_0 = 0;
    
    function my_return = calc_y(t) % 什么奇怪的函数定义方式
        if t==0
            my_return = y_0; % 递归中止
        else
            my_return = calc_y(t-1) + x(t); % 递推式  y(t) = y(t-1) + x(t)
        end
    end

    % 生成数组
    y = [];
    for i = 1:20
        y(i) = calc_y(i);
    end
    
    stem(y)
end



