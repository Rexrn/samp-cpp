// File description:
// Implements Color class and provides over 600 named colors (within agdk::colors) namespace.
#pragma once

// Precompiled header:
#include "../../../stdafx.h"

namespace agdk
{	
	/// <summary>
	/// Represents color with 8-bit channels red, green, blue and alpha channels.
	/// </summary>
	/// <remarks>
	/// <para>This class does not provide floating point color channels.</para>
	/// </remarks>
	class Color
	{
	public:
		std::uint8_t r;		/// Red		color channel.
		std::uint8_t g;		/// Green	color channel.
		std::uint8_t b;		/// Blue	color channel.
		std::uint8_t a;		/// Alpha	color channel.
		
		/// <summary>
		/// Initializes a new instance of the <see cref="Color"/> class.
		/// </summary>
		/// <remarks>
		/// <para>Channels are initialized to non-transparent black color [0;0;0;255].</para>
		/// </remarks>
		constexpr Color()
			: r{ 0 }, g{ 0 }, b{ 0 }, a{ 255 }
		{
		}
		
		/// <summary>
		/// Initializes a new instance of the <see cref="Color"/> class using copy constructor.
		/// </summary>
		/// <param name="other_">Other color.</param>
		constexpr Color(const Color &other_) = default;
		
		/// <summary>
		/// Initializes a new instance of the <see cref="Color"/> class from 8-bit channels.
		/// </summary>
		/// <param name="red_">The red component.</param>
		/// <param name="green_">The green component.</param>
		/// <param name="blue_">The blue component.</param>
		/// <param name="alpha_">The alpha component.</param>
		constexpr Color(const std::uint8_t red_, const std::uint8_t green_, const std::uint8_t blue_, const std::uint8_t alpha_ = 255)
			: r{ red_ }, g{ green_ }, b{ blue_ }, a{ alpha_ }
		{
		}
		
		/// <summary>
		/// Initializes a new instance of the <see cref="Color"/> class using RGBA color packed into 32 bit unsigned integer four 8-bit channels.
		/// </summary>
		/// <param name="color_">The RGBA 32-bit color.</param>
		constexpr explicit Color(const std::uint32_t color_)
			:
			r{ color_ >> (3 * 8) },					// Red   component	=	Binary shift right by 3 bytes.								0xAABBCCDD => 0x000000AA
			g{ (color_ << (1 * 8)) >> (3 * 8) },	// Green component	=	Binary shift left by 1 byte  and then right by 3 bytes:		0xAABBCCDD => 0xBBCCDD00 => 0x000000BB
			b{ (color_ << (2 * 8)) >> (3 * 8) },	// Blue  component	=	Binary shift left by 2 bytes and then right by 3 bytes:		0xAABBCCDD => 0xCCDD0000 => 0x000000CC
			a{ (color_ << (3 * 8)) >> (3 * 8) }
		{
		}

		/*
			Creates color object from string
			It 
		*/
		
		/// <summary>
		/// Initializes a new instance of the <see cref="Color"/> class from std::string.
		/// </summary>
		/// <param name="color_">The color.</param>
		/// <remarks>
		/// <para>Color must be compatible with one of three formats:
		///		-	0xFFFFFF[FF]		Example: 0xAaBbCcDd		- case does not matter, fourth byte optional.
		///		-	FFFFFF[FF]			Example: AaBbCcDd		- case does not matter, fourth byte optional.
		///		-	{FFFFFF[FF]}		Example: {AaBbCcDd}		- case does not matter, fourth byte optional.
		/// </para>
		/// </remarks>
		explicit Color(const std::string &color_);

		/// <summary>
		/// Creates a new instance of the <see cref="Color"/> class from std::string.
		/// </summary>
		/// <param name="strColor">The color.</param>
		/// <remarks>
		/// <para>Color must be compatible with one of three formats:
		///		-	0xFFFFFF[FF]		Example: 0xAaBbCcDd		- case does not matter, fourth byte optional.
		///		-	FFFFFF[FF]			Example: AaBbCcDd		- case does not matter, fourth byte optional.
		///		-	{FFFFFF[FF]}		Example: {AaBbCcDd}		- case does not matter, fourth byte optional.
		/// </para>
		/// </remarks>
		static Color fromString(const std::string &strColor);
		
		/// <summary>
		/// Converts instance to RGBA 32-bit unsigned integer.
		/// </summary>
		/// <returns>RGBA 32-bit unsigned integer.</returns>
		constexpr std::uint32_t toUint32() const {
			return (std::uint32_t{ r } << 24) + (std::uint32_t{ g } << 16) + (std::uint32_t{ b } << 8) + std::uint32_t{ a };
		}

		/// <summary>
		/// Converts instance to RGBA 32-bit integer.
		/// </summary>
		/// <returns>RGBA 32-bit integer.</returns>
		constexpr std::int32_t toInt32() const {
			return static_cast<std::int32_t>(this->toUint32());
		}

		/// <summary>
		/// Converts instance to RGBA 32-bit unsigned integer.
		/// </summary>
		/// <returns>RGBA 32-bit unsigned integer.</returns>
		explicit constexpr operator std::uint32_t() const {
			return this->toUint32();
		}

		/// <summary>
		/// Converts instance to RGBA 32-bit integer.
		/// </summary>
		/// <returns>RGBA 32-bit integer.</returns>
		explicit constexpr operator std::int32_t() const {
			return this->toInt32();
		}

		/// <summary>
		/// Returns RGB-formatted uppercase string containing hex color.
		/// For example: [255; 0; 0; 255] => FF0000
		/// </summary>
		/// <returns>RGB uppercase string containing hex color.</returns>
		std::string toRGBString() const;

		/// <summary>
		/// Returns RGBA-formatted uppercase string containing hex color.
		/// For example: [255; 0; 0; 255] => FF0000FF
		/// </summary>
		/// <returns>RGBA uppercase string containing hex color.</returns>
		std::string toRGBAString() const;

		/// <summary>
		/// Returns RGBA-formatted uppercase string containing hex color.
		/// Contains "{" and "}" braces because it is used in chat.
		/// For example: [255; 0; 0; 255] => {FF0000FF}.
		/// </summary>
		/// <returns>RGBA uppercase string containing hex color surrounded with braces "{" and "}".</returns>
		std::string toChatString() const;

		/// <summary>
		/// Random RGB[A] color.
		/// </summary>
		/// <param name="randomAlpha_">[optional] Determines whether alpha channel should be also random.</param>
		/// <returns>Random RGB[A optional] color.</returns>
		/// <remarks>
		/// <para>If randomAlpha_ is set to false alpha channel is set to 255 (completely opaque).</para>
		/// </remarks>
		static Color random(const bool randomAlpha_ = false);
	};

	/// <summary>
	/// Allows to push <see cref="Color"/> objects to std::ostream streams using operator<<.
	/// </summary>
	std::ostream& operator<<(std::ostream &stream, const Color &color);
	
	/// <summary>
	/// List of built-in colors.
	/// </summary>
	namespace colors
	{
		constexpr Color AirForceblue{ 0x5d8aa8ff };
		constexpr Color Aliceblue{ 0xf0f8ffff };
		constexpr Color Alizarincrimson{ 0xe32636ff };
		constexpr Color Almond{ 0xefdecdff };
		constexpr Color Amaranth{ 0xe52b50ff };
		constexpr Color Amber{ 0xffbf00ff };
		constexpr Color Americanrose{ 0xff033eff };
		constexpr Color Amethyst{ 0x9966ccff };
		constexpr Color AndroidGreen{ 0xa4c639ff };
		constexpr Color Antiflashwhite{ 0xf2f3f4ff };
		constexpr Color Antiquebrass{ 0xcd9575ff };
		constexpr Color Antiquefuchsia{ 0x915c83ff };
		constexpr Color Antiquewhite{ 0xfaebd7ff };
		constexpr Color Ao{ 0x008000ff };
		constexpr Color Applegreen{ 0x8db600ff };
		constexpr Color Apricot{ 0xfbceb1ff };
		constexpr Color Aqua{ 0x00ffffff };
		constexpr Color Aquamarine{ 0x7fffd4ff };
		constexpr Color Armygreen{ 0x4b5320ff };
		constexpr Color Arylideyellow{ 0xe9d66bff };
		constexpr Color Ashgrey{ 0xb2beb5ff };
		constexpr Color Asparagus{ 0x87a96bff };
		constexpr Color Atomictangerine{ 0xff9966ff };
		constexpr Color Auburn{ 0xa52a2aff };
		constexpr Color Aureolin{ 0xfdee00ff };
		constexpr Color AuroMetalSaurus{ 0x6e7f80ff };
		constexpr Color Awesome{ 0xff2052ff };
		constexpr Color Azure{ 0x007fffff };
		constexpr Color Azuremistweb{ 0xf0ffffff };
		constexpr Color Babyblue{ 0x89cff0ff };
		constexpr Color Babyblueeyes{ 0xa1caf1ff };
		constexpr Color Babypink{ 0xf4c2c2ff };
		constexpr Color BallBlue{ 0x21abcdff };
		constexpr Color BananaMania{ 0xfae7b5ff };
		constexpr Color Bananayellow{ 0xffe135ff };
		constexpr Color Battleshipgrey{ 0x848482ff };
		constexpr Color Bazaar{ 0x98777bff };
		constexpr Color Beaublue{ 0xbcd4e6ff };
		constexpr Color Beaver{ 0x9f8170ff };
		constexpr Color Beige{ 0xf5f5dcff };
		constexpr Color Bisque{ 0xffe4c4ff };
		constexpr Color Bistre{ 0x3d2b1fff };
		constexpr Color Bittersweet{ 0xfe6f5eff };
		constexpr Color Black{ 0x000000ff };
		constexpr Color BlanchedAlmond{ 0xffebcdff };
		constexpr Color BleudeFrance{ 0x318ce7ff };
		constexpr Color BlizzardBlue{ 0xace5eeff };
		constexpr Color Blond{ 0xfaf0beff };
		constexpr Color Blue{ 0x0000ffff };
		constexpr Color BlueBell{ 0xa2a2d0ff };
		constexpr Color BlueGray{ 0x6699ccff };
		constexpr Color Bluegreen{ 0x0d98baff };
		constexpr Color Bluepurple{ 0x8a2be2ff };
		constexpr Color Blueviolet{ 0x8a2be2ff };
		constexpr Color Blush{ 0xde5d83ff };
		constexpr Color Bole{ 0x79443bff };
		constexpr Color Bondiblue{ 0x0095b6ff };
		constexpr Color Bone{ 0xe3dac9ff };
		constexpr Color BostonUniversityRed{ 0xcc0000ff };
		constexpr Color Bottlegreen{ 0x006a4eff };
		constexpr Color Boysenberry{ 0x873260ff };
		constexpr Color Brandeisblue{ 0x0070ffff };
		constexpr Color Brass{ 0xb5a642ff };
		constexpr Color Brickred{ 0xcb4154ff };
		constexpr Color Brightcerulean{ 0x1dacd6ff };
		constexpr Color Brightgreen{ 0x66ff00ff };
		constexpr Color Brightlavender{ 0xbf94e4ff };
		constexpr Color Brightmaroon{ 0xc32148ff };
		constexpr Color Brightpink{ 0xff007fff };
		constexpr Color Brightturquoise{ 0x08e8deff };
		constexpr Color Brightube{ 0xd19fe8ff };
		constexpr Color Brilliantlavender{ 0xf4bbffff };
		constexpr Color Brilliantrose{ 0xff55a3ff };
		constexpr Color Brinkpink{ 0xfb607fff };
		constexpr Color Britishracinggreen{ 0x004225ff };
		constexpr Color Bronze{ 0xcd7f32ff };
		constexpr Color Brown{ 0xa52a2aff };
		constexpr Color Bubblegum{ 0xffc1ccff };
		constexpr Color Bubbles{ 0xe7feffff };
		constexpr Color Buff{ 0xf0dc82ff };
		constexpr Color Bulgarianrose{ 0x480607ff };
		constexpr Color Burgundy{ 0x800020ff };
		constexpr Color Burlywood{ 0xdeb887ff };
		constexpr Color Burntorange{ 0xcc5500ff };
		constexpr Color Burntsienna{ 0xe97451ff };
		constexpr Color Burntumber{ 0x8a3324ff };
		constexpr Color Byzantine{ 0xbd33a4ff };
		constexpr Color Byzantium{ 0x702963ff };
		constexpr Color CGBlue{ 0x007aa5ff };
		constexpr Color CGRed{ 0xe03c31ff };
		constexpr Color Cadet{ 0x536872ff };
		constexpr Color Cadetblue{ 0x5f9ea0ff };
		constexpr Color Cadetgrey{ 0x91a3b0ff };
		constexpr Color Cadmiumgreen{ 0x006b3cff };
		constexpr Color Cadmiumorange{ 0xed872dff };
		constexpr Color Cadmiumred{ 0xe30022ff };
		constexpr Color Cadmiumyellow{ 0xfff600ff };
		constexpr Color Cafaulait{ 0xa67b5bff };
		constexpr Color Cafnoir{ 0x4b3621ff };
		constexpr Color CalPolyPomonagreen{ 0x1e4d2bff };
		constexpr Color CambridgeBlue{ 0xa3c1adff };
		constexpr Color Camel{ 0xc19a6bff };
		constexpr Color Camouflagegreen{ 0x78866bff };
		constexpr Color Canary{ 0xffff99ff };
		constexpr Color Canaryyellow{ 0xffef00ff };
		constexpr Color Candyapplered{ 0xff0800ff };
		constexpr Color Candypink{ 0xe4717aff };
		constexpr Color Capri{ 0x00bfffff };
		constexpr Color Caputmortuum{ 0x592720ff };
		constexpr Color Cardinal{ 0xc41e3aff };
		constexpr Color Caribbeangreen{ 0x00cc99ff };
		constexpr Color Carmine{ 0xff0040ff };
		constexpr Color Carminepink{ 0xeb4c42ff };
		constexpr Color Carminered{ 0xff0038ff };
		constexpr Color Carnationpink{ 0xffa6c9ff };
		constexpr Color Carnelian{ 0xb31b1bff };
		constexpr Color Carolinablue{ 0x99baddff };
		constexpr Color Carrotorange{ 0xed9121ff };
		constexpr Color Celadon{ 0xace1afff };
		constexpr Color Celeste{ 0xb2ffffff };
		constexpr Color Celestialblue{ 0x4997d0ff };
		constexpr Color Cerise{ 0xde3163ff };
		constexpr Color Cerisepink{ 0xec3b83ff };
		constexpr Color Cerulean{ 0x007ba7ff };
		constexpr Color Ceruleanblue{ 0x2a52beff };
		constexpr Color Chamoisee{ 0xa0785aff };
		constexpr Color Champagne{ 0xfad6a5ff };
		constexpr Color Charcoal{ 0x36454fff };
		constexpr Color Chartreuse{ 0x7fff00ff };
		constexpr Color Cherry{ 0xde3163ff };
		constexpr Color Cherryblossompink{ 0xffb7c5ff };
		constexpr Color Chestnut{ 0xcd5c5cff };
		constexpr Color Chocolate{ 0xd2691eff };
		constexpr Color Chromeyellow{ 0xffa700ff };
		constexpr Color Cinereous{ 0x98817bff };
		constexpr Color Cinnabar{ 0xe34234ff };
		constexpr Color Cinnamon{ 0xd2691eff };
		constexpr Color Citrine{ 0xe4d00aff };
		constexpr Color Classicrose{ 0xfbcce7ff };
		constexpr Color Cobalt{ 0x0047abff };
		constexpr Color Cocoabrown{ 0xd2691eff };
		constexpr Color Coffee{ 0x6f4e37ff };
		constexpr Color Columbiablue{ 0x9bddffff };
		constexpr Color Coolblack{ 0x002e63ff };
		constexpr Color Coolgrey{ 0x8c92acff };
		constexpr Color Copper{ 0xb87333ff };
		constexpr Color Copperrose{ 0x996666ff };
		constexpr Color Coquelicot{ 0xff3800ff };
		constexpr Color Coral{ 0xff7f50ff };
		constexpr Color Coralpink{ 0xf88379ff };
		constexpr Color Coralred{ 0xff4040ff };
		constexpr Color Cordovan{ 0x893f45ff };
		constexpr Color Corn{ 0xfbec5dff };
		constexpr Color CornellRed{ 0xb31b1bff };
		constexpr Color Cornflower{ 0x9aceebff };
		constexpr Color Cornflowerblue{ 0x6495edff };
		constexpr Color Cornsilk{ 0xfff8dcff };
		constexpr Color Cosmiclatte{ 0xfff8e7ff };
		constexpr Color Cottoncandy{ 0xffbcd9ff };
		constexpr Color Cream{ 0xfffdd0ff };
		constexpr Color Crimson{ 0xdc143cff };
		constexpr Color CrimsonRed{ 0x990000ff };
		constexpr Color Crimsonglory{ 0xbe0032ff };
		constexpr Color Cyan{ 0x00ffffff };
		constexpr Color Daffodil{ 0xffff31ff };
		constexpr Color Dandelion{ 0xf0e130ff };
		constexpr Color Darkblue{ 0x00008bff };
		constexpr Color Darkbrown{ 0x654321ff };
		constexpr Color Darkbyzantium{ 0x5d3954ff };
		constexpr Color Darkcandyapplered{ 0xa40000ff };
		constexpr Color Darkcerulean{ 0x08457eff };
		constexpr Color Darkchestnut{ 0x986960ff };
		constexpr Color Darkcoral{ 0xcd5b45ff };
		constexpr Color Darkcyan{ 0x008b8bff };
		constexpr Color Darkelectricblue{ 0x536878ff };
		constexpr Color Darkgoldenrod{ 0xb8860bff };
		constexpr Color Darkgray{ 0xa9a9a9ff };
		constexpr Color Darkgreen{ 0x013220ff };
		constexpr Color Darkjunglegreen{ 0x1a2421ff };
		constexpr Color Darkkhaki{ 0xbdb76bff };
		constexpr Color Darklava{ 0x483c32ff };
		constexpr Color Darklavender{ 0x734f96ff };
		constexpr Color Darkmagenta{ 0x8b008bff };
		constexpr Color Darkmidnightblue{ 0x003366ff };
		constexpr Color Darkolivegreen{ 0x556b2fff };
		constexpr Color Darkorange{ 0xff8c00ff };
		constexpr Color Darkorchid{ 0x9932ccff };
		constexpr Color Darkpastelblue{ 0x779ecbff };
		constexpr Color Darkpastelgreen{ 0x03c03cff };
		constexpr Color Darkpastelpurple{ 0x966fd6ff };
		constexpr Color Darkpastelred{ 0xc23b22ff };
		constexpr Color Darkpink{ 0xe75480ff };
		constexpr Color Darkpowderblue{ 0x003399ff };
		constexpr Color Darkraspberry{ 0x872657ff };
		constexpr Color Darkred{ 0x8b0000ff };
		constexpr Color Darksalmon{ 0xe9967aff };
		constexpr Color Darkscarlet{ 0x560319ff };
		constexpr Color Darkseagreen{ 0x8fbc8fff };
		constexpr Color Darksienna{ 0x3c1414ff };
		constexpr Color Darkslateblue{ 0x483d8bff };
		constexpr Color Darkslategray{ 0x2f4f4fff };
		constexpr Color Darkspringgreen{ 0x177245ff };
		constexpr Color Darktan{ 0x918151ff };
		constexpr Color Darktangerine{ 0xffa812ff };
		constexpr Color Darktaupe{ 0x483c32ff };
		constexpr Color Darkterracotta{ 0xcc4e5cff };
		constexpr Color Darkturquoise{ 0x00ced1ff };
		constexpr Color Darkviolet{ 0x9400d3ff };
		constexpr Color Dartmouthgreen{ 0x00693eff };
		constexpr Color Davygrey{ 0x555555ff };
		constexpr Color Debianred{ 0xd70a53ff };
		constexpr Color Deepcarmine{ 0xa9203eff };
		constexpr Color Deepcarminepink{ 0xef3038ff };
		constexpr Color Deepcarrotorange{ 0xe9692cff };
		constexpr Color Deepcerise{ 0xda3287ff };
		constexpr Color Deepchampagne{ 0xfad6a5ff };
		constexpr Color Deepchestnut{ 0xb94e48ff };
		constexpr Color Deepcoffee{ 0x704241ff };
		constexpr Color Deepfuchsia{ 0xc154c1ff };
		constexpr Color Deepjunglegreen{ 0x004b49ff };
		constexpr Color Deeplilac{ 0x9955bbff };
		constexpr Color Deepmagenta{ 0xcc00ccff };
		constexpr Color Deeppeach{ 0xffcba4ff };
		constexpr Color Deeppink{ 0xff1493ff };
		constexpr Color Deepsaffron{ 0xff9933ff };
		constexpr Color Deepskyblue{ 0x00bfffff };
		constexpr Color Denim{ 0x1560bdff };
		constexpr Color Desert{ 0xc19a6bff };
		constexpr Color Desertsand{ 0xedc9afff };
		constexpr Color Dimgray{ 0x696969ff };
		constexpr Color Dodgerblue{ 0x1e90ffff };
		constexpr Color Dogwoodrose{ 0xd71868ff };
		constexpr Color Dollarbill{ 0x85bb65ff };
		constexpr Color Drab{ 0x967117ff };
		constexpr Color Dukeblue{ 0x00009cff };
		constexpr Color Earthyellow{ 0xe1a95fff };
		constexpr Color Ecru{ 0xc2b280ff };
		constexpr Color Eggplant{ 0x614051ff };
		constexpr Color Eggshell{ 0xf0ead6ff };
		constexpr Color Egyptianblue{ 0x1034a6ff };
		constexpr Color Electricblue{ 0x7df9ffff };
		constexpr Color Electriccrimson{ 0xff003fff };
		constexpr Color Electriccyan{ 0x00ffffff };
		constexpr Color Electricgreen{ 0x00ff00ff };
		constexpr Color Electricindigo{ 0x6f00ffff };
		constexpr Color Electriclavender{ 0xf4bbffff };
		constexpr Color Electriclime{ 0xccff00ff };
		constexpr Color Electricpurple{ 0xbf00ffff };
		constexpr Color Electricultramarine{ 0x3f00ffff };
		constexpr Color Electricviolet{ 0x8f00ffff };
		constexpr Color Electricyellow{ 0xffff00ff };
		constexpr Color Emerald{ 0x50c878ff };
		constexpr Color Etonblue{ 0x96c8a2ff };
		constexpr Color Fallow{ 0xc19a6bff };
		constexpr Color Falured{ 0x801818ff };
		constexpr Color Famous{ 0xff00ffff };
		constexpr Color Fandango{ 0xb53389ff };
		constexpr Color Fashionfuchsia{ 0xf400a1ff };
		constexpr Color Fawn{ 0xe5aa70ff };
		constexpr Color Feldgrau{ 0x4d5d53ff };
		constexpr Color Fern{ 0x71bc78ff };
		constexpr Color Ferngreen{ 0x4f7942ff };
		constexpr Color FerrariRed{ 0xff2800ff };
		constexpr Color Fielddrab{ 0x6c541eff };
		constexpr Color Fireenginered{ 0xce2029ff };
		constexpr Color Firebrick{ 0xb22222ff };
		constexpr Color Flame{ 0xe25822ff };
		constexpr Color Flamingopink{ 0xfc8eacff };
		constexpr Color Flavescent{ 0xf7e98eff };
		constexpr Color Flax{ 0xeedc82ff };
		constexpr Color Floralwhite{ 0xfffaf0ff };
		constexpr Color Fluorescentorange{ 0xffbf00ff };
		constexpr Color Fluorescentpink{ 0xff1493ff };
		constexpr Color Fluorescentyellow{ 0xccff00ff };
		constexpr Color Folly{ 0xff004fff };
		constexpr Color Forestgreen{ 0x228b22ff };
		constexpr Color Frenchbeige{ 0xa67b5bff };
		constexpr Color Frenchblue{ 0x0072bbff };
		constexpr Color Frenchlilac{ 0x86608eff };
		constexpr Color Frenchrose{ 0xf64a8aff };
		constexpr Color Fuchsia{ 0xff00ffff };
		constexpr Color Fuchsiapink{ 0xff77ffff };
		constexpr Color Fulvous{ 0xe48400ff };
		constexpr Color FuzzyWuzzy{ 0xcc6666ff };
		constexpr Color Gainsboro{ 0xdcdcdcff };
		constexpr Color Gamboge{ 0xe49b0fff };
		constexpr Color Ghostwhite{ 0xf8f8ffff };
		constexpr Color Ginger{ 0xb06500ff };
		constexpr Color Glaucous{ 0x6082b6ff };
		constexpr Color Glitter{ 0xe6e8faff };
		constexpr Color Gold{ 0xffd700ff };
		constexpr Color Goldenbrown{ 0x996515ff };
		constexpr Color Goldenpoppy{ 0xfcc200ff };
		constexpr Color Goldenyellow{ 0xffdf00ff };
		constexpr Color Goldenrod{ 0xdaa520ff };
		constexpr Color GrannySmithApple{ 0xa8e4a0ff };
		constexpr Color Gray{ 0x808080ff };
		constexpr Color Grayasparagus{ 0x465945ff };
		constexpr Color Green{ 0x00ff00ff };
		constexpr Color GreenBlue{ 0x1164b4ff };
		constexpr Color Greenyellow{ 0xadff2fff };
		constexpr Color Grullo{ 0xa99a86ff };
		constexpr Color Guppiegreen{ 0x00ff7fff };
		constexpr Color Halaybe{ 0x663854ff };
		constexpr Color Hanblue{ 0x446ccfff };
		constexpr Color Hanpurple{ 0x5218faff };
		constexpr Color Hansayellow{ 0xe9d66bff };
		constexpr Color Harlequin{ 0x3fff00ff };
		constexpr Color Harvardcrimson{ 0xc90016ff };
		constexpr Color HarvestGold{ 0xda9100ff };
		constexpr Color HeartGold{ 0x808000ff };
		constexpr Color Heliotrope{ 0xdf73ffff };
		constexpr Color Hollywoodcerise{ 0xf400a1ff };
		constexpr Color Honeydew{ 0xf0fff0ff };
		constexpr Color Hookergreen{ 0x49796bff };
		constexpr Color Hotmagenta{ 0xff1dceff };
		constexpr Color Hotpink{ 0xff69b4ff };
		constexpr Color Huntergreen{ 0x355e3bff };
		constexpr Color Icterine{ 0xfcf75eff };
		constexpr Color Inchworm{ 0xb2ec5dff };
		constexpr Color Indiagreen{ 0x138808ff };
		constexpr Color Indianred{ 0xcd5c5cff };
		constexpr Color Indianyellow{ 0xe3a857ff };
		constexpr Color Indigo{ 0x4b0082ff };
		constexpr Color InternationalKleinBlue{ 0x002fa7ff };
		constexpr Color Internationalorange{ 0xff4f00ff };
		constexpr Color Iris{ 0x5a4fcfff };
		constexpr Color Isabelline{ 0xf4f0ecff };
		constexpr Color Islamicgreen{ 0x009000ff };
		constexpr Color Ivory{ 0xfffff0ff };
		constexpr Color Jade{ 0x00a86bff };
		constexpr Color Jasmine{ 0xf8de7eff };
		constexpr Color Jasper{ 0xd73b3eff };
		constexpr Color Jazzberryjam{ 0xa50b5eff };
		constexpr Color Jonquil{ 0xfada5eff };
		constexpr Color Junebud{ 0xbdda57ff };
		constexpr Color Junglegreen{ 0x29ab87ff };
		constexpr Color KUCrimson{ 0xe8000dff };
		constexpr Color Kellygreen{ 0x4cbb17ff };
		constexpr Color Khaki{ 0xc3b091ff };
		constexpr Color LaSalleGreen{ 0x087830ff };
		constexpr Color Languidlavender{ 0xd6caddff };
		constexpr Color Lapislazuli{ 0x26619cff };
		constexpr Color LaserLemon{ 0xfefe22ff };
		constexpr Color Laurelgreen{ 0xa9ba9dff };
		constexpr Color Lava{ 0xcf1020ff };
		constexpr Color Lavender{ 0xe6e6faff };
		constexpr Color Lavenderblue{ 0xccccffff };
		constexpr Color Lavenderblush{ 0xfff0f5ff };
		constexpr Color Lavendergray{ 0xc4c3d0ff };
		constexpr Color Lavenderindigo{ 0x9457ebff };
		constexpr Color Lavendermagenta{ 0xee82eeff };
		constexpr Color Lavendermist{ 0xe6e6faff };
		constexpr Color Lavenderpink{ 0xfbaed2ff };
		constexpr Color Lavenderpurple{ 0x967bb6ff };
		constexpr Color Lavenderrose{ 0xfba0e3ff };
		constexpr Color Lawngreen{ 0x7cfc00ff };
		constexpr Color Lemon{ 0xfff700ff };
		constexpr Color LemonYellow{ 0xfff44fff };
		constexpr Color Lemonchiffon{ 0xfffacdff };
		constexpr Color Lemonlime{ 0xbfff00ff };
		constexpr Color LightCrimson{ 0xf56991ff };
		constexpr Color LightThulianpink{ 0xe68facff };
		constexpr Color Lightapricot{ 0xfdd5b1ff };
		constexpr Color Lightblue{ 0xadd8e6ff };
		constexpr Color Lightbrown{ 0xb5651dff };
		constexpr Color Lightcarminepink{ 0xe66771ff };
		constexpr Color Lightcoral{ 0xf08080ff };
		constexpr Color Lightcornflowerblue{ 0x93cceaff };
		constexpr Color Lightcyan{ 0xe0ffffff };
		constexpr Color Lightfuchsiapink{ 0xf984efff };
		constexpr Color Lightgoldenrodyellow{ 0xfafad2ff };
		constexpr Color Lightgray{ 0xd3d3d3ff };
		constexpr Color Lightgreen{ 0x90ee90ff };
		constexpr Color Lightkhaki{ 0xf0e68cff };
		constexpr Color Lightpastelpurple{ 0xb19cd9ff };
		constexpr Color Lightpink{ 0xffb6c1ff };
		constexpr Color Lightsalmon{ 0xffa07aff };
		constexpr Color Lightsalmonpink{ 0xff9999ff };
		constexpr Color Lightseagreen{ 0x20b2aaff };
		constexpr Color Lightskyblue{ 0x87cefaff };
		constexpr Color Lightslategray{ 0x778899ff };
		constexpr Color Lighttaupe{ 0xb38b6dff };
		constexpr Color Lightyellow{ 0xffffedff };
		constexpr Color Lilac{ 0xc8a2c8ff };
		constexpr Color Lime{ 0xbfff00ff };
		constexpr Color Limegreen{ 0x32cd32ff };
		constexpr Color Lincolngreen{ 0x195905ff };
		constexpr Color Linen{ 0xfaf0e6ff };
		constexpr Color Lion{ 0xc19a6bff };
		constexpr Color Liver{ 0x534b4fff };
		constexpr Color Lust{ 0xe62020ff };
		constexpr Color MSUGreen{ 0x18453bff };
		constexpr Color MacaroniandCheese{ 0xffbd88ff };
		constexpr Color Magenta{ 0xff00ffff };
		constexpr Color Magicmint{ 0xaaf0d1ff };
		constexpr Color Magnolia{ 0xf8f4ffff };
		constexpr Color Mahogany{ 0xc04000ff };
		constexpr Color Maize{ 0xfbec5dff };
		constexpr Color MajorelleBlue{ 0x6050dcff };
		constexpr Color Malachite{ 0x0bda51ff };
		constexpr Color Manatee{ 0x979aaaff };
		constexpr Color MangoTango{ 0xff8243ff };
		constexpr Color Mantis{ 0x74c365ff };
		constexpr Color Maroon{ 0x800000ff };
		constexpr Color Mauve{ 0xe0b0ffff };
		constexpr Color Mauvetaupe{ 0x915f6dff };
		constexpr Color Mauvelous{ 0xef98aaff };
		constexpr Color Mayablue{ 0x73c2fbff };
		constexpr Color Meatbrown{ 0xe5b73bff };
		constexpr Color MediumPersianblue{ 0x0067a5ff };
		constexpr Color Mediumaquamarine{ 0x66ddaaff };
		constexpr Color Mediumblue{ 0x0000cdff };
		constexpr Color Mediumcandyapplered{ 0xe2062cff };
		constexpr Color Mediumcarmine{ 0xaf4035ff };
		constexpr Color Mediumchampagne{ 0xf3e5abff };
		constexpr Color Mediumelectricblue{ 0x035096ff };
		constexpr Color Mediumjunglegreen{ 0x1c352dff };
		constexpr Color Mediumlavendermagenta{ 0xdda0ddff };
		constexpr Color Mediumorchid{ 0xba55d3ff };
		constexpr Color Mediumpurple{ 0x9370dbff };
		constexpr Color Mediumredviolet{ 0xbb3385ff };
		constexpr Color Mediumseagreen{ 0x3cb371ff };
		constexpr Color Mediumslateblue{ 0x7b68eeff };
		constexpr Color Mediumspringbud{ 0xc9dc87ff };
		constexpr Color Mediumspringgreen{ 0x00fa9aff };
		constexpr Color Mediumtaupe{ 0x674c47ff };
		constexpr Color Mediumtealblue{ 0x0054b4ff };
		constexpr Color Mediumturquoise{ 0x48d1ccff };
		constexpr Color Mediumvioletred{ 0xc71585ff };
		constexpr Color Melon{ 0xfdbcb4ff };
		constexpr Color Midnightblue{ 0x191970ff };
		constexpr Color Midnightgreen{ 0x004953ff };
		constexpr Color Mikadoyellow{ 0xffc40cff };
		constexpr Color Mint{ 0x3eb489ff };
		constexpr Color Mintcream{ 0xf5fffaff };
		constexpr Color Mintgreen{ 0x98ff98ff };
		constexpr Color Mistyrose{ 0xffe4e1ff };
		constexpr Color Moccasin{ 0xfaebd7ff };
		constexpr Color Modebeige{ 0x967117ff };
		constexpr Color Moonstoneblue{ 0x73a9c2ff };
		constexpr Color Mordantred{ 0xae0c00ff };
		constexpr Color Mossgreen{ 0xaddfadff };
		constexpr Color MountainMeadow{ 0x30ba8fff };
		constexpr Color Mountbattenpink{ 0x997a8dff };
		constexpr Color Mulberry{ 0xc54b8cff };
		constexpr Color Munsell{ 0xf2f3f4ff };
		constexpr Color Mustard{ 0xffdb58ff };
		constexpr Color Myrtle{ 0x21421eff };
		constexpr Color Nadeshikopink{ 0xf6adc6ff };
		constexpr Color Napiergreen{ 0x2a8000ff };
		constexpr Color Naplesyellow{ 0xfada5eff };
		constexpr Color Navajowhite{ 0xffdeadff };
		constexpr Color Navyblue{ 0x000080ff };
		constexpr Color NeonCarrot{ 0xffa343ff };
		constexpr Color Neonfuchsia{ 0xfe59c2ff };
		constexpr Color Neongreen{ 0x39ff14ff };
		constexpr Color Nonphotoblue{ 0xa4ddedff };
		constexpr Color NorthTexasGreen{ 0x059033ff };
		constexpr Color OceanBoatBlue{ 0x0077beff };
		constexpr Color Ochre{ 0xcc7722ff };
		constexpr Color Officegreen{ 0x008000ff };
		constexpr Color Oldgold{ 0xcfb53bff };
		constexpr Color Oldlace{ 0xfdf5e6ff };
		constexpr Color Oldlavender{ 0x796878ff };
		constexpr Color Oldmauve{ 0x673147ff };
		constexpr Color Oldrose{ 0xc08081ff };
		constexpr Color Olive{ 0x808000ff };
		constexpr Color OliveDrab{ 0x6b8e23ff };
		constexpr Color OliveGreen{ 0xbab86cff };
		constexpr Color Olivine{ 0x9ab973ff };
		constexpr Color Onyx{ 0x0f0f0fff };
		constexpr Color Operamauve{ 0xb784a7ff };
		constexpr Color Orange{ 0xffa500ff };
		constexpr Color OrangeYellow{ 0xf8d568ff };
		constexpr Color Orangepeel{ 0xff9f00ff };
		constexpr Color Orangered{ 0xff4500ff };
		constexpr Color Orchid{ 0xda70d6ff };
		constexpr Color Otterbrown{ 0x654321ff };
		constexpr Color OuterSpace{ 0x414a4cff };
		constexpr Color OutrageousOrange{ 0xff6e4aff };
		constexpr Color OxfordBlue{ 0x002147ff };
		constexpr Color PacificBlue{ 0x1ca9c9ff };
		constexpr Color Pakistangreen{ 0x006600ff };
		constexpr Color Palatinateblue{ 0x273be2ff };
		constexpr Color Palatinatepurple{ 0x682860ff };
		constexpr Color Paleaqua{ 0xbcd4e6ff };
		constexpr Color Paleblue{ 0xafeeeeff };
		constexpr Color Palebrown{ 0x987654ff };
		constexpr Color Palecarmine{ 0xaf4035ff };
		constexpr Color Palecerulean{ 0x9bc4e2ff };
		constexpr Color Palechestnut{ 0xddadafff };
		constexpr Color Palecopper{ 0xda8a67ff };
		constexpr Color Palecornflowerblue{ 0xabcdefff };
		constexpr Color Palegold{ 0xe6be8aff };
		constexpr Color Palegoldenrod{ 0xeee8aaff };
		constexpr Color Palegreen{ 0x98fb98ff };
		constexpr Color Palelavender{ 0xdcd0ffff };
		constexpr Color Palemagenta{ 0xf984e5ff };
		constexpr Color Palepink{ 0xfadaddff };
		constexpr Color Paleplum{ 0xdda0ddff };
		constexpr Color Paleredviolet{ 0xdb7093ff };
		constexpr Color Palerobineggblue{ 0x96ded1ff };
		constexpr Color Palesilver{ 0xc9c0bbff };
		constexpr Color Palespringbud{ 0xecebbdff };
		constexpr Color Paletaupe{ 0xbc987eff };
		constexpr Color Palevioletred{ 0xdb7093ff };
		constexpr Color Pansypurple{ 0x78184aff };
		constexpr Color Papayawhip{ 0xffefd5ff };
		constexpr Color ParisGreen{ 0x50c878ff };
		constexpr Color Pastelblue{ 0xaec6cfff };
		constexpr Color Pastelbrown{ 0x836953ff };
		constexpr Color Pastelgray{ 0xcfcfc4ff };
		constexpr Color Pastelgreen{ 0x77dd77ff };
		constexpr Color Pastelmagenta{ 0xf49ac2ff };
		constexpr Color Pastelorange{ 0xffb347ff };
		constexpr Color Pastelpink{ 0xffd1dcff };
		constexpr Color Pastelpurple{ 0xb39eb5ff };
		constexpr Color Pastelred{ 0xff6961ff };
		constexpr Color Pastelviolet{ 0xcb99c9ff };
		constexpr Color Pastelyellow{ 0xfdfd96ff };
		constexpr Color Patriarch{ 0x800080ff };
		constexpr Color Paynegrey{ 0x536878ff };
		constexpr Color Peach{ 0xffe5b4ff };
		constexpr Color Peachpuff{ 0xffdab9ff };
		constexpr Color Peachyellow{ 0xfadfadff };
		constexpr Color Pear{ 0xd1e231ff };
		constexpr Color Pearl{ 0xeae0c8ff };
		constexpr Color PearlAqua{ 0x88d8c0ff };
		constexpr Color Peridot{ 0xe6e200ff };
		constexpr Color Periwinkle{ 0xccccffff };
		constexpr Color Persianblue{ 0x1c39bbff };
		constexpr Color Persianindigo{ 0x32127aff };
		constexpr Color Persianorange{ 0xd99058ff };
		constexpr Color Persianpink{ 0xf77fbeff };
		constexpr Color Persianplum{ 0x701c1cff };
		constexpr Color Persianred{ 0xcc3333ff };
		constexpr Color Persianrose{ 0xfe28a2ff };
		constexpr Color Phlox{ 0xdf00ffff };
		constexpr Color Phthaloblue{ 0x000f89ff };
		constexpr Color Phthalogreen{ 0x123524ff };
		constexpr Color Piggypink{ 0xfddde6ff };
		constexpr Color Pinegreen{ 0x01796fff };
		constexpr Color Pink{ 0xffc0cbff };
		constexpr Color PinkFlamingo{ 0xfc74fdff };
		constexpr Color PinkSherbet{ 0xf78fa7ff };
		constexpr Color Pinkpearl{ 0xe7accfff };
		constexpr Color Pistachio{ 0x93c572ff };
		constexpr Color Platinum{ 0xe5e4e2ff };
		constexpr Color Plum{ 0xdda0ddff };
		constexpr Color PortlandOrange{ 0xff5a36ff };
		constexpr Color Powderblue{ 0xb0e0e6ff };
		constexpr Color Princetonorange{ 0xff8f00ff };
		constexpr Color Prussianblue{ 0x003153ff };
		constexpr Color Psychedelicpurple{ 0xdf00ffff };
		constexpr Color Puce{ 0xcc8899ff };
		constexpr Color Pumpkin{ 0xff7518ff };
		constexpr Color Purple{ 0x800080ff };
		constexpr Color PurpleHeart{ 0x69359cff };
		constexpr Color PurpleMountainsMajesty{ 0x9d81baff };
		constexpr Color Purplemountainmajesty{ 0x9678b6ff };
		constexpr Color Purplepizzazz{ 0xfe4edaff };
		constexpr Color Purpletaupe{ 0x50404dff };
		constexpr Color Rackley{ 0x5d8aa8ff };
		constexpr Color RadicalRed{ 0xff355eff };
		constexpr Color Raspberry{ 0xe30b5dff };
		constexpr Color Raspberryglace{ 0x915f6dff };
		constexpr Color Raspberrypink{ 0xe25098ff };
		constexpr Color Raspberryrose{ 0xb3446cff };
		constexpr Color RawSienna{ 0xd68a59ff };
		constexpr Color Razzledazzlerose{ 0xff33ccff };
		constexpr Color Razzmatazz{ 0xe3256bff };
		constexpr Color Red{ 0xff0000ff };
		constexpr Color RedOrange{ 0xff5349ff };
		constexpr Color Redbrown{ 0xa52a2aff };
		constexpr Color Redviolet{ 0xc71585ff };
		constexpr Color Richblack{ 0x004040ff };
		constexpr Color Richcarmine{ 0xd70040ff };
		constexpr Color Richelectricblue{ 0x0892d0ff };
		constexpr Color Richlilac{ 0xb666d2ff };
		constexpr Color Richmaroon{ 0xb03060ff };
		constexpr Color Riflegreen{ 0x414833ff };
		constexpr Color RobinsEggBlue{ 0x1fcecbff };
		constexpr Color Rose{ 0xff007fff };
		constexpr Color Rosebonbon{ 0xf9429eff };
		constexpr Color Roseebony{ 0x674846ff };
		constexpr Color Rosegold{ 0xb76e79ff };
		constexpr Color Rosemadder{ 0xe32636ff };
		constexpr Color Rosepink{ 0xff66ccff };
		constexpr Color Rosequartz{ 0xaa98a9ff };
		constexpr Color Rosetaupe{ 0x905d5dff };
		constexpr Color Rosevale{ 0xab4e52ff };
		constexpr Color Rosewood{ 0x65000bff };
		constexpr Color Rossocorsa{ 0xd40000ff };
		constexpr Color Rosybrown{ 0xbc8f8fff };
		constexpr Color Royalazure{ 0x0038a8ff };
		constexpr Color Royalblue{ 0x4169e1ff };
		constexpr Color Royalfuchsia{ 0xca2c92ff };
		constexpr Color Royalpurple{ 0x7851a9ff };
		constexpr Color Ruby{ 0xe0115fff };
		constexpr Color Ruddy{ 0xff0028ff };
		constexpr Color Ruddybrown{ 0xbb6528ff };
		constexpr Color Ruddypink{ 0xe18e96ff };
		constexpr Color Rufous{ 0xa81c07ff };
		constexpr Color Russet{ 0x80461bff };
		constexpr Color Rust{ 0xb7410eff };
		constexpr Color SacramentoStategreen{ 0x00563fff };
		constexpr Color Saddlebrown{ 0x8b4513ff };
		constexpr Color Safetyorange{ 0xff6700ff };
		constexpr Color Saffron{ 0xf4c430ff };
		constexpr Color SaintPatrickBlue{ 0x23297aff };
		constexpr Color Salmon{ 0xff8c69ff };
		constexpr Color Salmonpink{ 0xff91a4ff };
		constexpr Color Sand{ 0xc2b280ff };
		constexpr Color Sanddune{ 0x967117ff };
		constexpr Color Sandstorm{ 0xecd540ff };
		constexpr Color Sandybrown{ 0xf4a460ff };
		constexpr Color Sandytaupe{ 0x967117ff };
		constexpr Color Sapgreen{ 0x507d2aff };
		constexpr Color Sapphire{ 0x0f52baff };
		constexpr Color Satinsheengold{ 0xcba135ff };
		constexpr Color Scarlet{ 0xff2400ff };
		constexpr Color Schoolbusyellow{ 0xffd800ff };
		constexpr Color ScreaminGreen{ 0x76ff7aff };
		constexpr Color Seablue{ 0x006994ff };
		constexpr Color Seagreen{ 0x2e8b57ff };
		constexpr Color Sealbrown{ 0x321414ff };
		constexpr Color Seashell{ 0xfff5eeff };
		constexpr Color Selectiveyellow{ 0xffba00ff };
		constexpr Color Sepia{ 0x704214ff };
		constexpr Color Shadow{ 0x8a795dff };
		constexpr Color Shamrock{ 0x45cea2ff };
		constexpr Color Shamrockgreen{ 0x009e60ff };
		constexpr Color Shockingpink{ 0xfc0fc0ff };
		constexpr Color Sienna{ 0x882d17ff };
		constexpr Color Silver{ 0xc0c0c0ff };
		constexpr Color Sinopia{ 0xcb410bff };
		constexpr Color Skobeloff{ 0x007474ff };
		constexpr Color Skyblue{ 0x87ceebff };
		constexpr Color Skymagenta{ 0xcf71afff };
		constexpr Color Slateblue{ 0x6a5acdff };
		constexpr Color Slategray{ 0x708090ff };
		constexpr Color Smalt{ 0x003399ff };
		constexpr Color Smokeytopaz{ 0x933d41ff };
		constexpr Color Smokyblack{ 0x100c08ff };
		constexpr Color Snow{ 0xfffafaff };
		constexpr Color SpiroDiscoBall{ 0x0fc0fcff };
		constexpr Color Springbud{ 0xa7fc00ff };
		constexpr Color Springgreen{ 0x00ff7fff };
		constexpr Color Steelblue{ 0x4682b4ff };
		constexpr Color Stildegrainyellow{ 0xfada5eff };
		constexpr Color Stizza{ 0x990000ff };
		constexpr Color Stormcloud{ 0x008080ff };
		constexpr Color Straw{ 0xe4d96fff };
		constexpr Color Sunglow{ 0xffcc33ff };
		constexpr Color Sunset{ 0xfad6a5ff };
		constexpr Color SunsetOrange{ 0xfd5e53ff };
		constexpr Color Tan{ 0xd2b48cff };
		constexpr Color Tangelo{ 0xf94d00ff };
		constexpr Color Tangerine{ 0xf28500ff };
		constexpr Color Tangerineyellow{ 0xffcc00ff };
		constexpr Color Taupe{ 0x483c32ff };
		constexpr Color Taupegray{ 0x8b8589ff };
		constexpr Color Tawny{ 0xcd5700ff };
		constexpr Color Teagreen{ 0xd0f0c0ff };
		constexpr Color Tearose{ 0xf4c2c2ff };
		constexpr Color Teal{ 0x008080ff };
		constexpr Color Tealblue{ 0x367588ff };
		constexpr Color Tealgreen{ 0x006d5bff };
		constexpr Color Terracotta{ 0xe2725bff };
		constexpr Color Thistle{ 0xd8bfd8ff };
		constexpr Color Thulianpink{ 0xde6fa1ff };
		constexpr Color TickleMePink{ 0xfc89acff };
		constexpr Color TiffanyBlue{ 0x0abab5ff };
		constexpr Color Tigereye{ 0xe08d3cff };
		constexpr Color Timberwolf{ 0xdbd7d2ff };
		constexpr Color Titaniumyellow{ 0xeee600ff };
		constexpr Color Tomato{ 0xff6347ff };
		constexpr Color Toolbox{ 0x746cc0ff };
		constexpr Color Topaz{ 0xffc87cff };
		constexpr Color Tractorred{ 0xfd0e35ff };
		constexpr Color TrolleyGrey{ 0x808080ff };
		constexpr Color Tropicalrainforest{ 0x00755eff };
		constexpr Color TrueBlue{ 0x0073cfff };
		constexpr Color TuftsBlue{ 0x417dc1ff };
		constexpr Color Tumbleweed{ 0xdeaa88ff };
		constexpr Color Turkishrose{ 0xb57281ff };
		constexpr Color Turquoise{ 0x30d5c8ff };
		constexpr Color Turquoiseblue{ 0x00ffefff };
		constexpr Color Turquoisegreen{ 0xa0d6b4ff };
		constexpr Color Tuscanred{ 0x66424dff };
		constexpr Color Twilightlavender{ 0x8a496bff };
		constexpr Color Tyrianpurple{ 0x66023cff };
		constexpr Color UAblue{ 0x0033aaff };
		constexpr Color UAred{ 0xd9004cff };
		constexpr Color UCLABlue{ 0x536895ff };
		constexpr Color UCLAGold{ 0xffb300ff };
		constexpr Color UFOGreen{ 0x3cd070ff };
		constexpr Color UPForestgreen{ 0x014421ff };
		constexpr Color UPMaroon{ 0x7b1113ff };
		constexpr Color USCCardinal{ 0x990000ff };
		constexpr Color USCGold{ 0xffcc00ff };
		constexpr Color Ube{ 0x8878c3ff };
		constexpr Color Ultrapink{ 0xff6fffff };
		constexpr Color Ultramarine{ 0x120a8fff };
		constexpr Color Ultramarineblue{ 0x4166f5ff };
		constexpr Color Umber{ 0x635147ff };
		constexpr Color UnitedNationsblue{ 0x5b92e5ff };
		constexpr Color UniversityofCaliforniaGold{ 0xb78727ff };
		constexpr Color UnmellowYellow{ 0xffff66ff };
		constexpr Color Upsdellred{ 0xae2029ff };
		constexpr Color Urobilin{ 0xe1ad21ff };
		constexpr Color UtahCrimson{ 0xd3003fff };
		constexpr Color Vanilla{ 0xf3e5abff };
		constexpr Color Vegasgold{ 0xc5b358ff };
		constexpr Color Venetianred{ 0xc80815ff };
		constexpr Color Verdigris{ 0x43b3aeff };
		constexpr Color Vermilion{ 0xe34234ff };
		constexpr Color Veronica{ 0xa020f0ff };
		constexpr Color Violet{ 0xee82eeff };
		constexpr Color VioletBlue{ 0x324ab2ff };
		constexpr Color VioletRed{ 0xf75394ff };
		constexpr Color Viridian{ 0x40826dff };
		constexpr Color Vividauburn{ 0x922724ff };
		constexpr Color Vividburgundy{ 0x9f1d35ff };
		constexpr Color Vividcerise{ 0xda1d81ff };
		constexpr Color Vividtangerine{ 0xffa089ff };
		constexpr Color Vividviolet{ 0x9f00ffff };
		constexpr Color Warmblack{ 0x004242ff };
		constexpr Color Waterspout{ 0x00ffffff };
		constexpr Color Wenge{ 0x645452ff };
		constexpr Color Wheat{ 0xf5deb3ff };
		constexpr Color White{ 0xffffffff };
		constexpr Color Whitesmoke{ 0xf5f5f5ff };
		constexpr Color WildStrawberry{ 0xff43a4ff };
		constexpr Color WildWatermelon{ 0xfc6c85ff };
		constexpr Color Wildblueyonder{ 0xa2add0ff };
		constexpr Color Wine{ 0x722f37ff };
		constexpr Color Wisteria{ 0xc9a0dcff };
		constexpr Color Xanadu{ 0x738678ff };
		constexpr Color YaleBlue{ 0x0f4d92ff };
		constexpr Color Yellow{ 0xffff00ff };
		constexpr Color YellowOrange{ 0xffae42ff };
		constexpr Color Yellowgreen{ 0x9acd32ff };
		constexpr Color Zaffre{ 0x0014a8ff };
		constexpr Color Zinnwalditebrown{ 0x2c1608ff };
	}
}
