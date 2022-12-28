#include "../lib/catch_amalgamated.hpp"
#include "../src/matrix.h"

TEST_CASE("Matrix", "[matrix]")
{
    SECTION("Matrix::Matrix")
    {
        Matrix matrix;

        REQUIRE(matrix.Empty() == true);
        REQUIRE(matrix.timeline.size() == 0);
    }

    SECTION("Matrix::Append")
    {
        Matrix matrix;

        matrix.Append(0,   MARK_PUSH, 0);
        matrix.Append(300, MARK_PUSH, 1);
        matrix.Append(100, MARK_PUSH, 1);

        REQUIRE(matrix.Empty()         == false);
        REQUIRE(matrix.timeline.size() == 3);

        REQUIRE(matrix.timeline.top().first.first  == 0);
        REQUIRE(matrix.timeline.top().first.second == MARK_PUSH);
        REQUIRE(matrix.timeline.top().second       == 0);
        matrix.timeline.pop();

        REQUIRE(matrix.timeline.top().first.first  == 100);
        REQUIRE(matrix.timeline.top().first.second == MARK_PUSH);
        REQUIRE(matrix.timeline.top().second       == 1);
        matrix.timeline.pop();

        REQUIRE(matrix.timeline.top().first.first  == 300);
        REQUIRE(matrix.timeline.top().first.second == MARK_PUSH);
        REQUIRE(matrix.timeline.top().second       == 1);
        matrix.timeline.pop();

        REQUIRE(matrix.Empty()         == true);
        REQUIRE(matrix.timeline.size() == 0);
    }

    SECTION("Matrix::Clear")
    {
        Matrix matrix;

        matrix.Append(0,   MARK_PUSH, 0);
        matrix.Append(300, MARK_PUSH, 1);
        matrix.Append(100, MARK_PUSH, 1);
        REQUIRE(matrix.Empty()         == false);
        REQUIRE(matrix.timeline.size() == 3);

        matrix.Clear();
        REQUIRE(matrix.Empty()         == true);
        REQUIRE(matrix.timeline.size() == 0);
    }

    SECTION("Matrix::Export Matrix::Import")
    {
        Matrix         matrix;
        uint32_t       duration;
        const uint32_t recordduration = 350;

        matrix.Append(0,              MARK_PUSH,     0);
        matrix.Append(300,            MARK_PUSH,     1);
        matrix.Append(100,            MARK_PUSH,     1);
        matrix.Append(recordduration, MARK_REC_STOP, 1);
        REQUIRE(matrix.Empty()         == false);
        REQUIRE(matrix.timeline.size() == 4);

        // Exporting the same file twice will yield a debug message, but this is fine.
        matrix.Export("test2.matrix");
        matrix.Clear();
        REQUIRE(matrix.Empty()         == true);
        REQUIRE(matrix.timeline.size() == 0);

        std::tie(matrix, duration) = Matrix::Import("test2.matrix");
        REQUIRE(matrix.Empty()         != true);
        REQUIRE(matrix.timeline.size() == 4);

        REQUIRE(matrix.timeline.top().first.first  == 0);
        REQUIRE(matrix.timeline.top().first.second == MARK_PUSH);
        REQUIRE(matrix.timeline.top().second       == 0);
        matrix.timeline.pop();

        REQUIRE(matrix.timeline.top().first.first  == 100);
        REQUIRE(matrix.timeline.top().first.second == MARK_PUSH);
        REQUIRE(matrix.timeline.top().second       == 1);
        matrix.timeline.pop();

        REQUIRE(matrix.timeline.top().first.first  == 300);
        REQUIRE(matrix.timeline.top().first.second == MARK_PUSH);
        REQUIRE(matrix.timeline.top().second       == 1);
        matrix.timeline.pop();

        REQUIRE(matrix.timeline.top().first.first  == recordduration);
        REQUIRE(matrix.timeline.top().first.second == MARK_REC_STOP);
        REQUIRE(matrix.timeline.top().second       == 1);
        matrix.timeline.pop();

        REQUIRE(matrix.Empty()         == true);
        REQUIRE(matrix.timeline.size() == 0);
    }

    SECTION("Matrix::Empty")
    {
        Matrix matrix;

        REQUIRE(matrix.Empty() == true);

        matrix.Append(0,   MARK_PUSH, 0);
        REQUIRE(matrix.Empty()         != true);
        REQUIRE(matrix.timeline.size() == 1);

        matrix.Clear();
        REQUIRE(matrix.Empty()         == true);
        REQUIRE(matrix.timeline.size() == 0);
    }
}
