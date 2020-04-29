% EnginHears Version 2.0
%{ 
    I'm calling this version 2.0 even though there was no official version
    1.0. I'm treating the algorithm that changed the frequency spectru  in
    a specific band as version 1.0. Version 2.0 uses the ski-slope filter
    that we found online in hearingAidF.m. If a nother significant change
    to the algorithm occurs, we'll call that Version 3.0 and so on. Version
    2.0 also includes other functions: createPowerSpectrum, viewAudio, and
    controlVolume.
%}
%% x = original audio signal
%% Fs = sample rate in Hertz
%% L = number of samples
%% X = the fft of x
%% transitionV = a vector of 4 frequencies used for the calcualtion of the ski-slope filter in freqshape
%% gain = input gainused for the max value in freqshape
%% Xleft_editted = is a variable used to make the application of the filter easier
%% Xright_editted = is a variable used to make the application of the filter easier
%% y = the ifft of the X after the filter is applied

clear; close all;
%% Read Audio File
[x, Fs] = audioread('Conversation-Moderate.mp3');

%% Take the FFT of the input signal x
X = fft(x);

%% From MATLAB: create Power Spectrum
createPowerSpectrum(X, Fs, ' X')

%% Calculate and Apply Ski-Slope Filter
transitionV = [1000, 1500, 2550, 5000];
g = 5;
[~, gain] = freqshape(x, g, transitionV, Fs); % freqshape claims to adjust 
% the signal for you, but the output is not changed noticeably, so I have 
%elected to apply the filter manually

Xleft_editted = X(:,1).*gain;
Xright_editted = X(:,2).*gain;
X_editted = cat(2,Xleft_editted,Xright_editted);

%% take the ifft of the editted X signal
y = ifft(X_editted,'symmetric');

%% create audio players for the signals
%play player for origional sample and player2 for new sample
player = audioplayer( controlVolume(x,1), Fs);
player2 = audioplayer(controlVolume(y, 1), Fs);
play(player2)
%%
viewAudio(x,Fs,' Conversation-Severe')
viewAudio(y,Fs,' Editted Conversation-Severe')