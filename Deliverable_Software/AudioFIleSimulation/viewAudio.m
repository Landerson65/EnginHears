function viewAudio(x, Fs, filename)
% x = signal you're trying to view
L = length(x);
figure
subplot(2,1,1);
plot((1:L)/Fs, x(:,1));
title(strcat('Left Channel of', ' ' ,filename));
xlabel('t (seconds)');
ylabel('x(t)')
subplot(2,1,2);
plot((1:L)/Fs, x(:,2));
title(strcat('Right Channel of', ' ' ,filename));
xlabel('t (seconds)');
ylabel('x(t)')

end