#include <gtest/gtest.h>

#include <SAMP-EDGEngine/Everything.hpp>

#include <string>
#include <string_view>

namespace samp = samp_edgengine;
namespace ascii = samp::text::ascii;

TEST(TextAscii, Format)
{
	constexpr std::string_view fmt 		= "Hello {0}! It's your {1} visit on the server \\{9{0}!";
	constexpr std::string_view expected = "Hello CrossX! It's your 30 visit on the server \\{9CrossX!";
	std::string const playerName = "CrossX";
	Int32 const playerVisit = 30;

	std::string const result = ascii::format(fmt, playerName, playerVisit);
	EXPECT_EQ(result, expected);
}