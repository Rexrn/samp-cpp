#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include <SAMP-EDGEngine/Ext/ResourceIO/XMLMapObjectSerializer.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLNames.hpp>

#include <SAMP-EDGEngine/Ext/ResourceIO/XMLMapObjectMaterialSerializer.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLTextureMaterialSerializer.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLTextMaterialSerializer.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/Logging.hpp>

#include <iostream>

namespace samp_edgengine::ext::resource_io
{

////////////////////////////////////////////////////////////////////////////////////////////////
void XMLMapObjectSerializer::serializeMaterials(xml::xml_node<>& node_) const
{
	auto const& materials = object.getMaterials();
	for (std::size_t i = 0; i < materials.size(); i++)
	{
		// # Assertion note:
		// There is code inconsistency which allows settings a material with index >= MaxMaterialCount. Fix your code.
		assert(i < IMapObject::MaxMaterialCount);

		if (materials[i])
		{
			if (const_a textMat = dynamic_cast<IMapObject::Text*>(materials[i].get()))
			{
				XMLTextMaterialSerializer serializer{ *materials[i], static_cast<Uint8>( i ), node_ };

				if (!serializer.serialize())
				{
					std::clog << ModuleLogPrefix << "(Warning): Failed to serialize text material #" << i << "." << std::endl;
				}
			}
			else if (const_a textureMat = dynamic_cast<IMapObject::Texture*>(materials[i].get()))
			{
				XMLTextureMaterialSerializer serializer{ *materials[i], static_cast<Uint8>( i ), node_ };

				if (!serializer.serialize())
				{
					std::clog << ModuleLogPrefix << "(Warning): Failed to serialize texture material #" << i << "." << std::endl;
				}
			}			
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
std::string_view XMLMapObjectSerializer::stringifyType(IMapObject::Type type_)
{
	switch (type_)
	{
	case IMapObject::Global:	return "Global";
	case IMapObject::Personal:	return "Personal";
	case IMapObject::Universal: return "Universal";
	default: return "Unknown";
	}
}

}
