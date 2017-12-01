#include "stdafx.h"					// Precompiled header.
#include <Misc/Color.hpp>			// Color header

#include <Misc/Random.hpp>		// used in Color::random
#include <Misc/String.hpp>			// for string manipulation

#include <sstream>

namespace agdk
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Color::Color(const std::string &strColor_)
		: Color()
	{
		constexpr const char* szLegalCharacters =		"{}xX0123456789AaBbCcDdEeFf";
		constexpr const char* szLegalColorCharacters =	"0123456789AaBbCcDdEeFf";

		if ((strColor_.length() == 6 || strColor_.length() == 8 || strColor_.length() == 10)
			&& strColor_.find_first_not_of(szLegalCharacters) == std::string::npos)
		{
			// Dummy variable.
			std::string hexString;

			// Check for 0xAABBCC[DD] format
			if (strColor_.length() != 6 && StringHelper::toLower(strColor_.substr(0, 2)) == "0x")
			{
				hexString = StringHelper::toLower(				// make result lowercase
					strColor_.substr(2,							// cut string: begin after 2nd character [0x]
						(strColor_.length() == 8 ? 6 : 8)		// cut string: end based on its length (three bytes - 6 chars, or four bytes - 8 chars)
					));
			}
			else if // Check for AABBCC, AABBCCDD format
				( strColor_.length() != 10 && strColor_.find_first_not_of(szLegalColorCharacters) == std::string::npos)
			{
				hexString = strColor_; // just copy it
			}
			else if // Check for {AABBCC} and {AABBCCDD} format
				(strColor_.length() != 6								// 6-chars length is impossible
				&& strColor_.front() == '{' && strColor_.back() == '}'
				&& strColor_.substr(1, (strColor_.length() == 8 ? 6 : 8)).find_first_not_of(szLegalColorCharacters) == std::string::npos)
			{
				hexString = strColor_.substr(1, (strColor_.length() == 8 ? 6 : 8));
			}
			else
			{
				return;
			}

			// Add fourth byte "ff" if missing.
			if (hexString.length() == 6)
				hexString += "ff";

			// Convert it resulting hex string to 32bit unsigned integer.
			std::uint32_t color = 0;
			color = std::stoul(hexString, nullptr, 16);

			*this = Color{ color };
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	Color Color::fromString(const std::string &color_)
	{
		return Color{ color_ };
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::uint32_t Color::toUint32() const
	{
		return (std::uint32_t(r) << 24) + (std::uint32_t(g) << 16) + (std::uint32_t(b) << 8) + std::uint32_t(a);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::int32_t Color::toInt32() const
	{
		return static_cast<std::int32_t>(this->toUint32());
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string Color::toRGBString() const
	{
		auto packWithPrefix = [](std::stringstream &stream_, const std::uint8_t color_)
		{ 
			stream_ << (color_ < 16 ? "0" : "") << std::hex << color_;
		};
		std::stringstream stream;
		packWithPrefix(stream, r);
		packWithPrefix(stream, g);
		packWithPrefix(stream, b);
		return StringHelper::toUpper(stream.str());
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string Color::toRGBAString() const
	{
		auto packWithPrefix = [](std::stringstream &stream_, const std::uint8_t color_)
		{
			stream_ << (color_ < 16 ? "0" : "") << std::hex << color_;
		};
		std::stringstream stream;
		packWithPrefix(stream, r);
		packWithPrefix(stream, g);
		packWithPrefix(stream, b);
		packWithPrefix(stream, a);
		return StringHelper::toUpper(stream.str());
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string Color::toChatString() const
	{
		return std::string("{") + this->toRGBString() + std::string("}");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	Color Color::random(const bool randomAlpha_)
	{
		return Color(	Random::next<std::int32_t>(0, 255),							// The red channel
						Random::next<std::int32_t>(0, 255),							// The green channel
						Random::next<std::int32_t>(0, 255),							// The blue channel
						(randomAlpha_ ? Random::next<std::int32_t>(0, 255) : 255)	// The alpha channel
					);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::ostream& operator<<(std::ostream& stream_, const Color& color_)
	{
		return stream_ << color_.toChatString();
	}
}
