#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include <SAMP-EDGEngine/Ext/ResourceIO/XMLPerPlayerObjectSerializer.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLNames.hpp>

namespace samp_cpp::ext::resource_io
{

///////////////////////////////////////////////////////////////////////////
bool XMLPerPlayerObjectSerializer::serialize() const
{
	xml::xml_node<>& node = *parentNode.document()->allocate_node(xml::node_element, XMLNames::UniversalObjectNode);
	parentNode.append_node(&node);

	
	{
		xml_helper::setAttribute(node, XMLNames::Attributes::ModelIndex, std::to_string(object.getModel()), xml_helper::AllocValue);
		
		
		const_a perPlayerObject = dynamic_cast<PerPlayerObject const*>(&object);

		// # Assertion note:
		// This deserializer supports only per player objects. Fix your code.
		assert(perPlayerObject != nullptr);

		// Save world visibility mode and world index if needed:
		xml_helper::setAttribute(node, XMLNames::Attributes::WorldMode, stringifyVisibilityMode(perPlayerObject->getWorldMode()), xml_helper::DontAlloc);
		
		if (perPlayerObject->getWorldMode() != PerPlayerObject::VisibilityMode::Everywhere)
		{
			xml_helper::setAttribute(node, XMLNames::Attributes::World, std::to_string(perPlayerObject->getWorld()), xml_helper::AllocValue);
		}

		// Save interior visibility mode and interior index if needed:
		xml_helper::setAttribute(node, XMLNames::Attributes::InteriorMode, stringifyVisibilityMode(perPlayerObject->getInteriorMode()), xml_helper::DontAlloc);
		
		if (perPlayerObject->getInteriorMode() != PerPlayerObject::VisibilityMode::Everywhere)
		{
			xml_helper::setAttribute(node, XMLNames::Attributes::Interior, std::to_string(perPlayerObject->getInterior()), xml_helper::AllocValue);
		}

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

///////////////////////////////////////////////////////////////////////////
std::string_view XMLPerPlayerObjectSerializer::stringifyVisibilityMode(PerPlayerObject::VisibilityMode mode_)
{
	switch (mode_)
	{
	case PerPlayerObject::VisibilityMode::Everywhere:
		return "Everywhere";
	case PerPlayerObject::VisibilityMode::Specified:
		return "Specified";
	case PerPlayerObject::VisibilityMode::AllButSpecified:
		return "AllButSpecified";
	default:
		return "Everywhere";
	}
}

}
