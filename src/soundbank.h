#pragma once

#include "sound.h"
#include <map>
#include <memory>
#include <optional>

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

	sid Assign(const sid index, std::shared_ptr<Sound> sound);
	sid Assign(const sid index, const QUrl &url);
	void Unassign(const sid index)
	{
		return sound[index].reset();
	}
	std::optional<std::shared_ptr<Sound>> Assigned(const sid index);
};
