#pragma once

#include SAMPCPP_PCH

namespace samp_cpp
{

enum class CameraInterpMode
{
	CameraSmooth 	= CAMERA_MOVE,
	CameraCut 		= CAMERA_CUT
};

// Description source:
// http://wiki.sa-mp.com/wiki/CameraModes
enum class CameraMode
{
	Train						= 3,				// Train/tram camera.
	FollowPed					= 4,				// Follow ped (normal behind player camera).
	Sniper						= 7,				// Sniper aiming.
	RocketLauncher				= 8,				// Rocket Launcher aiming.
	Fixed						= 15,				// Fixed camera (non-moving) - used for Pay 'n' Spray, chase camera, tune shops, entering buildings, buying food etc.
	VehicleFront				= 16,				// Vehicle front camera, bike side camera.
	NormalCar					= 18,				// Normal car (+skimmer+helicopter+airplane), several variable distances.
	NormalBoat					= 22,				// Normal boat camera.
	TakePicture					= 46,				// Camera weapon aiming.
	HSRocketLauncher			= 51,				// Heat-seeking Rocket Launcher aiming.
	NormalWeapon				= 53,				// Aiming any other weapon.
	DriveBy						= 55,				// Vehicle passenger drive-by camera.
	Chase_1						= 56,				// Chase camera: helicopter/bird view.
	Chase_2						= 57,				// Chase camera: ground camera, zooms in very quickly. (Similar to 56, but on the ground.)
	Chase_3						= 58,				// Chase camera: horizontal flyby past vehicle.
	Chase_4						= 59,				// Chase camera (for air vehicles only): ground camera, looking up to the air vehicle.
	Chase_5						= 62,				// Chase camera (for air vehicles only): vertical flyby past air vehicle.
	Chase_6						= 63,				// Chase camera (for air vehicles only): horizontal flyby past air vehicle (similar to 58 and 62).
	Chase_7						= 64				// Chase camera (for air vehicles only): camera focused on pilot, similar to pressing LOOK_BEHIND key on foot, but in air vehicle.
};

enum class PlayerStatus
{
	None = 0,
	OnFoot = 1,
	Driver = 2,
	Passenger = 3,
	ExitVehicle = 4,
	EnterAsDriver = 5,
	EnterAsPassenger = 6,
	Wasted = 7,
	Spawned = 8,
	Spectating = 9
};

}