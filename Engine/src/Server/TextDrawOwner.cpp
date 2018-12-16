#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/Server/TextDrawOwner.hpp>


namespace samp_edgengine
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename TTextDraw>
TTextDraw* TextDrawOwner<TTextDraw>::getTextDraw(Int32 handle_) const
{
	assert(handle_ >= 0);

	return (static_cast<std::size_t>(handle_) < m_textDraws.size() ? m_textDraws[handle_] : nullptr);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename TTextDraw>
void TextDrawOwner<TTextDraw>::bindTextDraw(Int32 handle_, TTextDraw& textDraw_)
{
	assert(handle_ >= 0);

	if (static_cast<std::size_t>(handle_) > m_textDraws.size())
	{
		m_textDraws.resize(((static_cast<std::size_t>(handle_) / MemoryManagementChunk) + 1) * MemoryManagementChunk, nullptr);
	}

	m_textDraws[handle_] = &textDraw_;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename TTextDraw>
void TextDrawOwner<TTextDraw>::unbindTextDraw(Int32 handle_)
{
	// # Assertion note:
	// Handle with that id does not exits! Fix your code.
	assert(handle_ >= 0 && static_cast<std::size_t>(handle_) < m_textDraws.size());

	m_textDraws[handle_] = nullptr;

	std::size_t numConsecutiveEmpty = 0;
	for (std::size_t i = m_textDraws.size(); i-- > 0; )
	{
		if (m_textDraws[i] == nullptr)
			numConsecutiveEmpty++;
		else
			break;
	}

	if (numConsecutiveEmpty > MemoryManagementChunk)
	{
		m_textDraws.resize(m_textDraws.size() - (numConsecutiveEmpty / MemoryManagementChunk) * MemoryManagementChunk);
	}
}

template class TextDrawOwner<PlayerTextDraw>;
template class TextDrawOwner<GlobalTextDraw>;

}