#include <SAMP-EDGEngine/Ext/ResourceIO/PAWNSceneDeserializer.hpp>

namespace samp_edgengine::ext::resource_io
{

/////////////////////////////////////////////////////////////////////////////////
bool PAWNSceneDeserializer::deserialize() const
{
	auto const colorFromARGBString = [](std::string string_) -> std::optional< Uint32 >
		{
			
			try
			{
				return std::stoul(string_, nullptr, string_.find_first_of("xX") == std::string::npos ? 10 : 16);
			}
			catch(...) {
			}
			return {};
		};

	using VisMode = PerPlayerObject::VisibilityMode;

	VisMode			worldVisibility		= VisMode::Everywhere;
	VisMode			interiorVisibility	= VisMode::Everywhere;
	std::int32_t	world				= 0;
	std::int32_t	interior			= 0;
	float			drawDistance		= -1;

	std::unique_ptr<UniversalObject> mapObject;

	std::size_t		lineNumber = 0;
	while (!inputStream.eof())
	{
		// Read next line from stream:
		std::string line;
		std::getline(inputStream, line);

		lineNumber++;

		// Check if the line isn't a comment.
		if (auto trimmed = text::ascii::trimLeft(line); trimmed.length() >= 2 && trimmed.substr(0, 2) == "//")
			continue;

		// Handle line contents:
		// Note: this method is very primitive and should be reimplemented to be more scalable and faster (current method is very slow).

		// Handle attributes:
		if (auto pos = line.find("[[world]]"); pos != std::string::npos)
		{
			line = line.substr(pos + 9);

			std::istringstream lineStream{ line };

			if (lineStream >> text::skipIf<'('>)
			{
				lineStream >> world;
				if (mapObject)
				{
					mapObject->setWorld( world );
				}
			}
		}
		else if (auto pos = line.find("[[interior]]"); pos != std::string::npos)
		{
			line = line.substr(pos + 12);

			std::istringstream lineStream{ line };

			if (lineStream >> text::skipIf<'('>)
			{
				lineStream >> interior;
				if (mapObject)
					mapObject->setInterior( interior );
			}
		}
		else if (line.find("[[world_every]]") != std::string::npos)
		{
			worldVisibility = VisMode::Everywhere;
			if (mapObject)
				mapObject->setWorldMode( worldVisibility );
		}
		else if (line.find("[[world_specified]]") != std::string::npos)
		{
			worldVisibility = VisMode::Specified;
			if (mapObject)
				mapObject->setWorldMode(worldVisibility);
		}
		else if (line.find("[[world_allbutspecified]]") != std::string::npos)
		{
			worldVisibility = VisMode::AllButSpecified;
			if (mapObject)
				mapObject->setWorldMode(worldVisibility);
		}
		else if (line.find("[[interior_every]]") != std::string::npos)
		{
			interiorVisibility = VisMode::Everywhere;
			if (mapObject)
				mapObject->setInteriorMode(interiorVisibility);
		}
		else if (line.find("[[interior_specified]]") != std::string::npos)
		{
			interiorVisibility = VisMode::Specified;
			if (mapObject)
				mapObject->setInteriorMode(interiorVisibility);
		}
		else if (line.find("[[interior_allbutspecified]]") != std::string::npos)
		{
			interiorVisibility = VisMode::AllButSpecified;
			if (mapObject)
				mapObject->setInteriorMode(interiorVisibility);
		}
		else if (auto pos = line.find("[[draw_distance]]"); pos != std::string::npos)
		{
			line = line.substr(pos + 17);

			std::istringstream lineStream{ line };

			if (lineStream >> text::skipIf<'('>)
			{
				lineStream >> drawDistance;
				if (mapObject)
				{
					mapObject->setDrawDistance( drawDistance );
				}
			}
		}
		else if (auto pos = line.find("CreateObject"); pos != std::string::npos)
		{
			line = line.substr(pos + 12);

			std::istringstream lineStream(line);

			std::int32_t	modelIndex = -1;
			math::Vector3f	location;
			math::Vector3f	rotation;

			if (lineStream >>
				text::skipIf<'('> >> modelIndex >>
				text::skipIf<','> >> location.x >> text::skipIf<','> >> location.y >> text::skipIf<','> >> location.z >>
				text::skipIf<','> >> rotation.x >> text::skipIf<','> >> rotation.y >> text::skipIf<','> >> rotation.z)
			{
				if (modelIndex != -1)
				{
					if (mapObject)
					{
						scene.finalizeConstruction( std::move(mapObject) );
					}

					mapObject = std::make_unique<UniversalObject>();

					mapObject->setModel(modelIndex);
					mapObject->setLocation(location);
					mapObject->setRotation(rotation);
					mapObject->setDrawDistance(drawDistance);

					mapObject->setWorld(world);
					mapObject->setWorldMode(worldVisibility);
					mapObject->setInterior(interior);
					mapObject->setInteriorMode(interiorVisibility);
				}
			}
		}
		else if (auto pos = line.find("SetObjectMaterial(tmpobjid"); pos != std::string::npos && mapObject)
		{
			line = line.substr(pos + 26);
			line = line.substr(0, line.find(");"));

			std::istringstream	lineStream{ line };

			Uint32						materialIndex;
			IMapObject::Texture			material;
			std::string					color;

			if (lineStream >>
				text::skipIf<','> >> materialIndex >>
				text::skipIf<','> >> material.modelIndex >>
				text::skipIf<','> >> std::quoted(material.txdName) >> text::skipIf<'"' > >>		// NOTE: MVSC has broken implementation and manual skipping trailing " character is necessary.
				text::skipIf<','> >> std::quoted(material.textureName) >> text::skipIf<'"' > >>
				text::skipIf<','> >> color)
			{
				if (auto colorOpt = colorFromARGBString(color); colorOpt.has_value()) {
					material.color = Color{ colorOpt.value() }.fromARGB();
				}
				else {
					std::clog << ModuleLogPrefix << "(Warning): Failed to read material color. Using default: " << Color{ material.color }.toRGBAString() << std::endl;
				}

				mapObject->setMaterial(materialIndex, material);

				//std::clog << "Read material: \n"
				//	<< "-- MaterialIndex:\t" << materialIndex
				//	<< "\n-- MaterialModIndex:\t" << material.modelIndex
				//	<< "\n-- MaterialTxdName:\t" << material.txdName
				//	<< "\n-- MaterialTxtName:\t" << material.textureName
				//	<< "\n-- MaterialColor:\t" << material.color
				//	<< std::endl;
			}
		}
		else if (auto pos = line.find("SetObjectMaterialText(tmpobjid"); pos != std::string::npos && mapObject)
		{
			line = line.substr(pos + 30);
			line = line.substr(0, line.find(");"));

			std::istringstream lineStream{ line };

			Uint32				materialIndex;
			IMapObject::Text	material;
			std::string			fontColor;
			std::string			backColor;
			std::int32_t		textAlign = 0;

			// At first we need to load required arguments.
			// NOTE: MVSC has broken implementation and manual skipping trailing " character is necessary.
			if (lineStream >> text::skipIf<','> >> std::quoted(material.text) >> text::skipIf<'"'>)
			{
				// Now load optional arguments.
				if (lineStream >>
					text::skipIf<','> >> materialIndex >>
					text::skipIf<','> >> material.size >>
					text::skipIf<','> >> std::quoted(material.font) >> text::skipIf<'"'> >>
					text::skipIf<','> >> material.fontSize >>
					text::skipIf<','> >> material.bold)
				{
					// These needs to be separated, because program that generates it require this.
					// It either writes it or not.
					if (lineStream >> text::skipIf<','> && std::getline(lineStream, fontColor, ','))
					{
						fontColor = text::ascii::trimLeft(fontColor);

						if (auto fontColorOpt = colorFromARGBString(fontColor); fontColorOpt.has_value()) {
							material.fontColor = Color{ fontColorOpt.value() }.fromARGB();
						}
						else {
							std::clog << ModuleLogPrefix << "(Warning): Failed to read material font color. Using default: " << material.fontColor << std::endl;
						}

						if (std::getline(lineStream, backColor, ','))
						{
							backColor = text::ascii::trimLeft(backColor);

							if (auto backColorOpt = colorFromARGBString(backColor); backColorOpt.has_value()) {
								material.backColor = Color{ backColorOpt.value() }.fromARGB();
							}
							else {
								std::clog << ModuleLogPrefix << "(Warning): Failed to read material font color. Using default: " << material.fontColor << std::endl;
							}

							if (lineStream >> textAlign)
							{
								material.textAlign = static_cast<IMapObject::Text::TextAlign>(textAlign);
							}
						}
					}
				}

				mapObject->setMaterial(materialIndex, material);

				//std::clog << "Read material text: \n"
				// 	<< "-- MaterialIndex:\t" << materialIndex
				// 	<< "\n-- MaterialSize:\t" << material.size
				// 	<< "\n-- MaterialFont:\t" << material.font
				// 	<< "\n-- MaterialFontSize:\t" << material.fontSize
				// 	<< "\n-- MaterialBold:\t" << material.bold
				// 	<< "\n-- MaterialFontColor:\t" << material.fontColor
				// 	<< "\n-- MaterialBackColor:\t" << material.backColor
				// 	<< std::endl;
			}

		}
		else if (auto pos = line.find("RemoveBuildingForPlayer(playerid"); pos != std::string::npos)
		{
			line = line.substr(pos + 32);

			std::istringstream lineStream{ line };

			samp_edgengine::RemovedBuilding building;
			if (lineStream >>
				text::skipIf<','> >> building.model >>
				text::skipIf<','> >> building.origin.x >> text::skipIf<','> >> building.origin.y >> text::skipIf<','> >> building.origin.z >>
				text::skipIf<','> >> building.radius.value)
			{
				scene.removeBuilding(building);
			}
		}
/*#ifdef _DEBUG
		else if (!line.empty())
		{
			// TODO: make it a debug log.
			std::cerr << "[Error](Line: " << lineNumber << "): Could not parse line: \"" << line << "\"" << std::endl;
		}
#endif*/
		
	}

	// If some object is still not pushed, do it.
	if (mapObject)
	{
		scene.finalizeConstruction( std::move(mapObject) );
	}

	// TODO: debug log:
	std::clog << ModuleLogPrefix << "(Info): Read " << scene.getObjects().size() << " objects." << std::endl;

	return true;
}

}
