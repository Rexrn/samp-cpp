#include "stdafx.h"				// Precompiled header.
#include <Misc/String.hpp>

#include <algorithm>
#include <cctype>				// std::isspace, etc.
#include <functional>

namespace agdk
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string StringHelper::trimLeft(std::string string_)
	{
		// Note: string_ is passed by value on purpose, copying it is mandatory even when passing by const ref.

		if (!string_.empty())
		{
			std::size_t firstNotSpace{};
			while (string_.length() > firstNotSpace && std::isspace(string_[firstNotSpace++]));
			string_ = string_.substr(firstNotSpace);
		}
		return string_;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string StringHelper::trimRight(std::string string_)
	{
		// Note: `string_` is passed by value on purpose, copying it is mandatory even when passing by const ref.

		if (!string_.empty())
		{
			std::size_t lastNotSpace{string_.length()-1};

			// Note: don't decrement `lastNotSpace` in while condition.
			// When decrementing std::size_t typed variable below 0 (which would happen in the end) it wraps around to max value,
			// causing memory violation (reading std::outside string data) and infinite loop.
			while (lastNotSpace >= 0 && std::isspace(string_[lastNotSpace]))
			{
				if (lastNotSpace > 0)
					lastNotSpace--;
				else
					break;
			}
			
			if(lastNotSpace > 0)
				string_ = string_.substr(0, lastNotSpace + 1); // + 1 because last checked character is also considered. 
		}
		return string_;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string StringHelper::trim(std::string string_)
	{
		return StringHelper::trimLeft(StringHelper::trimRight(string_));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string StringHelper::toLower(std::string string_)
	{
		std::transform(string_.begin(), string_.end(), string_.begin(), [](unsigned char c) { return std::tolower(c); });
		return string_;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string StringHelper::toUpper(std::string string_)
	{
		std::transform(string_.begin(), string_.end(), string_.begin(), [](unsigned char c) { return std::toupper(c); });
		return string_;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string StringHelper::removeSpaces(std::string string_)
	{
		string_.erase(std::remove_if(string_.begin(), string_.end(), std::isspace), string_.end());
		return string_;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::string StringHelper::replace(std::string subject, const std::string& search, const std::string& replace)
	{
		std::size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return subject;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::size_t StringHelper::count(const std::string &subject_, const std::string &sequence_)
	{
		std::size_t occurrences{ 0 };
		std::size_t start{ 0 };

		while ((start = subject_.find(sequence_, start)) != std::string::npos) {
			occurrences++;
			start += sequence_.length();
		}
		return occurrences;
	}


	bool StringHelper::storesInteger(const std::string &string_, bool unsigned_)
	{
		for (std::size_t i{ 0u }; i < string_.size(); i++)
		{
			const auto& _char = string_[i];
			if (_char == '-')
			{
				if (i != 0 || unsigned_)		// Minus is only allowed at the beginning.
					return false;
				else
					continue;
			}
			else if (!std::isdigit(_char))		// Every other character that is not a digit is forbidden.
				return false;
		}
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool StringHelper::storesFloat(const std::string &string_, const std::string::value_type separator_)
	{
		bool alreadyFoundSeparator{ false };
		for (std::size_t i{ 0u }; i < string_.size(); i++)
		{
			const auto& _char = string_[i];
			if (_char == '-')
			{
				if (i != 0)						// Minus is only allowed at the beginning.
					return false;
				else
					continue;
			}
			else if (_char == separator_)
			{
				if (alreadyFoundSeparator)		// Only one separator is allowed.
					return false;
				else
					continue;
			}
			else if (!std::isdigit(_char))		// Every other character that is not a digit is forbidden.
				return false;
		}
		return true;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool StringHelper::storesBoolean(const std::string &string_)
	{
		auto lower = StringHelper::toLower(string_);
		return (lower == "true" || lower == "false" || lower == "1" || lower == "0");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool StringHelper::storesNumber(const std::string &A, const std::string::value_type separator_)
	{
		return StringHelper::storesFloat(A, separator_);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::size_t StringHelper::maxSequenceLength(const std::string &string_, const std::string &sequence_)
	{
		std::size_t maxScore = 0;
		std::size_t score = 0;
		for (std::size_t i{ 0 }; i < sequence_.length(); i++)
		{
			if (string_[score] == sequence_[i])
				score++;
			else
				score = 0;

			if (score > maxScore)
				maxScore = score;
			if (score >= string_.length())
				break;
		}
		return maxScore;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector<std::string> StringHelper::explode(const std::string& string_, const std::string::value_type delimiter_)
	{
		std::vector<std::string> tokens;
		std::size_t start = 0, end = 0;
		while ((end = string_.find(delimiter_, start)) != std::string::npos) {
			tokens.push_back(string_.substr(start, end - start));
			start = end + 1;
		}
		tokens.push_back(string_.substr(start));
		return tokens;
	}

	/*	DEPRECATED.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::pair<std::string, std::string> StringHelper::splitPath(const std::string &fullPath_)
		{
			std::string path, fileName;
			std::size_t lastPos = fullPath_.find_last_of("\\/");
			if (lastPos != std::string::npos)
			{
				path = fullPath_.substr(0, lastPos);
				if (fullPath_.length() > lastPos + 1)
					fileName = fullPath.substr(lastPos + 1);
			}
			else
				fileName = fullPath_;

			return std::pair<std::string, std::string>(path, fileName);
		}
	*/
}
