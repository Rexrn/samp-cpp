#include "ResourceIOPCH.hpp"

#include <SAMP-EDGEngine-Ext/ResourceIO/XMLSceneDeserializer.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLNames.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLPerPlayerObjectDeserializer.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLGlobalObjectDeserializer.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLRemovedBuildingDeserializer.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLNames.hpp>

namespace samp_edgengine::ext::resource_io
{

////////////////////////////////////////////////////////////////
bool XMLSceneDeserializer::deserialize() const
{
	using VisMode = PerPlayerObject::VisibilityMode;

	std::optional<VisMode> forcedWorldMode, forcedInteriorMode;
	std::optional<Int32> forcedWorld, forcedInterior;

	// Deserialize world mode:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::ForceWorldMode))
	{
		forcedWorldMode = XMLPerPlayerObjectDeserializer::extractVisibilityModeFromString( xml_helper::getAttribute(sourceNode, XMLNames::Attributes::ForceWorldMode) );
	}

	// Deserialize interior mode:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::ForceInteriorMode))
	{
		forcedInteriorMode = XMLPerPlayerObjectDeserializer::extractVisibilityModeFromString(xml_helper::getAttribute(sourceNode, XMLNames::Attributes::ForceInteriorMode));
	}

	// Deserialize world index:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::ForceWorld))
	{
		auto const worldStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::ForceWorld);
		try
		{
			forcedWorld = std::stoi(worldStr);
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid (forced) world index \"" << worldStr << "\"." << std::endl;
		}
	}

	// Deserialize interior index:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::ForceInterior))
	{
		auto const interiorStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::ForceInterior);
		try
		{
			forcedInterior = std::stoi(interiorStr);
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid (forced) interior index \"" << interiorStr << "\"." << std::endl;
		}
	}

	for (auto it = sourceNode.first_node(); it; it = it->next_sibling())
	{
		std::string name = it->name();
		//std::cout << "Node name: " << it->name() << std::endl;
		if (name == XMLNames::UniversalObjectNode)
		{
			auto object = scene.beginConstruction<UniversalObject>();
			XMLPerPlayerObjectDeserializer deserializer{ *object, *it };
			if(deserializer.deserialize())
			{
				if (forcedWorldMode.has_value())
					object->setWorldMode(*forcedWorldMode);
				if (forcedInteriorMode.has_value())
					object->setInteriorMode(*forcedInteriorMode);
				if (forcedWorld.has_value())
					object->setWorld(*forcedWorld);
				if (forcedInterior.has_value())
					object->setInterior(*forcedInterior);

				scene.finalizeConstruction(object);
			}
		}
		else if (name == XMLNames::GlobalObjectNode)
		{
			auto object = scene.beginConstruction<GlobalObject>();
			XMLGlobalObjectDeserializer deserializer{ *object, *it };
			if (deserializer.deserialize())
			{
				scene.finalizeConstruction(object);
			}
		}
		else if (name == XMLNames::RemovedBuildingNode)
		{
			RemovedBuilding removedBuilding;
			XMLRemovedBuildingDeserializer deserializer{ removedBuilding, *it };
			if (deserializer.deserialize())
			{
				scene.removeBuilding(removedBuilding);
			}
		}
		// else: sorry, does not supported.
		// TODO: consider error checking and notifying.
	}

	return true;
}

}
