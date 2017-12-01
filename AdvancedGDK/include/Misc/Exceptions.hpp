#pragma once

#include "AdvancedGDKMain.hpp"
#include "String.hpp"

namespace agdk
{
	/*	Class used for exceptions.
	*/
	class Exception
	{
	protected:
		std::string m_content;	
	public:
		/*
			Constructor.
		*/
		Exception(const int line, const std::string &file, const std::string &content)
			: m_content(String::format("AGDK EXCEPTION [\"", String::splitPath(file).second, "\" - L:", line, "]: ", content))
		{
		}

		/*
			Returns exception content.
		*/
		std::string what() const { return m_content; }
	};

	/*	Class used when passed null player pointer.
	*/
	class PlayerNullException
		: public Exception
	{
	public:
		PlayerNullException(const int line, const std::string &file)
			: Exception(line, file, "Player pointer is nullptr.")
		{
		}
	};
}
