#include <SAMP-EDGEngine/Ext/ResourceIO/Everything.hpp>

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <thread>
#include <chrono>

namespace rcio	= samp_edgengine::ext::resource_io;
namespace fs	= std::filesystem;
namespace samp	= samp_edgengine;

bool serializeSceneToXML(std::ostream& outputStream_, samp::Scene const& scene_)
{
	rcio::xml::xml_document<> document;

	rcio::XMLSceneSerializer serializer{ scene_, document };
	if (!serializer.serialize())
	{
		std::cerr << "XML Scene Serialization failed!" << std::endl;
		return false;
	}

	std::string outputString;
	outputString.reserve(scene_.getObjects().size() * 1024);
	rcio::xml::print( std::back_inserter(outputString), document );

	outputStream_ << outputString;
	return true;
}

bool deserializeSceneFromPAWN(std::istream& inputStream_, samp::Scene& scene_)
{
	rcio::PAWNSceneDeserializer deserializer{ scene_, inputStream_ };
	return deserializer.deserialize();
}

bool convertSceneFromPAWNToXML(std::istream& PAWNInput_, std::ostream& XMLOutput_)
{
	samp::Scene scene;

	if (!deserializeSceneFromPAWN(PAWNInput_, scene))
	{
		std::cerr << "Could not deserialize scene from PAWN." << std::endl;
		return false;
	}

	if (!serializeSceneToXML(XMLOutput_, scene))
	{
		std::cerr << "Could not serialize scene to XML." << std::endl;
		return false;
	}

	return true;
}

bool convertSceneFileFromPAWNToXML(fs::path inputPath_, fs::path outputPath_)
{
	std::ifstream inputFile{ inputPath_ };
	std::ofstream outputFile{ outputPath_ };
	if ( !inputFile.is_open() )
	{
		std::cerr << "Could not open input file for reading!" << std::endl;
		return false;
	}
	if ( !outputFile.is_open())
	{
		std::cerr << "Could not open output file for writing!" << std::endl;
		return false;
	}

	if ( !convertSceneFromPAWNToXML(inputFile, outputFile) )
	{
		std::cerr << "File conversion failed." << std::endl;
		return false;
	}

	return true;
}

bool performConversion()
{
	std::cout << "==== PAWN -> XML Scene converter ====" << std::endl;

	std::cout	<< "What to convert, file (f) / directory (d)?\n"
				<< ">";

	char option = 'f';
	std::cin >> option;
	option = samp::text::toLower(option);

	fs::path inputPath, outputPath;

	std::cout	<< "Enter input path:\n"
				<< ">";

	std::cin >> inputPath;

	if ( (option == 'f' && !fs::is_regular_file(inputPath) ) ||
		 (option == 'd' && !fs::is_directory(inputPath) )
		)
	{
		std::cout << "You've entered invalid input path." << std::endl;
		return false;
	}

	std::cout	<< "Files will be overwritten if existed before.\n"
				<< "Enter output path:\n"
				<< ">";
	std::cin >> outputPath;

	if (option == 'f')
	{
		return convertSceneFileFromPAWNToXML(inputPath, outputPath);
	}
	else if (option == 'd')
	{
		std::cout	<< "Scan files recursively (y/n)?\n"
					<< ">";
		char recursively = 'y';
		std::cin >> recursively;
		recursively = samp::text::toLower(recursively);

		if (recursively == 'y')
		{
			for (auto entry : fs::recursive_directory_iterator(inputPath))
			{
				if (fs::is_regular_file(entry))
				{
					auto outRelativePath = outputPath / fs::relative(entry.path(), inputPath);
					auto dir = outRelativePath;
					outRelativePath.replace_extension(".xml");
					fs::create_directories(dir.remove_filename());
					if (!convertSceneFileFromPAWNToXML(entry.path(), outRelativePath))
					{
						std::cerr << "Failed to convert: \"" << entry.path() << "\" -> \"" << outRelativePath << "\"" << std::endl;
					}
				}
			}
		}
		else
		{
			for (auto entry : fs::directory_iterator(inputPath))
			{
				if (fs::is_regular_file(entry))
				{
					auto outRelativePath = outputPath / fs::relative(entry.path(), inputPath);
					auto dir = outRelativePath;
					outRelativePath.replace_extension(".xml");
					fs::create_directories(dir.remove_filename());
					if (!convertSceneFileFromPAWNToXML(entry.path(), outRelativePath))
					{
						std::cerr << "Failed to convert: \"" << entry.path() << "\" -> \"" << outRelativePath << "\"" << std::endl;
					}
				}
			}
		}
		
	}

	return true;
}

int main()
{
	if ( !performConversion() ) {
		std::cerr << "Conversion failed.";
	}
	else {
		std::cout << "Conversion succeeded.";
	}

	std::cout << "Program will exit in 15 seconds...";

	std::this_thread::sleep_for(std::chrono::seconds{ 15 });
}