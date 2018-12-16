#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH



#include "XMLMapObjectMaterialSerializer.hpp"

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// A XML <see cref="TextureMaterial"/> serialization algorithm.
/// </summary>
struct XMLTextureMaterialSerializer
	: XMLMapObjectMaterialSerializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLTextureMaterialSerializer" /> struct.
	/// </summary>
	/// <param name="material_">The serialized material.</param>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="parentNode_">The parent node.</param>
	XMLTextureMaterialSerializer(IMapObject::IMaterial const& material_, Uint8 materialIndex_, xml::xml_node<>& parentNode_)
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
};

}