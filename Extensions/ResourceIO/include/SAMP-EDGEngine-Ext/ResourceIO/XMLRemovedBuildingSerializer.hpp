#pragma once

#include SAMP_EDGENGINE_EXT_RESOURCEIO_PCH

#include <SAMP-EDGEngine-Ext/ResourceIO/XMLSerializer.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/RemovedBuildingSerializer.hpp>

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// A <see cref="RemovedBuilding"/> XML serialization algorithm.
/// </summary>
struct XMLRemovedBuildingSerializer
	:
	IXMLSerializer,
	IRemovedBuildingSerializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLRemovedBuildingSerializer" /> struct.
	/// </summary>
	/// <param name="removedBuilding_">The removed building.</param>
	/// <param name="parentNode_">The parent node.</param>
	XMLRemovedBuildingSerializer(RemovedBuilding const& removedBuilding_, xml::xml_node<>& parentNode_)
		:
		IXMLSerializer{ parentNode_ },
		IRemovedBuildingSerializer{ removedBuilding_ }
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
