#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include "Deserializer.hpp"

namespace samp_cpp::ext::resource_io
{

/// <summary>
/// An interface to every XML deserialization algorithm.
/// </summary>
struct IXMLDeserializer
	: virtual IDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="IXMLDeserializer" /> struct.
	/// </summary>
	/// <param name="parentNode_">The source node.</param>
	IXMLDeserializer(xml::xml_node<> const &sourceNode_)
		: sourceNode{ sourceNode_ }
	{
	}

	// Information will be gathered from this node:
	xml::xml_node<> const& sourceNode;
};

}
