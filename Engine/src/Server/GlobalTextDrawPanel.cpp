#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/Server/GlobalTextDrawPanel.hpp>

namespace samp_edgengine
{

////////////////////////////////////////////////////////////////////////
GlobalTextDrawPanel::GlobalTextDrawPanel()
{
}

////////////////////////////////////////////////////////////////////////
GlobalTextDrawPanel::~GlobalTextDrawPanel()
{
}

////////////////////////////////////////////////////////////////////////
GlobalTextDraw& GlobalTextDrawPanel::finalizeConstruction(std::string const & name_, ObjectPtrType< GlobalTextDraw > const& textDraw_)
{
	m_textdraws[name_] = textDraw_;
	m_vTextdraws.push_back(textDraw_.get());
	return *textDraw_;
}

////////////////////////////////////////////////////////////////////////
bool GlobalTextDrawPanel::remove(std::string const & name_)
{
	auto it = m_textdraws.find(name_);
	if (it != m_textdraws.end())
	{
		auto vIt = std::find_if(m_vTextdraws.begin(), m_vTextdraws.end(),
			[&it](GlobalTextDraw *elem_)
		{
			return elem_ == it->second.get();
		});

		if (vIt != m_vTextdraws.end())
			m_vTextdraws.erase(vIt);

		m_textdraws.erase(it);
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////
GlobalTextDraw* GlobalTextDrawPanel::get(std::string const & name_) const
{
	auto it = m_textdraws.find(name_);
	if (it != m_textdraws.end())
		return it->second.get();

	return nullptr;
}

////////////////////////////////////////////////////////////////////////
bool GlobalTextDrawPanel::exists(std::string const & name_) const
{
	return m_textdraws.find(name_) != m_textdraws.end();
}

////////////////////////////////////////////////////////////////////////
void GlobalTextDrawPanel::createAll(bool show_)
{
	for (auto & td : m_vTextdraws)
		td->create(show_);
}

////////////////////////////////////////////////////////////////////////
void GlobalTextDrawPanel::destroyAll()
{
	for (auto & td : m_vTextdraws)
		td->destroy();
}

////////////////////////////////////////////////////////////////////////
void GlobalTextDrawPanel::recreateAll()
{
	for (auto & td : m_vTextdraws)
		td->recreate();
}

////////////////////////////////////////////////////////////////////////
void GlobalTextDrawPanel::showAll(Player* player_)
{
	if (player_)
	{
		for (auto & td : m_vTextdraws)
			td->show(*player_);
	}
	else
	{
		for (auto & td : m_vTextdraws)
			td->showToEveryone();
	}
}

////////////////////////////////////////////////////////////////////////
void GlobalTextDrawPanel::hideAll(Player* player_)
{
	if (player_)
	{
		for (auto & td : m_vTextdraws)
			td->hide(*player_);
	}
	else
	{
		for (auto & td : m_vTextdraws)
			td->hideFromEveryone();
	}
}

////////////////////////////////////////////////////////////////////////
void GlobalTextDrawPanel::rearrange()
{
	std::sort(m_vTextdraws.begin(), m_vTextdraws.end(),
		[](GlobalTextDraw *left_, GlobalTextDraw *right_)
		{
			return left_->getLayer() < right_->getLayer();
		});
}


}
