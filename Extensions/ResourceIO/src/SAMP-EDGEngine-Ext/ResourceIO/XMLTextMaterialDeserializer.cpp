#include "ResourceIOPCH.hpp"

#include <SAMP-EDGEngine-Ext/ResourceIO/XMLTextMaterialDeserializer.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMP-EDGEngine-Ext/ResourceIO/XMLNames.hpp>

namespace samp_edgengine::ext::resource_io
{

/////////////////////////////////////////////////////////////////////////////////
bool XMLTextMaterialDeserializer::deserialize() const
{
	// Deserialize material size:
	if ( !this->deserializeMaterialIndex() )
		return false;
	
	const_a text = dynamic_cast<IMapObject::Text*>(&material);

	// # Assertion note:
	// This deserialization algorithm supports only text materials. Fix your code.
	assert(text != nullptr);

	// Deserialize material text content (required):
	if (xml_helper::hasRequiredAttribute(sourceNode, XMLNames::Attributes::TextContent))
	{
		text->text = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::TextContent);
	}
	else
		return false;

	// Deserialize material size:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::MaterialSize))
	{
		auto const sizeStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::MaterialSize);
		try
		{
			text->size = std::stoi(sizeStr);
		}
		catch (...)
		{
			std::clog << ModuleLogPrefix << "(Warning): Invalid material size \"" << sizeStr << "\". Using default: " << text->size << "." << std::endl;
		}
	}

	// Deserialize font face:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::FontFace))
	{
		auto const fontFaceStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::FontFace);
		if (!fontFaceStr.empty())
			text->font = fontFaceStr;
		else
			std::clog << ModuleLogPrefix << "(Warning): Empty material font face. Using default: " << text->font << "." << std::endl;
	}

	// Deserialize font size:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::FontSize))
	{
		auto const fontSizeStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::FontSize);
		try
		{
			text->fontSize = std::stoi(fontSizeStr);
		}
		catch (...)
		{
			std::clog << ModuleLogPrefix << "(Warning): Invalid material font size \"" << fontSizeStr << "\". Using default: " << text->fontSize << "." << std::endl;
		}
	}

	// Deserialize font boldness:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::Bold))
	{
		auto const fontWeightBoldStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::Bold);
		try
		{
			text->bold = static_cast< bool >( std::stoi(fontWeightBoldStr) );
		}
		catch (...)
		{
			std::clog << ModuleLogPrefix << "(Warning): Invalid material font boldness: \"" << fontWeightBoldStr << "\". Using default: " << text->bold << "." << std::endl;
		}
	}

	// Deserialize font color:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::FontColor))
	{
		auto const fontColorStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::FontColor);
		try
		{
			text->fontColor = Color{ static_cast<Uint32>(std::stoul(fontColorStr, nullptr, 16)) };
		}
		catch (...)
		{
			std::clog << ModuleLogPrefix << "(Warning): Invalid material font color: \"" << fontColorStr << "\". Using default: " << text->fontColor.toRGBAString() << "." << std::endl;
		}
	}

	// Deserialize background color:
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::BackColor))
	{
		auto const backColorStr = xml_helper::getAttribute(sourceNode, XMLNames::Attributes::BackColor);
		try
		{
			text->backColor = Color{ static_cast<Uint32>(std::stoul(backColorStr, nullptr, 16)) };
		}
		catch (...)
		{
			std::clog << ModuleLogPrefix << "(Warning): Invalid material background color: \"" << backColorStr << "\". Using default: " << text->backColor.toRGBAString() << "." << std::endl;
		}
	}

	// Deserialize text alignment
	if (xml_helper::hasAttribute(sourceNode, XMLNames::Attributes::TextAlign))
	{
		text->textAlign = extractTextAlignFromString( xml_helper::getAttribute(sourceNode, XMLNames::Attributes::TextAlign) );
	}
	
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
IMapObject::Text::TextAlign XMLTextMaterialDeserializer::extractTextAlignFromString(std::string_view string_)
{
	using TextAlign = IMapObject::Text::TextAlign;
	if (string_ == "Left")
		return TextAlign::Left;
	if (string_ == "Right")
		return TextAlign::Right;
	if (string_ == "Center")
		return TextAlign::Center;

	std::clog << ModuleLogPrefix << "(Warning): Text alignment mode \"" << string_ << "\" is not recognised, using default: \"Left\"." << std::endl;
	return TextAlign::Left;
}

}
