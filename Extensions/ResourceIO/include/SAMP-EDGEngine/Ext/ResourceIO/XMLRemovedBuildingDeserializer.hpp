#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include "XMLDeserializer.hpp"
#include "RemovedBuildingDeserializer.hpp"

namespace samp_cpp::ext::resource_io
{

/// <summary>
/// A <see cref="RemovedBuilding"/> XML deserialization algorithm.
/// </summary>
struct XMLRemovedBuildingDeserializer
	:
	IXMLDeserializer,
	IRemovedBuildingDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLRemovedBuildingDeserializer" /> struct.
	/// </summary>
	/// <param name="removedBuilding_">The removed building.</param>
	/// <param name="sourceNode_">The source node.</param>
	XMLRemovedBuildingDeserializer(RemovedBuilding & removedBuilding_, xml::xml_node<> &sourceNode_)
		:
		IXMLDeserializer{ sourceNode_ },
		IRemovedBuildingDeserializer{ removedBuilding_ }
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