// File description:
// TODO: Provides basic exception classes for common runtime errors.
#pragma once

// Precompiled header:
#include ADVANCEDGDK_PCH

namespace agdk
{
// TODO: implement exception classes.

class AlgorithmError
	: public std::exception
{
public:
	using std::exception::exception;
};

class ReferenceCountingError
	: public AlgorithmError
{
public:
	using AlgorithmError::AlgorithmError;
};

}
