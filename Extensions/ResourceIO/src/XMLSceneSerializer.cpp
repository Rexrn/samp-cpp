#include SAMPCPP_EXT_RESOURCEIO_PCH

#include <SAMPCpp/Ext/ResourceIO/XMLSceneSerializer.hpp>
#include <SAMPCpp/Ext/ResourceIO/XMLNames.hpp>

#include <SAMPCpp/Ext/ResourceIO/XMLPerPlayerObjectSerializer.hpp>
#include <SAMPCpp/Ext/ResourceIO/XMLGlobalObjectSerializer.hpp>
#include <SAMPCpp/Ext/ResourceIO/XMLRemovedBuildingSerializer.hpp>


namespace samp_cpp::ext::resource_io
{

////////////////////////////////////////////////////////////
bool XMLSceneSerializer::serialize() const
{
	char*				sceneName		= parentNode.document()->allocate_string(XMLNames::MapSceneNode);
	xml::xml_node<>*	sceneRootNode	= parentNode.document()->allocate_node(xml::node_element, sceneName);
	parentNode.append_node(sceneRootNode);

	if (sceneRootNode)
	{
		for (auto const & removedBuilding : scene.getRemovedBuildings())
		{
			XMLRemovedBuildingSerializer serializer{ removedBuilding, *sceneRootNode };
			if (serializer.serialize())
			{
				// TODO: what to do now?
			}
		}

		for (auto const & object : scene.getObjects())
		{
			if (const_a universal = dynamic_cast<UniversalObject const*>(object))
			{
				XMLPerPlayerObjectSerializer serializer{ *universal, *sceneRootNode };
				if (serializer.serialize())
				{
					// TODO: what to do now?
				}
			}
			else if (const_a global = dynamic_cast<GlobalObject const*>(object))
			{
				XMLGlobalObjectSerializer serializer{ *global, *sceneRootNode };
				if (serializer.serialize())
				{
					// TODO: what to do now?
				}
			}
			// else: sorry, can't now.
			// TODO: some error checking and notifying.
		}
		
	}
	else
		return false;

	return true;
}


}
