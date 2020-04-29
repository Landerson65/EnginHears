%% Real Time Demo in MATLAB

%% Screen Display Settings

%Measure Screen Size of the device
%Calculate position values of figure windows
scrsz = get(0,'ScreenSize');
P1 = [50 300 scrsz(3)/2 scrsz(4)/2];
P4 = [620 80 scrsz(3)/2 scrsz(4)/2];

%% Initialise Microphone Parameters
SamplesPerFrame=1024;
Fs=25000;
T=6;%Specify Algorithm run time in seconds here
numplays = (T*Fs)/SamplesPerFrame;

%% Initialise Audio recorder toolbox Parameters
mic=dsp.AudioRecorder();
mic.SamplesPerFrame=SamplesPerFrame;
mic.DeviceName='Default';
mic.NumChannels=1;
mic.SampleRate=Fs;
mic.OutputDataType='double';
mic.BufferSizeSource='Property';
mic.QueueDuration=2;
mic.BufferSize=128;

%% Create and Configure an Audio Player System Object
audplyer = dsp.AudioPlayer('SampleRate',Fs);

%% Scope Parameter Initialisation
scope = dsp.TimeScope('SampleRate',Fs,'TimeSpan',0.1,...
   'Position',P1,'YLimits',[-1 1]);
scope.ShowGrid = 1;
scope.ShowLegend = 1;

%% Spectrum Analyser Specification 
SpectroGraph = dsp.SpectrumAnalyzer('SampleRate',Fs,'Position',P4,...
    'PlotAsTwoSidedSpectrum',false);
SpectroGraph.SpectrumType = 'Spectrogram';

%% Apply filter
while numplays>0                    
    data=step(mic);
    
    %% Take the FFT of the input signal x
    X = fft(data);
                                   

    %% Calculate and Apply Ski-Slope Filter

    transitionV = [1000, 1500, 2550, 5000];
    g = 50;
    [gain] = freqshape(data, g, transitionV, Fs);
    X_editted = X .*gain;

    %% take the ifft of the editted X signal
    data2 = ifft(X_editted,'symmetric');
    
    step(audplyer, double(data));%Play the Output Signal
    step(scope,data2);
    step(SpectroGraph,data2);
    numplays = numplays-1;
        
end

%% Release Hardware
release(mic);
release(audplyer);
release(scope);
release(SpectroGraph);

%% End of Program

