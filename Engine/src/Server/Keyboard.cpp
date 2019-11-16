#include SAMPEDGENGINE_PCH

#include <SAMP-EDGEngine/Server/Server.hpp>

namespace samp_cpp
{

///////////////////////////////////////////////////////////////////////////
Keyboard::Keyboard()
{
	this->update(0, 0, 0);
}

///////////////////////////////////////////////////////////////////////////
Keyboard::Keyboard(Int32 keys_, Int32 upDown_, Int32 leftRight_)
{
	this->update(keys_, upDown_, leftRight_);
}

///////////////////////////////////////////////////////////////////////////
Keyboard::KeysStatus Keyboard::update(Int32 keys_, Int32 upDown_, Int32 leftRight_)
{
	auto const updateKey = [&keys_](Key &key_, Int32 keyMacro_)
	{
		if (keys_ & keyMacro_)
		{
			if (key_.pressed)
			{
				key_.pressed = false;
				key_.holding = true;
				key_.released = false;
			}
			else
			{
				key_.pressed = true;
				key_.holding = false;
				key_.released = false;
			}
		}
		else
		{
			if (key_.pressed || key_.holding)
			{
				key_.pressed = false;
				key_.holding = false;
				key_.released = true;
			}
			else if (key_.released)
			{
				key_.pressed = false;
				key_.holding = false;
				key_.released = false;
			}
		}
	};

	/* Movement keys require other treatment */
	auto const updateMoveKey = [](Key &key_, Int32 keyMacro_, Int32 value_)
	{
		if (value_ == keyMacro_) // pressed
		{
			if (key_.pressed) // was pressed before so now we must switch it to holding
			{
				key_.pressed = false;
				key_.holding = true;
				key_.released = false;
			}
			else // wasn't pressed before so now it must be
			{
				key_.pressed = true;
				key_.holding = false;
				key_.released = false;
			}
		}
		else // not pressed
		{
			if (key_.pressed || key_.holding) // was pressed before so now it must switch to released
			{
				key_.pressed = false;
				key_.holding = false;
				key_.released = true;
			}
			else if (key_.released) // was released so now it must be all false
			{
				key_.pressed = false;
				key_.holding = false;
				key_.released = false;
			}
		}
	};

	updateKey(m_keysStatus[Key::Action],		KEY_ACTION);
	updateKey(m_keysStatus[Key::Crouch],		KEY_CROUCH);
	updateKey(m_keysStatus[Key::Fire],			KEY_FIRE);
	updateKey(m_keysStatus[Key::Sprint],		KEY_SPRINT);
	updateKey(m_keysStatus[Key::Attack2nd],		KEY_SECONDARY_ATTACK);
	updateKey(m_keysStatus[Key::Jump],			KEY_JUMP);
	updateKey(m_keysStatus[Key::LookRight],		KEY_LOOK_RIGHT);
	updateKey(m_keysStatus[Key::Aim],			KEY_HANDBRAKE);
	updateKey(m_keysStatus[Key::LookLeft],		KEY_LOOK_LEFT);
	updateKey(m_keysStatus[Key::Submission],	KEY_SUBMISSION);
	updateKey(m_keysStatus[Key::Walk],			KEY_WALK);
	updateKey(m_keysStatus[Key::AnalogUp],		KEY_ANALOG_UP);
	updateKey(m_keysStatus[Key::AnalogDown],	KEY_ANALOG_DOWN);
	updateKey(m_keysStatus[Key::AnalogLeft],	KEY_ANALOG_LEFT);
	updateKey(m_keysStatus[Key::AnalogRight],	KEY_ANALOG_RIGHT);
	updateKey(m_keysStatus[Key::Yes],			KEY_YES);
	updateKey(m_keysStatus[Key::No],			KEY_NO);
	updateKey(m_keysStatus[Key::ControlBack],	KEY_CTRL_BACK);


	updateMoveKey(m_keysStatus[Key::MoveUp],	KEY_UP,		upDown_);
	updateMoveKey(m_keysStatus[Key::MoveDown],	KEY_DOWN,	upDown_);
	updateMoveKey(m_keysStatus[Key::MoveLeft],	KEY_LEFT,	leftRight_);
	updateMoveKey(m_keysStatus[Key::MoveRight], KEY_RIGHT,	leftRight_);

	return m_keysStatus;
}

}