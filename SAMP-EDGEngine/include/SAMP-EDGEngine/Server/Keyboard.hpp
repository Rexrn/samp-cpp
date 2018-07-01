#pragma once

#include SAMP_EDGENGINE_PCH

namespace agdk
{

struct Key
{
	/// <summary>
	/// List (enum) of supported keys. Key is not exact keyboard key but an in-game action.
	/// </summary>
	enum Task
	{
		Action,
		Crouch,
		Fire,
		Sprint,
		Attack2nd,
		Jump,
		LookRight,
		Aim,
		LookLeft,
		Submission,
		Walk,
		AnalogUp,
		AnalogDown,
		AnalogLeft,
		AnalogRight,
		Yes,
		No,
		ControlBack,
		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight,
		KEY_COUNT,
		Handbrake = Aim
	};
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Key"/> struct.
	/// </summary>
	Key()
		: pressed(false), holding(false), released(false)
	{
	}
	bool pressed;
	bool holding;
	bool released;
};

/// <summary>
/// Represents user keyboard.
/// </summary>
class Keyboard
{
public:
	// Helper alias:
	using KeysStatus = std::array<Key, Key::KEY_COUNT>;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Keyboard"/> class.
	/// </summary>
	Keyboard();
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Keyboard"/> class.
	/// </summary>
	/// <param name="keys_">The keys.</param>
	/// <param name="upDown_">Up down.</param>
	/// <param name="leftRight_">The left right.</param>
	Keyboard(Int32 keys_, Int32 upDown_ = 0, Int32 leftRight_ = 0);

	/// <summary>
	/// Updates key statuses using SAMPGDK data parameters.
	/// </summary>
	/// <param name="keys_">The keys.</param>
	/// <param name="upDown_">Up/down.</param>
	/// <param name="leftRight_">The left/right.</param>
	/// <returns>Current keys status.</returns>
	KeysStatus update(Int32 keys_, Int32 upDown_, Int32 leftRight_);

	/// <summary>
	/// Returns specified key status.
	/// </summary>
	/// <param name="keyTask_">The key task.</param>
	/// <returns>Specified key status.</returns>
	Key getKeyStatus(Key::Task keyTask_) const {
		return m_keysStatus[static_cast<Int32>(keyTask_)];
	}

	/// <summary>
	/// Returns keys status.
	/// </summary>
	/// <returns>Keys status.</returns>
	KeysStatus getKeys() const {
		return m_keysStatus;
	}

protected:
	//	Key statuses.
	KeysStatus m_keysStatus;
};


}
