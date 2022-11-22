#include<stdexcept>
#include <qdebug.h>
#include "soundbank.h"

SoundBank::SoundBank(void)
{

}

SoundBank::~SoundBank(void)
{

}

sid
SoundBank::Assign(const sid index, std::shared_ptr<Sound> sound)
{
    auto it = this->sound.find(index);

    if (it != this->sound.end())
    {
        it->second->Stop();
    }
    this->sound[index] = sound;
    return index;
}

std::optional<std::shared_ptr<Sound>>
SoundBank::Assigned(const sid index)
{
    std::optional<std::shared_ptr<Sound>> instance = {};

    auto it = this->sound.find(index);
    if (it != this->sound.end() && it->second != nullptr)
    {
        instance = it->second;
    }

    return instance;
}
