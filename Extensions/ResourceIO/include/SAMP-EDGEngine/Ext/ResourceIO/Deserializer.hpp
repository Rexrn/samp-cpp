#pragma once

namespace samp_edgengine::ext::resource_io
{

/// <summary>
/// An interface to every deserialization algorithm.
/// </summary>
struct IDeserializer
{
	/// <summary>
	/// Finalizes an instance of the <see cref="IDeserializer"/> class.
	/// </summary>
	virtual ~IDeserializer() = default;

	/// <summary>
	/// Performs deserialization with given setup.
	/// </summary>
	/// <returns>
	///		<c>true</c> if deserialization succeeded; otherwise, <c>false</c>.
	/// </returns>
	virtual bool deserialize() const = 0;
};

}