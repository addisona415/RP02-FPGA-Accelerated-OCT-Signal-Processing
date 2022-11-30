Fs = 1000;          % Sampling Freq
T = 1/Fs;           % Sampling Period
L = 1500;           % Length of Signal
t = (0:L-1) * T;    % Time Vector
x = linspace(0,3);  % Plot layouts
tiledlayout(2,1);   % Plot config

signal = 0.7*sin(2*pi*50*t) + sin(2*pi*120*t);   %Signal containing 50Hz and 120Hz sinusoid

noise = signal + 2*randn(size(t));                   %Add noise to the signal

% Plot of noisy signal
plot1 = nexttile;
plot(plot1, 1000*t(1:50),noise(1:50))
title("Signal Corrupted with Zero-Mean Random Noise")
xlabel("t (milliseconds)")
ylabel("X(t)")

fourierTransform = fft(noise);

twoSided = abs(fourierTransform/L);
oneSided = twoSided(1:L/2+1);
oneSided(2:end-1) = 2*oneSided(2:end-1);

% Plot of Single Sided spectrum
plot2 = nexttile;
f = Fs*(0:(L/2))/L;
plot(plot2,f,oneSided) 
title("Single-Sided Amplitude Spectrum of X(t)")
xlabel("f (Hz)")
ylabel("|oneSided(f)|")