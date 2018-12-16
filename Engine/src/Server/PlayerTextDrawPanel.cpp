#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/Server/PlayerTextDrawPanel.hpp>

namespace samp_edgengine
{

////////////////////////////////////////////////////////////////////////
PlayerTextDrawPanel::PlayerTextDrawPanel(Player& owner_)
	: m_owner{ owner_ }
{
}

////////////////////////////////////////////////////////////////////////
PlayerTextDrawPanel::~PlayerTextDrawPanel()
{
}

////////////////////////////////////////////////////////////////////////
PlayerTextDraw& PlayerTextDrawPanel::finalizeConstruction(std::string const & name_, ObjectPtrType< PlayerTextDraw > const& textDraw_)
{
	m_textdraws[ name_ ] = textDraw_;
	m_vTextdraws.push_back(textDraw_.get());
	return *textDraw_;
}

////////////////////////////////////////////////////////////////////////
bool PlayerTextDrawPanel::remove(std::string const & name_)
{
	auto it = m_textdraws.find( name_ );
	if (it != m_textdraws.end())
	{
		auto vIt = std::find_if(m_vTextdraws.begin(), m_vTextdraws.end(),
			[&it](PlayerTextDraw *elem_)
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
PlayerTextDraw* PlayerTextDrawPanel::get(std::string const & name_) const
{
	auto it = m_textdraws.find( name_ );
	if (it != m_textdraws.end())
		return it->second.get();

	return nullptr;
}

////////////////////////////////////////////////////////////////////////
bool PlayerTextDrawPanel::exists(std::string const & name_) const
{
	return m_textdraws.find( name_ ) != m_textdraws.end();
}

////////////////////////////////////////////////////////////////////////
void PlayerTextDrawPanel::createAll(bool show_)
{
	for (auto & td : m_vTextdraws)
		td->create(show_);
}

////////////////////////////////////////////////////////////////////////
void PlayerTextDrawPanel::destroyAll()
{
	for (auto & td : m_vTextdraws)
		td->destroy();
}

////////////////////////////////////////////////////////////////////////
void PlayerTextDrawPanel::recreateAll()
{
	for (auto & td : m_vTextdraws)
		td->recreate();
}

////////////////////////////////////////////////////////////////////////
void PlayerTextDrawPanel::showAll()
{
	for (auto & td : m_vTextdraws)
		td->show();
}

////////////////////////////////////////////////////////////////////////
void PlayerTextDrawPanel::hideAll()
{
	for (auto & td : m_vTextdraws)
		td->hide();
}

////////////////////////////////////////////////////////////////////////
bool PlayerTextDrawPanel::isShown(std::string const & name_) const
{
	if (auto td = this->get(name_))
		return td->isShown();

	return false;
}

////////////////////////////////////////////////////////////////////////
void PlayerTextDrawPanel::rearrange()
{
	std::sort(m_vTextdraws.begin(), m_vTextdraws.end(),
		[](PlayerTextDraw *left_, PlayerTextDraw *right_)
		{
			return left_->getLayer() < right_->getLayer();
		});
}


}
