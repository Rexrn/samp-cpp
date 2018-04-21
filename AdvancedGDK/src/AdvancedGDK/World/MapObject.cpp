#include "AdvancedGDKPCH.hpp"

#include <AdvancedGDK/World/MapObject.hpp>
#include <AdvancedGDK/Server/Player/Player.hpp>

namespace agdk
{

//////////////////////////////////////////////////////////////////////////
IMapObject::Texture::Texture()
	: modelIndex{ 0 }
{
}

//////////////////////////////////////////////////////////////////////////
void IMapObject::Texture::apply(IMapObject & object_, std::size_t const materialIndex_, Player const * player_) const
{
	object_.applyTexture(materialIndex_, *this, player_);
}

//////////////////////////////////////////////////////////////////////////
IMapObject::Text::Text()
	:
	size{ 90 }, font{ "Arial" }, fontSize{ 24 },
	bold{ true }, fontColor{ 0xFFFFFFFF }, backColor{ 0 },
	textAlign{ TextAlign::Left }
{
}

//////////////////////////////////////////////////////////////////////////
void IMapObject::Text::apply(IMapObject & object_, std::size_t const materialIndex_, Player const * player_) const
{
	object_.applyText(materialIndex_, *this, player_);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
IMapObject::IMapObject()
	:
	m_modelIndex{ -1 },
	m_drawDistance{ cxDefaultDrawDistance },
	m_inMotion{ false }
{

}

//////////////////////////////////////////////////////////////////////////
void IMapObject::setModel(std::int32_t const modelIndex_)
{
	m_modelIndex = modelIndex_;
	// TODO: respawn?
}

//////////////////////////////////////////////////////////////////////////
void IMapObject::setMaterial(std::size_t const materialIndex_, Text const & textMaterial_)
{
	if (materialIndex_ <= 15)
	{
		if (m_materials.size() <= materialIndex_)
			m_materials.resize(materialIndex_ + 1);

		m_materials[materialIndex_] = std::make_unique<IMapObject::Text>(textMaterial_);

		this->applyText(materialIndex_, textMaterial_);
	}
#ifdef ADVANCEDGDK_DEBUG
	else {
		assert(false);
	}
	// Assertion note:
	// You've tried to set material with index > 15, but SAMP does not allow it. Fix your code.
#endif
}

//////////////////////////////////////////////////////////////////////////
void IMapObject::setMaterial(std::size_t const materialIndex_, Texture const & textureMaterial_)
{
	if (materialIndex_ <= 15)
	{
		if (m_materials.size() <= materialIndex_)
			m_materials.resize(materialIndex_ + 1);

		m_materials[materialIndex_] = std::make_unique<IMapObject::Texture>(textureMaterial_);

		this->applyTexture(materialIndex_, textureMaterial_);
	}
#ifdef ADVANCEDGDK_DEBUG
	else {
		// Assertion note:
		// You've tried to set material with index > 15, but SAMP does not allow it. Fix your code.
		assert(false);
	}
#endif
}

//////////////////////////////////////////////////////////////////////////
void IMapObject::setRotation(math::Vector3f const & rotationAxes_)
{
	m_rotation = rotationAxes_;
}

//////////////////////////////////////////////////////////////////////////
void IMapObject::applyMaterial(std::size_t const materialIndex_, IMaterial const & material_, Player const * player_)
{
	material_.apply(*this, materialIndex_, player_);
}

}