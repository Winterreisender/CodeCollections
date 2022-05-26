
function [] = my_system_resp()
    a=[1,-1,0.9];
    b=[1];
    [h,t] = impz(b,a,-20:100);
    
    figure(1)
    stem(-20:100,h)
    figure(2)
    zplane(b,a)

    b = [0.0181,0.0543,0.0543,0.0181];
    a=[1.000,-1.76,1.1829,-0.2781];
    N = 128;
    [H,w]=freqz(b,a,N);
    figure(3)
    plot(0:(pi/N):(pi-(pi/N)),abs(H))
    figure(4)
    plot(0:(pi/N):(pi-(pi/N)),angle(H))
end