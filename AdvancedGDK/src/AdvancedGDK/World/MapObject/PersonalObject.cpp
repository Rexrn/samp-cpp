#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/MapObject/PersonalObject.hpp>
#include <AdvancedGDK/Server/Player/Player.hpp>

namespace agdk
{

///////////////////////////////////////////////////////////////////////////////////////////////////
PersonalObject::PersonalObject(Player const & player_)
	: m_player{ player_ }, m_handle{ INVALID_OBJECT_ID }
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////
PersonalObject::~PersonalObject()
{
	this->despawn(m_player);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void PersonalObject::setModel(std::int32_t const modelIndex_)
{
	IMapObject::setModel(modelIndex_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void PersonalObject::setLocation(math::Vector3f const & location_)
{
	PerPlayerObject::setLocation(location_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void PersonalObject::setRotation(math::Vector3f const & rotationAxes_)
{
	IMapObject::setRotation(rotationAxes_);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
math::Vector3f PersonalObject::getLocation() const
{
	if (m_handle != INVALID_OBJECT_ID)
	{
		math::Vector3f location;
		sampgdk_GetPlayerObjectPos(m_player.getIndex(), m_handle, &location.x, &location.y, &location.z);
		return location;
	}
	return m_location;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
math::Vector3f PersonalObject::getRotation() const
{
	if (m_handle != INVALID_OBJECT_ID)
	{
		math::Vector3f rotation;
		sampgdk_GetPlayerObjectRot(m_player.getIndex(), m_handle, &rotation.x, &rotation.y, &rotation.z);
		return rotation;
	}
	return m_location;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void PersonalObject::applyText(std::size_t const materialIndex_, Text const & textMaterial_, [[maybe_unused]] Player const * player_)
{
	if (m_handle != INVALID_OBJECT_ID)
	{
		sampgdk_SetPlayerObjectMaterialText(m_player.getIndex(), m_handle,
			textMaterial_.text.c_str(), materialIndex_, textMaterial_.size,
			textMaterial_.font.c_str(), textMaterial_.fontSize, textMaterial_.bold,
			textMaterial_.fontColor.toARGB().toInt32(), textMaterial_.backColor.toARGB().toInt32(),
			static_cast<std::int32_t>(textMaterial_.textAlign));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void PersonalObject::applyTexture(std::size_t const materialIndex_, Texture const & textureMaterial_, [[maybe_unused]] Player const * player_)
{
	if (m_handle != INVALID_OBJECT_ID)
	{
		sampgdk_SetPlayerObjectMaterial(m_player.getIndex(), m_handle, materialIndex_, textureMaterial_.modelIndex,
			textureMaterial_.txdName.c_str(), textureMaterial_.textureName.c_str(), textureMaterial_.color.toARGB().toInt32());
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
math::Meters PersonalObject::getDistanceSquaredTo(Player const & player_) const
{
	return player_.getLocation().distanceSquared(this->getLocation());
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool PersonalObject::spawn([[maybe_unused]] Player const & player_)
{
	if (m_handle == INVALID_OBJECT_ID) {
		m_handle = sampgdk_CreatePlayerObject(m_player.getIndex(), m_modelIndex, m_location.x, m_location.y, m_location.z,
			m_rotation.x, m_rotation.y, m_rotation.z, m_drawDistance);
	}
	return m_handle != INVALID_OBJECT_ID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void PersonalObject::despawn([[maybe_unused]] Player const & player_)
{
	if (m_handle != INVALID_OBJECT_ID) {
		sampgdk_DestroyPlayerObject(m_player.getIndex(), m_handle);
	}
	m_handle = INVALID_OBJECT_ID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
math::Vector3f PersonalObject::getLocationFor([[maybe_unused]] Player const & player_) const
{
	return this->getLocation();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
math::Vector3f PersonalObject::getRotationFor([[maybe_unused]] Player const & player_) const
{
	return this->getRotation();
}

}