#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include "XMLMapObjectSerializer.hpp"

namespace samp_cpp::ext::resource_io
{

/// <summary>
/// A <see cref="GlobalObject"/> XML serialization algorithm.
/// </summary>
struct XMLGlobalObjectSerializer
	: XMLMapObjectSerializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLGlobalObjectSerializer" /> struct.
	/// </summary>
	/// <param name="object_">The serialized object.</param>
	/// <param name="parentNode_">The parent node.</param>
	XMLGlobalObjectSerializer(IMapObject const& object_, xml::xml_node<>& parentNode_)
		: XMLMapObjectSerializer{ object_, parentNode_ }
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