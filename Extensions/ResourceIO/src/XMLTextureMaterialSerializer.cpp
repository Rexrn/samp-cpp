#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include <SAMP-EDGEngine/Ext/ResourceIO/XMLTextureMaterialSerializer.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/XMLNames.hpp>

namespace samp_edgengine::ext::resource_io
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool XMLTextureMaterialSerializer::serialize() const
{
	xml::xml_node<>& node = *parentNode.document()->allocate_node( xml::node_element, XMLNames::TextureMaterialNode );
	parentNode.append_node(&node);

	const_a textureMaterial = dynamic_cast<IMapObject::Texture const*>(&material);

	// # Assertion note:
	// This serializer supports only texture materials. Fix your code.
	assert(textureMaterial != nullptr);

	xml_helper::setAttribute(node, XMLNames::Attributes::MaterialIndex,	std::to_string(materialIndex),					xml_helper::AllocValue);
	xml_helper::setAttribute(node, XMLNames::Attributes::ModelIndex,	std::to_string(textureMaterial->modelIndex),	xml_helper::AllocValue);
	xml_helper::setAttribute(node, XMLNames::Attributes::TxdName,		textureMaterial->txdName,						xml_helper::AllocValue);
	xml_helper::setAttribute(node, XMLNames::Attributes::TextureName,	textureMaterial->textureName,					xml_helper::AllocValue);
	xml_helper::setAttribute(node, XMLNames::Attributes::Tint,			"0x" + textureMaterial->color.toRGBAString(),	xml_helper::AllocValue);

	return true;
}

}
