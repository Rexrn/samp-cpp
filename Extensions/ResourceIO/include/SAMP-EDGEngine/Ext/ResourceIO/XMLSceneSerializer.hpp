#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include "XMLSerializer.hpp"
#include "SceneSerializer.hpp"

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// A <see cref="Scene"/> XML serialization algorithm.
/// </summary>
struct XMLSceneSerializer
	:
	IXMLSerializer,
	ISceneSerializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLSceneSerializer" /> struct.
	/// </summary>
	/// <param name="scene_">The serialized scene.</param>
	/// <param name="parentNode_">The parent node.</param>
	XMLSceneSerializer(Scene const& scene_, xml::xml_node<> &parentNode_)
		:
		IXMLSerializer{ parentNode_ },
		ISceneSerializer{ scene_ }
	{
	}
	
	/// <summary>
	/// Performs serialization with given setup.
	/// </summary>
	/// <returns>
	///		<c>true</c> if serialization succeeded; otherwise, <c>false</c>.
	/// </returns>
	virtual bool serialize() const override;
};

}
