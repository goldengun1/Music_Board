#include "../lib/catch_amalgamated.hpp"
#include "../src/recorder.h"
#include <thread>
#include <chrono>

TEST_CASE("Recorder", "[class]")
{
    SECTION("Recorder::Start method sets recording variable to true")
    {
        Recorder recorder;

        REQUIRE_FALSE(recorder.Recording());

        recorder.Start();

        REQUIRE(recorder.Recording());
    }

    SECTION("Recorder::Mark method correctly puts marks in the matrix timeline")
    {
        Recorder recorder;
        recorder.Start();

        const marktype_t mark1 = recorder.Mark(1, MARK_PUSH);
        const marktype_t mark2 = recorder.Mark(1, MARK_RELEASE);
        auto timeline = recorder.getMatrix().timeline;

        REQUIRE(timeline.size() == 2);

        // Verify that the matrix contains the correct marks
        REQUIRE(timeline.top().first.second == mark1);
        REQUIRE(timeline.top().second == 1);
        timeline.pop();

        REQUIRE(timeline.size() == 1);
        REQUIRE(timeline.top().first.second == mark2);
        REQUIRE(timeline.top().second == 1);
        timeline.pop();

        REQUIRE(timeline.empty());
    }

    SECTION("Recorder::Stop method sets recording durations correctly")
    {
        Recorder recorder;
        recorder.Start();
        REQUIRE(recorder.firstRecordingDuration == 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        recorder.Stop();

        REQUIRE(recorder.firstRecordingDuration > 0);
        REQUIRE(recorder.firstRecordingDuration == recorder.longestRecordingDuration);
    }

    SECTION("Recorder::Stop method sets recording variable to false")
    {
        Recorder recorder;
        recorder.Start();

        recorder.Stop();

        REQUIRE(recorder.Recording() == false);
    }

    SECTION("Recorder::Stop method puts MARK_REC_STOP in the matrix timeline")
    {
        Recorder recorder;
        recorder.Start();

        recorder.Stop();

        // Verify that the matrix contains the correct marks
        REQUIRE(recorder.getMatrix().timeline.size() == 1);
        REQUIRE(recorder.getMatrix().timeline.top().first.second == MARK_REC_STOP);
    }

    SECTION("Recorder::Reset method sets all the variables correctly")
    {
        Recorder recorder;
        recorder.Start();
        recorder.Mark(1, MARK_PUSH);
        recorder.firstRecordingDuration = 1;
        recorder.longestRecordingDuration = 1;

        recorder.Reset();

        REQUIRE(recorder.getMatrix().Empty());
        REQUIRE_FALSE(recorder.Recording());
        REQUIRE(recorder.firstRecordingDuration == 0);
        REQUIRE(recorder.longestRecordingDuration == 0);
    }
}
