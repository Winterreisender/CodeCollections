function fir = makeFilter(Fpass,Fstop,Dpass,Dstop,Fs)
% All  Hz.
[N,Wn,BETA,TYPE] = kaiserord([Fpass Fstop]/(Fs/2), [1 0], [Dstop Dpass]);
b  = fir1(N, Wn, TYPE, kaiser(N+1, BETA), 'scale');
fir = dfilt.dffir(b);
end
