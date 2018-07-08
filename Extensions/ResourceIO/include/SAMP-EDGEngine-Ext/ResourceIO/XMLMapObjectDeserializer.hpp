#pragma once

#include SAMP_EDGENGINE_EXT_RESOURCEIO_PCH

#include <SAMP-EDGEngine-Ext/ResourceIO/XMLDeserializer.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/MapObjectDeserializer.hpp>

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// A XML <see cref="IMapObject"/> deserialization algorithm.
/// </summary>
struct XMLMapObjectDeserializer
	:
	IXMLDeserializer,
	IMapObjectDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLMapObjectDeserializer" /> struct.
	/// </summary>
	/// <param name="object_">The deserialized object.</param>
	/// <param name="sourceNode_">The source node.</param>
	XMLMapObjectDeserializer(IMapObject& object_, xml::xml_node<> const& sourceNode_)
		:
		IXMLDeserializer{ sourceNode_ },
		IMapObjectDeserializer{ object_ }
	{
	}

protected:

	/// <summary>
	/// Deserializes the index of the model.
	/// </summary>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	bool deserializeModelIndex() const;

	/// <summary>
	/// Deserializes the draw distance.
	/// </summary>
	void deserializeDrawDistance() const;

	/// <summary>
	/// Deserializes the location.
	/// </summary>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	bool deserializeLocation() const;

	/// <summary>
	/// Deserializes the rotation.
	/// </summary>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	bool deserializeRotation() const;

	/// <summary>
	/// Deserializes the materials.
	/// </summary>
	void deserializeMaterials() const;
};

}