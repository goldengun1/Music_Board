#include "../lib/catch_amalgamated.hpp"
#include "../src/sound.h"
TEST_CASE("SOUND", "[class]"){
    SECTION("Test Sound::Check that the sound is now playing")
    {
        // Create a Sound object with a sample audio file as the source
        QUrl source("../src/resursi/zvukovi/A.wav");
        Sound sound(source);

        // Set the volume to a non-zero value
        sound.setVolume(50);

        // Call the Play method with a non-zero master volume
        REQUIRE(sound.Play(100));

        // Check that the sound is now playing
        REQUIRE(sound.IsPlaying() == true);
    }
    SECTION("Test Sound::Check that the sound is no longer playing")
    {
        // Create a Sound object with a sample audio file as the source
        QUrl source("../src/resursi/zvukovi/A.wav");
        Sound sound(source);

        // Set the volume to a non-zero value and start playing the sound
        sound.setVolume(50);
        sound.Play(100);

        // Call the Stop method
        REQUIRE(sound.Stop() == true);

        // Check that the sound is no longer playing
        REQUIRE(sound.IsPlaying() == false);
    }
    SECTION("Test Sound::Check that the volume was set correctly")
   {
       // Create a Sound object with a sample audio file as the source
       QUrl source("../src/resursi/zvukovi/A.wav");
       Sound sound(source);

       // Set the volume to a non-zero value
       sound.setVolume(50);

       // Check that the volume was set correctly
       REQUIRE(sound.getVolume() == 50);
   }
    SECTION("Test Sound::Check that the getVolume method returns the correct value")
   {
       // Create a Sound object with a sample audio file as the source
       QUrl source("sample.mp3");
       Sound sound(source);

       // Set the volume to a non-zero value
       sound.setVolume(50);

       // Check that the getVolume method returns the correct value
       REQUIRE(sound.getVolume() == 50);
   }
    SECTION("Test Sound::Check that the Duration method return correct value")
   {
       // Create a Sound object with a sample audio file as the source
       QUrl source("../src/resursi/zvukovi/A.wav");
      Sound sound(source);

      REQUIRE(sound.Duration() >= 0);
   }
    SECTION("Test Sound::Check that the IsPlaying method returns true")
   {
       // Create a Sound object with a sample audio file as the source
       QUrl source("../src/resursi/zvukovi/A.wav");
       Sound sound(source);

       // Set the volume to a non-zero value and start playing the sound
       sound.setVolume(50);
       sound.Play(100);

       // Check that the IsPlaying method returns true
       REQUIRE(sound.IsPlaying() == true);

       // Stop the sound and check that the IsPlaying method returns false
       sound.Stop();
       REQUIRE(sound.IsPlaying() == false);
   }



}







