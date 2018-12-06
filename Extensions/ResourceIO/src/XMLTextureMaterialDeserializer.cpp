#include <SAMP-EDGEngine/Ext/ResourceIO/XMLTextureMaterialDeserializer.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLNames.hpp>

namespace samp_edgengine::ext::resource_io
{

/////////////////////////////////////////////////////////////////////////////////
bool XMLTextureMaterialDeserializer::deserialize() const
{
	// Deserialize material size:
	if ( !this->deserializeMaterialIndex() )
		return false;

	
	const_a texture = dynamic_cast<IMapObject::Texture*>(&material);

	// # Assertion note:
	// This deserialization algorithm supports only texture materials.
	assert(texture != nullptr);

	// Deserialize material model index:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::ModelIndex))
	{
		auto const modelIndexStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::ModelIndex);
		try
		{
			texture->modelIndex = std::stoi(modelIndexStr);
		}
		catch (...)
		{
			std::clog << ModuleLogPrefix << "(Warning): Invalid model index \"" << modelIndexStr << "\"." << std::endl;
		}
	}
	else
		return false;

	// Deserialize txd name:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::TxdName))
	{
		auto const txdNameStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::TxdName);
		if (!txdNameStr.empty())
			texture->txdName = txdNameStr;
		else {
			std::cerr << ModuleLogPrefix << "(Error): Empty material txd name." << std::endl;
			return false;
		}
	}
	else
		return false;

	// Deserialize texture name:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::TextureName))
	{
		auto const textureNameStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::TextureName);
		if (!textureNameStr.empty())
			texture->textureName = textureNameStr;
		else {
			std::cerr << ModuleLogPrefix << "(Error): Empty material texture name." << std::endl;
			return false;
		}
	}
	else
		return false;

	// Deserialize texture tint:
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::Tint))
	{
		auto const tintStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::Tint);
		try
		{
			texture->color = Color{ static_cast<Uint32>( std::stoul(tintStr, nullptr, 16) ) };
		}
		catch (...)
		{
			std::cerr << ModuleLogPrefix << "(Error): Invalid material texture tint: \"" << tintStr << "\"." << std::endl;
			return false;
		}
	}
	else
		return false;
	
	return true;
}

}
