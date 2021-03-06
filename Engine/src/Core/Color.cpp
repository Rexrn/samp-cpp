#include SAMPCPP_PCH

// Custom headers:
#include <SAMPCpp/Core/Color.hpp>			// Color header
#include <SAMPCpp/Core/Text/ASCII.hpp>		// for string manipulation

#include <SAMPCpp/Dependencies/QuickMaffs.hpp>


namespace samp_cpp
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Color::Color(const std::string &strColor_)
		: Color()
	{
		constexpr const char* szLegalCharacters			=	"{}xX0123456789AaBbCcDdEeFf";
		constexpr const char* szLegalColorCharacters	=	"0123456789AaBbCcDdEeFf";

		if ((strColor_.length() == 6 || strColor_.length() == 8 || strColor_.length() == 10)
			&& strColor_.find_first_not_of(szLegalCharacters) == std::string::npos)
		{
			// Dummy variable.
			std::string hexString;

			// Check for 0xAABBCC[DD] format
			if (strColor_.length() != 6 &&
				text::equal<text::CaseInsensitive>(strColor_.substr(0, 2), "0x") )
			{
				hexString = text::toLower(				// make result lowercase
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
			Uint32 color = 0;
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
	std::string Color::toRGBString() const
	{
		auto packWithPrefix = [](std::stringstream &stream_, Uint8 color_)
		{ 
			stream_ << (color_ < 16 ? "0" : "") << std::hex << static_cast<Int32>(color_);
		};
		std::stringstream stream;
		packWithPrefix(stream, r);
		packWithPrefix(stream, g);
		packWithPrefix(stream, b);
		return text::toUpper(stream.str());
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string Color::toRGBAString() const
	{
		auto packWithPrefix = [](std::stringstream &stream_, Uint8 color_)
		{
			stream_ << (color_ < 16 ? "0" : "") << std::hex << static_cast<Int32>(color_);
		};
		std::stringstream stream;
		packWithPrefix(stream, r);
		packWithPrefix(stream, g);
		packWithPrefix(stream, b);
		packWithPrefix(stream, a);
		return text::toUpper(stream.str());
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string Color::toChatString() const
	{
		return std::string("{") + this->toRGBString() + std::string("}");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	Color Color::random(bool const randomAlpha_)
	{
		return Color(	math::random::generate<Int32>(0, 255),							// The red channel
						math::random::generate<Int32>(0, 255),							// The green channel
						math::random::generate<Int32>(0, 255),							// The blue channel
						(randomAlpha_ ? math::random::generate<Int32>(0, 255) : 255)		// The alpha channel
					);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::ostream& operator<<(std::ostream& stream_, const Color& color_)
	{
		return stream_ << color_.toChatString();
	}
}
