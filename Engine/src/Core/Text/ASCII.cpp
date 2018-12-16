#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/Core/Text/ASCII.hpp>


namespace samp_edgengine::text::ascii
{
///////////////////////////////////////////////////////////////////////
std::string toLower(std::string_view const string_)
{
	std::string result{ string_ };
	std::transform(result.begin(), result.end(), result.begin(), toLower<char>);
	return result;
}

///////////////////////////////////////////////////////////////////////
std::string toUpper(std::string_view const string_)
{
	std::string result{ string_ };
	std::transform(result.begin(), result.end(), result.begin(), toUpper<char>);
	return result;
}

///////////////////////////////////////////////////////////////////////
bool startsWith(std::string_view string_, std::string_view testedPrefix_)
{
	if (string_.length() < testedPrefix_.length())
		return false;

	for (std::size_t prefIndex = 0; prefIndex < testedPrefix_.length(); prefIndex++)
	{
		if (string_[prefIndex] != testedPrefix_[prefIndex])
			return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////
std::string trimLeft(std::string_view const string_)
{
	auto it = std::find_if(string_.begin(), string_.end(),
		[](auto character) {
			return !isSpace(character);
		});
	return std::string{ it, string_.end() };
}

///////////////////////////////////////////////////////////////////////
std::string trimRight(std::string_view const string_)
{
	auto it = std::find_if(string_.rbegin(), string_.rend(),
		[](auto character) {
			return !isSpace(character);
		});
	return std::string{ string_.begin(), it.base() };
}

///////////////////////////////////////////////////////////////////////
std::string	trim(std::string_view const string_)
{
	auto itFromBeg = std::find_if(string_.begin(), string_.end(),
		[](auto character) {
		return !isSpace(character);
	});

	if (itFromBeg == string_.end())
		return std::string{}; // Contains only whitespaces.

	auto itFromEnd = std::find_if(string_.rbegin(), string_.rend(),
		[](auto character) {
		return !isSpace(character);
	});

	return std::string{ itFromBeg, itFromEnd.base() };
}

///////////////////////////////////////////////////////////////////////
std::string removeSpaces(std::string_view const string_)
{
	std::string result{ string_ };
	result.erase(std::remove_if(result.begin(), result.end(), isSpace<char>), result.end());
	return result;
}

///////////////////////////////////////////////////////////////////////
std::string replaceAll(std::string_view const target_, std::string_view const from_, std::string_view const to_)
{
	std::string result{ target_ };
	std::string::size_type pos = 0;
	while ((pos = result.find(from_, pos)) != std::string::npos) {
		result.replace(pos, from_.length(), to_);
		pos += to_.length();
	}
	return result;
}

///////////////////////////////////////////////////////////////////////
std::string::size_type count(std::string_view const subject_, std::string_view const sequence_)
{
	std::string::size_type pos = 0;
	std::string::size_type occurrences = 0;
	while ((pos = subject_.find(sequence_, pos)) != std::string::npos) {
		pos += sequence_.length();
		occurrences++;
	}
	return occurrences;
}

///////////////////////////////////////////////////////////////////////
bool storesBoolean(std::string_view const string_)
{
	return stores<bool>(string_);
}


} // namespace