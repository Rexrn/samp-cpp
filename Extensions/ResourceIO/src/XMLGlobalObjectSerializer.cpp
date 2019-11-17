#include SAMPCPP_EXT_RESOURCEIO_PCH

#include <SAMPCpp/Ext/ResourceIO/XMLGlobalObjectSerializer.hpp>
#include <SAMPCpp/Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMPCpp/Ext/ResourceIO/XMLNames.hpp>

namespace samp_cpp::ext::resource_io
{

///////////////////////////////////////////////////////////////////////////
bool XMLGlobalObjectSerializer::serialize() const
{
	xml::xml_node<>& node = *parentNode.document()->allocate_node(xml::node_element, XMLNames::GlobalObjectNode);
	parentNode.append_node(&node);

	{
		xml_helper::setAttribute(node, XMLNames::Attributes::ModelIndex, std::to_string(object.getModel()), xml_helper::AllocValue);

		if (object.getDrawDistance() > 0.001f)
		{
			xml_helper::setAttribute(node, XMLNames::Attributes::DrawDistance, std::to_string(object.getDrawDistance()), xml_helper::AllocValue);
		}

		const_a location = object.getLocation();
		const_a rotation = object.getRotation();

		xml_helper::setAttribute(node, XMLNames::Attributes::LocX, std::to_string(location.x), xml_helper::AllocValue);
		xml_helper::setAttribute(node, XMLNames::Attributes::LocY, std::to_string(location.y), xml_helper::AllocValue);
		xml_helper::setAttribute(node, XMLNames::Attributes::LocZ, std::to_string(location.z), xml_helper::AllocValue);
		xml_helper::setAttribute(node, XMLNames::Attributes::RotX, std::to_string(rotation.x), xml_helper::AllocValue);
		xml_helper::setAttribute(node, XMLNames::Attributes::RotY, std::to_string(rotation.y), xml_helper::AllocValue);
		xml_helper::setAttribute(node, XMLNames::Attributes::RotZ, std::to_string(rotation.z), xml_helper::AllocValue);
	}

	this->serializeMaterials( node );

	return true;
}

}
