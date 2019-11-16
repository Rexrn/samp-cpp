#pragma once
#include SAMPEDGENGINE_PCH



#include <SAMP-EDGEngine/Core/Clock.hpp>
#include <SAMP-EDGEngine/Core/Events.hpp>
#include <SAMP-EDGEngine/Core/BasicInterfaces/PlacementTracker.hpp>

#include <SAMP-EDGEngine/World/WI3DNode.hpp>
#include <SAMP-EDGEngine/Dependencies/SampGDK.hpp>


namespace samp_cpp
{
class Player;
class ServerClass;

enum class VehicleCategory : Uint8
{
	OffRoad = 0,
	Saloons,
	SportVehicles,
	Industrial,
	StationWagons,
	UniqueVehicles,
	PublicService,
	Lowriders,
	Helicopters,
	Boats,
	Trailers,
	Convertibles,
	RCVehicles,
	Bikes,
	Airplanes
};

enum class SpeedUnit : Uint8
{
	GameDefault,
	KMPH,
	MPH
};

// Vehicle name					<std::string_view>
// Vehicle unformatted name		<std::string_view>
// Vehicle model name			<std::string_view>
// Vehicle top speed			<float>
// Vehicle category				<VehicleCategory>
using TVehicleInfoT = std::tuple<std::string_view, std::string_view, std::string_view, float, VehicleCategory>;

const std::map<Uint32, TVehicleInfoT> g_vehiclesDataM = {
	{ 400,{ "Landstalker", "Landstalker", "landstal", 157.f, VehicleCategory::OffRoad } },
	{ 401,{ "Bravura", "Bravura", "bravura", 147.f, VehicleCategory::Saloons } },
	{ 402,{ "Buffalo", "Buffalo", "buffalo", 186.f, VehicleCategory::SportVehicles } },
	{ 403,{ "Linerunner", "Linerunner", "linerun", 110.f, VehicleCategory::Industrial } },
	{ 404,{ "Perenniel", "Perenniel", "peren", 133.f, VehicleCategory::StationWagons } },
	{ 405,{ "Sentinel", "Sentinel", "sentinel", 164.f, VehicleCategory::Saloons } },
	{ 406,{ "Dumper", "Dumper", "dumper", 110.f, VehicleCategory::UniqueVehicles } },
	{ 407,{ "Firetruck", "Firetruck", "firetruk", 148.f, VehicleCategory::PublicService } },
	{ 408,{ "Trashmaster", "Trashmaster", "trash", 100.f, VehicleCategory::Industrial } },
	{ 409,{ "Stretch", "Stretch", "stretch", 158.f, VehicleCategory::UniqueVehicles } },
	{ 410,{ "Manana", "Manana", "manana", 129.f, VehicleCategory::Saloons } },
	{ 411,{ "Infernus", "Infernus", "infernus", 221.f, VehicleCategory::SportVehicles } },
	{ 412,{ "Voodoo", "Voodoo", "voodoo", 168.f, VehicleCategory::Lowriders } },
	{ 413,{ "Pony", "Pony", "pony", 110.f, VehicleCategory::Industrial } },
	{ 414,{ "Mule", "Mule", "mule", 105.f, VehicleCategory::Industrial } },
	{ 415,{ "Cheetah", "Cheetah", "cheetah", 192.f, VehicleCategory::SportVehicles } },
	{ 416,{ "Ambulance", "Ambulance", "ambulan", 154.f, VehicleCategory::PublicService } },
	{ 417,{ "Leviathan", "Leviathan", "leviathn", 270.f, VehicleCategory::Helicopters } },
	{ 418,{ "Moonbeam", "Moonbeam", "moonbeam", 115.f, VehicleCategory::StationWagons } },
	{ 419,{ "Esperanto", "Esperanto", "esperant", 149.f, VehicleCategory::Saloons } },
	{ 420,{ "Taxi", "Taxi", "taxi", 145.f, VehicleCategory::PublicService } },
	{ 421,{ "Washington", "Washington", "washing", 154.f, VehicleCategory::Saloons } },
	{ 422,{ "Bobcat", "Bobcat", "bobcat", 140.f, VehicleCategory::Industrial } },
	{ 423,{ "Mr. Whoopee", "MrWhoopee", "mrwhoop", 99.f, VehicleCategory::UniqueVehicles } },
	{ 424,{ "BF Injection", "BFInjection", "bfinject", 135.f, VehicleCategory::OffRoad } },
	{ 425,{ "Hunter", "Hunter", "hunter", 270.f, VehicleCategory::Helicopters } },
	{ 426,{ "Premier", "Premier", "premier", 173.f, VehicleCategory::Saloons } },
	{ 427,{ "Enforcer", "Enforcer", "enforcer", 165.f, VehicleCategory::PublicService } },
	{ 428,{ "Securicar", "Securicar", "securica", 157.f, VehicleCategory::UniqueVehicles } },
	{ 429,{ "Banshee", "Banshee", "banshee", 201.f, VehicleCategory::SportVehicles } },
	{ 430,{ "Predator", "Predator", "predator", 190.f, VehicleCategory::Boats } },
	{ 431,{ "Bus", "Bus", "bus", 130.f, VehicleCategory::PublicService } },
	{ 432,{ "Rhino", "Rhino", "rhino", 94.f, VehicleCategory::PublicService } },
	{ 433,{ "Barracks", "Barracks", "barracks", 110.f, VehicleCategory::PublicService } },
	{ 434,{ "Hotknife", "Hotknife", "hotknife", 167.f, VehicleCategory::UniqueVehicles } },
	{ 435,{ "Article Trailer", "ArticleTrailer", "artict1", 0.f, VehicleCategory::Trailers } },
	{ 436,{ "Previon", "Previon", "previon", 149.f, VehicleCategory::Saloons } },
	{ 437,{ "Coach", "Coach", "coach", 158.f, VehicleCategory::PublicService } },
	{ 438,{ "Cabbie", "Cabbie", "cabbie", 142.f, VehicleCategory::PublicService } },
	{ 439,{ "Stallion", "Stallion", "stallion", 168.f, VehicleCategory::Convertibles } },
	{ 440,{ "Rumpo", "Rumpo", "rumpo", 136.f, VehicleCategory::Industrial } },
	{ 441,{ "RC Bandit", "RCBandit", "rcbandit", 145.f, VehicleCategory::RCVehicles } },
	{ 442,{ "Romero", "Romero", "romero", 139.f, VehicleCategory::UniqueVehicles } },
	{ 443,{ "Packer", "Packer", "packer", 126.f, VehicleCategory::Industrial } },
	{ 444,{ "Monster", "Monster", "monster", 110.f, VehicleCategory::OffRoad } },
	{ 445,{ "Admiral", "Admiral", "admiral", 164.f, VehicleCategory::Saloons } },
	{ 446,{ "Squallo", "Squallo", "squalo", 270.f, VehicleCategory::Boats } },
	{ 447,{ "Seasparrow", "Seasparrow", "seaspar", 270.f, VehicleCategory::Helicopters } },
	{ 448,{ "Pizzaboy", "Pizzaboy", "pizzaboy", 111.f, VehicleCategory::Bikes } },
	{ 449,{ "Tram", "Tram", "tram", 0.f, VehicleCategory::UniqueVehicles } },
	{ 450,{ "Article Trailer 2", "ArticleTrailer2", "artict2", 0.f, VehicleCategory::Trailers } },
	{ 451,{ "Turismo", "Turismo", "turismo", 193.f, VehicleCategory::SportVehicles } },
	{ 452,{ "Speeder", "Speeder", "speeder", 270.f, VehicleCategory::Boats } },
	{ 453,{ "Reefer", "Reefer", "reefer", 60.f, VehicleCategory::Boats } },
	{ 454,{ "Tropic", "Tropic", "tropic", 135.f, VehicleCategory::Boats } },
	{ 455,{ "Flatbed", "Flatbed", "flatbed", 157.f, VehicleCategory::Industrial } },
	{ 456,{ "Yankee", "Yankee", "yankee", 106.f, VehicleCategory::Industrial } },
	{ 457,{ "Caddy", "Caddy", "caddy", 95.f, VehicleCategory::UniqueVehicles } },
	{ 458,{ "Solair", "Solair", "solair", 157.f, VehicleCategory::StationWagons } },
	{ 459,{ "Topfun Van (Berkley's RC)", "TopfunVanBerkleysRC", "topfun", 136.f, VehicleCategory::Industrial } },
	{ 460,{ "Skimmer", "Skimmer", "skimmer", 270.f, VehicleCategory::Airplanes } },
	{ 461,{ "PCJ-600", "PCJ600", "pcj600", 160.f, VehicleCategory::Bikes } },
	{ 462,{ "Faggio", "Faggio", "faggio", 111.f, VehicleCategory::Bikes } },
	{ 463,{ "Freeway", "Freeway", "freeway", 142.f, VehicleCategory::Bikes } },
	{ 464,{ "RC Baron", "RCBaron", "rcbaron", 145.f, VehicleCategory::RCVehicles } },
	{ 465,{ "RC Raider", "RCRaider", "rcraider", 145.f, VehicleCategory::RCVehicles } },
	{ 466,{ "Glendale", "Glendale", "glendale", 147.f, VehicleCategory::Saloons } },
	{ 467,{ "Oceanic", "Oceanic", "oceanic", 140.f, VehicleCategory::Saloons } },
	{ 468,{ "Sanchez", "Sanchez", "sanchez", 144.f, VehicleCategory::Bikes } },
	{ 469,{ "Sparrow", "Sparrow", "sparrow", 270.f, VehicleCategory::Helicopters } },
	{ 470,{ "Patriot", "Patriot", "patriot", 157.f, VehicleCategory::OffRoad } },
	{ 471,{ "Quad", "Quad", "quad", 110.f, VehicleCategory::Bikes } },
	{ 472,{ "Coastguard", "Coastguard", "coastg", 190.f, VehicleCategory::Boats } },
	{ 473,{ "Dinghy", "Dinghy", "dinghy", 190.f, VehicleCategory::Boats } },
	{ 474,{ "Hermes", "Hermes", "hermes", 149.f, VehicleCategory::Saloons } },
	{ 475,{ "Sabre", "Sabre", "sabre", 173.f, VehicleCategory::SportVehicles } },
	{ 476,{ "Rustler", "Rustler", "rustler", 270.f, VehicleCategory::Airplanes } },
	{ 477,{ "ZR-350", "ZR350", "zr350", 186.f, VehicleCategory::SportVehicles } },
	{ 478,{ "Walton", "Walton", "walton", 117.f, VehicleCategory::Industrial } },
	{ 479,{ "Regina", "Regina", "regina", 140.f, VehicleCategory::StationWagons } },
	{ 480,{ "Comet", "Comet", "comet", 184.f, VehicleCategory::Convertibles } },
	{ 481,{ "BMX", "BMX", "bmx", 73.f, VehicleCategory::Bikes } },
	{ 482,{ "Burrito", "Burrito", "burrito", 156.f, VehicleCategory::Industrial } },
	{ 483,{ "Camper", "Camper", "camper", 122.f, VehicleCategory::UniqueVehicles } },
	{ 484,{ "Marquis", "Marquis", "marquis", 190.f, VehicleCategory::Boats } },
	{ 485,{ "Baggage", "Baggage", "baggage", 99.f, VehicleCategory::UniqueVehicles } },
	{ 486,{ "Dozer", "Dozer", "dozer", 64.f, VehicleCategory::UniqueVehicles } },
	{ 487,{ "Maverick", "Maverick", "maverick", 270.f, VehicleCategory::Helicopters } },
	{ 488,{ "SAN News Maverick", "SANNewsMaverick", "vcnmav", 270.f, VehicleCategory::Helicopters } },
	{ 489,{ "Rancher", "Rancher", "rancher", 139.f, VehicleCategory::OffRoad } },
	{ 490,{ "FBI Rancher", "FBIRancher", "fbiranch", 157.f, VehicleCategory::PublicService } },
	{ 491,{ "Virgo", "Virgo", "virgo", 149.f, VehicleCategory::Saloons } },
	{ 492,{ "Greenwood", "Greenwood", "greenwoo", 140.f, VehicleCategory::Saloons } },
	{ 493,{ "Jetmax", "Jetmax", "jetmax", 270.f, VehicleCategory::Boats } },
	{ 494,{ "Hotring Racer", "HotringRacer", "hotring", 214.f, VehicleCategory::SportVehicles } },
	{ 495,{ "Sandking", "Sandking", "sandking", 176.f, VehicleCategory::OffRoad } },
	{ 496,{ "Blista Compact", "BlistaCompact", "blistac", 162.f, VehicleCategory::SportVehicles } },
	{ 497,{ "Police Maverick", "PoliceMaverick", "polmav", 270.f, VehicleCategory::Helicopters } },
	{ 498,{ "Boxville", "Boxville", "boxville", 108.f, VehicleCategory::Industrial } },
	{ 499,{ "Benson", "Benson", "benson", 123.f, VehicleCategory::Industrial } },
	{ 500,{ "Mesa", "Mesa", "mesa", 140.f, VehicleCategory::OffRoad } },
	{ 501,{ "RC Goblin", "RCGoblin", "rcgoblin", 145.f, VehicleCategory::RCVehicles } },
	{ 502,{ "Hotring Racer A", "HotringRacerA", "hotrina", 216.f, VehicleCategory::SportVehicles } },
	{ 503,{ "Hotring Racer B", "HotringRacerB", "hotrinb", 216.f, VehicleCategory::SportVehicles } },
	{ 504,{ "Bloodring Banger", "BloodringBanger", "bloodra / bloodrb", 173.f, VehicleCategory::Saloons } },
	{ 505,{ "Rancher Lure", "RancherLure", "rnchlure", 140.f, VehicleCategory::OffRoad } },
	{ 506,{ "Super GT", "SuperGT", "supergt", 179.f, VehicleCategory::SportVehicles } },
	{ 507,{ "Elegant", "Elegant", "elegant", 166.f, VehicleCategory::Saloons } },
	{ 508,{ "Journey", "Journey", "journey", 108.f, VehicleCategory::UniqueVehicles } },
	{ 509,{ "Bike", "Bike", "bike", 79.f, VehicleCategory::Bikes } },
	{ 510,{ "Mountain Bike", "MountainBike", "mtbike", 101.f, VehicleCategory::Bikes } },
	{ 511,{ "Beagle", "Beagle", "beagle", 270.f, VehicleCategory::Airplanes } },
	{ 512,{ "Cropduster", "Cropduster", "cropdust", 270.f, VehicleCategory::Airplanes } },
	{ 513,{ "Stuntplane", "Stuntplane", "stunt", 270.f, VehicleCategory::Airplanes } },
	{ 514,{ "Tanker", "Tanker", "petro", 120.f, VehicleCategory::Industrial } },
	{ 515,{ "Roadtrain", "Roadtrain", "rdtrain", 142.f, VehicleCategory::Industrial } },
	{ 516,{ "Nebula", "Nebula", "nebula", 157.f, VehicleCategory::Saloons } },
	{ 517,{ "Majestic", "Majestic", "majestic", 157.f, VehicleCategory::Saloons } },
	{ 518,{ "Buccaneer", "Buccaneer", "buccanee", 164.f, VehicleCategory::Saloons } },
	{ 519,{ "Shamal", "Shamal", "shamal", 270.f, VehicleCategory::Airplanes } },
	{ 520,{ "Hydra", "Hydra", "hydra", 270.f, VehicleCategory::Airplanes } },
	{ 521,{ "FCR-900", "FCR900", "fcr900", 160.f, VehicleCategory::Bikes } },
	{ 522,{ "NRG-500", "NRG500", "nrg500", 176.f, VehicleCategory::Bikes } },
	{ 523,{ "HPV1000", "HPV1000", "copbike", 151.f, VehicleCategory::PublicService } },
	{ 524,{ "Cement Truck", "CementTruck", "cement", 130.f, VehicleCategory::Industrial } },
	{ 525,{ "Towtruck", "Towtruck", "towtruck", 160.f, VehicleCategory::UniqueVehicles } },
	{ 526,{ "Fortune", "Fortune", "fortune", 158.f, VehicleCategory::Saloons } },
	{ 527,{ "Cadrona", "Cadrona", "cadrona", 149.f, VehicleCategory::Saloons } },
	{ 528,{ "FBI Truck", "FBITruck", "fbitruck", 176.f, VehicleCategory::PublicService } },
	{ 529,{ "Willard", "Willard", "willard", 149.f, VehicleCategory::Saloons } },
	{ 530,{ "Forklift", "Forklift", "forklift", 60.f, VehicleCategory::UniqueVehicles } },
	{ 531,{ "Tractor", "Tractor", "tractor", 70.f, VehicleCategory::Industrial } },
	{ 532,{ "Combine Harvester", "CombineHarvester", "combine", 110.f, VehicleCategory::UniqueVehicles } },
	{ 533,{ "Feltzer", "Feltzer", "feltzer", 167.f, VehicleCategory::Convertibles } },
	{ 534,{ "Remington", "Remington", "remingtn", 168.f, VehicleCategory::Lowriders } },
	{ 535,{ "Slamvan", "Slamvan", "slamvan", 158.f, VehicleCategory::Lowriders } },
	{ 536,{ "Blade", "Blade", "blade", 173.f, VehicleCategory::Lowriders } },
	{ 537,{ "Freight (Train)", "FreightTrain", "freight", 0.f, VehicleCategory::UniqueVehicles } },
	{ 538,{ "Brownstreak (Train)", "BrownstreakTrain", "streak", 0.f, VehicleCategory::UniqueVehicles } },
	{ 539,{ "Vortex", "Vortex", "vortex", 270.f, VehicleCategory::UniqueVehicles } },
	{ 540,{ "Vincent", "Vincent", "vincent", 149.f, VehicleCategory::Saloons } },
	{ 541,{ "Bullet", "Bullet", "bullet", 203.f, VehicleCategory::SportVehicles } },
	{ 542,{ "Clover", "Clover", "clover", 164.f, VehicleCategory::Saloons } },
	{ 543,{ "Sadler", "Sadler", "sadler", 151.f, VehicleCategory::Industrial } },
	{ 544,{ "Firetruck LA", "FiretruckLA", "firela", 150.f, VehicleCategory::PublicService } },
	{ 545,{ "Hustler", "Hustler", "hustler", 147.f, VehicleCategory::UniqueVehicles } },
	{ 546,{ "Intruder", "Intruder", "intruder", 149.f, VehicleCategory::Saloons } },
	{ 547,{ "Primo", "Primo", "primo", 142.f, VehicleCategory::Saloons } },
	{ 548,{ "Cargobob", "Cargobob", "cargobob", 270.f, VehicleCategory::Helicopters } },
	{ 549,{ "Tampa", "Tampa", "tampa", 153.f, VehicleCategory::Saloons } },
	{ 550,{ "Sunrise", "Sunrise", "sunrise", 145.f, VehicleCategory::Saloons } },
	{ 551,{ "Merit", "Merit", "merit", 157.f, VehicleCategory::Saloons } },
	{ 552,{ "Utility Van", "UtilityVan", "utility", 121.f, VehicleCategory::Industrial } },
	{ 553,{ "Nevada", "Nevada", "nevada", 270.f, VehicleCategory::Airplanes } },
	{ 554,{ "Yosemite", "Yosemite", "yosemite", 144.f, VehicleCategory::Industrial } },
	{ 555,{ "Windsor", "Windsor", "windsor", 158.f, VehicleCategory::Convertibles } },
	{ 556,{ "Monster A", "MonsterA", "monstera", 113.f, VehicleCategory::OffRoad } },
	{ 557,{ "Monster B", "MonsterB", "monsterb", 113.f, VehicleCategory::OffRoad } },
	{ 558,{ "Uranus", "Uranus", "uranus", 156.f, VehicleCategory::SportVehicles } },
	{ 559,{ "Jester", "Jester", "jester", 178.f, VehicleCategory::SportVehicles } },
	{ 560,{ "Sultan", "Sultan", "sultan", 169.f, VehicleCategory::Saloons } },
	{ 561,{ "Stratum", "Stratum", "stratum", 154.f, VehicleCategory::StationWagons } },
	{ 562,{ "Elegy", "Elegy", "elegy", 178.f, VehicleCategory::Saloons } },
	{ 563,{ "Raindance", "Raindance", "raindanc", 270.f, VehicleCategory::Helicopters } },
	{ 564,{ "RC Tiger", "RCTiger", "rctiger", 145.f, VehicleCategory::RCVehicles } },
	{ 565,{ "Flash", "Flash", "flash", 165.f, VehicleCategory::SportVehicles } },
	{ 566,{ "Tahoma", "Tahoma", "tahoma", 160.f, VehicleCategory::Lowriders } },
	{ 567,{ "Savanna", "Savanna", "savanna", 173.f, VehicleCategory::Lowriders } },
	{ 568,{ "Bandito", "Bandito", "bandito", 146.f, VehicleCategory::OffRoad } },
	{ 569,{ "Freight Flat Trailer (Train)", "FreightFlatTrailerTrain", "freiflat", 0.f, VehicleCategory::Trailers } },
	{ 570,{ "Streak Trailer (Train)", "StreakTrailerTrain", "streakc", 0.f, VehicleCategory::Trailers } },
	{ 571,{ "Kart", "Kart", "kart", 93.f, VehicleCategory::UniqueVehicles } },
	{ 572,{ "Mower", "Mower", "mower", 60.f, VehicleCategory::UniqueVehicles } },
	{ 573,{ "Dune", "Dune", "duneride", 110.f, VehicleCategory::OffRoad } },
	{ 574,{ "Sweeper", "Sweeper", "sweeper", 60.f, VehicleCategory::UniqueVehicles } },
	{ 575,{ "Broadway", "Broadway", "broadway", 158.f, VehicleCategory::Lowriders } },
	{ 576,{ "Tornado", "Tornado", "tornado", 158.f, VehicleCategory::Lowriders } },
	{ 577,{ "AT400", "AT400", "at400", 270.f, VehicleCategory::Airplanes } },
	{ 578,{ "DFT-30", "DFT30", "dft30", 130.f, VehicleCategory::Industrial } },
	{ 579,{ "Huntley", "Huntley", "huntley", 158.f, VehicleCategory::OffRoad } },
	{ 580,{ "Stafford", "Stafford", "stafford", 153.f, VehicleCategory::Saloons } },
	{ 581,{ "BF-400", "BF400", "bf400", 151.f, VehicleCategory::Bikes } },
	{ 582,{ "Newsvan", "Newsvan", "newsvan", 136.f, VehicleCategory::Industrial } },
	{ 583,{ "Tug", "Tug", "tug", 85.f, VehicleCategory::UniqueVehicles } },
	{ 584,{ "Petrol Trailer", "PetrolTrailer", "petrotr", 0.f, VehicleCategory::Trailers } },
	{ 585,{ "Emperor", "Emperor", "emperor", 153.f, VehicleCategory::Saloons } },
	{ 586,{ "Wayfarer", "Wayfarer", "wayfarer", 142.f, VehicleCategory::Bikes } },
	{ 587,{ "Euros", "Euros", "euros", 165.f, VehicleCategory::SportVehicles } },
	{ 588,{ "Hotdog", "Hotdog", "hotdog", 108.f, VehicleCategory::UniqueVehicles } },
	{ 589,{ "Club", "Club", "club", 162.f, VehicleCategory::SportVehicles } },
	{ 590,{ "Freight Box Trailer (Train)", "FreightBoxTrailerTrain", "freibox", 0.f, VehicleCategory::Trailers } },
	{ 591,{ "Article Trailer 3", "ArticleTrailer", "artict3", 0.f, VehicleCategory::Trailers } },
	{ 592,{ "Andromada", "Andromada", "androm", 270.f, VehicleCategory::Airplanes } },
	{ 593,{ "Dodo", "Dodo", "dodo", 270.f, VehicleCategory::Airplanes } },
	{ 594,{ "RC Cam", "RCCam", "rccam", 130.f, VehicleCategory::RCVehicles } },
	{ 595,{ "Launch", "Launch", "launch", 190.f, VehicleCategory::Boats } },
	{ 596,{ "Police Car (LSPD)", "PoliceCarLSPD", "copcarla", 175.f, VehicleCategory::PublicService } },
	{ 597,{ "Police Car (SFPD)", "PoliceCarSFPD", "copcarsf", 175.f, VehicleCategory::PublicService } },
	{ 598,{ "Police Car (LVPD)", "PoliceCarLVPD", "copcarvg", 175.f, VehicleCategory::PublicService } },
	{ 599,{ "Police Ranger", "PoliceRanger", "copcarru", 158.f, VehicleCategory::PublicService } },
	{ 600,{ "Picador", "Picador", "picador", 151.f, VehicleCategory::Industrial } },
	{ 601,{ "S.W.A.T.", "SWAT", "swatvan", 110.f, VehicleCategory::PublicService } },
	{ 602,{ "Alpha", "Alpha", "alpha", 169.f, VehicleCategory::SportVehicles } },
	{ 603,{ "Phoenix", "Phoenix", "phoenix", 171.f, VehicleCategory::SportVehicles } },
	{ 604,{ "Glendale Shit", "GlendaleShit", "glenshit", 148.f, VehicleCategory::Saloons } },
	{ 605,{ "Sadler Shit", "SadlerShit", "sadlshit", 152.f, VehicleCategory::Industrial } },
	{ 606,{ "Baggage Trailer A", "BaggageTrailerA", "bagboxa", 0.f, VehicleCategory::Trailers } },
	{ 607,{ "Baggage Trailer B", "BaggageTrailerB", "bagboxb", 0.f, VehicleCategory::Trailers } },
	{ 608,{ "Tug Stairs Trailer", "TugStairsTrailer", "tugstair", 0.f, VehicleCategory::Trailers } },
	{ 609,{ "Boxville", "Boxville", "boxburg", 108.f, VehicleCategory::Industrial } },
	{ 610,{ "Farm Trailer", "FarmTrailer", "farmtr1", 0.f, VehicleCategory::Trailers } },
	{ 611,{ "Utility Trailer", "UtilityTrailer", "utiltr1", 0.f, VehicleCategory::Trailers } },
};

/// <summary>
/// Class storing vehicle handle and providing methods to manage it.
/// </summary>
class Vehicle
	: public IWI3DNode
{
public:
	// The base class:
	using Super = IWI3DNode;

	// Aliases:
	using Colors = std::pair<Int32, Int32>;

	// Constants:
	constexpr static Int32 InvalidHandle = INVALID_VEHICLE_ID;

	/// <summary>
	/// Initializes a new instance of the <see cref="Vehicle"/> class.
	/// </summary>
	Vehicle();

	/// <summary>
	/// Finalizes an instance of the <see cref="Vehicle"/> class.
	/// </summary>
	virtual ~Vehicle();

	/// <summary>
	/// Respawns this vehicle.
	/// </summary>
	void respawn();

	/// <summary>
	/// Repairs this vehicle.
	/// </summary>
	void repair();

	/// <summary>
	/// Sets the vehicle health.
	/// </summary>
	/// <param name="health_">The health.</param>
	/// <remarks>
	/// <para>100% health equals 1000.0f, 50% health equals 500.f, etc.</para>
	/// </remarks>
	void setHealth(float health_);


	/// <summary>
	/// Sets the vehicle world. If vehicle is spawned changes will be applied instantly.
	/// </summary>
	/// <param name="world_">The world.</param>
	virtual void setWorld(Int32 world_) override;
	
	/// <summary>
	/// Sets the vehicle interior. If vehicle is spawned changes will be applied instantly.
	/// </summary>
	/// <param name="interior_">The interior.</param>
	virtual void setInterior(Int32 interior_) override;

	/// <summary>
	/// Sets the vehicle location. If vehicle is spawned changes will be applied instantly.
	/// </summary>
	/// <param name="location_">The location.</param>
	virtual void setLocation(math::Vector3f const & location_) override;

	/// <summary>
	/// Sets the vehicle facing angle. If vehicle is spawned changes will be applied instantly.
	/// </summary>
	/// <param name="angle_">The angle.</param>
	void setFacingAngle(float angle_);

	/// <summary>
	/// Sets the vehicle speed in current direction. Works only when vehicle is spawned.
	/// </summary>
	/// <param name="speed_">The speed.</param>
	void setSpeed(float speed_);

	/// <summary>
	/// Sets the vehicle velocity. Works only when vehicle is spawned.
	/// </summary>
	/// <param name="velocity_">The velocity.</param>
	void setVelocity(math::Vector3f const & velocity_);
	
	/// <summary>
	/// Sets the vehicle model. Automatically respawns vehicle if was spawned before.
	/// </summary>
	/// <param name="modelIndex_">Index of the model.</param>
	void setModel(Int32 modelIndex_);

	/// <summary>
	/// Sets the vehicle first color. If vehicle is spawned changes will be applied instantly.
	/// </summary>
	/// <param name="color_">The color.</param>
	void setFirstColor(Int32 color_);

	/// <summary>
	/// Sets the vehicle second color. If vehicle is spawned changes will be applied instantly.
	/// </summary>
	/// <param name="color_">The color.</param>
	void setSecondColor(Int32 color_);
	
	/// <summary>
	/// Installs the nitro.
	/// </summary>
	void installNitro();

	/// <summary>
	/// Uninstalls the nitro.
	/// </summary>
	void uninstallNitro();

	/// <summary>
	/// Flips this vehicle.
	/// </summary>
	void flip();

	/// <summary>
	/// Returns the vehicle location.
	/// </summary>
	/// <returns>Vehicle's location.</returns>
	virtual math::Vector3f getLocation() const override;

	/// <summary>
	/// Returns the vehicle velocity or zero vector if not spawned.
	/// </summary>
	/// <returns>Vehicle's velocity.</returns>
	math::Vector3f getVelocity() const;

	/// <summary>
	/// Returns vehicle speed in specified units (km/h by default).
	/// </summary>
	/// <param name="unit_">The unit.</param>
	/// <returns>Vehicle's speed.</returns>
	float getSpeed(SpeedUnit unit_ = SpeedUnit::KMPH) const;

	/// <summary>
	/// Returns the vehicle rotation axis.
	/// </summary>
	/// <returns>Vehicle's angle in each axis.</returns>
	math::Vector3f getRotationAxis() const;

	/// <summary>
	/// Returns the vehicle forward vector. It does take into consideration ONLY Z axis angle. TODO: consider also other angles.
	/// </summary>
	/// <returns>Vehicle's forward vector</returns>
	math::Vector3f getForwardVector() const;
	
	/// <summary>
	/// Returns the vehicle backward vector. It does take into consideration ONLY Z axis angle. TODO: consider also other angles.
	/// </summary>
	/// <returns>Vehicle's backward vector.</returns>
	math::Vector3f getBackwardVector() const;

	/// <summary>
	/// Returns the vehicle right vector. It does take into consideration ONLY Z axis angle. TODO: consider also other angles.
	/// </summary>
	/// <returns>Vehicle's right vector.</returns>
	math::Vector3f getRightVector() const;

	/// <summary>
	/// Returns the vehicle left vector. It does take into consideration ONLY Z axis angle. TODO: consider also other angles.
	/// </summary>
	/// <returns>Vehicle's left vector.</returns>
	math::Vector3f getLeftVector() const;
	
	/// <summary>
	/// Returns the vehicle facing angle (angle around z-axis).
	/// </summary>
	/// <returns>Vehicles's facing angle.</returns>
	float getFacingAngle() const;

	/// <summary>
	/// Returns the vehicle health.
	/// </summary>
	/// <returns>Vehicle's health.</returns>
	float getHealth() const;
	
	/// <summary>
	/// Returns SAMP internal vehicle handle or `InvalidHandle` if not spawned.
	/// </summary>
	/// <returns>SAMP internal vehicle handle.</returns>
	Int32 getHandle() const;

	/// <summary>
	/// Returns the vehicle model.
	/// </summary>
	/// <returns>Vehicle's model.</returns>
	Int32 getModel() const;

	/// <summary>
	/// Returns the world vehicle is bound to (acquires it from the actual vehicle in the world).
	/// </summary>
	/// <returns>Vehicle's world.</returns>
	Int32 getClientWorld() const;

	/// <summary>
	/// Returns the vehicle placement.
	/// </summary>
	/// <returns>The vehicle placement.</returns>
	VehiclePlacement getPlacement() const;

	/// <summary>
	/// Returns vehicle first color index.
	/// </summary>
	/// <returns>Vehicle's first color index.</returns>
	Int32 getFirstColor() const;

	/// <summary>
	/// Returns vehicle second color index.
	/// </summary>
	/// <returns>Vehicle's second color index.</returns>
	Int32 getSecondColor() const;

	/// <summary>
	/// Returns the latest usage time point.
	/// </summary>
	/// <returns>Latest usage time point.</returns>
	Clock::TimePoint getLatestUsage() const;

	/// <summary>
	/// Returns the vehicle driver or nullptr if not driven.
	/// </summary>
	/// <returns></returns>
	Player* getDriver() const;

	/// <summary>
	/// Returns cref to the vehicle passengers.
	/// </summary>
	/// <returns>cref to the vehicle passengers.</returns>
	auto const& getPassengers() const
	{
		return m_passengers;
	}

	/// <summary>
	/// Returns count of passengers currently sitting in the vehicle.
	/// </summary>
	/// <returns>Count of passengers currently sitting in the vehicle.</returns>
	std::size_t getPassengersCount() const {
		return std::count_if(m_passengers.begin(), m_passengers.end(), [](Player* p) { return p != nullptr; });
	}

	/// <summary>
	/// Determines whether this vehicle is spawned.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this vehicle is spawned; otherwise, <c>false</c>.
	/// </returns>
	bool isSpawned() const;

	/// <summary>
	/// Determines whether this vehicle is occupied by any player.
	/// </summary>
	/// <returns>
	///   <c>true</c> if this vehicle is occupied by any player; otherwise, <c>false</c>.
	/// </returns>
	bool isOccupied() const;


	// Streaming functions and the placement tracker:

	/// <summary>
	/// Spawns the vehicle.
	/// </summary>
	/// <returns>
	///		<c>true</c> if spawn succeeded; otherwise, <c>false</c>.
	/// </returns>
	bool spawn();

	/// <summary>
	/// Despawns this vehicle.
	/// </summary>
	void despawn();

	/// <summary>
	/// Sets the placement tracker, used to properly stream vehicle.
	/// </summary>
	/// <param name="tracker_">The tracker.</param>
	void setPlacementTracker(I3DNodePlacementTracker *tracker_);

	/// <summary>
	/// Returns pointer the placement tracker.
	/// </summary>
	/// <returns>Pointer to the placement tracker, or nullptr if not set.</returns>
	I3DNodePlacementTracker* getPlacementTracker() const;

	/// <summary>
	/// Sends the placement update to the tracker.
	/// </summary>
	void sendPlacementUpdate();

	// Static functions:

	/// <summary>
	/// Determines whether specified model index is valid for lazy spawn.
	/// </summary>
	/// <param name="modelIndex_">Index of the model.</param>
	/// <returns>
	///   <c>true</c> if specified model index is valid for lazy spawn; otherwise, <c>false</c>.
	/// </returns>
	/// <remarks>
	/// <para>Vehicle is valid for "lazy spawn" if it can be spawned without any unexpected behaviour (like spawning trains makes invisible vehicles that crash game when trying to enter).</para>
	/// </remarks>
	static bool isValidForLazySpawn(Int32 const modelIndex_);

	/// <summary>
	/// Returns the vehicle model category.
	/// </summary>
	/// <param name="modelIndex_">Index of the model.</param>
	/// <returns>Vehicle model category.</returns>
	static VehicleCategory getModelCategory(Int32 const modelIndex_);

	/// <summary>
	/// Finds the model index by finding best match.
	/// </summary>
	/// <param name="name_">The name.</param>
	/// <param name="minimalScore_">The minimal score (min. number of characters matching in sequence).</param>
	/// <returns>Model index or -1 if not found.</returns>
	static Int32 findModelBestMatch(std::string const & name_, std::size_t const minimalScore_ = 3);

	/// <summary>
	/// Returns the 3D size of the vehicle model.
	/// </summary>
	/// <param name="modelIndex_">Index of the model.</param>
	/// <returns>3D size of the vehicle model.</returns>
	static math::Vector3f getModelSize(Int32 const modelIndex_);


	friend class MapClass;
	friend class ServerClass;
	friend class Player;
protected:

	/// <summary>
	/// Called when player enters vehicle
	/// </summary>
	/// <param name="player_">The player.</param>
	/// <param name="seatIndex_">The seat index (0 = driver).</param>
	void whenPlayerEnters(Player & player_, Int32 const seatIndex_);
	
	/// <summary>
	/// Called when player exits vehicle or player dies inside or falls off the bike.
	/// </summary>
	/// <param name="player_">The player.</param>
	void whenPlayerExits(Player & player_);

	Int32								m_handle;			// Handle for SAMP object. `InvalidHandle` if not spawned
	Int32								m_modelIndex;		// Vehicle Model ID
	math::Vector3f						m_location;			// Vehicle's location.			It is NOT updated at real time. Its used when vehicle is not spawned.
	float								m_facingAngle;		// Vehicle's angle.				It is NOT updated at real time. Its used when vehicle is not spawned.
	Int32								m_firstColor;		// Vehicle's first color.		It is NOT updated at real time. Its used when vehicle is not spawned.
	Int32								m_secondColor;		// Vehicle's second color.		It is NOT updated at real time. Its used when vehicle is not spawned.

	Clock::TimePoint					m_latestUsage;		// Absolute time vehicle was used last time.
	std::array<Player*, 6>				m_passengers;

private:

	I3DNodePlacementTracker*			m_placementTracker;
};


/// <summary>
/// A vehicle that returns to it's original location when destroyed.
/// </summary>
/// <seealso cref="Vehicle" />
class StaticVehicle final
	: public Vehicle
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="StaticVehicle"/> class.
	/// </summary>
	StaticVehicle();

	/// <summary>
	/// Sets the vehicle spawn location.
	/// </summary>
	/// <param name="location_">The location.</param>
	void setSpawnLocation(math::Vector3f const & location_);
	
	/// <summary>
	/// Sets the vehicle spawn facing angle.
	/// </summary>
	/// <param name="angle_">The angle.</param>
	void setSpawnFacingAngle(float const angle_);
	
	/// <summary>
	/// Sets the vehicle spawn world.
	/// </summary>
	/// <param name="world_">The world.</param>
	void setSpawnWorld(Int32 const world_);
	
	/// <summary>
	/// Sets the vehicle spawn interior.
	/// </summary>
	/// <param name="interior_">The interior.</param>
	void setSpawnInterior(Int32 const interior_);

	/// <summary>
	/// Sets the vehicle spawn first color.
	/// </summary>
	/// <param name="firstColor_">The first color.</param>
	void setSpawnFirstColor(Int32 const firstColor_);
	
	/// <summary>
	/// Sets the vehicle spawn second color.
	/// </summary>
	/// <param name="secondColor_">The second color..</param>
	void setSpawnSecondColor(Int32 const secondColor_);

	/// <summary>
	/// Restores to vehicle spawn.
	/// </summary>
	void restoreToSpawn();

	/// <summary>
	/// Returns the vehicle spawn location.
	/// </summary>
	/// <returns>Vehicle's spawn location.</returns>
	math::Vector3f getSpawnLocation() const;

	/// <summary>
	/// Returns the vehicle spawn facing angle.
	/// </summary>
	/// <returns>Vehicle's spawn facing angle.</returns>
	float getSpawnFacingAngle() const;

	/// <summary>
	/// Returns the vehicle spawn world.
	/// </summary>
	/// <returns>Vehicle's spawn world.</returns>
	Int32 getSpawnWorld() const;

	/// <summary>
	/// Returns the vehicle spawn interior.
	/// </summary>
	/// <returns>Vehicle's spawn interior.</returns>
	Int32 getSpawnInterior() const;

	/// <summary>
	/// Returns the vehicle spawn first color.
	/// </summary>
	/// <returns>Vehicle's spawn first color.</returns>
	Int32 getSpawnFirstColor() const;

	/// <summary>
	/// Returns the vehicle spawn second color.
	/// </summary>
	/// <returns>Vehicle's spawn second color.</returns>
	Int32 getSpawnSecondColor() const;

private:	

	math::Vector3f		m_spawnLocation;			// Spawn location
	float				m_spawnAngle;				// Spawn angle
	Int32				m_spawnWorld;				// Spawn world
	Int32				m_spawnInterior;			// Spawn interior

	Int32				m_spawnFirstColor;			// Spawn first color
	Int32				m_spawnSecondColor;			// Spawn second color

}; // class StaticVehicle

} // namespace agdk