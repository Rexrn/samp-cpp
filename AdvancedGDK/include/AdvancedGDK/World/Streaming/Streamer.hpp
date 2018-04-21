#pragma once

#include "Chunk.hpp"

#include <AdvancedGDK/Core/Container/DivisibleGrid3.hpp>

namespace agdk
{
class Streamer
{
public:
	// Half extent of the highest-level chunk: 1'638'400;
	// Number of divisions in each iteration: 4
	// Number of iterations: 7
	// Lowest level half extent: 100x100x100
	using GridType = DivisibleGrid3Node<Chunk, std::ratio<1'638'400>, 4, 7>;
 

private:
	GridType m_worldGrid;
};

}
