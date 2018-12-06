#include <SAMP-EDGEngine/Ext/ResourceIO/XMLMapObjectMaterialDeserializer.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLNames.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/Logging.hpp>

#include <iostream>

namespace samp_edgengine::ext::resource_io
{

/////////////////////////////////////////////////////////////////////////////////
bool XMLMapObjectMaterialDeserializer::deserializeMaterialIndex() const
{
	// Deserialize material size:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::MaterialIndex))
	{
		auto const indexStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::MaterialIndex);
		bool exceptionOccurred = false;
		try
		{
			materialIndex = std::stoi(indexStr);
		}
		catch (...)
		{
			exceptionOccurred = true;
		}

		if (exceptionOccurred || materialIndex < 0 || materialIndex > 15)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid material index \"" << indexStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;

	return true;
}

}
