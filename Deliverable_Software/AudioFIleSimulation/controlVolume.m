function newAudio = controlVolume(audio, desiredVolume)
if (size(audio,2) == 1)
    maxSample = max(abs(audio));
    newAudio = audio * desiredVolume / maxSample;
end
if (size(audio,2) == 2)
    newAudio = zeros(length(audio),2);
    maxSample1 = max(abs(audio(:,1)));
    newAudio(:,1) = audio(:,1) .* (desiredVolume / maxSample1);
    maxSample2 = max(abs(audio(:,2)));
    newAudio(:,2) = audio(:,2) * desiredVolume / maxSample2;
end
end
