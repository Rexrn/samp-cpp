#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/MapObject/UniversalObject.hpp>
#include <AdvancedGDK/Server/Player/Player.hpp>

namespace agdk
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////
UniversalObject::~UniversalObject()
{
	for (auto const & sP : m_playerHandles) {
		sampgdk_DestroyPlayerObject(sP.first->getIndex(), sP.second);
	}
}

//////////////////////////////////////////////////////////////////////////
void UniversalObject::setModel(std::int32_t const modelIndex_)
{
	IMapObject::setModel(modelIndex_);
}

//////////////////////////////////////////////////////////////////////////
void UniversalObject::setLocation(math::Vector3f const & location_)
{
	PerPlayerObject::setLocation(location_);

	for (auto const & sP : m_playerHandles) {
		sampgdk_SetPlayerObjectPos(static_cast<int>( sP.first->getIndex() ), sP.second, m_location.x, m_location.y, m_location.z);
	}
}

//////////////////////////////////////////////////////////////////////////
void UniversalObject::setRotation(math::Vector3f const & rotationAxes_)
{
	IMapObject::setRotation(rotationAxes_);

	for (auto const & sP : m_playerHandles) {
		sampgdk_SetPlayerObjectRot(static_cast<int>( sP.first->getIndex() ), sP.second, m_rotation.x, m_rotation.y, m_rotation.z);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UniversalObject::applyText(std::size_t const materialIndex_, Text const & textMaterial_, const Player * player_)
{
	if (player_ != nullptr)
	{
		auto const it = std::find_if(m_playerHandles.begin(), m_playerHandles.end(), [player_](auto const & pair_) { return pair_.first == player_; });

		if (it != m_playerHandles.end())
		{
			sampgdk_SetPlayerObjectMaterialText(static_cast<int>( it->first->getIndex() ), it->second,
				textMaterial_.text.c_str(), materialIndex_, textMaterial_.size,
				textMaterial_.font.c_str(), textMaterial_.fontSize, textMaterial_.bold,
				textMaterial_.fontColor.toARGB().toInt32(), textMaterial_.backColor.toARGB().toInt32(),
				static_cast<std::int32_t>(textMaterial_.textAlign));
		}
	}
	else
	{
		for (auto const & sP : m_playerHandles)
		{
			sampgdk_SetPlayerObjectMaterialText(static_cast<int>( sP.first->getIndex() ), sP.second,
				textMaterial_.text.c_str(), materialIndex_, textMaterial_.size,
				textMaterial_.font.c_str(), textMaterial_.fontSize, textMaterial_.bold,
				textMaterial_.fontColor.toARGB().toInt32(), textMaterial_.backColor.toARGB().toInt32(),
				static_cast<std::int32_t>(textMaterial_.textAlign));
		}
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UniversalObject::applyTexture(std::size_t const materialIndex_, Texture const & textureMaterial_, const Player * player_)
{
	if (player_ != nullptr)
	{
		auto const it = std::find_if(m_playerHandles.begin(), m_playerHandles.end(), [player_](auto const & pair_) { return pair_.first == player_; });

		if (it != m_playerHandles.end())
		{
			sampgdk_SetPlayerObjectMaterial(static_cast<int>( it->first->getIndex() ), it->second, materialIndex_, textureMaterial_.modelIndex,
				textureMaterial_.txdName.c_str(), textureMaterial_.textureName.c_str(), textureMaterial_.color.toARGB().toInt32());
		}

	}
	else
	{
		for (auto const & sP : m_playerHandles)
		{
			sampgdk_SetPlayerObjectMaterial(static_cast<int>( sP.first->getIndex() ), sP.second, materialIndex_, textureMaterial_.modelIndex,
				textureMaterial_.txdName.c_str(), textureMaterial_.textureName.c_str(), textureMaterial_.color.toARGB().toInt32());
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
math::Meters UniversalObject::getDistanceSquaredTo(Player const & player_) const
{
	return player_.getLocation().distanceSquared(this->getLocationFor(player_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
math::Vector3f UniversalObject::getLocationFor(Player const & player_) const
{
	for (auto const & sP : m_playerHandles)
	{
		if (sP.first == &player_)
		{
			math::Vector3f location;
			sampgdk_GetPlayerObjectPos(static_cast<int>( sP.first->getIndex() ), sP.second, &location.x, &location.y, &location.z);
			return location;
		}
	}
	return m_location;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
math::Vector3f UniversalObject::getRotationFor(Player const & player_) const
{
	for (auto const & sP : m_playerHandles)
	{
		if (sP.first == &player_)
		{
			math::Vector3f rotation;
			sampgdk_GetPlayerObjectRot(static_cast<int>( sP.first->getIndex() ), sP.second, &rotation.x, &rotation.y, &rotation.z);
			return rotation;
		}
	}
	return m_rotation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UniversalObject::spawn(Player const & player_)
{
	auto const it = std::find_if(m_playerHandles.begin(), m_playerHandles.end(), [&player_](auto const & pair_) { return pair_.first == &player_; });
	if (it == m_playerHandles.end())
	{
		std::int32_t handle = sampgdk_CreatePlayerObject(static_cast<int>( player_.getIndex() ), m_modelIndex, m_location.x, m_location.y, m_location.z,
			m_rotation.x, m_rotation.y, m_rotation.z, m_drawDistance);
		if (handle != INVALID_OBJECT_ID) {

			m_playerHandles.emplace_back(&player_, handle);

			// PERFORMANCE TODO: could be optimalized:
			// "applyMaterial" needs to find specified handle in vector.
			// We have already this handle in this piece of code: `handle`.
			// We could pass it and get better performance.
			for (std::size_t i = 0; i < m_materials.size(); i++)
			{
				auto const &material = m_materials[i];
				if (material)
					this->applyMaterial(i, *material, &player_);
			}
		}
		else
			return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UniversalObject::despawn(Player const & player_)
{
	auto it = std::find_if(m_playerHandles.begin(), m_playerHandles.end(), [&player_](auto const & pair_) { return pair_.first == &player_; });
	if (it != m_playerHandles.end())
	{
		sampgdk_DestroyPlayerObject(static_cast<int>( player_.getIndex() ), it->second);
		m_playerHandles.erase(it);
	}
}

} // namespace agdk


