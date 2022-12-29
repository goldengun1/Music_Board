#include "../lib/catch_amalgamated.hpp"
#include "../src/soundbank.h"
#include <memory>
#include <QUrl>
#include <QThread>

TEST_CASE("SoundBank", "[soundbank]")
{
    auto source = QUrl::fromLocalFile("/Users/aleksastevic/Desktop/RS/projekat/05-muzicka-tabla/src/resursi/zvukovi/A.wav");
    auto sound = std::make_shared<Sound>(source);
    SoundBank soundBank;

    sid index1 = 0;
    sid index2 = 1;
    sid index3 = 2;
    sid index4 = 3;
    sid unassignedIndex = 4;

    SECTION("SoundBank::Assign")
    {
        SECTION("correctly returns assigned index")
        {
            REQUIRE(soundBank.Assign(index1, sound) == index1);
            REQUIRE(soundBank.Assign(index2, source) == index2);
        }

        SECTION("does not throw") {
            REQUIRE_NOTHROW(soundBank.Assign(index3, sound));
            REQUIRE_NOTHROW(soundBank.Assign(index4, source));
        }
    }

    SECTION("SoundBank::Assigned")
    {
        SECTION("returns defined Sound value when sound is assigned")
        {
            soundBank.Assign(index1, sound);
            REQUIRE(soundBank.Assigned(index1).value() == sound);
            soundBank.Assign(index2, source);
            auto snd = soundBank.Assigned(index2);
            REQUIRE(snd.value()->Source() == source);
        }

        SECTION("returns empty value when sound is not previously assigned")
        {
            auto snd = soundBank.Assigned(unassignedIndex);
            REQUIRE_FALSE(snd.has_value());
        }

        SECTION("does not throw")
        {
            soundBank.Assign(index1, sound);
            REQUIRE_NOTHROW(soundBank.Assigned(index1));
            REQUIRE_NOTHROW(soundBank.Assigned(unassignedIndex));
        }
    }

    SECTION("SoundBank::Unassign")
    {
        soundBank.Assign(index1, sound);
        soundBank.Unassign(index1);
        REQUIRE_FALSE(soundBank.Assigned(index1).has_value());
        soundBank.Unassign(unassignedIndex);
        REQUIRE_FALSE(soundBank.Assigned(unassignedIndex).has_value());
    }
}
