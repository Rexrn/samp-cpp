/**
 * Header: Color.hpp
 * Author: Pawe³ Syska aka RazzorFlame.
 * Description:
 * Implements Color class and provides over 600 named colors (within agdk::colors) namespace.
**/

#pragma once

#include <cinttypes>
#include <iostream>		// for std::ostream
#include <string>		// for std::string


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
			: r(0), g(0), b(0), a(255)
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
			: r(red_), g(green_), b(blue_), a(alpha_)
		{
		}
		
		/// <summary>
		/// Initializes a new instance of the <see cref="Color"/> class using RGBA color packed into 32 bit unsigned integer four 8-bit channels.
		/// </summary>
		/// <param name="color_">The RGBA 32-bit color.</param>
		constexpr explicit Color(const std::uint32_t color_)
			:
			r(color_	>> (3 * 8)),					// Red   component	=	Binary shift right by 3 bytes.								0xAABBCCDD => 0x000000AA
			g((color_	<< (1 * 8)) >> (3 * 8)),		// Green component	=	Binary shift left by 1 byte  and then right by 3 bytes:		0xAABBCCDD => 0xBBCCDD00 => 0x000000BB
			b((color_	<< (2 * 8)) >> (3 * 8)),		// Blue  component	=	Binary shift left by 2 bytes and then right by 3 bytes:		0xAABBCCDD => 0xCCDD0000 => 0x000000CC
			a((color_	<< (3 * 8)) >> (3 * 8))
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
		std::uint32_t toUint32() const;

		/// <summary>
		/// Converts instance to RGBA 32-bit integer.
		/// </summary>
		/// <returns>RGBA 32-bit integer.</returns>
		std::int32_t toInt32() const;

		/// <summary>
		/// Converts instance to RGBA 32-bit unsigned integer.
		/// </summary>
		/// <returns>RGBA 32-bit unsigned integer.</returns>
		explicit operator std::uint32_t() const { return this->toUint32(); }

		/// <summary>
		/// Converts instance to RGBA 32-bit integer.
		/// </summary>
		/// <returns>RGBA 32-bit integer.</returns>
		explicit operator std::int32_t() const { return this->toInt32(); }

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
		static constexpr Color AirForceblue{ 0x5d8aa8ff };
		static constexpr Color Aliceblue{ 0xf0f8ffff };
		static constexpr Color Alizarincrimson{ 0xe32636ff };
		static constexpr Color Almond{ 0xefdecdff };
		static constexpr Color Amaranth{ 0xe52b50ff };
		static constexpr Color Amber{ 0xffbf00ff };
		static constexpr Color Americanrose{ 0xff033eff };
		static constexpr Color Amethyst{ 0x9966ccff };
		static constexpr Color AndroidGreen{ 0xa4c639ff };
		static constexpr Color Antiflashwhite{ 0xf2f3f4ff };
		static constexpr Color Antiquebrass{ 0xcd9575ff };
		static constexpr Color Antiquefuchsia{ 0x915c83ff };
		static constexpr Color Antiquewhite{ 0xfaebd7ff };
		static constexpr Color Ao{ 0x008000ff };
		static constexpr Color Applegreen{ 0x8db600ff };
		static constexpr Color Apricot{ 0xfbceb1ff };
		static constexpr Color Aqua{ 0x00ffffff };
		static constexpr Color Aquamarine{ 0x7fffd4ff };
		static constexpr Color Armygreen{ 0x4b5320ff };
		static constexpr Color Arylideyellow{ 0xe9d66bff };
		static constexpr Color Ashgrey{ 0xb2beb5ff };
		static constexpr Color Asparagus{ 0x87a96bff };
		static constexpr Color Atomictangerine{ 0xff9966ff };
		static constexpr Color Auburn{ 0xa52a2aff };
		static constexpr Color Aureolin{ 0xfdee00ff };
		static constexpr Color AuroMetalSaurus{ 0x6e7f80ff };
		static constexpr Color Awesome{ 0xff2052ff };
		static constexpr Color Azure{ 0x007fffff };
		static constexpr Color Azuremistweb{ 0xf0ffffff };
		static constexpr Color Babyblue{ 0x89cff0ff };
		static constexpr Color Babyblueeyes{ 0xa1caf1ff };
		static constexpr Color Babypink{ 0xf4c2c2ff };
		static constexpr Color BallBlue{ 0x21abcdff };
		static constexpr Color BananaMania{ 0xfae7b5ff };
		static constexpr Color Bananayellow{ 0xffe135ff };
		static constexpr Color Battleshipgrey{ 0x848482ff };
		static constexpr Color Bazaar{ 0x98777bff };
		static constexpr Color Beaublue{ 0xbcd4e6ff };
		static constexpr Color Beaver{ 0x9f8170ff };
		static constexpr Color Beige{ 0xf5f5dcff };
		static constexpr Color Bisque{ 0xffe4c4ff };
		static constexpr Color Bistre{ 0x3d2b1fff };
		static constexpr Color Bittersweet{ 0xfe6f5eff };
		static constexpr Color Black{ 0x000000ff };
		static constexpr Color BlanchedAlmond{ 0xffebcdff };
		static constexpr Color BleudeFrance{ 0x318ce7ff };
		static constexpr Color BlizzardBlue{ 0xace5eeff };
		static constexpr Color Blond{ 0xfaf0beff };
		static constexpr Color Blue{ 0x0000ffff };
		static constexpr Color BlueBell{ 0xa2a2d0ff };
		static constexpr Color BlueGray{ 0x6699ccff };
		static constexpr Color Bluegreen{ 0x0d98baff };
		static constexpr Color Bluepurple{ 0x8a2be2ff };
		static constexpr Color Blueviolet{ 0x8a2be2ff };
		static constexpr Color Blush{ 0xde5d83ff };
		static constexpr Color Bole{ 0x79443bff };
		static constexpr Color Bondiblue{ 0x0095b6ff };
		static constexpr Color Bone{ 0xe3dac9ff };
		static constexpr Color BostonUniversityRed{ 0xcc0000ff };
		static constexpr Color Bottlegreen{ 0x006a4eff };
		static constexpr Color Boysenberry{ 0x873260ff };
		static constexpr Color Brandeisblue{ 0x0070ffff };
		static constexpr Color Brass{ 0xb5a642ff };
		static constexpr Color Brickred{ 0xcb4154ff };
		static constexpr Color Brightcerulean{ 0x1dacd6ff };
		static constexpr Color Brightgreen{ 0x66ff00ff };
		static constexpr Color Brightlavender{ 0xbf94e4ff };
		static constexpr Color Brightmaroon{ 0xc32148ff };
		static constexpr Color Brightpink{ 0xff007fff };
		static constexpr Color Brightturquoise{ 0x08e8deff };
		static constexpr Color Brightube{ 0xd19fe8ff };
		static constexpr Color Brilliantlavender{ 0xf4bbffff };
		static constexpr Color Brilliantrose{ 0xff55a3ff };
		static constexpr Color Brinkpink{ 0xfb607fff };
		static constexpr Color Britishracinggreen{ 0x004225ff };
		static constexpr Color Bronze{ 0xcd7f32ff };
		static constexpr Color Brown{ 0xa52a2aff };
		static constexpr Color Bubblegum{ 0xffc1ccff };
		static constexpr Color Bubbles{ 0xe7feffff };
		static constexpr Color Buff{ 0xf0dc82ff };
		static constexpr Color Bulgarianrose{ 0x480607ff };
		static constexpr Color Burgundy{ 0x800020ff };
		static constexpr Color Burlywood{ 0xdeb887ff };
		static constexpr Color Burntorange{ 0xcc5500ff };
		static constexpr Color Burntsienna{ 0xe97451ff };
		static constexpr Color Burntumber{ 0x8a3324ff };
		static constexpr Color Byzantine{ 0xbd33a4ff };
		static constexpr Color Byzantium{ 0x702963ff };
		static constexpr Color CGBlue{ 0x007aa5ff };
		static constexpr Color CGRed{ 0xe03c31ff };
		static constexpr Color Cadet{ 0x536872ff };
		static constexpr Color Cadetblue{ 0x5f9ea0ff };
		static constexpr Color Cadetgrey{ 0x91a3b0ff };
		static constexpr Color Cadmiumgreen{ 0x006b3cff };
		static constexpr Color Cadmiumorange{ 0xed872dff };
		static constexpr Color Cadmiumred{ 0xe30022ff };
		static constexpr Color Cadmiumyellow{ 0xfff600ff };
		static constexpr Color Cafaulait{ 0xa67b5bff };
		static constexpr Color Cafnoir{ 0x4b3621ff };
		static constexpr Color CalPolyPomonagreen{ 0x1e4d2bff };
		static constexpr Color CambridgeBlue{ 0xa3c1adff };
		static constexpr Color Camel{ 0xc19a6bff };
		static constexpr Color Camouflagegreen{ 0x78866bff };
		static constexpr Color Canary{ 0xffff99ff };
		static constexpr Color Canaryyellow{ 0xffef00ff };
		static constexpr Color Candyapplered{ 0xff0800ff };
		static constexpr Color Candypink{ 0xe4717aff };
		static constexpr Color Capri{ 0x00bfffff };
		static constexpr Color Caputmortuum{ 0x592720ff };
		static constexpr Color Cardinal{ 0xc41e3aff };
		static constexpr Color Caribbeangreen{ 0x00cc99ff };
		static constexpr Color Carmine{ 0xff0040ff };
		static constexpr Color Carminepink{ 0xeb4c42ff };
		static constexpr Color Carminered{ 0xff0038ff };
		static constexpr Color Carnationpink{ 0xffa6c9ff };
		static constexpr Color Carnelian{ 0xb31b1bff };
		static constexpr Color Carolinablue{ 0x99baddff };
		static constexpr Color Carrotorange{ 0xed9121ff };
		static constexpr Color Celadon{ 0xace1afff };
		static constexpr Color Celeste{ 0xb2ffffff };
		static constexpr Color Celestialblue{ 0x4997d0ff };
		static constexpr Color Cerise{ 0xde3163ff };
		static constexpr Color Cerisepink{ 0xec3b83ff };
		static constexpr Color Cerulean{ 0x007ba7ff };
		static constexpr Color Ceruleanblue{ 0x2a52beff };
		static constexpr Color Chamoisee{ 0xa0785aff };
		static constexpr Color Champagne{ 0xfad6a5ff };
		static constexpr Color Charcoal{ 0x36454fff };
		static constexpr Color Chartreuse{ 0x7fff00ff };
		static constexpr Color Cherry{ 0xde3163ff };
		static constexpr Color Cherryblossompink{ 0xffb7c5ff };
		static constexpr Color Chestnut{ 0xcd5c5cff };
		static constexpr Color Chocolate{ 0xd2691eff };
		static constexpr Color Chromeyellow{ 0xffa700ff };
		static constexpr Color Cinereous{ 0x98817bff };
		static constexpr Color Cinnabar{ 0xe34234ff };
		static constexpr Color Cinnamon{ 0xd2691eff };
		static constexpr Color Citrine{ 0xe4d00aff };
		static constexpr Color Classicrose{ 0xfbcce7ff };
		static constexpr Color Cobalt{ 0x0047abff };
		static constexpr Color Cocoabrown{ 0xd2691eff };
		static constexpr Color Coffee{ 0x6f4e37ff };
		static constexpr Color Columbiablue{ 0x9bddffff };
		static constexpr Color Coolblack{ 0x002e63ff };
		static constexpr Color Coolgrey{ 0x8c92acff };
		static constexpr Color Copper{ 0xb87333ff };
		static constexpr Color Copperrose{ 0x996666ff };
		static constexpr Color Coquelicot{ 0xff3800ff };
		static constexpr Color Coral{ 0xff7f50ff };
		static constexpr Color Coralpink{ 0xf88379ff };
		static constexpr Color Coralred{ 0xff4040ff };
		static constexpr Color Cordovan{ 0x893f45ff };
		static constexpr Color Corn{ 0xfbec5dff };
		static constexpr Color CornellRed{ 0xb31b1bff };
		static constexpr Color Cornflower{ 0x9aceebff };
		static constexpr Color Cornflowerblue{ 0x6495edff };
		static constexpr Color Cornsilk{ 0xfff8dcff };
		static constexpr Color Cosmiclatte{ 0xfff8e7ff };
		static constexpr Color Cottoncandy{ 0xffbcd9ff };
		static constexpr Color Cream{ 0xfffdd0ff };
		static constexpr Color Crimson{ 0xdc143cff };
		static constexpr Color CrimsonRed{ 0x990000ff };
		static constexpr Color Crimsonglory{ 0xbe0032ff };
		static constexpr Color Cyan{ 0x00ffffff };
		static constexpr Color Daffodil{ 0xffff31ff };
		static constexpr Color Dandelion{ 0xf0e130ff };
		static constexpr Color Darkblue{ 0x00008bff };
		static constexpr Color Darkbrown{ 0x654321ff };
		static constexpr Color Darkbyzantium{ 0x5d3954ff };
		static constexpr Color Darkcandyapplered{ 0xa40000ff };
		static constexpr Color Darkcerulean{ 0x08457eff };
		static constexpr Color Darkchestnut{ 0x986960ff };
		static constexpr Color Darkcoral{ 0xcd5b45ff };
		static constexpr Color Darkcyan{ 0x008b8bff };
		static constexpr Color Darkelectricblue{ 0x536878ff };
		static constexpr Color Darkgoldenrod{ 0xb8860bff };
		static constexpr Color Darkgray{ 0xa9a9a9ff };
		static constexpr Color Darkgreen{ 0x013220ff };
		static constexpr Color Darkjunglegreen{ 0x1a2421ff };
		static constexpr Color Darkkhaki{ 0xbdb76bff };
		static constexpr Color Darklava{ 0x483c32ff };
		static constexpr Color Darklavender{ 0x734f96ff };
		static constexpr Color Darkmagenta{ 0x8b008bff };
		static constexpr Color Darkmidnightblue{ 0x003366ff };
		static constexpr Color Darkolivegreen{ 0x556b2fff };
		static constexpr Color Darkorange{ 0xff8c00ff };
		static constexpr Color Darkorchid{ 0x9932ccff };
		static constexpr Color Darkpastelblue{ 0x779ecbff };
		static constexpr Color Darkpastelgreen{ 0x03c03cff };
		static constexpr Color Darkpastelpurple{ 0x966fd6ff };
		static constexpr Color Darkpastelred{ 0xc23b22ff };
		static constexpr Color Darkpink{ 0xe75480ff };
		static constexpr Color Darkpowderblue{ 0x003399ff };
		static constexpr Color Darkraspberry{ 0x872657ff };
		static constexpr Color Darkred{ 0x8b0000ff };
		static constexpr Color Darksalmon{ 0xe9967aff };
		static constexpr Color Darkscarlet{ 0x560319ff };
		static constexpr Color Darkseagreen{ 0x8fbc8fff };
		static constexpr Color Darksienna{ 0x3c1414ff };
		static constexpr Color Darkslateblue{ 0x483d8bff };
		static constexpr Color Darkslategray{ 0x2f4f4fff };
		static constexpr Color Darkspringgreen{ 0x177245ff };
		static constexpr Color Darktan{ 0x918151ff };
		static constexpr Color Darktangerine{ 0xffa812ff };
		static constexpr Color Darktaupe{ 0x483c32ff };
		static constexpr Color Darkterracotta{ 0xcc4e5cff };
		static constexpr Color Darkturquoise{ 0x00ced1ff };
		static constexpr Color Darkviolet{ 0x9400d3ff };
		static constexpr Color Dartmouthgreen{ 0x00693eff };
		static constexpr Color Davygrey{ 0x555555ff };
		static constexpr Color Debianred{ 0xd70a53ff };
		static constexpr Color Deepcarmine{ 0xa9203eff };
		static constexpr Color Deepcarminepink{ 0xef3038ff };
		static constexpr Color Deepcarrotorange{ 0xe9692cff };
		static constexpr Color Deepcerise{ 0xda3287ff };
		static constexpr Color Deepchampagne{ 0xfad6a5ff };
		static constexpr Color Deepchestnut{ 0xb94e48ff };
		static constexpr Color Deepcoffee{ 0x704241ff };
		static constexpr Color Deepfuchsia{ 0xc154c1ff };
		static constexpr Color Deepjunglegreen{ 0x004b49ff };
		static constexpr Color Deeplilac{ 0x9955bbff };
		static constexpr Color Deepmagenta{ 0xcc00ccff };
		static constexpr Color Deeppeach{ 0xffcba4ff };
		static constexpr Color Deeppink{ 0xff1493ff };
		static constexpr Color Deepsaffron{ 0xff9933ff };
		static constexpr Color Deepskyblue{ 0x00bfffff };
		static constexpr Color Denim{ 0x1560bdff };
		static constexpr Color Desert{ 0xc19a6bff };
		static constexpr Color Desertsand{ 0xedc9afff };
		static constexpr Color Dimgray{ 0x696969ff };
		static constexpr Color Dodgerblue{ 0x1e90ffff };
		static constexpr Color Dogwoodrose{ 0xd71868ff };
		static constexpr Color Dollarbill{ 0x85bb65ff };
		static constexpr Color Drab{ 0x967117ff };
		static constexpr Color Dukeblue{ 0x00009cff };
		static constexpr Color Earthyellow{ 0xe1a95fff };
		static constexpr Color Ecru{ 0xc2b280ff };
		static constexpr Color Eggplant{ 0x614051ff };
		static constexpr Color Eggshell{ 0xf0ead6ff };
		static constexpr Color Egyptianblue{ 0x1034a6ff };
		static constexpr Color Electricblue{ 0x7df9ffff };
		static constexpr Color Electriccrimson{ 0xff003fff };
		static constexpr Color Electriccyan{ 0x00ffffff };
		static constexpr Color Electricgreen{ 0x00ff00ff };
		static constexpr Color Electricindigo{ 0x6f00ffff };
		static constexpr Color Electriclavender{ 0xf4bbffff };
		static constexpr Color Electriclime{ 0xccff00ff };
		static constexpr Color Electricpurple{ 0xbf00ffff };
		static constexpr Color Electricultramarine{ 0x3f00ffff };
		static constexpr Color Electricviolet{ 0x8f00ffff };
		static constexpr Color Electricyellow{ 0xffff00ff };
		static constexpr Color Emerald{ 0x50c878ff };
		static constexpr Color Etonblue{ 0x96c8a2ff };
		static constexpr Color Fallow{ 0xc19a6bff };
		static constexpr Color Falured{ 0x801818ff };
		static constexpr Color Famous{ 0xff00ffff };
		static constexpr Color Fandango{ 0xb53389ff };
		static constexpr Color Fashionfuchsia{ 0xf400a1ff };
		static constexpr Color Fawn{ 0xe5aa70ff };
		static constexpr Color Feldgrau{ 0x4d5d53ff };
		static constexpr Color Fern{ 0x71bc78ff };
		static constexpr Color Ferngreen{ 0x4f7942ff };
		static constexpr Color FerrariRed{ 0xff2800ff };
		static constexpr Color Fielddrab{ 0x6c541eff };
		static constexpr Color Fireenginered{ 0xce2029ff };
		static constexpr Color Firebrick{ 0xb22222ff };
		static constexpr Color Flame{ 0xe25822ff };
		static constexpr Color Flamingopink{ 0xfc8eacff };
		static constexpr Color Flavescent{ 0xf7e98eff };
		static constexpr Color Flax{ 0xeedc82ff };
		static constexpr Color Floralwhite{ 0xfffaf0ff };
		static constexpr Color Fluorescentorange{ 0xffbf00ff };
		static constexpr Color Fluorescentpink{ 0xff1493ff };
		static constexpr Color Fluorescentyellow{ 0xccff00ff };
		static constexpr Color Folly{ 0xff004fff };
		static constexpr Color Forestgreen{ 0x228b22ff };
		static constexpr Color Frenchbeige{ 0xa67b5bff };
		static constexpr Color Frenchblue{ 0x0072bbff };
		static constexpr Color Frenchlilac{ 0x86608eff };
		static constexpr Color Frenchrose{ 0xf64a8aff };
		static constexpr Color Fuchsia{ 0xff00ffff };
		static constexpr Color Fuchsiapink{ 0xff77ffff };
		static constexpr Color Fulvous{ 0xe48400ff };
		static constexpr Color FuzzyWuzzy{ 0xcc6666ff };
		static constexpr Color Gainsboro{ 0xdcdcdcff };
		static constexpr Color Gamboge{ 0xe49b0fff };
		static constexpr Color Ghostwhite{ 0xf8f8ffff };
		static constexpr Color Ginger{ 0xb06500ff };
		static constexpr Color Glaucous{ 0x6082b6ff };
		static constexpr Color Glitter{ 0xe6e8faff };
		static constexpr Color Gold{ 0xffd700ff };
		static constexpr Color Goldenbrown{ 0x996515ff };
		static constexpr Color Goldenpoppy{ 0xfcc200ff };
		static constexpr Color Goldenyellow{ 0xffdf00ff };
		static constexpr Color Goldenrod{ 0xdaa520ff };
		static constexpr Color GrannySmithApple{ 0xa8e4a0ff };
		static constexpr Color Gray{ 0x808080ff };
		static constexpr Color Grayasparagus{ 0x465945ff };
		static constexpr Color Green{ 0x00ff00ff };
		static constexpr Color GreenBlue{ 0x1164b4ff };
		static constexpr Color Greenyellow{ 0xadff2fff };
		static constexpr Color Grullo{ 0xa99a86ff };
		static constexpr Color Guppiegreen{ 0x00ff7fff };
		static constexpr Color Halaybe{ 0x663854ff };
		static constexpr Color Hanblue{ 0x446ccfff };
		static constexpr Color Hanpurple{ 0x5218faff };
		static constexpr Color Hansayellow{ 0xe9d66bff };
		static constexpr Color Harlequin{ 0x3fff00ff };
		static constexpr Color Harvardcrimson{ 0xc90016ff };
		static constexpr Color HarvestGold{ 0xda9100ff };
		static constexpr Color HeartGold{ 0x808000ff };
		static constexpr Color Heliotrope{ 0xdf73ffff };
		static constexpr Color Hollywoodcerise{ 0xf400a1ff };
		static constexpr Color Honeydew{ 0xf0fff0ff };
		static constexpr Color Hookergreen{ 0x49796bff };
		static constexpr Color Hotmagenta{ 0xff1dceff };
		static constexpr Color Hotpink{ 0xff69b4ff };
		static constexpr Color Huntergreen{ 0x355e3bff };
		static constexpr Color Icterine{ 0xfcf75eff };
		static constexpr Color Inchworm{ 0xb2ec5dff };
		static constexpr Color Indiagreen{ 0x138808ff };
		static constexpr Color Indianred{ 0xcd5c5cff };
		static constexpr Color Indianyellow{ 0xe3a857ff };
		static constexpr Color Indigo{ 0x4b0082ff };
		static constexpr Color InternationalKleinBlue{ 0x002fa7ff };
		static constexpr Color Internationalorange{ 0xff4f00ff };
		static constexpr Color Iris{ 0x5a4fcfff };
		static constexpr Color Isabelline{ 0xf4f0ecff };
		static constexpr Color Islamicgreen{ 0x009000ff };
		static constexpr Color Ivory{ 0xfffff0ff };
		static constexpr Color Jade{ 0x00a86bff };
		static constexpr Color Jasmine{ 0xf8de7eff };
		static constexpr Color Jasper{ 0xd73b3eff };
		static constexpr Color Jazzberryjam{ 0xa50b5eff };
		static constexpr Color Jonquil{ 0xfada5eff };
		static constexpr Color Junebud{ 0xbdda57ff };
		static constexpr Color Junglegreen{ 0x29ab87ff };
		static constexpr Color KUCrimson{ 0xe8000dff };
		static constexpr Color Kellygreen{ 0x4cbb17ff };
		static constexpr Color Khaki{ 0xc3b091ff };
		static constexpr Color LaSalleGreen{ 0x087830ff };
		static constexpr Color Languidlavender{ 0xd6caddff };
		static constexpr Color Lapislazuli{ 0x26619cff };
		static constexpr Color LaserLemon{ 0xfefe22ff };
		static constexpr Color Laurelgreen{ 0xa9ba9dff };
		static constexpr Color Lava{ 0xcf1020ff };
		static constexpr Color Lavender{ 0xe6e6faff };
		static constexpr Color Lavenderblue{ 0xccccffff };
		static constexpr Color Lavenderblush{ 0xfff0f5ff };
		static constexpr Color Lavendergray{ 0xc4c3d0ff };
		static constexpr Color Lavenderindigo{ 0x9457ebff };
		static constexpr Color Lavendermagenta{ 0xee82eeff };
		static constexpr Color Lavendermist{ 0xe6e6faff };
		static constexpr Color Lavenderpink{ 0xfbaed2ff };
		static constexpr Color Lavenderpurple{ 0x967bb6ff };
		static constexpr Color Lavenderrose{ 0xfba0e3ff };
		static constexpr Color Lawngreen{ 0x7cfc00ff };
		static constexpr Color Lemon{ 0xfff700ff };
		static constexpr Color LemonYellow{ 0xfff44fff };
		static constexpr Color Lemonchiffon{ 0xfffacdff };
		static constexpr Color Lemonlime{ 0xbfff00ff };
		static constexpr Color LightCrimson{ 0xf56991ff };
		static constexpr Color LightThulianpink{ 0xe68facff };
		static constexpr Color Lightapricot{ 0xfdd5b1ff };
		static constexpr Color Lightblue{ 0xadd8e6ff };
		static constexpr Color Lightbrown{ 0xb5651dff };
		static constexpr Color Lightcarminepink{ 0xe66771ff };
		static constexpr Color Lightcoral{ 0xf08080ff };
		static constexpr Color Lightcornflowerblue{ 0x93cceaff };
		static constexpr Color Lightcyan{ 0xe0ffffff };
		static constexpr Color Lightfuchsiapink{ 0xf984efff };
		static constexpr Color Lightgoldenrodyellow{ 0xfafad2ff };
		static constexpr Color Lightgray{ 0xd3d3d3ff };
		static constexpr Color Lightgreen{ 0x90ee90ff };
		static constexpr Color Lightkhaki{ 0xf0e68cff };
		static constexpr Color Lightpastelpurple{ 0xb19cd9ff };
		static constexpr Color Lightpink{ 0xffb6c1ff };
		static constexpr Color Lightsalmon{ 0xffa07aff };
		static constexpr Color Lightsalmonpink{ 0xff9999ff };
		static constexpr Color Lightseagreen{ 0x20b2aaff };
		static constexpr Color Lightskyblue{ 0x87cefaff };
		static constexpr Color Lightslategray{ 0x778899ff };
		static constexpr Color Lighttaupe{ 0xb38b6dff };
		static constexpr Color Lightyellow{ 0xffffedff };
		static constexpr Color Lilac{ 0xc8a2c8ff };
		static constexpr Color Lime{ 0xbfff00ff };
		static constexpr Color Limegreen{ 0x32cd32ff };
		static constexpr Color Lincolngreen{ 0x195905ff };
		static constexpr Color Linen{ 0xfaf0e6ff };
		static constexpr Color Lion{ 0xc19a6bff };
		static constexpr Color Liver{ 0x534b4fff };
		static constexpr Color Lust{ 0xe62020ff };
		static constexpr Color MSUGreen{ 0x18453bff };
		static constexpr Color MacaroniandCheese{ 0xffbd88ff };
		static constexpr Color Magenta{ 0xff00ffff };
		static constexpr Color Magicmint{ 0xaaf0d1ff };
		static constexpr Color Magnolia{ 0xf8f4ffff };
		static constexpr Color Mahogany{ 0xc04000ff };
		static constexpr Color Maize{ 0xfbec5dff };
		static constexpr Color MajorelleBlue{ 0x6050dcff };
		static constexpr Color Malachite{ 0x0bda51ff };
		static constexpr Color Manatee{ 0x979aaaff };
		static constexpr Color MangoTango{ 0xff8243ff };
		static constexpr Color Mantis{ 0x74c365ff };
		static constexpr Color Maroon{ 0x800000ff };
		static constexpr Color Mauve{ 0xe0b0ffff };
		static constexpr Color Mauvetaupe{ 0x915f6dff };
		static constexpr Color Mauvelous{ 0xef98aaff };
		static constexpr Color Mayablue{ 0x73c2fbff };
		static constexpr Color Meatbrown{ 0xe5b73bff };
		static constexpr Color MediumPersianblue{ 0x0067a5ff };
		static constexpr Color Mediumaquamarine{ 0x66ddaaff };
		static constexpr Color Mediumblue{ 0x0000cdff };
		static constexpr Color Mediumcandyapplered{ 0xe2062cff };
		static constexpr Color Mediumcarmine{ 0xaf4035ff };
		static constexpr Color Mediumchampagne{ 0xf3e5abff };
		static constexpr Color Mediumelectricblue{ 0x035096ff };
		static constexpr Color Mediumjunglegreen{ 0x1c352dff };
		static constexpr Color Mediumlavendermagenta{ 0xdda0ddff };
		static constexpr Color Mediumorchid{ 0xba55d3ff };
		static constexpr Color Mediumpurple{ 0x9370dbff };
		static constexpr Color Mediumredviolet{ 0xbb3385ff };
		static constexpr Color Mediumseagreen{ 0x3cb371ff };
		static constexpr Color Mediumslateblue{ 0x7b68eeff };
		static constexpr Color Mediumspringbud{ 0xc9dc87ff };
		static constexpr Color Mediumspringgreen{ 0x00fa9aff };
		static constexpr Color Mediumtaupe{ 0x674c47ff };
		static constexpr Color Mediumtealblue{ 0x0054b4ff };
		static constexpr Color Mediumturquoise{ 0x48d1ccff };
		static constexpr Color Mediumvioletred{ 0xc71585ff };
		static constexpr Color Melon{ 0xfdbcb4ff };
		static constexpr Color Midnightblue{ 0x191970ff };
		static constexpr Color Midnightgreen{ 0x004953ff };
		static constexpr Color Mikadoyellow{ 0xffc40cff };
		static constexpr Color Mint{ 0x3eb489ff };
		static constexpr Color Mintcream{ 0xf5fffaff };
		static constexpr Color Mintgreen{ 0x98ff98ff };
		static constexpr Color Mistyrose{ 0xffe4e1ff };
		static constexpr Color Moccasin{ 0xfaebd7ff };
		static constexpr Color Modebeige{ 0x967117ff };
		static constexpr Color Moonstoneblue{ 0x73a9c2ff };
		static constexpr Color Mordantred{ 0xae0c00ff };
		static constexpr Color Mossgreen{ 0xaddfadff };
		static constexpr Color MountainMeadow{ 0x30ba8fff };
		static constexpr Color Mountbattenpink{ 0x997a8dff };
		static constexpr Color Mulberry{ 0xc54b8cff };
		static constexpr Color Munsell{ 0xf2f3f4ff };
		static constexpr Color Mustard{ 0xffdb58ff };
		static constexpr Color Myrtle{ 0x21421eff };
		static constexpr Color Nadeshikopink{ 0xf6adc6ff };
		static constexpr Color Napiergreen{ 0x2a8000ff };
		static constexpr Color Naplesyellow{ 0xfada5eff };
		static constexpr Color Navajowhite{ 0xffdeadff };
		static constexpr Color Navyblue{ 0x000080ff };
		static constexpr Color NeonCarrot{ 0xffa343ff };
		static constexpr Color Neonfuchsia{ 0xfe59c2ff };
		static constexpr Color Neongreen{ 0x39ff14ff };
		static constexpr Color Nonphotoblue{ 0xa4ddedff };
		static constexpr Color NorthTexasGreen{ 0x059033ff };
		static constexpr Color OceanBoatBlue{ 0x0077beff };
		static constexpr Color Ochre{ 0xcc7722ff };
		static constexpr Color Officegreen{ 0x008000ff };
		static constexpr Color Oldgold{ 0xcfb53bff };
		static constexpr Color Oldlace{ 0xfdf5e6ff };
		static constexpr Color Oldlavender{ 0x796878ff };
		static constexpr Color Oldmauve{ 0x673147ff };
		static constexpr Color Oldrose{ 0xc08081ff };
		static constexpr Color Olive{ 0x808000ff };
		static constexpr Color OliveDrab{ 0x6b8e23ff };
		static constexpr Color OliveGreen{ 0xbab86cff };
		static constexpr Color Olivine{ 0x9ab973ff };
		static constexpr Color Onyx{ 0x0f0f0fff };
		static constexpr Color Operamauve{ 0xb784a7ff };
		static constexpr Color Orange{ 0xffa500ff };
		static constexpr Color OrangeYellow{ 0xf8d568ff };
		static constexpr Color Orangepeel{ 0xff9f00ff };
		static constexpr Color Orangered{ 0xff4500ff };
		static constexpr Color Orchid{ 0xda70d6ff };
		static constexpr Color Otterbrown{ 0x654321ff };
		static constexpr Color OuterSpace{ 0x414a4cff };
		static constexpr Color OutrageousOrange{ 0xff6e4aff };
		static constexpr Color OxfordBlue{ 0x002147ff };
		static constexpr Color PacificBlue{ 0x1ca9c9ff };
		static constexpr Color Pakistangreen{ 0x006600ff };
		static constexpr Color Palatinateblue{ 0x273be2ff };
		static constexpr Color Palatinatepurple{ 0x682860ff };
		static constexpr Color Paleaqua{ 0xbcd4e6ff };
		static constexpr Color Paleblue{ 0xafeeeeff };
		static constexpr Color Palebrown{ 0x987654ff };
		static constexpr Color Palecarmine{ 0xaf4035ff };
		static constexpr Color Palecerulean{ 0x9bc4e2ff };
		static constexpr Color Palechestnut{ 0xddadafff };
		static constexpr Color Palecopper{ 0xda8a67ff };
		static constexpr Color Palecornflowerblue{ 0xabcdefff };
		static constexpr Color Palegold{ 0xe6be8aff };
		static constexpr Color Palegoldenrod{ 0xeee8aaff };
		static constexpr Color Palegreen{ 0x98fb98ff };
		static constexpr Color Palelavender{ 0xdcd0ffff };
		static constexpr Color Palemagenta{ 0xf984e5ff };
		static constexpr Color Palepink{ 0xfadaddff };
		static constexpr Color Paleplum{ 0xdda0ddff };
		static constexpr Color Paleredviolet{ 0xdb7093ff };
		static constexpr Color Palerobineggblue{ 0x96ded1ff };
		static constexpr Color Palesilver{ 0xc9c0bbff };
		static constexpr Color Palespringbud{ 0xecebbdff };
		static constexpr Color Paletaupe{ 0xbc987eff };
		static constexpr Color Palevioletred{ 0xdb7093ff };
		static constexpr Color Pansypurple{ 0x78184aff };
		static constexpr Color Papayawhip{ 0xffefd5ff };
		static constexpr Color ParisGreen{ 0x50c878ff };
		static constexpr Color Pastelblue{ 0xaec6cfff };
		static constexpr Color Pastelbrown{ 0x836953ff };
		static constexpr Color Pastelgray{ 0xcfcfc4ff };
		static constexpr Color Pastelgreen{ 0x77dd77ff };
		static constexpr Color Pastelmagenta{ 0xf49ac2ff };
		static constexpr Color Pastelorange{ 0xffb347ff };
		static constexpr Color Pastelpink{ 0xffd1dcff };
		static constexpr Color Pastelpurple{ 0xb39eb5ff };
		static constexpr Color Pastelred{ 0xff6961ff };
		static constexpr Color Pastelviolet{ 0xcb99c9ff };
		static constexpr Color Pastelyellow{ 0xfdfd96ff };
		static constexpr Color Patriarch{ 0x800080ff };
		static constexpr Color Paynegrey{ 0x536878ff };
		static constexpr Color Peach{ 0xffe5b4ff };
		static constexpr Color Peachpuff{ 0xffdab9ff };
		static constexpr Color Peachyellow{ 0xfadfadff };
		static constexpr Color Pear{ 0xd1e231ff };
		static constexpr Color Pearl{ 0xeae0c8ff };
		static constexpr Color PearlAqua{ 0x88d8c0ff };
		static constexpr Color Peridot{ 0xe6e200ff };
		static constexpr Color Periwinkle{ 0xccccffff };
		static constexpr Color Persianblue{ 0x1c39bbff };
		static constexpr Color Persianindigo{ 0x32127aff };
		static constexpr Color Persianorange{ 0xd99058ff };
		static constexpr Color Persianpink{ 0xf77fbeff };
		static constexpr Color Persianplum{ 0x701c1cff };
		static constexpr Color Persianred{ 0xcc3333ff };
		static constexpr Color Persianrose{ 0xfe28a2ff };
		static constexpr Color Phlox{ 0xdf00ffff };
		static constexpr Color Phthaloblue{ 0x000f89ff };
		static constexpr Color Phthalogreen{ 0x123524ff };
		static constexpr Color Piggypink{ 0xfddde6ff };
		static constexpr Color Pinegreen{ 0x01796fff };
		static constexpr Color Pink{ 0xffc0cbff };
		static constexpr Color PinkFlamingo{ 0xfc74fdff };
		static constexpr Color PinkSherbet{ 0xf78fa7ff };
		static constexpr Color Pinkpearl{ 0xe7accfff };
		static constexpr Color Pistachio{ 0x93c572ff };
		static constexpr Color Platinum{ 0xe5e4e2ff };
		static constexpr Color Plum{ 0xdda0ddff };
		static constexpr Color PortlandOrange{ 0xff5a36ff };
		static constexpr Color Powderblue{ 0xb0e0e6ff };
		static constexpr Color Princetonorange{ 0xff8f00ff };
		static constexpr Color Prussianblue{ 0x003153ff };
		static constexpr Color Psychedelicpurple{ 0xdf00ffff };
		static constexpr Color Puce{ 0xcc8899ff };
		static constexpr Color Pumpkin{ 0xff7518ff };
		static constexpr Color Purple{ 0x800080ff };
		static constexpr Color PurpleHeart{ 0x69359cff };
		static constexpr Color PurpleMountainsMajesty{ 0x9d81baff };
		static constexpr Color Purplemountainmajesty{ 0x9678b6ff };
		static constexpr Color Purplepizzazz{ 0xfe4edaff };
		static constexpr Color Purpletaupe{ 0x50404dff };
		static constexpr Color Rackley{ 0x5d8aa8ff };
		static constexpr Color RadicalRed{ 0xff355eff };
		static constexpr Color Raspberry{ 0xe30b5dff };
		static constexpr Color Raspberryglace{ 0x915f6dff };
		static constexpr Color Raspberrypink{ 0xe25098ff };
		static constexpr Color Raspberryrose{ 0xb3446cff };
		static constexpr Color RawSienna{ 0xd68a59ff };
		static constexpr Color Razzledazzlerose{ 0xff33ccff };
		static constexpr Color Razzmatazz{ 0xe3256bff };
		static constexpr Color Red{ 0xff0000ff };
		static constexpr Color RedOrange{ 0xff5349ff };
		static constexpr Color Redbrown{ 0xa52a2aff };
		static constexpr Color Redviolet{ 0xc71585ff };
		static constexpr Color Richblack{ 0x004040ff };
		static constexpr Color Richcarmine{ 0xd70040ff };
		static constexpr Color Richelectricblue{ 0x0892d0ff };
		static constexpr Color Richlilac{ 0xb666d2ff };
		static constexpr Color Richmaroon{ 0xb03060ff };
		static constexpr Color Riflegreen{ 0x414833ff };
		static constexpr Color RobinsEggBlue{ 0x1fcecbff };
		static constexpr Color Rose{ 0xff007fff };
		static constexpr Color Rosebonbon{ 0xf9429eff };
		static constexpr Color Roseebony{ 0x674846ff };
		static constexpr Color Rosegold{ 0xb76e79ff };
		static constexpr Color Rosemadder{ 0xe32636ff };
		static constexpr Color Rosepink{ 0xff66ccff };
		static constexpr Color Rosequartz{ 0xaa98a9ff };
		static constexpr Color Rosetaupe{ 0x905d5dff };
		static constexpr Color Rosevale{ 0xab4e52ff };
		static constexpr Color Rosewood{ 0x65000bff };
		static constexpr Color Rossocorsa{ 0xd40000ff };
		static constexpr Color Rosybrown{ 0xbc8f8fff };
		static constexpr Color Royalazure{ 0x0038a8ff };
		static constexpr Color Royalblue{ 0x4169e1ff };
		static constexpr Color Royalfuchsia{ 0xca2c92ff };
		static constexpr Color Royalpurple{ 0x7851a9ff };
		static constexpr Color Ruby{ 0xe0115fff };
		static constexpr Color Ruddy{ 0xff0028ff };
		static constexpr Color Ruddybrown{ 0xbb6528ff };
		static constexpr Color Ruddypink{ 0xe18e96ff };
		static constexpr Color Rufous{ 0xa81c07ff };
		static constexpr Color Russet{ 0x80461bff };
		static constexpr Color Rust{ 0xb7410eff };
		static constexpr Color SacramentoStategreen{ 0x00563fff };
		static constexpr Color Saddlebrown{ 0x8b4513ff };
		static constexpr Color Safetyorange{ 0xff6700ff };
		static constexpr Color Saffron{ 0xf4c430ff };
		static constexpr Color SaintPatrickBlue{ 0x23297aff };
		static constexpr Color Salmon{ 0xff8c69ff };
		static constexpr Color Salmonpink{ 0xff91a4ff };
		static constexpr Color Sand{ 0xc2b280ff };
		static constexpr Color Sanddune{ 0x967117ff };
		static constexpr Color Sandstorm{ 0xecd540ff };
		static constexpr Color Sandybrown{ 0xf4a460ff };
		static constexpr Color Sandytaupe{ 0x967117ff };
		static constexpr Color Sapgreen{ 0x507d2aff };
		static constexpr Color Sapphire{ 0x0f52baff };
		static constexpr Color Satinsheengold{ 0xcba135ff };
		static constexpr Color Scarlet{ 0xff2400ff };
		static constexpr Color Schoolbusyellow{ 0xffd800ff };
		static constexpr Color ScreaminGreen{ 0x76ff7aff };
		static constexpr Color Seablue{ 0x006994ff };
		static constexpr Color Seagreen{ 0x2e8b57ff };
		static constexpr Color Sealbrown{ 0x321414ff };
		static constexpr Color Seashell{ 0xfff5eeff };
		static constexpr Color Selectiveyellow{ 0xffba00ff };
		static constexpr Color Sepia{ 0x704214ff };
		static constexpr Color Shadow{ 0x8a795dff };
		static constexpr Color Shamrock{ 0x45cea2ff };
		static constexpr Color Shamrockgreen{ 0x009e60ff };
		static constexpr Color Shockingpink{ 0xfc0fc0ff };
		static constexpr Color Sienna{ 0x882d17ff };
		static constexpr Color Silver{ 0xc0c0c0ff };
		static constexpr Color Sinopia{ 0xcb410bff };
		static constexpr Color Skobeloff{ 0x007474ff };
		static constexpr Color Skyblue{ 0x87ceebff };
		static constexpr Color Skymagenta{ 0xcf71afff };
		static constexpr Color Slateblue{ 0x6a5acdff };
		static constexpr Color Slategray{ 0x708090ff };
		static constexpr Color Smalt{ 0x003399ff };
		static constexpr Color Smokeytopaz{ 0x933d41ff };
		static constexpr Color Smokyblack{ 0x100c08ff };
		static constexpr Color Snow{ 0xfffafaff };
		static constexpr Color SpiroDiscoBall{ 0x0fc0fcff };
		static constexpr Color Springbud{ 0xa7fc00ff };
		static constexpr Color Springgreen{ 0x00ff7fff };
		static constexpr Color Steelblue{ 0x4682b4ff };
		static constexpr Color Stildegrainyellow{ 0xfada5eff };
		static constexpr Color Stizza{ 0x990000ff };
		static constexpr Color Stormcloud{ 0x008080ff };
		static constexpr Color Straw{ 0xe4d96fff };
		static constexpr Color Sunglow{ 0xffcc33ff };
		static constexpr Color Sunset{ 0xfad6a5ff };
		static constexpr Color SunsetOrange{ 0xfd5e53ff };
		static constexpr Color Tan{ 0xd2b48cff };
		static constexpr Color Tangelo{ 0xf94d00ff };
		static constexpr Color Tangerine{ 0xf28500ff };
		static constexpr Color Tangerineyellow{ 0xffcc00ff };
		static constexpr Color Taupe{ 0x483c32ff };
		static constexpr Color Taupegray{ 0x8b8589ff };
		static constexpr Color Tawny{ 0xcd5700ff };
		static constexpr Color Teagreen{ 0xd0f0c0ff };
		static constexpr Color Tearose{ 0xf4c2c2ff };
		static constexpr Color Teal{ 0x008080ff };
		static constexpr Color Tealblue{ 0x367588ff };
		static constexpr Color Tealgreen{ 0x006d5bff };
		static constexpr Color Terracotta{ 0xe2725bff };
		static constexpr Color Thistle{ 0xd8bfd8ff };
		static constexpr Color Thulianpink{ 0xde6fa1ff };
		static constexpr Color TickleMePink{ 0xfc89acff };
		static constexpr Color TiffanyBlue{ 0x0abab5ff };
		static constexpr Color Tigereye{ 0xe08d3cff };
		static constexpr Color Timberwolf{ 0xdbd7d2ff };
		static constexpr Color Titaniumyellow{ 0xeee600ff };
		static constexpr Color Tomato{ 0xff6347ff };
		static constexpr Color Toolbox{ 0x746cc0ff };
		static constexpr Color Topaz{ 0xffc87cff };
		static constexpr Color Tractorred{ 0xfd0e35ff };
		static constexpr Color TrolleyGrey{ 0x808080ff };
		static constexpr Color Tropicalrainforest{ 0x00755eff };
		static constexpr Color TrueBlue{ 0x0073cfff };
		static constexpr Color TuftsBlue{ 0x417dc1ff };
		static constexpr Color Tumbleweed{ 0xdeaa88ff };
		static constexpr Color Turkishrose{ 0xb57281ff };
		static constexpr Color Turquoise{ 0x30d5c8ff };
		static constexpr Color Turquoiseblue{ 0x00ffefff };
		static constexpr Color Turquoisegreen{ 0xa0d6b4ff };
		static constexpr Color Tuscanred{ 0x66424dff };
		static constexpr Color Twilightlavender{ 0x8a496bff };
		static constexpr Color Tyrianpurple{ 0x66023cff };
		static constexpr Color UAblue{ 0x0033aaff };
		static constexpr Color UAred{ 0xd9004cff };
		static constexpr Color UCLABlue{ 0x536895ff };
		static constexpr Color UCLAGold{ 0xffb300ff };
		static constexpr Color UFOGreen{ 0x3cd070ff };
		static constexpr Color UPForestgreen{ 0x014421ff };
		static constexpr Color UPMaroon{ 0x7b1113ff };
		static constexpr Color USCCardinal{ 0x990000ff };
		static constexpr Color USCGold{ 0xffcc00ff };
		static constexpr Color Ube{ 0x8878c3ff };
		static constexpr Color Ultrapink{ 0xff6fffff };
		static constexpr Color Ultramarine{ 0x120a8fff };
		static constexpr Color Ultramarineblue{ 0x4166f5ff };
		static constexpr Color Umber{ 0x635147ff };
		static constexpr Color UnitedNationsblue{ 0x5b92e5ff };
		static constexpr Color UniversityofCaliforniaGold{ 0xb78727ff };
		static constexpr Color UnmellowYellow{ 0xffff66ff };
		static constexpr Color Upsdellred{ 0xae2029ff };
		static constexpr Color Urobilin{ 0xe1ad21ff };
		static constexpr Color UtahCrimson{ 0xd3003fff };
		static constexpr Color Vanilla{ 0xf3e5abff };
		static constexpr Color Vegasgold{ 0xc5b358ff };
		static constexpr Color Venetianred{ 0xc80815ff };
		static constexpr Color Verdigris{ 0x43b3aeff };
		static constexpr Color Vermilion{ 0xe34234ff };
		static constexpr Color Veronica{ 0xa020f0ff };
		static constexpr Color Violet{ 0xee82eeff };
		static constexpr Color VioletBlue{ 0x324ab2ff };
		static constexpr Color VioletRed{ 0xf75394ff };
		static constexpr Color Viridian{ 0x40826dff };
		static constexpr Color Vividauburn{ 0x922724ff };
		static constexpr Color Vividburgundy{ 0x9f1d35ff };
		static constexpr Color Vividcerise{ 0xda1d81ff };
		static constexpr Color Vividtangerine{ 0xffa089ff };
		static constexpr Color Vividviolet{ 0x9f00ffff };
		static constexpr Color Warmblack{ 0x004242ff };
		static constexpr Color Waterspout{ 0x00ffffff };
		static constexpr Color Wenge{ 0x645452ff };
		static constexpr Color Wheat{ 0xf5deb3ff };
		static constexpr Color White{ 0xffffffff };
		static constexpr Color Whitesmoke{ 0xf5f5f5ff };
		static constexpr Color WildStrawberry{ 0xff43a4ff };
		static constexpr Color WildWatermelon{ 0xfc6c85ff };
		static constexpr Color Wildblueyonder{ 0xa2add0ff };
		static constexpr Color Wine{ 0x722f37ff };
		static constexpr Color Wisteria{ 0xc9a0dcff };
		static constexpr Color Xanadu{ 0x738678ff };
		static constexpr Color YaleBlue{ 0x0f4d92ff };
		static constexpr Color Yellow{ 0xffff00ff };
		static constexpr Color YellowOrange{ 0xffae42ff };
		static constexpr Color Yellowgreen{ 0x9acd32ff };
		static constexpr Color Zaffre{ 0x0014a8ff };
		static constexpr Color Zinnwalditebrown{ 0x2c1608ff };
	}
}
