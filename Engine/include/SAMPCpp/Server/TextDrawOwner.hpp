#pragma once
#include SAMPCPP_PCH



#include <SAMPCpp/Server/TextDraw.hpp>
#include <SAMPCpp/Server/PlayerTextDraw.hpp>
#include <SAMPCpp/Server/GlobalTextDraw.hpp>

namespace samp_cpp
{

template <typename TTextDraw>
class TextDrawOwner
{
public:
	static_assert(std::is_base_of_v<ITextDraw, TTextDraw>, "Template parameter must be a class that derive from ITextDraw!");

	/// <summary>
	/// Returns pointer to the textdraw, or nullptr if textdraw with this id is not bound.
	/// </summary>
	/// <param name="handle_">The handle.</param>
	/// <returns>Pointer to the textdraw, or nullptr if textdraw with this id is not bound.</returns>
	TTextDraw * getTextDraw(Int32 handle_) const;



	/// <summary>
	/// Returns vector of pointers to textdraws. Some may be nullptr.
	/// </summary>
	/// <returns>vector of pointers to textdraws.</returns>
	std::vector<TTextDraw*> getTextDrawsAllowNull() const {
		return m_textDraws;
	}

	friend TTextDraw;
private:
	constexpr static std::size_t MemoryManagementChunk = 64; // Store chunks of this amount when storing text draws. It optimizes performance.

	/// <summary>
	/// Binds the textdraw to specified handle.
	/// </summary>
	/// <param name="handle_">The handle.</param>
	/// <param name="textDraw_">The textdraw.</param>
	void bindTextDraw(Int32 handle_, TTextDraw& textDraw_);

	/// <summary>
	/// Unbinds the textdraw from specified handle.
	/// </summary>
	/// <param name="handle_">The handle.</param>
	void unbindTextDraw(Int32 handle_);

	std::vector<TTextDraw*> m_textDraws;
};

}
