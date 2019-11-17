#include SAMPCPP_EXT_RESOURCEIO_PCH

#include <SAMPCpp/Ext/ResourceIO/XMLMapObjectDeserializer.hpp>
#include <SAMPCpp/Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMPCpp/Ext/ResourceIO/XMLNames.hpp>

#include <SAMPCpp/Ext/ResourceIO/XMLTextMaterialDeserializer.hpp>
#include <SAMPCpp/Ext/ResourceIO/XMLTextureMaterialDeserializer.hpp>
#include <SAMPCpp/Ext/ResourceIO/Logging.hpp>

#include <iostream>

namespace samp_cpp::ext::resource_io
{

/////////////////////////////////////////////////////////////////////
bool XMLMapObjectDeserializer::deserializeModelIndex() const
{
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::ModelIndex))
	{
		auto const modelIndexStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::ModelIndex);
		try
		{
			object.setModel(std::stoi(modelIndexStr));
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid model index \"" << modelIndexStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;

	return true;
}

/////////////////////////////////////////////////////////////////////
void XMLMapObjectDeserializer::deserializeDrawDistance() const
{
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::DrawDistance))
	{
		auto const drawDistanceStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::DrawDistance);
		if (drawDistanceStr != "Default")
		{
			try
			{
				object.setDrawDistance(std::stof(drawDistanceStr));
			}
			catch (...)
			{
				std::cerr << ModuleLogPrefix << "(Error): Invalid draw distance \"" << drawDistanceStr << "\"." << std::endl;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////
bool XMLMapObjectDeserializer::deserializeLocation() const
{
	math::Vector3f location;

	// Deserialize 'x' component of the location:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::LocX))
	{
		auto const locXStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::LocX);
		try
		{
			location.x = std::stof(locXStr);
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid 'x' component of the location \"" << locXStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;

	// Deserialize 'y' component of the location:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::LocY))
	{
		auto const locYStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::LocY);
		try
		{
			location.y = std::stof(locYStr);
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid 'y' component of the location \"" << locYStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;

	// Deserialize 'z' component of the location:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::LocZ))
	{
		auto const locZStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::LocZ);
		try
		{
			location.z = std::stof(locZStr);
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid 'z' component of the location \"" << locZStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;

	object.setLocation(location);

	return true;
}

/////////////////////////////////////////////////////////////////////
bool XMLMapObjectDeserializer::deserializeRotation() const
{
	math::Vector3f rotation;

	// Deserialize 'x' component of the rotation:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::RotX))
	{
		auto const rotXStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::RotX);
		try
		{
			rotation.x = std::stof(rotXStr);
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid 'x' component of the rotation \"" << rotXStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;

	// Deserialize 'y' component of the rotation:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::RotY))
	{
		auto const rotYStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::RotY);
		try
		{
			rotation.y = std::stof(rotYStr);
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid 'y' component of the rotation \"" << rotYStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;

	// Deserialize 'z' component of the rotation:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::RotZ))
	{
		auto const rotZStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::RotZ);
		try
		{
			rotation.z = std::stof(rotZStr);
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid 'z' component of the rotation \"" << rotZStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;

	object.setRotation(rotation);

	return true;
}

/////////////////////////////////////////////////////////////////////
void XMLMapObjectDeserializer::deserializeMaterials() const
{
	std::vector<Uint8> isMaterialOccupied(IMapObject::MaxMaterialCount, 0);

	for(auto it = sourceNode.first_node(); it; it = it->next_sibling())
	{
		std::string name = it->name();
		if (name == XMLNames::TextMaterialNode)
		{
			IMapObject::Text			material;
			Uint8						materialIndex = 0;
			XMLTextMaterialDeserializer deserializer{ material, materialIndex, *it };

			if (deserializer.deserialize())
			{
				if (isMaterialOccupied[materialIndex] == 0)
				{
					isMaterialOccupied[materialIndex] = 1;
					object.setMaterial(materialIndex, material);
				}
			}
			
		}
		else if (name == XMLNames::TextureMaterialNode)
		{
			IMapObject::Texture				material;
			Uint8							materialIndex = 0;
			XMLTextureMaterialDeserializer	deserializer{ material, materialIndex, *it };

			if (deserializer.deserialize())
			{
				if (isMaterialOccupied[ materialIndex ] == 0)
				{
					isMaterialOccupied[ materialIndex ] = 1;
					object.setMaterial(materialIndex, material);
				}
			}
		}
	}
}

}
