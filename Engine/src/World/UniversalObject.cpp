// The header of this class:
#include <SAMP-EDGEngine/World/UniversalObject.hpp>

// Other includes:
#include <SAMP-EDGEngine/Server/Player.hpp>

namespace samp_edgengine
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////
UniversalObject::~UniversalObject()
{
	for (auto const & sP : m_playerHandles)
	{
		sampgdk_DestroyPlayerObject(sP.first->getIndex(), sP.second);
	}
}

//////////////////////////////////////////////////////////////////////////
void UniversalObject::setModel(Int32 const modelIndex_)
{
	IMapObject::setModel(modelIndex_);
}

//////////////////////////////////////////////////////////////////////////
void UniversalObject::setLocation(math::Vector3f const & location_)
{
	PerPlayerObject::setLocation(location_);

	for (auto const & playerHandle : m_playerHandles)
	{
		sampgdk_SetPlayerObjectPos(static_cast<Int32>( playerHandle.first->getIndex() ), playerHandle.second, location_.x, location_.y, location_.z);
	}
}

//////////////////////////////////////////////////////////////////////////
void UniversalObject::setRotation(math::Vector3f const & rotationAxes_)
{
	IMapObject::setRotation(rotationAxes_);

	for (auto const & playerHandle : m_playerHandles)
	{
		sampgdk_SetPlayerObjectRot(static_cast<Int32>( playerHandle.first->getIndex() ), playerHandle.second, m_rotation.x, m_rotation.y, m_rotation.z);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UniversalObject::applyText(std::size_t const materialIndex_, Text const & textMaterial_, const Player * player_)
{
	if (player_)
	{
		auto const it = std::find_if(m_playerHandles.begin(), m_playerHandles.end(),
			[player_](std::pair<Player const*, Int32> const & pair_)
			{
				return pair_.first == player_;
			});

		if (it != m_playerHandles.end())
		{
			sampgdk_SetPlayerObjectMaterialText( static_cast<Int32>( it->first->getIndex() ), it->second,
				textMaterial_.text.c_str(), materialIndex_, textMaterial_.size,
				textMaterial_.font.c_str(), textMaterial_.fontSize, textMaterial_.bold,
				textMaterial_.fontColor.toARGB().toInt32(), textMaterial_.backColor.toARGB().toInt32(),
				static_cast<Int32>(textMaterial_.textAlign)
			);
		}
	}
	else
	{
		for (auto const & sP : m_playerHandles)
		{
			sampgdk_SetPlayerObjectMaterialText( static_cast<Int32>( sP.first->getIndex() ), sP.second,
				textMaterial_.text.c_str(), materialIndex_, textMaterial_.size,
				textMaterial_.font.c_str(), textMaterial_.fontSize, textMaterial_.bold,
				textMaterial_.fontColor.toARGB().toInt32(), textMaterial_.backColor.toARGB().toInt32(),
				static_cast<Int32>(textMaterial_.textAlign)
			);
		}
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UniversalObject::applyTexture(std::size_t const materialIndex_, Texture const & textureMaterial_, const Player * player_)
{
	if (player_ != nullptr)
	{
		auto const it = std::find_if(m_playerHandles.begin(), m_playerHandles.end(),
			[player_](std::pair<Player const*, Int32> const & pair_)
			{
				return pair_.first == player_;
			});

		if (it != m_playerHandles.end())
		{
			sampgdk_SetPlayerObjectMaterial(static_cast<Int32>( it->first->getIndex() ), it->second, materialIndex_, textureMaterial_.modelIndex,
				textureMaterial_.txdName.c_str(), textureMaterial_.textureName.c_str(), textureMaterial_.color.toARGB().toInt32());
		}

	}
	else
	{
		for (auto const & sP : m_playerHandles)
		{
			sampgdk_SetPlayerObjectMaterial(static_cast<Int32>( sP.first->getIndex() ), sP.second, materialIndex_, textureMaterial_.modelIndex,
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
	for (auto const & playerHandle : m_playerHandles)
	{
		if (playerHandle.first == &player_)
		{
			math::Vector3f location;
			sampgdk_GetPlayerObjectPos(static_cast<Int32>( playerHandle.first->getIndex() ), playerHandle.second, &location.x, &location.y, &location.z);
			return location;
		}
	}
	return m_storedLocation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
math::Vector3f UniversalObject::getRotationFor(Player const & player_) const
{
	for (auto const & playerHandle : m_playerHandles)
	{
		if (playerHandle.first == &player_)
		{
			math::Vector3f rotation;
			sampgdk_GetPlayerObjectRot(static_cast<Int32>( playerHandle.first->getIndex() ), playerHandle.second, &rotation.x, &rotation.y, &rotation.z);
			return rotation;
		}
	}
	return m_rotation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UniversalObject::spawn(Player const & player_)
{
	auto const it = std::find_if(m_playerHandles.begin(), m_playerHandles.end(),
		[&player_](std::pair<Player const*, Int32> const & pair_)
		{
			return pair_.first == &player_;
		});

	if (it == m_playerHandles.end())
	{
		Int32 handle = sampgdk_CreatePlayerObject(static_cast<Int32>( player_.getIndex() ), m_modelIndex, m_storedLocation.x, m_storedLocation.y, m_storedLocation.z,
			m_rotation.x, m_rotation.y, m_rotation.z, m_drawDistance);
		if (handle != InvalidHandle) {

			m_playerHandles.emplace_back(&player_, handle);

			// PERFORMANCE TODO: could get optimized:
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
	auto it = std::find_if(m_playerHandles.begin(), m_playerHandles.end(),
		[&player_](auto const & pair_) { return pair_.first == &player_; });
	if (it != m_playerHandles.end())
	{
		sampgdk_DestroyPlayerObject(static_cast<Int32>( player_.getIndex() ), it->second);
		m_playerHandles.erase(it);
	}
}

} // namespace agdk


