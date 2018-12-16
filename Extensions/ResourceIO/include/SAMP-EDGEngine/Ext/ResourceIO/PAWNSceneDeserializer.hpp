#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH



#include "PAWNDeserializer.hpp"
#include "SceneDeserializer.hpp"

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// A <see cref="Scene"/> PAWN deserialization algorithm.
/// </summary>
struct PAWNSceneDeserializer
	:
	IPAWNDeserializer,
	ISceneDeserializer
{
	/// <summary>
	/// Initializes a new instance of the <see cref="PAWNSceneSerializer" /> struct.
	/// </summary>
	/// <param name="scene_">The deserialized scene.</param>
	/// <param name="inputStream_">The input stream.</param>
	PAWNSceneDeserializer(Scene & scene_, std::istream& inputStream_)
		:
		IPAWNDeserializer{ inputStream_ },
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