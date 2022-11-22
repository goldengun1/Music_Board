#include "soundplayer.h"

SoundPlayer::SoundPlayer(std::shared_ptr<SoundBank> bank)
    :bank(bank)
{

}

SoundPlayer::~SoundPlayer(void)
{

}

bool
SoundPlayer::Play(const sid index)
{
    bool played = false;
    std::optional<std::shared_ptr<Sound>> sound = bank->Assigned(index);

    if(sound.has_value())
    {
        played = sound->get()->Play();
    }

    return played;
}
