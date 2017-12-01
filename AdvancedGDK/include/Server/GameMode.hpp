#pragma once


namespace agdk
{	
	/// <summary>
	/// Provides abstract interface for every gamemode.
	/// </summary>
	class IGameMode
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
		
	};
}



