#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include "XMLMapObjectDeserializer.hpp"

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// A <see cref="PerPlayerObject"/> XML deserialization algorithm.
/// </summary>
struct XMLPerPlayerObjectDeserializer
	: XMLMapObjectDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLPerPlayerObjectDeserializer" /> struct.
	/// </summary>
	/// <param name="object_">The deserialized object.</param>
	/// <param name="sourceNode_">The source node.</param>
	XMLPerPlayerObjectDeserializer(IMapObject& object_, xml::xml_node<> const& sourceNode_)
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

	/// <summary>
	/// Extracts the visibility mode from string.
	/// </summary>
	/// <param name="string_">The string.</param>
	/// <returns>
	///		Extracted visibility mode from given string.
	/// </returns>
	static PerPlayerObject::VisibilityMode extractVisibilityModeFromString(std::string_view string_);
};

}