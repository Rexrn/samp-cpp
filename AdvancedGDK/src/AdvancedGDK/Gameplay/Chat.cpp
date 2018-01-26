#include "stdafx.h" // PCH


#include <AdvancedGDK/Gameplay/Chat.hpp>
#include <AdvancedGDK/Player/PlayerPool.hpp>
#include <AdvancedGDK/Player/Player.hpp>

#include <AdvancedGDK/Misc/Color.hpp>
#include <AdvancedGDK/Misc/String.hpp>

#include <AdvancedGDK/Server/Server.hpp>
#include <AdvancedGDK/Server/GameMode.hpp>


namespace agdk
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector<std::string> IChat::splitMessage(const std::string &text)
	{
		static constexpr std::string_view hexColorChars{ "0123456789abcdef" };

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
	void IChat::messagePlayer(Player & player_, std::string const & text_)
	{
		auto splitted = splitMessage(text_);
		for (auto const & msg : splitted)
			sampgdk::SendClientMessage(player_.getIndex(), 0xFFFFFFFF, msg.c_str());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	void IChat::messageAll(std::string const & text_)
	{
		sampgdk::SendClientMessageToAll(0xFFFFFFFF, text_.c_str());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	void IChat::messagePlayerML(Player & player_, std::vector<std::string> const text_)
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
			for (auto player : g_gameMode->players.getAll())
			{
				this->messagePlayerML(player, text_);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	void DefaultChat::onPlayerText(Player & player, std::string_view const text_)
	{
		this->messageAll(make_string(player.getColor(), player.getName(), colors::White, " (", player.getIndex(), "): ", text_));
	}
}
