#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include "Serializer.hpp"

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// An interface to every XML serialization algorithm.
/// </summary>
struct IXMLSerializer
	: virtual ISerializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="IXMLSerializer" /> struct.
	/// </summary>
	/// <param name="parentNode_">The parent node.</param>
	IXMLSerializer(xml::xml_node<> &parentNode_)
		: parentNode{ parentNode_ }
	{
	}

	// Serializer will create a child node of this one
	xml::xml_node<>& parentNode;
};

}