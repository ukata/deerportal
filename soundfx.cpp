#include "soundfx.h"

SoundFX::SoundFX()
{
    if (!soundCollectBuffer.loadFromFile("assets/audio/collect.wav"))
        exit(-1);
    soundCollect.setBuffer(soundCollectBuffer);
    if (!soundLetsBeginBuffer.loadFromFile("assets/audio/letsbegin.ogg"))
        exit(-1);
    soundLetsBegin.setBuffer(soundLetsBeginBuffer);
    soundLetsBegin.setVolume(20);
}

void SoundFX::playCollect()
{
    soundCollect.play();
}

void SoundFX::playLetsBegin()
{
    std::cout << "playing.... begin lets" << std::endl;
    soundLetsBegin.play();
}
