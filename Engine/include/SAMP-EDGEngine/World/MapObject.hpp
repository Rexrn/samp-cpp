#pragma once
#include SAMPEDGENGINE_PCH



// Base class headers:
#include <SAMP-EDGEngine/World/3DNode.hpp>
#include <SAMP-EDGEngine/Core/BasicInterfaces/NonCopyable.hpp>

// Other headers:
#include <SAMP-EDGEngine/Core/Pointers.hpp>
#include <SAMP-EDGEngine/Core/Color.hpp>

#include <SAMP-EDGEngine/Dependencies/SampGDK.hpp>


namespace samp_cpp
{
class Player;

/// <summary>
/// A base class for every map object.
/// </summary>
class IMapObject
	:
	public virtual I3DNode,
	public INonCopyable
{	
public:
	class IMaterial;
protected:
	

	/// <summary>
	/// Applies the material.
	/// </summary>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="textureMaterial_">The texture material.</param>
	void applyMaterial(std::size_t const materialIndex_, IMaterial const & textureMaterial_, Player const * player_ = nullptr);

public:
	constexpr static Uint8 MaxMaterialCount = 16;

	/// <summary>
	/// A base class for Texture and Text materials.
	/// </summary>
	class IMaterial
	{
	public:
		/// <summary>
		/// Finalizes an instance of the <see cref="IMaterial"/> class.
		/// </summary>
		virtual ~IMaterial() = default;

		friend void IMapObject::applyMaterial(std::size_t const materialIndex_, IMaterial const & textureMaterial_, Player const * player_);
	protected:

		/// <summary>
		/// Applies material to the specified object.
		/// </summary>
		/// <param name="object_">The object.</param>
		/// <param name="materialIndex_">Index of the material.</param>
		/// <param name="player_">The player.</param>
		virtual void apply(IMapObject &object_, std::size_t const materialIndex_, Player const * player_ = nullptr) const = 0;
	};

	// Types and aliases:
	using HandleType			= Int32;
	using MaterialsContainer	= std::vector< UniquePtr<IMaterial> >;

	constexpr static Int32 InvalidHandle = INVALID_OBJECT_ID;

	enum class EditResponse
	{
		Cancel	= EDIT_RESPONSE_CANCEL,
		Final	= EDIT_RESPONSE_FINAL,
		Update	= EDIT_RESPONSE_UPDATE
	};

	enum Type
	{
		Global,
		Universal,
		Personal
	};

	// Some settings:
	constexpr static float cxDefaultDrawDistance = 700.f;

	/// <summary>
	/// A class containing texture material settings.
	/// </summary>
	class Texture final
		: public IMaterial
	{
	protected:
		/// <summary>
		/// Applies material to the specified object.
		/// </summary>
		/// <param name="object_">The object.</param>
		/// <param name="materialIndex_">Index of the material.</param>
		/// <param name="player_">The player.</param>
		virtual void apply(IMapObject &object_, std::size_t const materialIndex_, Player const * player_) const override;

	public:		
		/// <summary>
		/// Initializes a new instance of the <see cref="Texture"/> class.
		/// </summary>
		Texture();

		int			modelIndex;
		std::string txdName;
		std::string textureName;
		Color		color;
	};

	/// <summary>
	/// A class containing text material settings.
	/// </summary>
	class Text final
		: public IMaterial
	{	
		/// <summary>
		/// Applies material to the specified object.
		/// </summary>
		/// <param name="object_">The object.</param>
		/// <param name="materialIndex_">Index of the material.</param>
		/// <param name="player_">The player.</param>
		virtual void apply(IMapObject &object_, std::size_t const materialIndex_, Player const * player_) const override;
	public:
		enum class TextAlign {
			Left = 0,
			Center = 1,
			Right = 2
		};
		
		/// <summary>
		/// Initializes a new instance of the <see cref="Text"/> class.
		/// </summary>
		Text();

		std::string text;
		int			size;
		std::string font;
		int			fontSize;
		bool		bold;
		Color		fontColor;
		Color		backColor;
		TextAlign	textAlign;
	};
	
	/// <summary>
	/// Initializes a new instance of the <see cref="IMapObject"/> class.
	/// </summary>
	IMapObject();
	
	/// <summary>
	/// Finalizes an instance of the <see cref="IMapObject"/> class.
	/// </summary>
	virtual ~IMapObject() = default;
	
	/// <summary>
	/// Sets the object model.
	/// </summary>
	/// <param name="modelIndex_">Index of the model.</param>
	virtual void setModel(Int32 const modelIndex_);
	
	/// <summary>
	/// Sets the object material (text).
	/// </summary>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="textMaterial_">The text material.</param>
	void setMaterial(std::size_t const materialIndex_, Text const & textMaterial_);
	
	/// <summary>
	/// Sets the object material (texture).
	/// </summary>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="textureMaterial_">The texture material.</param>
	void setMaterial(std::size_t const materialIndex_, Texture const & textureMaterial_);
	
	/// <summary>
	/// Sets the object rotation.
	/// </summary>
	/// <param name="rotationAxes_">The rotation axes.</param>
	virtual void setRotation(math::Vector3f const & rotationAxes_);
		
	/// <summary>
	/// Sets the object draw distance. Object must be respawned in order to apply this setting.
	/// </summary>
	/// <param name="drawDistance_">The draw distance.</param>
	/// <remarks>
	/// <para>
	///		Set the value to 0.f to use default in-game draw distance.
	///		Keep in mind, that draw distance is not streaming distance.
	///		Object can be streamed in from greater distance and still not be visible, because of draw distance.
	/// </para>
	/// </remarks>	
	void setDrawDistance(float const drawDistance_);

	/// <summary>
	/// Returns the object model.
	/// </summary>
	/// <returns>The object model.</returns>
	virtual Int32 getModel() const;

	/// <summary>
	/// Returns the object rotation.
	/// </summary>
	/// <returns>The object rotation.</returns>
	virtual math::Vector3f getRotation() const;

	/// <summary>
	/// Returns the object draw distance.
	/// </summary>
	/// <returns></returns>
	float getDrawDistance() const;

	/// <summary>
	/// Returns cref to materials.
	/// </summary>
	/// <returns>cref to the materials.</returns>
	MaterialsContainer const& getMaterials() const;

	/// <summary>
	/// Determines whether object is in motion.
	/// </summary>
	/// <returns>
	///   <c>true</c> if object is in motion; otherwise, <c>false</c>.
	/// </returns>
	bool isInMotion() const;
	
	/// <summary>
	/// Returns object type.
	/// </summary>
	/// <returns>
	///		Type of the object.
	/// </returns>
	virtual Type getType() const = 0;
protected:
	
	/// <summary>
	/// Applies the text material.
	/// </summary>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="textMaterial_">The text material.</param>
	/// <param name="player_">The player.</param>
	virtual void applyText(std::size_t const materialIndex_, Text const & textMaterial_, Player const * player_ = nullptr) = 0;
	
	/// <summary>
	/// Applies the texture material.
	/// </summary>
	/// <param name="materialIndex_">Index of the material.</param>
	/// <param name="textureMaterial_">The texture material.</param>
	/// <param name="player_">The player.</param>
	virtual void applyTexture(std::size_t const materialIndex_, Texture const & textureMaterial_, Player const * player_ = nullptr) = 0;

	Int32				m_modelIndex;
	math::Vector3f		m_rotation;
	float				m_drawDistance;
	bool				m_inMotion;
	MaterialsContainer	m_materials;
};

}
