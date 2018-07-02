#pragma once

#include SAMP_EDGENGINE_CONVERTER_PCH

namespace samp_edgengine::io
{

using Int32 = std::int32_t;

struct MapObject
{
	struct TextMaterial
	{
		enum class TextAlign
		{
			Left = 0,
			Center = 1,
			Right = 2
		};

		/// <summary>
		/// Initializes a new instance of the <see cref="TextMaterial"/> class.
		/// </summary>
		TextMaterial()
		{
			
		}

		std::string text;
		int			size;
		std::string fontName;
		int			fontSize;
		bool		bold;
		Int32		fontColor;
		Int32		backColor;
		TextAlign	textAlign;
	};

	/// <summary>
	/// A structure containing texture material settings.
	/// </summary>
	struct TextureMaterial
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="TextureMaterial"/> class.
		/// </summary>
		TextureMaterial()
		{
			
		}

		int			modelIndex;
		std::string txdName;
		std::string textureName;
		Int32		color;
	};

	enum Type
	{
		Global, Personal, Universal
	};

	MapObject(Type type)
	{
	}

	Type				type;
	Int32				modelIndex;
	Int32				world,
						interior;
	math::Vector3f		location,
						rotation;
	float				drawDistance;

	void loadFromXML();
	void saveToXML();
};

}
