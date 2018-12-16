// File description:
// TODO: Provides basic exception classes for common runtime errors.
#pragma once
#include SAMPEDGENGINE_PCH



#include <stdexcept>

namespace samp_edgengine
{
// TODO: implement exception classes.

class AlgorithmError
	: public std::logic_error
{
public:
	using std::logic_error::logic_error;
};

class ReferenceCountingError
	: public AlgorithmError
{
public:
	using AlgorithmError::AlgorithmError;
};

}
