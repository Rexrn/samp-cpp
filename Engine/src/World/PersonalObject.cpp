#include SAMPCPP_PCH

// The header of this class:
#include <SAMPCpp/World/PersonalObject.hpp>

// Other headers:
#include <SAMPCpp/Server/Player.hpp>

namespace samp_cpp
{

///////////////////////////////////////////////////////////////////////////////////////////////////
PersonalObject::PersonalObject(Player const & player_)
	: m_player{ player_ }, m_handle{ InvalidHandle }
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////
PersonalObject::~PersonalObject()
{
	this->despawn(m_player);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void PersonalObject::setModel(Int32 const modelIndex_)
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
	if (m_handle != InvalidHandle)
	{
		math::Vector3f location;
		sampgdk_GetPlayerObjectPos(m_player.getIndex(), m_handle, &location.x, &location.y, &location.z);
		return location;
	}
	return m_storedLocation;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
math::Vector3f PersonalObject::getRotation() const
{
	if (m_handle != InvalidHandle)
	{
		math::Vector3f rotation;
		sampgdk_GetPlayerObjectRot(m_player.getIndex(), m_handle, &rotation.x, &rotation.y, &rotation.z);
		return rotation;
	}
	return m_rotation;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
Int32 PersonalObject::getHandle() const
{
	return m_handle;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
Player const& PersonalObject::getPlayer() const
{
	return m_player;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
bool PersonalObject::isSpawned() const
{
	return this->getHandle() != InvalidHandle;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void PersonalObject::applyText(std::size_t const materialIndex_, Text const & textMaterial_, [[maybe_unused]] Player const * player_)
{
	if (m_handle != InvalidHandle)
	{
		sampgdk_SetPlayerObjectMaterialText(m_player.getIndex(), m_handle,
			textMaterial_.text.c_str(), materialIndex_, textMaterial_.size,
			textMaterial_.font.c_str(), textMaterial_.fontSize, textMaterial_.bold,
			textMaterial_.fontColor.toARGB().toInt32(), textMaterial_.backColor.toARGB().toInt32(),
			static_cast<Int32>(textMaterial_.textAlign));
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void PersonalObject::applyTexture(std::size_t const materialIndex_, Texture const & textureMaterial_, [[maybe_unused]] Player const * player_)
{
	if (m_handle != InvalidHandle)
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
	if (m_handle == InvalidHandle)
	{
		m_handle = sampgdk_CreatePlayerObject(m_player.getIndex(), m_modelIndex, m_storedLocation.x, m_storedLocation.y, m_storedLocation.z,
			m_rotation.x, m_rotation.y, m_rotation.z, m_drawDistance);
	}
	return m_handle != InvalidHandle;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void PersonalObject::despawn([[maybe_unused]] Player const & player_)
{
	if (m_handle != InvalidHandle) {
		sampgdk_DestroyPlayerObject(m_player.getIndex(), m_handle);
	}
	m_handle = InvalidHandle;
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