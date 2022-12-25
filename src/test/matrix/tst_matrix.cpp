#include "../../matrix.h"
#define CONFIG_CATCH_MAIN
#include "../catch_amalgamated.hpp"

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
}
