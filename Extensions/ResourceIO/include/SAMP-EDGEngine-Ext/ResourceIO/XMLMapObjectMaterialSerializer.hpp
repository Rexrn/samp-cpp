#pragma once

#include SAMP_EDGENGINE_EXT_RESOURCEIO_PCH

#include <SAMP-EDGEngine-Ext/ResourceIO/XMLSerializer.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/MapObjectMaterialSerializer.hpp>

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// An interface to XML map object material serialization algorithm.
/// </summary>
struct XMLMapObjectMaterialSerializer
	:
	IXMLSerializer,
	IMapObjectMaterialSerializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLMapObjectMaterialSerializer" /> struct.
	/// </summary>
	/// <param name="material_">The serialized material.</param>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="parentNode_">The parent node.</param>
	XMLMapObjectMaterialSerializer(IMapObject::IMaterial const& material_, Uint8 materialIndex_, xml::xml_node<>& parentNode_)
		:
		IXMLSerializer{ parentNode_ },
		IMapObjectMaterialSerializer{ material_, materialIndex_ }
	{
	}
};

}
