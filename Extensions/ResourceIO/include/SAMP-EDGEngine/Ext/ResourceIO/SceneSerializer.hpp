#pragma once

#include "Serializer.hpp"

#include <SAMP-EDGEngine/Everything.hpp>

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// An interface to every <see cref="Scene"/> serialization algorithm.
/// </summary>
struct ISceneSerializer
	: virtual ISerializer
{	
	/// <summary>
	/// Initializes a new instance of the <see cref="ISceneSerializer"/> struct.
	/// </summary>
	/// <param name="scene_">The serialized scene.</param>
	ISceneSerializer(Scene const& scene_)
		: scene{ scene_ }
	{
	}

	// The serialized scene:
	Scene const& scene;
};

}