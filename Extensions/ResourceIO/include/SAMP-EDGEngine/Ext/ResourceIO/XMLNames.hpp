#pragma once
#include SAMPEDGENGINE_EXT_RESOURCEIO_PCH

namespace samp_edgengine::ext::resource_io
{

struct XMLNames
{
#define cxs_auto constexpr static auto

	cxs_auto MapSceneNode			= "MapScene";
	cxs_auto GlobalObjectNode		= "GlobalObject";
	cxs_auto UniversalObjectNode	= "UniversalObject";
	cxs_auto TextMaterialNode		= "TextMaterial";
	cxs_auto TextureMaterialNode	= "TextureMaterial";
	cxs_auto RemovedBuildingNode	= "RemovedBuilding";
	struct Attributes
	{
		cxs_auto Type				= "Type";
		cxs_auto ModelIndex			= "ModelIndex";
		cxs_auto WorldMode			= "WorldMode";
		cxs_auto InteriorMode		= "InteriorMode";
		cxs_auto World				= "World";
		cxs_auto Interior			= "Interior";
		cxs_auto DrawDistance		= "DrawDistance";
		cxs_auto LocX				= "LocX";
		cxs_auto LocY				= "LocY";
		cxs_auto LocZ				= "LocZ";
		cxs_auto RotX				= "RotX";
		cxs_auto RotY				= "RotY";
		cxs_auto RotZ				= "RotZ";

		cxs_auto MaterialIndex		= "Index";
		cxs_auto MaterialSize		= "Size";
		cxs_auto TextContent		= "Content";
		cxs_auto TextAlign			= "TextAlign";
		cxs_auto FontFace			= "FontFace";
		cxs_auto FontSize			= "FontSize";
		cxs_auto FontColor			= "FontColor";
		cxs_auto BackColor			= "BackColor";
		cxs_auto Bold				= "Bold";

		cxs_auto TxdName			= "TxdName";
		cxs_auto TextureName		= "TextureName";
		cxs_auto Tint				= "Tint";

		cxs_auto OriginX			= "OriginX";
		cxs_auto OriginY			= "OriginY";
		cxs_auto OriginZ			= "OriginZ";
		cxs_auto Radius				= "Radius";

		cxs_auto ForceWorld			= "ForceWorld";
		cxs_auto ForceWorldMode		= "ForceWorldMode";
		cxs_auto ForceInterior		= "ForceInterior";
		cxs_auto ForceInteriorMode	= "ForceInteriorMode";
	};

#undef cxs_auto
};

}
