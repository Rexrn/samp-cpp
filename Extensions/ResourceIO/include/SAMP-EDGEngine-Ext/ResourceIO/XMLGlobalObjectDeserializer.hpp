#pragma once

#include SAMP_EDGENGINE_EXT_RESOURCEIO_PCH

#include <SAMP-EDGEngine-Ext/ResourceIO/XMLMapObjectDeserializer.hpp>

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// A XML <see cref="IMapObject"/> deserialization algorithm.
/// </summary>
struct XMLGlobalObjectDeserializer
	: XMLMapObjectDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLGlobalObjectDeserializer" /> struct.
	/// </summary>
	/// <param name="object_">The deserialized object.</param>
	/// <param name="sourceNode_">The source node.</param>
	XMLGlobalObjectDeserializer(IMapObject& object_, xml::xml_node<> const& sourceNode_)
		:
		XMLMapObjectDeserializer{ object_, sourceNode_ }
	{
	}
	
	/// <summary>
	/// Performs deserialization with given setup.
	/// </summary>
	/// <returns>
	///		<c>true</c> if deserialization succeeded; otherwise, <c>false</c>.
	/// </returns>
	virtual bool deserialize() const override;
};

}