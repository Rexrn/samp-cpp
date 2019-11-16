#pragma once
#include SAMPEDGENGINE_PCH



namespace samp_cpp
{
/// <summary>
/// Base class for every stream-loading algorithms.
/// </summary>
template <typename _Ty>
class StreamLoader
{
public:	
	/// <summary>
	/// Base class for every stream loading failure.
	/// </summary>
	class Failure
		: public std::runtime_error
	{ };
	
	/// <summary>
	/// Initializes a new instance of the <see cref="StreamLoader"/> class.
	/// </summary>
	/// <param name="stream_">The stream.</param>
	StreamLoader(std::istream &stream_)
		: m_stream{stream_}
	{
	}
	
	/// <summary>
	/// Loads data from stream. May throw StreamLoader::Failure exception.
	/// </summary>
	/// <returns></returns>
	virtual _Ty load() = 0;
protected:
	std::istream &m_stream;
};

}