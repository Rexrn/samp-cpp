#pragma once
#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/Server/GlobalTextDraw.hpp>
#include <SAMP-EDGEngine/Core/Pointers.hpp>

#include <map>
#include <string>
#include <vector>

namespace samp_edgengine
{


class GlobalTextDrawPanel
{
public:
	template <typename TType>
	using ObjectPtrType			= SharedPtr<TType>;
	template <typename TType>
	using ObjectContainerType	= std::map<std::string, ObjectPtrType<TType> >;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="GlobalTextDrawPanel"/> class.
	/// </summary>
	GlobalTextDrawPanel();
	
	/// <summary>
	/// Finalizes an instance of the <see cref="GlobalTextDrawPanel"/> class.
	/// </summary>
	virtual ~GlobalTextDrawPanel();

	/// <summary>
	/// Constructs specified textdraw inside the panel.
	/// </summary>
	/// <param name="name_">The name of the constructed text draw.</param>
	/// <param name="args_">The construction params.</param>
	/// <returns>Reference to the constructed object..</returns>
	template <typename TType, typename... TArgTypes>
	TType& construct(std::string const &name_, TArgTypes&&...args_)
	{
		return this->finalizeConstruction(name_, this->beginConstruction<TType>(std::forward<TArgTypes>(args_)...));
	}

	/// <summary>
	/// Begins the textdraw construction (it is not added yet to the panel).
	/// </summary>
	/// <param name="args_">The construction params.</param>
	/// <returns>Owning pointer to the constructed object.</returns>
	template <typename TType, typename... TArgTypes>
	ObjectPtrType<TType> beginConstruction(TArgTypes&&...args_)
	{
		return std::make_shared<TType>(std::forward<TArgTypes>(args_)...);
	}

	/// <summary>
	/// Finalizes the player textdraw construction - adds it to the pool.
	/// </summary>
	/// <param name="name_">The name of the constructed text draw.</param>
	/// <param name="textDraw_">The textdraw.</param>
	/// <returns>Reference to created textdraw.</returns>
	GlobalTextDraw& finalizeConstruction(std::string const & name_, ObjectPtrType< GlobalTextDraw > const& textDraw_);
	
	/// <summary>
	/// Removes the specified textdraw.
	/// </summary>
	/// <param name="name_">The name.</param>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	bool remove(std::string const & name_);
	
	/// <summary>
	/// Returns the textdraw with specified name.
	/// </summary>
	/// <param name="name_">The name.</param>
	/// <returns>
	///		Pointer to the textdraw with specified name, or nullptr if not exists.
	/// </returns>
	GlobalTextDraw* get(std::string const & name_) const;
	
	/// <summary>
	/// Determines whether textdraw with specified name exists.
	/// </summary>
	/// <param name="name_">The name.</param>
	/// <returns>
	///		<c>true</c> if textdraw with specified name exists; otherwise, <c>false</c>.
	/// </returns>
	bool exists(std::string const & name_) const;
	
	/// <summary>
	/// Creates all textdraws.
	/// </summary>
	/// <param name="show_">if set to <c>true</c> show them all after creating.</param>
	void createAll(bool show_ = false);
	
	/// <summary>
	/// Destroys all textdraws.
	/// </summary>
	void destroyAll();
	
	/// <summary>
	/// Recreates all textdraws.
	/// </summary>
	void recreateAll();
	
	/// <summary>
	/// Shows all textdraws.
	/// </summary>
	/// <param name="player_">The player; if set to nullptr, every textdraw will be shown to every player.</param>
	void showAll(Player* player_ = nullptr);
	
	/// <summary>
	/// Hides all textdraws.
	/// </summary>
	/// <param name="player_">The player; if set to nullptr, every textdraw will be hidden from every player.</param>
	void hideAll(Player* player_ = nullptr);
	
	/// <summary>
	/// Rearranges textdraws so their order match their layer indices. You still need to hide and show them again.
	/// </summary>
	void rearrange();
protected:

	//	Contains all textdraws.
	ObjectContainerType<GlobalTextDraw> m_textdraws;
	//	Contains all textdraws (vector is useful when rearranging).
	std::vector<GlobalTextDraw*>		m_vTextdraws;
};


}