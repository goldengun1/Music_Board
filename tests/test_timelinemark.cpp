#include "../lib/catch_amalgamated.hpp"
#include "../src/timelinemark.h"
#include "../headers/utils.h"

TEST_CASE("TimelineMark", "[class]")
{
    SECTION("TimelineMark::boundingRect function returns a rectangle with the correct width and height")
    {
        // Create a TimelineMark object with a width of 100 and a track number of 1
        TimelineMark mark(1, 0, 100, "Test mark");

        // Test
        REQUIRE(mark.boundingRect().width() == 100);
        REQUIRE(mark.boundingRect().height() == Utils::TRACK_HEIGHT);
    }

    SECTION("TimelineMark::Overlaps function correctly detects when the two TimelineMark objects overlap")
    {
        // Create two TimelineMark objects with a width of 100 and a track number of 1
        TimelineMark mark1(1, 0, 100, "Test mark 1");
        TimelineMark mark2(1, 50, 100, "Test mark 2");

        // Test
        REQUIRE(mark1.Overlaps(&mark2) == true);
    }

    SECTION("TimelineMark::IncreaseTrack function correctly increases the track number of the TimelineMark object")
    {
        // Create a TimelineMark object with a width of 100 and a track number of 1
        TimelineMark mark(1, 0, 100, "Test mark");

        // Test
        mark.IncreaseTrack();
        REQUIRE(mark.getTrack() == 2);
    }

    SECTION("TimelineMark::SetWidth function correctly updates the width of the TimelineMark object")
    {
        // Create a TimelineMark object with a width of 100 and a track number of 1
        TimelineMark mark(1, 0, 100, "Test mark");

        // Test
        mark.SetWidth(200);
        REQUIRE(mark.getW() == 200);
    }
}
