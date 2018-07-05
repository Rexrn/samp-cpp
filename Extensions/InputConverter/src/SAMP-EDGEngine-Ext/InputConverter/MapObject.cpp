#include "InputConverterPCH.hpp"

#include <SAMP-EDGEngine-Ext/InputConverter/MapObject.hpp>

namespace samp_edgengine::ext::input_converter
{

////////////////////////////////////////////////////////////////////////////////////////////////
MapObject::TextMaterial::TextMaterial()
{
	// TODO: implement this.
}

////////////////////////////////////////////////////////////////////////////////////////////////
xml::xml_node<>* MapObject::TextMaterial::serialize(xml::xml_node<>& parentNode_) const
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////
bool MapObject::TextMaterial::deserialize(xml::xml_node<>& node_)
{
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
MapObject::TextureMaterial::TextureMaterial()
{
	// TODO: implement this.
}

////////////////////////////////////////////////////////////////////////////////////////////////
xml::xml_node<>* MapObject::TextureMaterial::serialize(xml::xml_node<>& parentNode_) const
{
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////
bool MapObject::TextureMaterial::deserialize(xml::xml_node<>& node_)
{
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
MapObject::MapObject(Type type_)
	:
	type{ type_ },
	modelIndex{},
	world{},
	interior{},
	location{},
	rotation{},
	drawDistance{}
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
std::string_view MapObject::getTypeString() const
{
	switch (type)
	{
	case Global: return "Global";
	case Personal: return "Personal";
	case Universal: return "Universal";
	default: return "Default";
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
std::string_view MapObject::getWorldModeString() const
{
	// TODO: implement this.
	return "";
}

////////////////////////////////////////////////////////////////////////////////////////////////
std::string_view MapObject::getInteriorModeString() const
{
	// TODO: implement this.
	return "";
}

////////////////////////////////////////////////////////////////////////////////////////////////
xml::xml_node<>* MapObject::serialize(xml::xml_node<>& parentNode_) const
{
	xml::xml_node<>& node = *parentNode_.document()->allocate_node(xml::node_element, XMLNames::Node);
	parentNode_.append_node(&node);

	auto const setAttribute = [](xml::xml_node<>& node_, std::string_view name_, std::string_view value_)
		{
			xml::xml_attribute<>& attribute = *node_.document()->allocate_attribute(name_.data(), value_.data(), name_.size(), value_.size());
			node_.append_attribute(&attribute);
		};

	{
		setAttribute(node, XMLNames::Parameters::Type, this->getTypeString() );
		setAttribute(node, XMLNames::Parameters::WorldMode, this->getWorldModeString() );
		setAttribute(node, XMLNames::Parameters::InteriorMode, this->getInteriorModeString() );
		setAttribute(node, XMLNames::Parameters::DrawDistance, (drawDistance > 0.001f ? std::to_string(drawDistance) : "Default") );
		setAttribute(node, XMLNames::Parameters::World, std::to_string(world) );
		setAttribute(node, XMLNames::Parameters::Interior, std::to_string(interior) );
		setAttribute(node, XMLNames::Parameters::LocX, std::to_string(location.x) );
		setAttribute(node, XMLNames::Parameters::LocY, std::to_string(location.y) );
		setAttribute(node, XMLNames::Parameters::LocZ, std::to_string(location.z) );
		setAttribute(node, XMLNames::Parameters::RotX, std::to_string(rotation.x) );
		setAttribute(node, XMLNames::Parameters::RotY, std::to_string(rotation.y) );
		setAttribute(node, XMLNames::Parameters::RotZ, std::to_string(rotation.z) );
	}

	for(auto const &material : materials)
	{
		if (material)
		{
			material->serialize(node);
		}
	}

	return &node;
}

////////////////////////////////////////////////////////////////////////////////////////////////
bool MapObject::deserialize(xml::xml_node<>& node_)
{
	// TODO: implement this.
	return false;
}

}
