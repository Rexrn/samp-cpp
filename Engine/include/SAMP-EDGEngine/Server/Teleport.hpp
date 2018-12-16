#pragma once
#include SAMPEDGENGINE_PCH



#include <SAMP-EDGEngine/Core/TypesAndDefinitions.hpp>
#include <SAMP-EDGEngine/Dependencies/QuickMaffs.hpp>

namespace samp_edgengine
{
	class Teleport
	{
	public:
		constexpr static Int32 cxInvalid		= -1;
		constexpr static Int32 cxNoChange		= -2;

		constexpr static Int32 cxEvery			= -1;
		constexpr static Int32 cxAllButDefault	= -2;


		/// <summary>
		/// Initializes a new instance of the <see cref="Teleport"/> class.
		/// </summary>
		constexpr Teleport()
			: facingAngle{ 0 }, world{ cxNoChange }, interior{ cxNoChange }
		{
		}
	
		/// <summary>
		/// Initializes a new instance of the <see cref="Teleport"/> class from passed parameters.
		/// World and interior are left without change when teleporting.
		/// </summary>
		/// <param name="location_">The location.</param>
		/// <param name="facingAngle_">The facing angle.</param>
		constexpr Teleport(math::Vector3f const &location_, float const facingAngle_)
			: location{ location_ }, facingAngle{ facingAngle_ }, world{ cxNoChange }, interior{ cxNoChange }
		{
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="Teleport"/> class from passed parameters.
		/// </summary>
		/// <param name="location_">The location.</param>
		/// <param name="facingAngle_">The facing angle.</param>
		/// <param name="world_">The world.</param>
		/// <param name="interior_">The interior.</param>
		constexpr Teleport(math::Vector3f const &location_, float const facingAngle_, Int32 const world_, Int32 const interior_)
			: location{ location_ }, facingAngle{ facingAngle_ }, world{ world_ }, interior{ interior_ }
		{
		}
	
		/// <summary>
		/// Constructs teleport with absolute world/interior.
		/// </summary>
		/// <param name="location_">The location.</param>
		/// <param name="facingAngle_">The facing angle.</param>
		/// <param name="world_">The world.</param>
		/// <param name="interior_">The interior.</param>
		/// <returns>Constructed teleport</returns>
		constexpr static Teleport absolute(math::Vector3f const &location_, float const facingAngle_, Int32 const world_, Int32 const interior_)
		{
			return Teleport(location_, facingAngle_, world_, interior_);
		}

		/// <summary>
		/// Constructs teleport without changing world or interior.
		/// </summary>
		/// <param name="location_">The location.</param>
		/// <param name="facingAngle_">The facing angle.</param>
		/// <returns>Constructed teleport</returns>
		constexpr static Teleport relative(math::Vector3f const &location_, float const facingAngle_)
		{
			return Teleport(location_, facingAngle_, cxNoChange, cxNoChange);
		}
		
		/// <summary>
		/// Constructs teleport without changing world but changes interior.
		/// </summary>
		/// <param name="location_">The location.</param>
		/// <param name="facingAngle_">The facing angle.</param>
		/// <param name="interior_">The interior.</param>
		/// <returns>Constructed teleport</returns>
		constexpr static Teleport relativeW(math::Vector3f const &location_, float const facingAngle_, Int32 const interior_)
		{
			return Teleport(location_, facingAngle_, cxNoChange, interior_);
		}
	
		/// <summary>
		/// Constructs teleport without changing interior but changes world.
		/// </summary>
		/// <param name="location_">The location.</param>
		/// <param name="facingAngle_">The facing angle.</param>
		/// <param name="world_">The world.</param>
		/// <returns>Constructed teleport</returns>
		constexpr static Teleport relativeI(math::Vector3f const &location_, float const facingAngle_, Int32 const world_)
		{
			return Teleport(location_, facingAngle_, world_, cxNoChange);
		}

		// The location
		math::Vector3f	location;

		// The direction (Z axis angle)
		float			facingAngle;

		// The world
		Int32			world;

		// The interior
		Int32			interior;
	};

	namespace teleports
	{
		///////////////////////////////////////////// Main cities
		static constexpr Teleport GroveStreet{ math::Vector3f(2495.3755f, -1669.4906f, 13.5163f), 0 };
		static constexpr Teleport SanFierro{ math::Vector3f(-1986.7297f, 884.7870f, 45.1206f), 0 };
		static constexpr Teleport LasVenturas{ math::Vector3f(2140.6675f, 993.1867f, 10.5248f), 0 };

		/*
		static const Teleport WangCars(Vector3(-1987.7372f, 288.7828f, 34.5681f), 0);

		static const Teleport UnityStation(Vector3(1761.9f, -1893.5f, 13.1f), 200.2f);
		static const Teleport SkatePark(Vector3(1914.2f, -1369.0f, 13.3f), 328.6f);
		static const Teleport GlenPark(Vector3(2037.6f, -1202.4f, 22.2f), 332.2f);

		static const Teleport MadDoggHouse(Vector3(1245.0f, -782.8f, 90.0f), 328.6f);

		static const Teleport BeachLS(Vector3(330.1647f, -1798.5216f, 4.7001f), 0);

		static const Teleport FourDragons(Vector3(2023.6055f, 1008.2421f, 10.3642f), 0);

		static const Teleport Spedition(Vector3(1065.9f, 1753.8f, 10.8f), 9.8f);
		static const Teleport Skyscraper(Vector3(1543.3f, -1352.5f, 329.5f), 0);
		static const Teleport Garage1(Vector3(2328.3f, 1407.2f, 42.5f), 193.3f);
		static const Teleport Garage2(Vector3(2260.1f, 1977.3f, 31.8f), 0);
		static const Teleport Garage3(Vector3(2110.7f, 2424.9f, 49.5f), 0);
		static const Teleport Garage4(Vector3(2792.0f, -1428.7f, 40.1f), 0);
		static const Teleport Garage5(Vector3(-1790.2f, 1306.4f, 59.8f), 0);

		static const Teleport BankLV(Vector3(2179.2f, 1991.2f, 10.8f), 0);
		static const Teleport Stadium(Vector3(1382.5f, 2184.2f, 11.0f), 137.1f);

		static const Teleport HighJumpLV(Vector3(2090.566f, 309.578f, 385.6f), 140.6f);

		// Tunings
		static const Teleport TransFender(Vector3(2387.0808f, 1016.9999f, 10.5459f), 0);
		static const Teleport TuneLS(Vector3(2644.3f, -2034.1f, 13.4f), 1.8f);
		static const Teleport TuneSF(Vector3(-1935.7f, 234.0f, 33.9f), 180.0f);
		static const Teleport TuneLV(Vector3(2386.5f, 1037.2f, 10.5f), 179.5f);


		// Airports
		static const Teleport LosSantosAirport(Vector3(1953.5204f, -2290.1130f, 13.5469f), 0);
		static const Teleport SanFierroAirport(Vector3(-1538.8635f, -422.9142f, 5.8516f), 0);
		static const Teleport LasVenturasAirport(Vector3(1686.3107f, 1609.5485f, 10.8203f), 0);

		///////////////////////////////////////////// Outside cities
		// Polish: /tama
		static const Teleport WaterGate(Vector3(-912.1113f, 2005.2953f, 60.4852f), 0);
		static const Teleport MountChilliad(Vector3(-2321.1321f, -1634.2689f, 483.8788f), 0);

		static const Teleport Farm(Vector3(-80.3f, -7.8f, 2.6f), 328.6f);
		static const Teleport AbandonedAirport(Vector3(430.2f, 2505.1f, 16.0f), 108.1f);
		static const Teleport Mine(Vector3(783.2f, 841.3f, 5.3f), 90.5f);
		static const Teleport CatalinasHouse(Vector3(876.5f, -36.5f, 63.1f), 69.3f);

		static const Teleport TreeHouse(Vector3(-1693.4219f, -2373.0935f, 111.3270f), 0);

		static const Teleport Area51(Vector3(214.8f, 1914.8f, 17.2f), 108.1f);
		///////////////////////////////////////////// Interiors
		static const Teleport WareHouse(Vector3(1388.7f, -19.8f, 1000.9f), 0, -1, 1);
		static const Teleport LibertyCity(Vector3(-826.3f, 502.5f, 1358.2f), 0, -1, 1);

		static const Teleport LSPD(Vector3(246.5f, 66.2f, 1003.6f), 1.7f, -1, 6);
		static const Teleport SFPD(Vector3(247.0f, 114.0f, 1003.2f), 87.3f, -1, 10);
		static const Teleport LVPD(Vector3(281.1f, 180.0f, 1007.1f), 89.2f, -1, 3);
		*/
	}
}
