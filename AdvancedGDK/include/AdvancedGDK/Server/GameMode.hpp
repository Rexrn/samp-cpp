// File description:
// Implements basic game mode interface.
#pragma once

// Precompiled header:
#include ADVANCEDGDK_PCH

// AGDK includes:
#include <AdvancedGDK/Core/MathInc.hpp>
#include <AdvancedGDK/Core/Events.hpp>
#include <AdvancedGDK/Server/Chat.hpp>
#include <AdvancedGDK/Server/Player/Weapon.hpp>
#include <AdvancedGDK/Server/Player/PlayerPool.hpp>
#include <AdvancedGDK/Server/Command/CommandManager.hpp>
#include <AdvancedGDK/World/Vehicle/VehiclePool.hpp>


namespace agdk
{	
	/// <summary>
	/// Provides abstract interface for every gamemode.
	/// </summary>
	class IGameMode
		: public IEventReceiver
	{
	public:		
		/// <summary>
		/// Initializes a new instance of the <see cref="IGameMode"/> class.
		/// </summary>
		IGameMode();
		
		/// <summary>
		/// Finalizes an instance of the <see cref="IGameMode"/> class.
		/// </summary>
		virtual ~IGameMode();
				
		/// <summary>
		/// Creates new player instance.
		/// </summary>
		/// <param name="playerIndex_">Index of the player.</param>
		/// <returns>
		/// New player instance with specified index.
		/// </returns>
		virtual std::shared_ptr<Player> newPlayerInstance(std::size_t const playerIndex_) const;
		
		/// <summary>
		/// Adds the player class.
		/// </summary>
		/// <param name="modelIndex_">Index of the model.</param>
		/// <param name="location_">The location.</param>
		/// <param name="facingAngle_">The facing angle.</param>
		/// <param name="weapons_">The weapons.</param>
		void addPlayerClass(std::size_t modelIndex_, math::Vector3f const location_, float const facingAngle_, std::array<Weapon, 3> weapons_ = {});

		friend class Server;
	protected:
		
		/// <summary>
		/// Setups the game mode.
		/// </summary>
		virtual void setup() {
			this->setupEvents();
		}

		/// <summary>
		/// Setups event receiving functions. Very important function!
		/// </summary>
		/// <remarks>
		/// <para>It is executed directly after GameMode creation, USE IT to setup event receivers, that receive events from server!</para>
		/// </remarks>
		virtual void setupEvents() {}

	public:
		PlayerPool				players;
		VehiclePool				vehicles;
		CommandManager			commands;

		std::unique_ptr<IChat>	chat;
	};
}



