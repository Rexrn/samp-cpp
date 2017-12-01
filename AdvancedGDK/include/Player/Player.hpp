#pragma once

// Standard includes
#include <memory>		// for std::shared_ptr
#include <cstddef>		// for std::size_t

namespace agdk
{	
	/// <summary>
	/// Class wrapping SAMP player data into class.
	/// </summary>
	class Player
		: public std::enable_shared_from_this<Player>
	{
	public:		

		/// <summary>
		/// Initializes a new instance of the <see cref="Player"/> class.
		/// </summary>
		/// <param name="index">Index of the player.</param>
		explicit Player(const std::size_t index_);
		
		/// <summary>
		/// Default constructor (deleted, use explicit index constructor instead).
		/// </summary>
		Player() = delete;

		/// <summary>
		/// Copy onstructor (deleted, use explicit index constructor instead).
		/// </summary>
		Player(const Player &)	= delete;

		/// <summary>
		/// Move constructor (deleted, use explicit index constructor instead).
		/// </summary>
		Player(Player &&)		= delete;
		
		/// <summary>
		/// Returns player index.
		/// </summary>
		/// <returns>Player index (std::size_t).</returns>
		std::size_t getIndex() const
		{
			return m_index;
		}
	protected:

	private:
		const std::size_t m_index;
	};
}