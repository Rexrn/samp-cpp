#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include <SAMP-EDGEngine/Ext/ResourceIO/XMLRemovedBuildingDeserializer.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLNames.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/Logging.hpp>

#include <iostream>

namespace samp_cpp::ext::resource_io
{

//////////////////////////////////////////////////////////////////////////////
bool XMLRemovedBuildingDeserializer::deserialize() const
{
	// Deserialize model index:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::ModelIndex))
	{
		auto const modelIndexStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::ModelIndex);
		try
		{
			removedBuilding.model = std::stoi(modelIndexStr);
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid model index \"" << modelIndexStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;

	// Deserialize radius:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::Radius))
	{
		auto const radius = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::Radius);
		if (radius != "Default")
		{
			try
			{
				removedBuilding.radius = std::stof(radius);
			}
			catch (...)
			{
				std::cerr << ModuleLogPrefix << "(Error): Invalid radius \"" << radius << "\"." << std::endl;
			}
		}
	}

	// Deserialize origin:
	math::Vector3f origin;

	// Deserialize 'x' component of the origin:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::OriginX))
	{
		auto const originXStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::OriginX);
		try
		{
			origin.x = std::stof(originXStr);
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid 'x' component of the origin \"" << originXStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;

	// Deserialize 'y' component of the origin:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::OriginY))
	{
		auto const originYStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::OriginY);
		try
		{
			origin.y = std::stof(originYStr);
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid 'y' component of the origin \"" << originYStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;

	// Deserialize 'z' component of the origin:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::OriginZ))
	{
		auto const originZStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::OriginZ);
		try
		{
			origin.z = std::stof(originZStr);
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid 'z' component of the origin \"" << originZStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;

	removedBuilding.origin = origin;

	return true;
}

}
