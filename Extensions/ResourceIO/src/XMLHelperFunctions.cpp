#include SAMPCPP_EXT_RESOURCEIO_PCH

#include <SAMPCpp/Ext/ResourceIO/XMLHelperFunctions.hpp>
#include <SAMPCpp/Ext/ResourceIO/Logging.hpp>

#include <iostream>

namespace samp_cpp::ext::resource_io::xml_helper
{

////////////////////////////////////////////////////////////////////////
void setAttribute(xml::xml_node<>& node_, std::string_view name_, std::string_view value_, CopyAllocMode copyAlloc_)
{
	char const* nameCopy = (copyAlloc_ & AllocName ? node_.document()->allocate_string(name_.data(), name_.size() + 1) : name_.data());
	char const* valueCopy = (copyAlloc_ & AllocValue ? node_.document()->allocate_string(value_.data(), value_.size() + 1) : value_.data());

	xml::xml_attribute<>& attribute = *node_.document()->allocate_attribute(nameCopy, valueCopy,
			(copyAlloc_ & AllocName ? 0 : name_.size()),
			(copyAlloc_ & AllocValue ? 0 : value_.size())
		);

	node_.append_attribute(&attribute);
}

////////////////////////////////////////////////////////////////////////
bool hasAttribute(xml::xml_node<> const& node_, std::string_view name_)
{
	return node_.first_attribute(name_.data(), name_.size()) != nullptr;
}

////////////////////////////////////////////////////////////////////////
std::string getAttribute(xml::xml_node<> const& node_, std::string_view name_)
{
	if (auto const attribute = node_.first_attribute(name_.data(), name_.size()))
	{
		return std::string(attribute->value());
	}
	return std::string{};
}

////////////////////////////////////////////////////////////////////////
bool hasRequiredAttribute(xml::xml_node<> const& node_, std::string_view name_)
{
	if (!hasAttribute(node_, name_))
	{
		std::cerr << ModuleLogPrefix << "(Error): MapObject attribute \"" << name_ << "\" is required!" << std::endl;
		return false;
	}
	return true;
}

}
