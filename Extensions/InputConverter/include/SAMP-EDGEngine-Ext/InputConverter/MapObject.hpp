#pragma once

#include SAMP_EDGENGINE_EXT_INPUTCONVERTER_PCH

#include <SAMP-EDGEngine-Ext/InputConverter/XMLSerializable.hpp>

namespace samp_edgengine::ext::input_converter
{

using Int32 = std::int32_t;

struct MapObject
	: IXMLSerializable
{
	constexpr static std::size_t MaxMaterialsCount = 16;

	struct XMLNames
	{
#define cxs_auto constexpr static auto

		cxs_auto Node				= "MapObject";
		struct Parameters
		{
			cxs_auto Type			= "Type";
			cxs_auto WorldMode		= "WorldMode";
			cxs_auto InteriorMode	= "InteriorMode";
			cxs_auto World			= "World";
			cxs_auto Interior		= "Interior";
			cxs_auto DrawDistance	= "DrawDistance";
			cxs_auto LocX			= "LocX";
			cxs_auto LocY			= "LocY";
			cxs_auto LocZ			= "LocZ";
			cxs_auto RotX			= "RotX";
			cxs_auto RotY			= "RotY";
			cxs_auto RotZ			= "RotZ";
		};

#undef cxs_auto
	};

	struct TextMaterial
		: IXMLSerializable
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
		TextMaterial();

		/// <summary>
		/// Serializes the object to XML by creating a child node to the `parentNode_`.
		/// </summary>
		/// <param name="parentNode_">The node to create child at.</param>
		/// <returns>
		///		Pointer to created node or nullptr if failed.
		/// </returns>
		virtual xml::xml_node<>* serialize(xml::xml_node<>& parentNode_) const override;

		/// <summary>
		/// Deserializes the object from XML from specified node.
		/// </summary>
		/// <param name="node_">The node to deserialize from.</param>
		/// <returns>
		///		<c>true</c> if succeeded; otherwise, <c>false</c>.
		/// </returns>
		virtual bool deserialize(xml::xml_node<>& node_) override;

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
		: IXMLSerializable
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="TextureMaterial"/> class.
		/// </summary>
		TextureMaterial();

		/// <summary>
		/// Serializes the object to XML by creating a child node to the `parentNode_`.
		/// </summary>
		/// <param name="parentNode_">The node to create child at.</param>
		/// <returns>
		///		Pointer to created node or nullptr if failed.
		/// </returns>
		virtual xml::xml_node<>* serialize(xml::xml_node<>& parentNode_) const override;

		/// <summary>
		/// Deserializes the object from XML from specified node.
		/// </summary>
		/// <param name="node_">The node to deserialize from.</param>
		/// <returns>
		///		<c>true</c> if succeeded; otherwise, <c>false</c>.
		/// </returns>
		virtual bool deserialize(xml::xml_node<>& node_) override;

		int			modelIndex;
		std::string txdName;
		std::string textureName;
		Int32		color;
	};

	enum Type
	{
		Global, Personal, Universal
	};
	
	/// <summary>
	/// Initializes a new instance of the <see cref="MapObject"/> struct.
	/// </summary>
	/// <param name="type">The type.</param>
	explicit MapObject(Type type_);
	
	/// <summary>
	/// Returns the type string.
	/// </summary>
	/// <returns>
	///		The type string.
	/// </returns>
	std::string_view getTypeString() const;

	/// <summary>
	/// Returns the world mode string.
	/// </summary>
	/// <returns>
	///		The world mode string.
	/// </returns>
	std::string_view getWorldModeString() const;

	/// <summary>
	/// Returns the interior mode string.
	/// </summary>
	/// <returns>
	///		The interior mode string.
	/// </returns>
	std::string_view getInteriorModeString() const;
	
	/// <summary>
	/// Serializes the object to XML by creating a child node to the `parentNode_`.
	/// </summary>
	/// <param name="parentNode_">The node to create child at.</param>
	/// <returns>
	///		Pointer to created node or nullptr if failed.
	/// </returns>
	virtual xml::xml_node<>* serialize(xml::xml_node<>& parentNode_) const override;
	
	/// <summary>
	/// Deserializes the object from XML from specified node.
	/// </summary>
	/// <param name="node_">The node to deserialize from.</param>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	virtual bool deserialize(xml::xml_node<>& node_) override;

	Type				type;
	Int32				modelIndex;
	Int32				world,
						interior;
	math::Vector3f		location,
						rotation;
	float				drawDistance;

	using MaterialsContainer = std::array< std::unique_ptr< IXMLSerializable >, MaxMaterialsCount>;
	MaterialsContainer	materials;
};

}
