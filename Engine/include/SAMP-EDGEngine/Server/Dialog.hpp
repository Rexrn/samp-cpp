#pragma once

#include SAMP_EDGENGINE_PCH

#include <SAMP-EDGEngine/Core/TypesAndDefinitions.hpp>

namespace samp_edgengine
{

class Player;

/// <summary>
/// Enumeration of existing dialog buttons.
/// </summary>
enum class DialogButton
{
	Left = 0,
	Right = 1,
	Default = 1
};

/// <summary>
/// Class (interface) that represents in-game dialog.
/// </summary>
class IDialog
{
public:
	
	/// <summary>
	/// Initializes a new instance of the <see cref="IDialog"/> class.
	/// </summary>
	IDialog();
		
	/// <summary>
	/// Initializes a new instance of the <see cref="IDialog"/> class.
	/// </summary>
	/// <param name="caption_">The caption.</param>
	/// <param name="message_">The message.</param>
	/// <param name="button1_">The first button.</param>
	/// <param name="button2_">The second button.</param>
	IDialog(std::string_view caption_, std::string_view message_, std::string_view button1_, std::string_view button2_);

	/// <summary>
	/// Function called when player responds to the dialog.
	/// </summary>
	/// <param name="button_">The dialog button.</param>
	/// <param name="listItem_">The list item.</param>
	/// <param name="input_">The input.</param>
	virtual void onResponse(DialogButton button_, Int32 listItem_, std::string_view input_) = 0;

	friend class Player;
protected:

	/// <summary>
	/// Sets the owner player.
	/// </summary>
	/// <param name="player_">The player.</param>
	void setOwner(Player & player_);

	/// <summary>
	/// Shows the specified dialog. Dialog ID can be modified with custom hash.
	/// </summary>
	/// <param name="customHash">The custom hash.</param>
	virtual void show(std::string_view customHash_ = "") = 0;

	// Reference to player the dialog is shown to.
	Player* m_player;
	//	Dialog caption.
	std::string m_caption;
	//	Dialog description.
	std::string m_desc;
	//	Dialog buttons.
	std::string m_buttons[2];

	/// <summary>
	/// Generates unique dialog hash.
	/// </summary>
	/// <param name="customHash_">The custom hash.</param>
	/// <returns></returns>
	Int32 generateDialogHash(std::string_view customHash_ = "");
private:

	/// <summary>
	/// Returns the index of the specified hash (or nullopt if hash does not exist in the record).
	/// </summary>
	/// <param name="hash_">The hash.</param>
	/// <returns>
	/// The index of the specified hash (or nullopt if hash does not exist in the record).
	/// </returns>
	static std::optional<Int32> getHashIndex(std::string const &hash_);

	/// <summary>
	/// Generates next unique hash index.
	/// </summary>
	/// <returns>
	/// Next unique hash index.
	/// </returns>
	static Int32 nextUniqueHashIndex();

	//	Index counter - accumulates everytime new index gets taken.
	static Int32 s_uniqueHashIndexCounter;
	//	Map of unique index per hash.
	static std::map<std::string, Int32> s_uniqueHashIndices;
};

/// <summary>
/// Class (interface) representing message box dialog.
/// </summary>
/// <seealso cref="IDialog" />
class IMessageBox
	: public IDialog
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="IMessageBox"/> class.
	/// </summary>
	IMessageBox();

	/// <summary>
	/// Initializes a new instance of the <see cref="IMessageBox"/> class.
	/// </summary>
	/// <param name="caption_">The caption.</param>
	/// <param name="message_">The message.</param>
	/// <param name="button1_">The first button.</param>
	/// <param name="button2_">The second button.</param>
	IMessageBox(std::string_view caption_, std::string_view message_, std::string_view button1_, std::string_view button2_);

protected:

	/// <summary>
	/// Shows the specified dialog. Dialog ID can be modified with custom hash.
	/// </summary>
	/// <param name="customHash">The custom hash.</param>
	virtual void show(std::string_view customHash_) override;
};


/// <summary>
/// Class (interface) representing input (text) box dialog.
/// </summary>
/// <seealso cref="IDialog" />
class IInputBox
	: public IDialog
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="IInputBox"/> class.
	/// </summary>
	IInputBox();

	/// <summary>
	/// Initializes a new instance of the <see cref="IInputBox"/> class.
	/// </summary>
	/// <param name="caption_">The caption.</param>
	/// <param name="message_">The message.</param>
	/// <param name="button1_">The first button.</param>
	/// <param name="button2_">The second button.</param>
	IInputBox(std::string_view caption_, std::string_view message_, std::string_view button1_, std::string_view button2_);

protected:

	/// <summary>
	/// Shows the specified dialog. Dialog ID can be modified with custom hash.
	/// </summary>
	/// <param name="customHash">The custom hash.</param>
	virtual void show(std::string_view customHash_) override;
};


/// <summary>
/// Class (interface) representing input (password) box dialog.
/// </summary>
/// <seealso cref="IDialog" />
class IPasswordBox
	: public IDialog
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="IPasswordBox"/> class.
	/// </summary>
	IPasswordBox();

	/// <summary>
	/// Initializes a new instance of the <see cref="IPasswordBox"/> class.
	/// </summary>
	/// <param name="caption_">The caption.</param>
	/// <param name="message_">The message.</param>
	/// <param name="button1_">The first button.</param>
	/// <param name="button2_">The second button.</param>
	IPasswordBox(std::string_view caption_, std::string_view message_, std::string_view button1_, std::string_view button2_);

protected:

	/// <summary>
	/// Shows the specified dialog. Dialog ID can be modified with custom hash.
	/// </summary>
	/// <param name="customHash">The custom hash.</param>
	virtual void show(std::string_view customHash_) override;
};


/// <summary>
/// Class (interface) representing list box dialog.
/// </summary>
/// <seealso cref="IDialog" />
class IListBox
	: public IDialog
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="IListBox"/> class.
	/// </summary>
	IListBox(Player & player_);

	/// <summary>
	/// Initializes a new instance of the <see cref="IListBox"/> class.
	/// </summary>
	/// <param name="caption_">The caption.</param>
	/// <param name="message_">The message.</param>
	/// <param name="button1_">The first button.</param>
	/// <param name="button2_">The second button.</param>
	IListBox(std::string_view caption_, std::string_view button1_, std::string_view button2_);

protected:

	/// <summary>
	/// Shows the specified dialog. Dialog ID can be modified with custom hash.
	/// </summary>
	/// <param name="customHash">The custom hash.</param>
	virtual void show(std::string_view customHash_) override;

	/// <summary>
	/// Adds specified string as an list item.
	/// </summary>
	/// <param name="item_">The item.</param>
	void addItem(std::string_view item_);
};


/// <summary>
/// Class (interface) representing multi-column list box dialog.
/// Tab character is used to separate columns.
/// </summary>
/// <seealso cref="IDialog" />
class ITabListBox
	: public IDialog
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ITabListBox"/> class.
	/// </summary>
	ITabListBox();

	/// <summary>
	/// Initializes a new instance of the <see cref="ITabListBox"/> class.
	/// </summary>
	/// <param name="caption_">The caption.</param>
	/// <param name="message_">The message.</param>
	/// <param name="button1_">The first button.</param>
	/// <param name="button2_">The second button.</param>
	ITabListBox(std::string_view caption_, std::string_view button1_, std::string_view button2_);

protected:

	/// <summary>
	/// Shows the specified dialog. Dialog ID can be modified with custom hash.
	/// </summary>
	/// <param name="customHash">The custom hash.</param>
	virtual void show(std::string_view customHash_) override;

	/// <summary>
	/// Adds specified string as an list item.
	/// </summary>
	/// <param name="item_">The item.</param>
	void addItem(std::string_view item_);
};


/// <summary>
/// Class (interface) representing multi-column list box dialog with column headers (captions).
/// Tab character is used to separate columns.
/// First line(also formatted with tabs) is used as column headers.
/// </summary>
/// <seealso cref="IDialog" />
class ITabListHeadersBox
	: public IDialog
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ITabListHeadersBox"/> class.
	/// </summary>
	ITabListHeadersBox();

	/// <summary>
	/// Initializes a new instance of the <see cref="ITabListHeadersBox"/> class.
	/// </summary>
	/// <param name="caption_">The caption.</param>
	/// <param name="message_">The message.</param>
	/// <param name="button1_">The first button.</param>
	/// <param name="button2_">The second button.</param>
	ITabListHeadersBox(std::string_view caption_, std::string_view button1_, std::string_view button2_);

protected:

	/// <summary>
	/// Shows the specified dialog. Dialog ID can be modified with custom hash.
	/// </summary>
	/// <param name="customHash">The custom hash.</param>
	virtual void show(std::string_view customHash_) override;

	/// <summary>
	/// Adds specified string as an list item.
	/// </summary>
	/// <param name="item_">The item.</param>
	void addItem(std::string_view item_);
};

}