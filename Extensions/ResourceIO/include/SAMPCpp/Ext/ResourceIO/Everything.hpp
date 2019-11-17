#pragma once

#ifndef SAMPCPP_EXT_RESOURCEIO_PCH
#define SAMPCPP_EXT_RESOURCEIO_PCH <SAMPCpp/Ext/ResourceIO/ResourceIOPCH.hpp>
#endif
#include SAMPCPP_EXT_RESOURCEIO_PCH

#include "XMLHelperFunctions.hpp"
#include "XMLNames.hpp"

// Serializers:
#include "MapObjectMaterialSerializer.hpp"
#include "MapObjectSerializer.hpp"
#include "RemovedBuildingSerializer.hpp"
#include "SceneSerializer.hpp"
#include "Serializer.hpp"
#include "XMLGlobalObjectSerializer.hpp"
#include "XMLMapObjectMaterialSerializer.hpp"
#include "XMLMapObjectSerializer.hpp"
#include "XMLPerPlayerObjectSerializer.hpp"
#include "XMLRemovedBuildingSerializer.hpp"
#include "XMLSceneSerializer.hpp"
#include "XMLSerializer.hpp"
#include "XMLTextMaterialSerializer.hpp"
#include "XMLTextureMaterialSerializer.hpp"

// Deserializers:
#include "Deserializer.hpp"
#include "MapObjectDeserializer.hpp"
#include "MapObjectMaterialDeserializer.hpp"
#include "PAWNDeserializer.hpp"
#include "PAWNSceneDeserializer.hpp"
#include "RemovedBuildingDeserializer.hpp"
#include "SceneDeserializer.hpp"
#include "XMLDeserializer.hpp"
#include "XMLGlobalObjectDeserializer.hpp"
#include "XMLMapObjectDeserializer.hpp"
#include "XMLMapObjectMaterialDeserializer.hpp"
#include "XMLPerPlayerObjectDeserializer.hpp"
#include "XMLRemovedBuildingDeserializer.hpp"
#include "XMLSceneDeserializer.hpp"
#include "XMLTextMaterialDeserializer.hpp"
#include "XMLTextureMaterialDeserializer.hpp"