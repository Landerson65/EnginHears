function createPowerSpectrum(X, Fs, name)
%
L = length(X); % number of samples
f = (0:L-1)*(Fs/L);     % frequency range
powerX = abs(X(:,1)).^2/L;    % power of the left FFT

figure
plot(f, powerX)
title(strcat('Power Spectrum of Left Channel of', ' ', name))
xlabel('Frequency')
ylabel('Power')

powerX = abs(X(:,2)).^2/L;    % power of the left FFT

figure
plot(f, powerX)
title(strcat('Power Spectrum of Right Channel of', ' ', name))
xlabel('Frequency')
ylabel('Power')

X0_left = fftshift(X(:,1)); % shift X values
X0_right = fftshift(X(:,1)); % shift X values
powerX0_left = abs(X0_left).^2/L; % 0-centered power
powerX0_right = abs(X0_right).^2/L; % 0-centered power
f0 = (-L/2:L/2-1)*(Fs/L); % 0-centered frequency range

figure
plot(f0,powerX0_left)
title(strcat('Zero-Centered Power Spectrum of Left Channel of', ' ', name))
xlabel('Frequency')
ylabel('Power')

figure
plot(f0,powerX0_right)
title(strcat('Zero-Centered Power Spectrum of Right Channel of',' ', name))
xlabel('Frequency')
ylabel('Power')

end