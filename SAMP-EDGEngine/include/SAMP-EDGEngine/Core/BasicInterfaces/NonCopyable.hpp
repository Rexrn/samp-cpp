#pragma once

namespace samp_edgengine
{

/// <summary>
/// Interface for every non-copyable class.
/// </summary>
class INonCopyable {
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="INonCopyable"/> class.
	/// </summary>
	INonCopyable() { }
	
	/// <summary>
	/// Prevents copy-constructing <see cref="INonCopyable"/> class.
	/// </summary>
	/// <param name="other_">The other object.</param>
	INonCopyable(INonCopyable const & other_) = delete;
	
	/// <summary>
	/// Prevents copy-assigning <see cref="INonCopyable"/> class.
	/// </summary>
	/// <param name="other_">The other object.</param>
	/// <returns>Reference to self; but method is deleted.</returns>
	INonCopyable& operator=(INonCopyable const & other_) = delete;
};

}
