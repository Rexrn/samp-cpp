#pragma once

#include SAMP_EDGENGINE_EXT_RESOURCEIO_PCH

namespace samp_edgengine::ext::resource_io::xml_helper
{

enum CopyAllocMode
{
	DontAlloc	= 0,
	AllocName	= 1 << 0,
	AllocValue	= 1 << 1,
	AllocAll	= AllocName + AllocValue
};

////////////////////////////////////////////////////////////////////////
void setAttribute(xml::xml_node<>& node_, std::string_view name_, std::string_view value_, CopyAllocMode copyAlloc_ = AllocAll);

////////////////////////////////////////////////////////////////////////
bool hasAttribute(xml::xml_node<> const& node_, std::string_view name_);

////////////////////////////////////////////////////////////////////////
std::string getAttribute(xml::xml_node<> const& node_, std::string_view name_);

////////////////////////////////////////////////////////////////////////
bool hasRequiredAttribute(xml::xml_node<> const& node_, std::string_view name_);

}