#pragma once

#include SAMP_EDGENGINE_EXT_RESOURCEIO_PCH

#include <SAMP-EDGEngine-Ext/ResourceIO/XMLSerializer.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/MapObjectSerializer.hpp>

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// A XML <see cref="IMapObject"/> serialization algorithm.
/// </summary>
struct XMLMapObjectSerializer
	:
	IXMLSerializer,
	IMapObjectSerializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLMapObjectSerializer" /> struct.
	/// </summary>
	/// <param name="object_">The serialized object.</param>
	/// <param name="parentNode_">The parent node.</param>
	XMLMapObjectSerializer(IMapObject const& object_, xml::xml_node<>& parentNode_)
		:
		IXMLSerializer{ parentNode_ },
		IMapObjectSerializer{ object_ }
	{
	}

protected:
	
	/// <summary>
	/// Serializes the materials.
	/// </summary>
	void serializeMaterials(xml::xml_node<>& node_) const;

	/// <summary>
	/// Returns string representation of the given object type.
	/// </summary>
	/// <param name="type_">The object type.</param>
	/// <returns>
	///		String representation of the given object type.
	/// </returns>
	static std::string_view stringifyType(IMapObject::Type type_);
};

}