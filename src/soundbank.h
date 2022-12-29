#pragma once

#include <map>
#include <memory>
#include <optional>
#include "sound.h"

// Sound identifier type.
typedef uint32_t sid;

///
/// Manage Sound objects.
/// Assign a Sound to an id (Assign function) and retrive it later (Assigned function).
/// Unassigned id points to nullptr and Assigned() returns std::optional with no value.
///
class SoundBank
{
    std::map<sid, std::shared_ptr<Sound>> sound;

public:
    SoundBank();
    ~SoundBank(void);

    /// Assigns the sound to the slot given by index
    sid Assign(const sid index, std::shared_ptr<Sound> sound);
    sid Assign(const sid index, const QUrl& url);

    // Unassings the sound assigned to slot given by index
    void Unassign(const sid index) { return sound[index].reset(); }

    // Returns a sound value that is assigned to the given index.
    std::optional<std::shared_ptr<Sound>> Assigned(const sid index);
};
