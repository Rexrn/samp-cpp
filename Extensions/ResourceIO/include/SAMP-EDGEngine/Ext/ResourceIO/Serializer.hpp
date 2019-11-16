#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

namespace samp_cpp::ext::resource_io
{

/// <summary>
/// An interface to every serialization algorithm.
/// </summary>
struct ISerializer
{		
	/// <summary>
	/// Finalizes an instance of the <see cref="ISerializer"/> class.
	/// </summary>
	virtual ~ISerializer() = default;

	/// <summary>
	/// Performs serialization with given setup.
	/// </summary>
	/// <returns>
	///		<c>true</c> if serialization succeeded; otherwise, <c>false</c>.
	/// </returns>
	virtual bool serialize() const = 0;
};

}