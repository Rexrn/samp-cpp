#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/MapObject/GlobalObject.hpp>
#include <AdvancedGDK/Server/Player/Player.hpp>

namespace agdk
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlobalObject::GlobalObject()
	:
	m_handle{ INVALID_OBJECT_ID },
	m_placementTracker{ nullptr }
{
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlobalObject::~GlobalObject()
{
	this->despawn();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalObject::setPlacementTracker(IGlobalObjectPlacementTracker* tracker_)
{
	m_placementTracker = tracker_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IGlobalObjectPlacementTracker* GlobalObject::getPlacementTracker() const
{
	return m_placementTracker;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalObject::sendPlacementUpdate()
{
	if (m_placementTracker)
		m_placementTracker->whenPlacementUpdateReceived( this->getPlacement() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GlobalObject::spawn()
{
	if (m_modelIndex != -1)
	{
		if (m_handle != INVALID_OBJECT_ID)
			sampgdk_DestroyObject(m_handle);

		m_handle = sampgdk_CreateObject(m_modelIndex, m_location.x, m_location.y, m_location.z, m_rotation.x, m_rotation.y, m_rotation.z, m_drawDistance);
	}
	return this->isSpawned();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalObject::despawn()
{
	if (m_handle != INVALID_OBJECT_ID)
		sampgdk_DestroyObject(m_handle);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalObject::setModel(std::int32_t const modelIndex_)
{
	IMapObject::setModel(modelIndex_);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalObject::setLocation(math::Vector3f const & location_)
{
	IActor::setLocation(location_);

	if (m_handle != INVALID_OBJECT_ID) {
		sampgdk_SetObjectPos(m_handle, location_.x, location_.y, location_.z);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalObject::setRotation(math::Vector3f const & rotationAxes_)
{
	IMapObject::setRotation(rotationAxes_);

	if (m_handle != INVALID_OBJECT_ID) {
		sampgdk_SetObjectRot(m_handle, rotationAxes_.x, rotationAxes_.y, rotationAxes_.z);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
math::Vector3f GlobalObject::getLocation() const
{
	if (m_handle != INVALID_OBJECT_ID) {
		math::Vector3f location;
		sampgdk_GetObjectPos(m_handle, &location.x, &location.y, &location.z);
		return location;
	}
	return IActor::getLocation();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
math::Vector3f GlobalObject::getRotation() const
{
	if (m_handle != INVALID_OBJECT_ID) {
		math::Vector3f rotation;
		sampgdk_GetObjectRot(m_handle, &rotation.x, &rotation.y, &rotation.z);
		return rotation;
	}
	return IActor::getLocation();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalObject::applyText(std::size_t const materialIndex_, Text const & textMaterial_, [[maybe_unused]] Player const * player_)
{
	if (m_handle != INVALID_OBJECT_ID)
	{
		sampgdk_SetObjectMaterialText(m_handle,
			textMaterial_.text.c_str(), materialIndex_, textMaterial_.size,
			textMaterial_.font.c_str(), textMaterial_.fontSize, textMaterial_.bold,
			textMaterial_.fontColor.toARGB().toInt32(), textMaterial_.backColor.toARGB().toInt32(),
			static_cast<std::int32_t>(textMaterial_.textAlign));
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalObject::applyTexture(std::size_t const materialIndex_, Texture const & textureMaterial_, [[maybe_unused]] Player const * player_)
{
	if (m_handle != INVALID_OBJECT_ID)
	{
		sampgdk_SetObjectMaterial(m_handle, materialIndex_, textureMaterial_.modelIndex,
			textureMaterial_.txdName.c_str(), textureMaterial_.textureName.c_str(), textureMaterial_.color.toARGB().toInt32());
	}
}

}
