
#include <SAMP-EDGEngine/Everything.hpp>
#include <SAMP-EDGEngine/Ext/ResourceIO/Everything.hpp>
#include <iostream>
#include <fstream>

#include <filesystem>
namespace fs = std::filesystem;

namespace samp = samp_edgengine;
namespace rcio = samp_edgengine::ext::resource_io;

void cmd_TeleportToLocation(samp::CommandInput input_)
{
	auto params = input_.splitParams();
	if (params.size() >= 3)
	{
		samp::math::Vector3f location;
		location.x = samp::text::convert<float>(params[0]).value();
		location.y = samp::text::convert<float>(params[1]).value();
		location.z = samp::text::convert<float>(params[2]).value();
		input_.target.setLocation(location);
		if (params.size() >= 5)
		{
			std::int32_t world		= samp::text::convert<std::int32_t>(params[3]).value();
			std::int32_t interior	= samp::text::convert<std::int32_t>(params[4]).value();
			input_.target.setWorld(world);
			input_.target.setInterior(interior);
		}
	}
}

void cmd_SpawnVehicle(samp::CommandInput input_)
{
	auto params = input_.splitParams();
	if (params.size() == 1)
	{
		auto pVeh = GameMode->map.beginConstruction<samp::Vehicle>();
		pVeh->setModel(samp::Vehicle::findModelBestMatch(params[0]));
		pVeh->setLocation(input_.target.getLocation());
		pVeh->setFacingAngle(input_.target.getFacingAngle());
		pVeh->setInterior(input_.target.getInterior());
		pVeh->setWorld(input_.target.getWorld());
		auto &veh = GameMode->map.finalizeConstruction(pVeh);
		input_.target.putInVehicle(veh, 0);
	}
}

void cmd_ObjectCount(samp::CommandInput input_)
{
	namespace txt = samp::text;
	auto tracker = static_cast<samp::default_streamer::PlayerWrapper*>(input_.target.getPlacementTracker());
	GameMode->chat->messagePlayer(input_.target, txt::compose("You have currently ", tracker->spawnedObjects.size(), " objects shown!"));
}

class MyGameMode
	: public samp::IGameMode
{
public:
	using Super = samp::IGameMode;

	MyGameMode(samp::ServerClass &server_ )
		: Super{ server_ }
	{	
		this->addPlayerClass(0, { 280, 180, 1010 }, 0, { samp::Weapon(samp::Weapon::Deagle, 999) });
	}
	
	virtual void setup() override
	{
		samp::IGameMode::setup();

		// Setup chat:
		chat = std::make_unique<samp::DefaultChat>(*this);
		
		// Setup command handler:
		commands = std::make_unique<samp::DefaultCommandHandler>(*this);
		server.onPlayerCommandText += { *commands, &samp::ICommandHandler::whenPlayerSendsCommandText };

		this->setupCommands();
		this->loadObjects();
	}

	void loadObjects()
	{
		for (auto& file : fs::directory_iterator("data/objects"))
		{
			if (fs::is_regular_file(file))
			{
				std::clog << "[i]: Reading file: " << file.path() << std::endl;

				// Open file:
				std::ifstream inputStream{ file.path().string() };

				auto scene = GameMode->map.beginConstruction<samp::Scene>();

				// Create XML document:
				rcio::xml::xml_document<> document;

				// Read entire file to the string:
				std::string inputContent;
				{
					char buffer[4 * 1024];
					while (inputStream.read(buffer, sizeof(buffer)))
						inputContent.append(buffer, sizeof(buffer));
					inputContent.append(buffer, inputStream.gcount());
				}
				
				// Make sure string is null terminated:
				inputContent.push_back(0);
				// Parse the document:
				document.parse<0>(inputContent.data());

				if (auto rootNode = document.first_node("MapScene"))
				{
					// Deserialize the scene:
					rcio::XMLSceneDeserializer deserializer{ *scene, *rootNode };
					if (deserializer.deserialize())
					{
						GameMode->map.finalizeConstruction(scene);
						std::cout << "Read: " << scene->getObjects().size() << " objects!" << std::endl;
					}
				}
				
			}
		}

	}

	virtual void setupEvents() override {
		Server->onPlayerSpawn += { *this, &MyGameMode::whenPlayerSpawns };
	}

	void whenPlayerSpawns(samp::Player & player_)
	{
		player_.setLocation({ 1958.33f, 1343.12f, 15.36f });
		player_.setWorld(0);
		player_.addWeapon(samp::Weapon(samp::Weapon::Deagle, 999));
	}

	void setupCommands()
	{
		auto& cmds = static_cast<samp::DefaultCommandHandler&>(*commands);
		cmds.add( samp::ProcedureCommand( { "tpc" }, cmd_TeleportToLocation ) );
		cmds.add( samp::ProcedureCommand( { "v" }, cmd_SpawnVehicle ) );
		cmds.add( samp::ProcedureCommand( { "objc" }, cmd_ObjectCount) );
	}
};

samp::GameModeSetupResult SAMPGameModeSetup()
{
	return std::make_unique<MyGameMode>(*Server);
}