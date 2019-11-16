#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include "XMLMapObjectMaterialDeserializer.hpp"

namespace samp_cpp::ext::resource_io
{

/// <summary>
/// A XML <see cref="TextMaterial"/> deserialization algorithm.
/// </summary>
struct XMLTextMaterialDeserializer
	: XMLMapObjectMaterialDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLTextMaterialDeserializer" /> struct.
	/// </summary>
	/// <param name="material_">The deserialized material.</param>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="sourceNode_">The source node.</param>
	XMLTextMaterialDeserializer(IMapObject::IMaterial& material_, Uint8 &materialIndex_, xml::xml_node<> const& sourceNode_)
		:
		XMLMapObjectMaterialDeserializer{ material_, materialIndex_, sourceNode_ }
	{
	}
	
	/// <summary>
	/// Performs deserialization with given setup.
	/// </summary>
	/// <returns>
	///		<c>true</c> if deserialization succeeded; otherwise, <c>false</c>.
	/// </returns>
	virtual bool deserialize() const override;

protected:
	/// <summary>
	/// Extracts the text alignment from string.
	/// </summary>
	/// <param name="string_">The string.</param>
	/// <returns>
	///		Extracted text alignment from given string.
	/// </returns>
	static IMapObject::Text::TextAlign extractTextAlignFromString(std::string_view string_);
};

}