#pragma once

#include SAMP_EDGENGINE_EXT_INPUTCONVERTER_PCH

namespace samp_edgengine::ext::input_converter
{

/// <summary>
/// An interface to every XML-serializable object.
/// </summary>
struct IXMLSerializable
{	
	/// <summary>
	/// Serializes the object to XML by creating a child node to the `parentNode_`.
	/// </summary>
	/// <param name="parentNode_">The node to create child at.</param>
	/// <returns>
	///		Pointer to created node or nullptr if failed.
	/// </returns>
	virtual xml::xml_node<>* serialize(xml::xml_node<>& parentNode_) const = 0;
	
	/// <summary>
	/// Deserializes the object from XML from specified node.
	/// </summary>
	/// <param name="node_">The node to deserialize from.</param>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	virtual bool deserialize(xml::xml_node<>& node_) = 0;
};

}