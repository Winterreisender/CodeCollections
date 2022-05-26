function [] = my_app() 
    recObj = audiorecorder(44100,16,1,-1);
    disp('Start speaking.')
    recordblocking(recObj,10);
    disp('End of Recording.');
    audioData = recObj.getaudiodata("double");


    %[n,Wn] = buttord(0.2,0.35,3,15);
    %[b,a] = butter(4,25,"low");

% ----------filter ------------

Fp=1500;
Fs=1200;
Ft=8000;
As=100;
Ap=1;
wp=2*pi*Fp/Ft;
ws=2*pi*Fs/Ft;
[n,wn]=ellipord(wp,ws,Ap,As,'s');
[b1,a1]=ellip(n,Ap,As,wn,'s');
[b,a]=bilinear(b1,a1,1);


% -----------------

    subplot(3,3,1)
    plot(audioData)

    subplot(3,3,2)
    plot(abs(fft(audioData)))

    subplot(3,3,3)
    plot(filter(b,a,audioData))

    pause(5)
    disp('Start playing.')
    sound(filter(b,a,audioData),recObj.SampleRate)
    disp('End of playing.')
    pause(5)
    pause(5)
    disp('Start playing.')
    sound(audioData,recObj.SampleRate)
    disp('End of playing.')

    subplot(3,3,4)
    plot(abs(fft(filter(b,a,audioData))))

    subplot(3,3,5)
    figure(2)
    freqz(b,a)
end

% fs=44100;
% t=0:1/fs:2;
% y=sin(2*pi*440*t);
% sound(y,fs)

