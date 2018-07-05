#include "EnginePCH.hpp"

#include <SAMP-EDGEngine/World/SceneLoader.hpp>
#include <SAMP-EDGEngine/World/Scene.hpp>
#include <SAMP-EDGEngine/World/PerPlayerObject.hpp>
#include <SAMP-EDGEngine/Core/TextInc.hpp>
#include <SAMP-EDGEngine/Core/Pointers.hpp>
#include <SAMP-EDGEngine/Server/GameMode.hpp>

namespace samp_edgengine
{

////////////////////////////////////////////////////////////
void DefaultSceneLoader::loadFromStream(Scene& scene_, std::istream& stream_) const
{
	using VisMode = PerPlayerObject::VisibilityMode;

	VisMode			worldVisibility		= VisMode::Everywhere;
	VisMode			interiorVisibility	= VisMode::Everywhere;
	std::int32_t	world				= 0;
	std::int32_t	interior			= 0;
	float			drawDistance		= IMapObject::cxDefaultDrawDistance;

	IMapObject*		currentObject		= nullptr;
	SharedPtr<UniversalObject> currentObjectU;
	SharedPtr<GlobalObject> currentObjectG;

	std::size_t		lineNumber = 0;
	while (!stream_.eof())
	{
		// Read next line from stream:
		std::string line;
		std::getline(stream_, line);

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
				if (currentObjectU)
				{
					currentObjectU->setWorld(world);
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
				if (currentObjectU)
					currentObjectU->setInterior(interior);
			}
		}
		else if (line.find("[[world_every]]") != std::string::npos)
		{
			worldVisibility = VisMode::Everywhere;
			if (currentObjectU)
				currentObjectU->setWorldVisibility(worldVisibility);
		}
		else if (line.find("[[world_specified]]") != std::string::npos)
		{
			worldVisibility = VisMode::Specified;
			if (currentObjectU)
				currentObjectU->setWorldVisibility(worldVisibility);
		}
		else if (line.find("[[world_allbutspecified]]") != std::string::npos)
		{
			worldVisibility = VisMode::AllButSpecified;
			if (currentObjectU)
				currentObjectU->setWorldVisibility(worldVisibility);
		}
		else if (line.find("[[interior_every]]") != std::string::npos)
		{
			interiorVisibility = VisMode::Everywhere;
			if (currentObjectU)
				currentObjectU->setInteriorVisibility(interiorVisibility);
		}
		else if (line.find("[[interior_specified]]") != std::string::npos)
		{
			interiorVisibility = VisMode::Specified;
			if (currentObjectU)
				currentObjectU->setInteriorVisibility(interiorVisibility);
		}
		else if (line.find("[[interior_allbutspecified]]") != std::string::npos)
		{
			interiorVisibility = VisMode::AllButSpecified;
			if (currentObjectU)
				currentObjectU->setInteriorVisibility(interiorVisibility);
		}
		else if (auto pos = line.find("[[draw_distance]]"); pos != std::string::npos)
		{
			line = line.substr(pos + 17);

			std::istringstream lineStream{ line };

			if (lineStream >> text::skipIf<'('>)
			{
				lineStream >> drawDistance;
				if (currentObject)
				{
					currentObject->setDrawDistance(drawDistance);
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
					if (currentObject)
					{
						if (currentObjectU) {
							scene_.finalizeConstruction(currentObjectU);
						}
						else if (currentObjectG) {
							scene_.finalizeConstruction(currentObjectG);
						}

						currentObject = nullptr;
						currentObjectG.reset();
						currentObjectU.reset();
					}

					currentObjectU = scene_.beginConstruction<UniversalObject>();
					currentObject = currentObjectU.get();

					currentObject->setModel(modelIndex);
					currentObject->setLocation(location);
					currentObject->setRotation(rotation);
					currentObject->setDrawDistance(drawDistance);

					if (currentObjectU)
					{
						currentObjectU->setWorldAndMode(world, worldVisibility);
						currentObjectU->setInteriorAndMode(interior, interiorVisibility);
					}
				}
			}
		}
		else if (auto pos = line.find("SetObjectMaterial(tmpobjid"); pos != std::string::npos && currentObject)
		{
			line = line.substr(pos + 26);
			line = line.substr(0, line.find(");"));
			
			std::istringstream	lineStream{ line };

			std::int32_t		materialIndex = 0;
			IMapObject::Texture material;
			std::string			color;

			if (lineStream >>
				text::skipIf<','> >> materialIndex >>
				text::skipIf<','> >> material.modelIndex >>
				text::skipIf<','> >> std::quoted(material.txdName) >> text::skipIf<'"' > >>		// NOTE: MVSC has broken implementation and manual skipping trailing " character is necessary.
				text::skipIf<','> >> std::quoted(material.textureName) >> text::skipIf<'"' > >>
				text::skipIf<','> >> color)
			{
				if (color.find_first_of("xX") == std::string::npos)
					material.color = Color{ text::ascii::convert<std::uint32_t>(color).value() }.fromARGB();
				else
					material.color = Color{ color }.fromARGB();

				currentObject->setMaterial(materialIndex, material);

				//std::clog << "Read material: \n"
				//	<< "-- MaterialIndex:\t" << materialIndex
				//	<< "\n-- MaterialModIndex:\t" << material.modelIndex
				//	<< "\n-- MaterialTxdName:\t" << material.txdName
				//	<< "\n-- MaterialTxtName:\t" << material.textureName
				//	<< "\n-- MaterialColor:\t" << material.color
				//	<< std::endl;
			}
		}
		else if (auto pos = line.find("SetObjectMaterialText(tmpobjid"); pos != std::string::npos && currentObject)
		{
			line = line.substr(pos + 30);
			line = line.substr(0, line.find(");"));

			std::istringstream lineStream{ line };

			std::int32_t materialIndex = 0;
			IMapObject::Text material;
			std::string fontColor;
			std::string backColor;
			std::int32_t textAlign = 0;

			// At first we need to load required arguments.
			// NOTE: MVSC has broken implementation and manual skipping trailing " character is necessary.
			if (lineStream >> text::skipIf<','> >> std::quoted(material.text) >> text::skipIf<'"' >)
			{
				// Now load optional arguments.
				if (lineStream >>
					text::skipIf<','> >> materialIndex >>
					text::skipIf<','> >> material.size >>
					text::skipIf<','> >> std::quoted(material.font) >> text::skipIf<'"' > >>
					text::skipIf<','> >> material.fontSize >>
					text::skipIf<','> >> material.bold)
				{
					// These needs to be separated, because program that generates it require this.
					// It either writes it or not.
					if (lineStream >> text::skipIf<','> && std::getline(lineStream, fontColor, ','))
					{
						fontColor = text::ascii::trimLeft(fontColor);

						if (fontColor.find_first_of("xX") == std::string::npos)
							material.fontColor = Color{ text::ascii::convert<std::uint32_t>(fontColor).value() }.fromARGB();
						else
							material.fontColor = Color{ fontColor.substr(2) }.fromARGB();

						if (std::getline(lineStream, backColor, ','))
						{
							backColor = text::ascii::trimLeft(backColor);
							
							if (backColor.find_first_of("xX") == std::string::npos)
								material.backColor = Color{ text::ascii::convert<std::uint32_t>(backColor).value() }.fromARGB();
							else
								material.backColor = Color{ backColor.substr(2) }.fromARGB();

							if (lineStream >> textAlign)
							{
								material.textAlign = static_cast<IMapObject::Text::TextAlign>(textAlign);
							}
						}
					}
				}
				
				currentObject->setMaterial(materialIndex, material);

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
				scene_.removeBuilding( building );
			}
		}
#ifdef _DEBUG
		else if (!line.empty())
		{
			// TODO: make it a debug log.
			std::cerr << "[Error](Line: " << lineNumber << "): Could not parse line: \"" << line << "\"" << std::endl;
		}
#endif
	}

	// If some object is still not pushed, do it.
	if (currentObjectU)
	{
		scene_.finalizeConstruction(currentObjectU);
	}

	// TODO: debug log:
	// std::clog << "Read " << scene_.getObjects().size() << " objects." << std::endl;
}

}
