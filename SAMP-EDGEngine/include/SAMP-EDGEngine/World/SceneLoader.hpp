#pragma once

#include SAMP_EDGENGINE_PCH

namespace samp_edgengine
{
class Scene;

class ISceneLoader
{
public:
	friend class Scene;
protected:
	/// <summary>
	/// Loads scene from stream.
	/// </summary>
	/// <param name="scene_">The scene.</param>
	/// <param name="stream_">The stream.</param>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	virtual void loadFromStream(Scene& scene_, std::istream & stream_) const = 0;
};

class DefaultSceneLoader
	: public ISceneLoader
{
private:
	/// <summary>
	/// Loads scene from stream.
	/// </summary>
	/// <param name="scene_">The scene.</param>
	/// <param name="stream_">The stream.</param>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	void loadFromStream(Scene& scene_, std::istream & stream_) const override;
};

}