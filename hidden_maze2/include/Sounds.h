#ifndef SOUNDS_H
#define SOUNDS_H
#include <SFML/Audio.hpp>
#include "Constants.h"


class Sounds
{
public:
    enum SoundName{Empty, Bounce, Wall, Light, Bomb, Fart, Win, Loss, Tick, NumberOfSounds};
    Sounds();
    ~Sounds();
    void play(SoundName, float volume = 50.0f);
    void playmusic();
    void stopmusic();
    sf::Sound& getSound(SoundName);
private:
    sf::SoundBuffer* buffer;
    sf::Sound* sound;
    sf::Music music;
};

#endif // SOUNDS_H
