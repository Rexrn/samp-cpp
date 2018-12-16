#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include "XMLMapObjectSerializer.hpp"

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// A <see cref="PerPlayerObject"/> XML serialization algorithm.
/// </summary>
struct XMLPerPlayerObjectSerializer
	: XMLMapObjectSerializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLPerPlayerObjectSerializer" /> struct.
	/// </summary>
	/// <param name="object_">The serialized object.</param>
	/// <param name="parentNode_">The parent node.</param>
	XMLPerPlayerObjectSerializer(IMapObject const& object_, xml::xml_node<>& parentNode_)
		:
		XMLMapObjectSerializer{ object_, parentNode_ }
	{
	}
	
	/// <summary>
	/// Performs serialization with given setup.
	/// </summary>
	/// <returns>
	///		<c>true</c> if serialization succeeded; otherwise, <c>false</c>.
	/// </returns>
	virtual bool serialize() const override;

private:

	/// <summary>
	/// Returns string representation of the given visibility mode.
	/// </summary>
	/// <param name="mode_">The mode.</param>
	/// <returns>
	///		String representation of the given visibility mode.
	/// </returns>
	static std::string_view stringifyVisibilityMode(PerPlayerObject::VisibilityMode mode_);
};

}