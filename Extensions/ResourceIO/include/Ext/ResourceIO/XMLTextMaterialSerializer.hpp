#pragma once

#include "XMLMapObjectMaterialSerializer.hpp"

#include <string_view>

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// A XML <see cref="TextMaterial"/> serialization algorithm.
/// </summary>
struct XMLTextMaterialSerializer
	: XMLMapObjectMaterialSerializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLTextMaterialSerializer" /> struct.
	/// </summary>
	/// <param name="material_">The serialized material.</param>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="parentNode_">The parent node.</param>
	XMLTextMaterialSerializer(IMapObject::IMaterial const& material_, Uint8 materialIndex_, xml::xml_node<>& parentNode_)
		: XMLMapObjectMaterialSerializer{ material_, materialIndex_, parentNode_ }
	{
	}

	/// <summary>
	/// Performs serialization with given setup.
	/// </summary>
	/// <returns>
	///		<c>true</c> if serialization succeeded; otherwise, <c>false</c>.
	/// </returns>
	virtual bool serialize() const override;

protected:
	/// <summary>
	/// Returns string representation of the given text alignment.
	/// </summary>
	/// <param name="align_">The object type.</param>
	/// <returns>
	///		String representation of the given text alignment.
	/// </returns>
	static std::string_view stringifyTextAlign(IMapObject::Text::TextAlign align_);
};

}