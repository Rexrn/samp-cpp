#include <SAMP-EDGEngine/Ext/ResourceIO/XMLRemovedBuildingSerializer.hpp>

#include <SAMP-EDGEngine/Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLNames.hpp>

namespace samp_edgengine::ext::resource_io
{

//////////////////////////////////////////////////////////////////////////////
bool XMLRemovedBuildingSerializer::serialize() const
{
	xml::xml_node<>& node = *parentNode.document()->allocate_node(xml::node_element, XMLNames::RemovedBuildingNode);
	parentNode.append_node(&node);

	{
		const_a modelIndex	= removedBuilding.model;
		const_a radius		= removedBuilding.radius.value;
		const_a origin		= removedBuilding.origin;
		xml_helper::setAttribute(node, XMLNames::Attributes::ModelIndex,	std::to_string(modelIndex), xml_helper::AllocValue);
		xml_helper::setAttribute(node, XMLNames::Attributes::Radius,		std::to_string(radius),		xml_helper::AllocValue);
		xml_helper::setAttribute(node, XMLNames::Attributes::OriginX,		std::to_string(origin.x),	xml_helper::AllocValue);
		xml_helper::setAttribute(node, XMLNames::Attributes::OriginY,		std::to_string(origin.y),	xml_helper::AllocValue);
		xml_helper::setAttribute(node, XMLNames::Attributes::OriginZ,		std::to_string(origin.z),	xml_helper::AllocValue);
	}

	return true;
}

}
