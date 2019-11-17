#pragma once
#include SAMPCPP_EXT_RESOURCEIO_PCH

#include "XMLDeserializer.hpp"
#include "SceneDeserializer.hpp"

namespace samp_cpp::ext::resource_io
{

/// <summary>
/// A XML deserialization algorithm.
/// </summary>
struct XMLSceneDeserializer
	:
	IXMLDeserializer,
	ISceneDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="XMLSceneDeserializer" /> struct.
	/// </summary>
	/// <param name="scene_">The deserialized scene.</param>
	/// <param name="sourceNode_">The source node.</param>
	XMLSceneDeserializer(Scene & scene_, xml::xml_node<> const & sourceNode_)
		:
		IXMLDeserializer{ sourceNode_ },
		ISceneDeserializer{ scene_ }
	{
	}
	
	/// <summary>
	/// Performs deserialization with given setup.
	/// </summary>
	/// <returns>
	///		<c>true</c> if deserialization succeeded; otherwise, <c>false</c>.
	/// </returns>
	virtual bool deserialize() const override;
};

}