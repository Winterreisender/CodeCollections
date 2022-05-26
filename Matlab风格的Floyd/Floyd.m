function [W,R] = Floyd(w)
    % 初始化
	n=length(w);
    r = reshape(0*(1:n),n,1) + reshape(1:n,1,n); % 等于列
    r(eye(n)==1 && w==inf) = 0; %对角归零,无穷归零

    % 更新矩阵
	for relay=1:n
        newW = w(relay,:)+w(:,relay); % 强制用relay中继后的w
        r(newW < w) = relay; % 更新用realy后w较小的部分的r
        w = min(w,newW); % w取较小值
	end
    
    %返回值
    W = w;
    R = r;
end


% w0=[0 , 2, inf, 6;2 , 0, 3, 2;inf , 3, 0, 2;6 , 2, 2, 0]
% Floyd(w0)
% [W,R] = Floyd(w0)



