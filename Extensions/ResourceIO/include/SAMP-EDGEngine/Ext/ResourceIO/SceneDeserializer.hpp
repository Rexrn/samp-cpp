#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

#include "Deserializer.hpp"

namespace samp_cpp::ext::resource_io
{

/// <summary>
/// An interface to every <see cref="Scene"/> deserialization algorithm.
/// </summary>
struct ISceneDeserializer
	: virtual IDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="ISceneDeserializer"/> struct.
	/// </summary>
	/// <param name="scene_">The deserialized scene.</param>
	ISceneDeserializer(Scene & scene_)
		: scene{ scene_ }
	{
	}

	// The deserialized scene:
	Scene & scene;
};

}