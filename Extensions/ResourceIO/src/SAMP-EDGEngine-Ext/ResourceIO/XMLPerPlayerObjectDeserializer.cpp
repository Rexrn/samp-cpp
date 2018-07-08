#include "ResourceIOPCH.hpp"

#include <SAMP-EDGEngine-Ext/ResourceIO/XMLPerPlayerObjectDeserializer.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLNames.hpp>

namespace samp_edgengine::ext::resource_io
{

///////////////////////////////////////////////////////////////////////////
bool XMLPerPlayerObjectDeserializer::deserialize() const
{
	if (!this->deserializeModelIndex())
		return false;

	const_a perPlayerObject = dynamic_cast<PerPlayerObject*>(&object);

	// # Assertion note:
	// This deserializer supports only per player objects. Fix your code.
	assert(perPlayerObject != nullptr);

	// Deserialize world mode:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::WorldMode))
	{
		perPlayerObject->setWorldMode( extractVisibilityModeFromString( xml_helper::getAttribute(sourceNode, XMLNames::Attributes::WorldMode) ) );
	}

	// Deserialize interior mode:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::InteriorMode))
	{
		perPlayerObject->setInteriorMode( extractVisibilityModeFromString(xml_helper::getAttribute(sourceNode, XMLNames::Attributes::InteriorMode)) );
	}

	// Deserialize world index:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::World))
	{
		auto const worldStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::World);
		try
		{
			perPlayerObject->setWorld( std::stoi(worldStr) );
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid world index \"" << worldStr << "\"." << std::endl;
		}
	}

	// Deserialize interior index:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::Interior))
	{
		auto const interiorStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::Interior);
		try
		{
			perPlayerObject->setInterior( std::stoi(interiorStr) );
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid interior index \"" << interiorStr << "\"." << std::endl;
		}
	}

	this->deserializeDrawDistance();

	if (!this->deserializeLocation())
		return false;

	if (!this->deserializeRotation())
		return false;

	this->deserializeMaterials();

	return true;
}

///////////////////////////////////////////////////////////////////////////
PerPlayerObject::VisibilityMode XMLPerPlayerObjectDeserializer::extractVisibilityModeFromString(std::string_view string_)
{
	using VisibilityMode = PerPlayerObject::VisibilityMode;

	// Note: this function is error friendly. Do not make spelling error.
	if (string_ == "Everywhere")
		return VisibilityMode::Everywhere;
	if (string_ == "AllButSpecified")
		return VisibilityMode::AllButSpecified;
	if (string_ == "Specified")
		return VisibilityMode::Specified;

	return VisibilityMode::Everywhere;
}

}
