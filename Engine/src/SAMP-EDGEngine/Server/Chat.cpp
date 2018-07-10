#include "EnginePCH.hpp" // PCH


#include <SAMP-EDGEngine/Server/Chat.hpp>
#include <SAMP-EDGEngine/Server/PlayerPool.hpp>
#include <SAMP-EDGEngine/Server/Player.hpp>

#include <SAMP-EDGEngine/Core/Color.hpp>
#include <SAMP-EDGEngine/Core/Text/ASCII.hpp>

#include <SAMP-EDGEngine/Server/GameMode.hpp>
#include <SAMP-EDGEngine/Server/Server.hpp>


namespace samp_edgengine
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	IChat::IChat()
	{
		Server->onPlayerText += { *this, &IChat::whenPlayerSendsText };
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector<std::string> IChat::splitMessage(const std::string &text)
	{
		using namespace std::string_view_literals;

		static constexpr std::string_view hexColorChars = "0123456789abcdef"sv;

		std::string lastColor;
		std::string currentLine;
		std::vector<std::string> msgs;

		bool readingColor = false;
		for (std::size_t i = 0; i < text.length(); i++)
		{
			if (!readingColor)
			{
				if (text[i] == '{') {
					lastColor		= text[i];
					readingColor	= true;
				}
				else if (text[i] == '\n') {
					msgs.push_back(currentLine);
					currentLine = lastColor;
				}
				else {
					currentLine += text[i];
				}
			}
			else
			{
				if (hexColorChars.find(text[i]) != std::string::npos)
				{
					if (lastColor.length() < 7)
						lastColor += text[i];
					else {
						lastColor += text[i];
						currentLine += lastColor;
						lastColor = "";
						readingColor = false;
					}
				}
				else if (text[i] == '}') {
					lastColor += text[i];
					currentLine += lastColor;
					readingColor = false;
				}
				else {
					lastColor += text[i];
					currentLine += lastColor;
					lastColor = "";
					readingColor = false;
				}
			}
		}

		if (currentLine.length() > 0 &&
			currentLine != lastColor) {
			msgs.push_back(currentLine);
		}
		return msgs;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	void IChat::messagePlayer(Player const & player_, std::string const & text_)
	{
		auto splitted = splitMessage(text_);
		for (auto const & msg : splitted)
			sampgdk_SendClientMessage(player_.getIndex(), 0xFFFFFFFF, msg.c_str());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	void IChat::messageAll(std::string const & text_)
	{
		sampgdk_SendClientMessageToAll(0xFFFFFFFF, text_.c_str());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	void IChat::messagePlayerML(Player const & player_, std::vector<std::string> const text_)
	{
		if (!text_.empty())
		{
			// For each language there must be one message.
			assert(player_.getLanguage() < text_.size());

			this->messagePlayer(player_, text_[ player_.getLanguage() ]);
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	void IChat::messageAllML(std::vector<std::string> const text_)
	{
		if (!text_.empty())
		{
			for (auto player : GameMode->Players.getPool())
			{
				this->messagePlayerML(*player, text_);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	void DefaultChat::whenPlayerSendsText(Player & player_, std::string_view text_)
	{
		auto text = text::ascii::compose(player_.getColor(), player_.getName(), colors::White, " (", player_.getIndex(), "): ", text_);
		this->messageAll(text);
	}
}
