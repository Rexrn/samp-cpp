#include "ResourceIOPCH.hpp"

#include <SAMP-EDGEngine-Ext/ResourceIO/XMLTextMaterialSerializer.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLNames.hpp>

namespace samp_edgengine::ext::resource_io
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool XMLTextMaterialSerializer::serialize() const
{
	xml::xml_node<>& node = *parentNode.document()->allocate_node( xml::node_element, XMLNames::TextMaterialNode );
	parentNode.append_node( &node );

	const_a textMaterial = dynamic_cast<IMapObject::Text const*>(&material);

	// # Assertion note:
	// This serializer supports only text materials. Fix your code.
	assert(textMaterial != nullptr);

	xml_helper::setAttribute(node, XMLNames::Attributes::MaterialIndex, std::to_string(materialIndex),							xml_helper::AllocValue);
	xml_helper::setAttribute(node, XMLNames::Attributes::TextContent,	textMaterial->text,										xml_helper::AllocValue);
	xml_helper::setAttribute(node, XMLNames::Attributes::MaterialSize,	std::to_string(textMaterial->size),						xml_helper::AllocValue);
	xml_helper::setAttribute(node, XMLNames::Attributes::FontFace,		textMaterial->font,										xml_helper::AllocValue);
	xml_helper::setAttribute(node, XMLNames::Attributes::FontSize,		std::to_string(textMaterial->fontSize),					xml_helper::AllocValue);
	xml_helper::setAttribute(node, XMLNames::Attributes::Bold,			std::to_string(static_cast<Int32>(textMaterial->bold)),	xml_helper::AllocValue);
	xml_helper::setAttribute(node, XMLNames::Attributes::FontColor,		"0x" + textMaterial->fontColor.toRGBAString(),			xml_helper::AllocValue);
	xml_helper::setAttribute(node, XMLNames::Attributes::BackColor,		"0x" + textMaterial->backColor.toRGBAString(),			xml_helper::AllocValue);
	xml_helper::setAttribute(node, XMLNames::Attributes::TextAlign,		stringifyTextAlign(textMaterial->textAlign),			xml_helper::DontAlloc);

	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string_view XMLTextMaterialSerializer::stringifyTextAlign(IMapObject::Text::TextAlign align_)
{
	using TextAlign = IMapObject::Text::TextAlign;
	switch (align_)
	{
	case TextAlign::Left:	return "Left";
	case TextAlign::Center: return "Center";
	case TextAlign::Right:	return "Right";
	default:				return "Left";
	}
}

}
