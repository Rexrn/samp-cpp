#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/Server/Dialog.hpp>

#include <SAMP-EDGEngine/Server/Player.hpp>
#include <SAMP-EDGEngine/Core/TextInc.hpp>


namespace samp_edgengine
{

// Initialize static members.
std::map<std::string, Int32> IDialog::s_uniqueHashIndices;
Int32 IDialog::s_uniqueHashIndexCounter = 0;

////////////////////////////////////////////////////////////////////////////////////
IDialog::IDialog()
	: m_player{ nullptr }
{
}

////////////////////////////////////////////////////////////////////////////////////
IDialog::IDialog(std::string_view caption_, std::string_view message_, std::string_view button1_, std::string_view button2_)
	:
	m_caption{ caption_ }, m_desc{ message_ },
	m_buttons{ std::string(button1_), std::string(button2_) }
{
}

////////////////////////////////////////////////////////////////////////////////////
void IDialog::setOwner(Player& player_)
{
	m_player = &player_;
}

////////////////////////////////////////////////////////////////////////////////////
Int32 IDialog::generateDialogHash(std::string_view customHash_)
{
	const std::type_info &type = typeid(*this);

	auto hashIndex = getHashIndex(text::ascii::compose(type.hash_code(), (customHash_ != "" ? std::string("::") + std::string(customHash_) : "")));
	
	if (hashIndex != std::nullopt) {
		return hashIndex.value();
	}

	auto id = nextUniqueHashIndex();
	s_uniqueHashIndices[ std::string(customHash_) ] = id;
	return id;
}

////////////////////////////////////////////////////////////////////////////////////
std::optional<Int32> IDialog::getHashIndex(std::string const & hash_)
{
	auto it = s_uniqueHashIndices.find( hash_ );
	if (it != s_uniqueHashIndices.end())
		return it->second;
	return std::nullopt;
}

////////////////////////////////////////////////////////////////////////////////////
Int32 IDialog::nextUniqueHashIndex()
{
	return s_uniqueHashIndexCounter++;
}

////////////////////////////////////////////////////////////////////////////////////
IMessageBox::IMessageBox()
{
}

////////////////////////////////////////////////////////////////////////////////////
IMessageBox::IMessageBox(std::string_view caption_, std::string_view message_, std::string_view button1_, std::string_view button2_)
	: IDialog{ caption_, message_, button1_, button2_ }
{
}

////////////////////////////////////////////////////////////////////////////////////
void IMessageBox::show(std::string_view customHash_)
{
	sampgdk::ShowPlayerDialog(m_player->getIndex(), this->generateDialogHash(customHash_), DIALOG_STYLE_MSGBOX, m_caption.c_str(), m_desc.c_str(), m_buttons[0].c_str(), m_buttons[1].c_str());
}

////////////////////////////////////////////////////////////////////////////////////
IInputBox::IInputBox()
{
}

////////////////////////////////////////////////////////////////////////////////////
IInputBox::IInputBox(std::string_view caption_, std::string_view message_, std::string_view button1_, std::string_view button2_)
	: IDialog{ caption_, message_, button1_, button2_ }
{
}

////////////////////////////////////////////////////////////////////////////////////
void IInputBox::show(std::string_view customHash_)
{
	sampgdk::ShowPlayerDialog(m_player->getIndex(), this->generateDialogHash(customHash_), DIALOG_STYLE_INPUT, m_caption.c_str(), m_desc.c_str(), m_buttons[0].c_str(), m_buttons[1].c_str());
}

////////////////////////////////////////////////////////////////////////////////////
IPasswordBox::IPasswordBox()
{
}

////////////////////////////////////////////////////////////////////////////////////
IPasswordBox::IPasswordBox(std::string_view caption_, std::string_view message_, std::string_view button1_, std::string_view button2_)
	: IDialog{ caption_, message_, button1_, button2_ }
{
}

////////////////////////////////////////////////////////////////////////////////////
void IPasswordBox::show(std::string_view customHash_)
{
	sampgdk::ShowPlayerDialog(m_player->getIndex(), this->generateDialogHash(customHash_), DIALOG_STYLE_PASSWORD, m_caption.c_str(), m_desc.c_str(), m_buttons[0].c_str(), m_buttons[1].c_str());
}

////////////////////////////////////////////////////////////////////////////////////
IListBox::IListBox(Player& player_)
{
}

////////////////////////////////////////////////////////////////////////////////////
IListBox::IListBox(std::string_view caption_, std::string_view button1_, std::string_view button2_)
	: IDialog{ caption_, "", button1_, button2_ }
{
}

////////////////////////////////////////////////////////////////////////////////////
void IListBox::show(std::string_view customHash_)
{
	sampgdk::ShowPlayerDialog(m_player->getIndex(), this->generateDialogHash(customHash_), DIALOG_STYLE_LIST, m_caption.c_str(), m_desc.c_str(), m_buttons[0].c_str(), m_buttons[1].c_str());
}

////////////////////////////////////////////////////////////////////////////////////
void IListBox::addItem(std::string_view item_)
{
	m_desc += item_;
	m_desc += "\n";
}

////////////////////////////////////////////////////////////////////////////////////
ITabListBox::ITabListBox()
{
}

////////////////////////////////////////////////////////////////////////////////////
ITabListBox::ITabListBox(std::string_view caption_, std::string_view button1_, std::string_view button2_)
	: IDialog{ caption_, "", button1_, button2_ }
{
}

////////////////////////////////////////////////////////////////////////////////////
void ITabListBox::show(std::string_view customHash_)
{
	sampgdk::ShowPlayerDialog(m_player->getIndex(), this->generateDialogHash(customHash_), DIALOG_STYLE_TABLIST, m_caption.c_str(), m_desc.c_str(), m_buttons[0].c_str(), m_buttons[1].c_str());
}

////////////////////////////////////////////////////////////////////////////////////
void ITabListBox::addItem(std::string_view item_)
{
	m_desc += item_;
	m_desc += "\n";
}

////////////////////////////////////////////////////////////////////////////////////
ITabListHeadersBox::ITabListHeadersBox()
{
}

////////////////////////////////////////////////////////////////////////////////////
ITabListHeadersBox::ITabListHeadersBox(std::string_view caption_, std::string_view button1_, std::string_view button2_)
	: IDialog{ caption_, "", button1_, button2_ }
{
}

////////////////////////////////////////////////////////////////////////////////////
void ITabListHeadersBox::show(std::string_view customHash_)
{
	sampgdk::ShowPlayerDialog(m_player->getIndex(), this->generateDialogHash(customHash_), DIALOG_STYLE_TABLIST_HEADERS, m_caption.c_str(), m_desc.c_str(), m_buttons[0].c_str(), m_buttons[1].c_str());
}

////////////////////////////////////////////////////////////////////////////////////
void ITabListHeadersBox::addItem(std::string_view item_)
{
	m_desc += item_;
	m_desc += "\n";
}

}
