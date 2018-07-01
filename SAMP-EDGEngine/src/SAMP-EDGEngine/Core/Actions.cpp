#include "SAMP-EDGEnginePCH.hpp"

#include <SAMP-EDGEngine/Core/Actions.hpp>

namespace agdk
{

/////////////////////////////////////////////////////////////////////////////////////////////
bool ActionScheduler::stop(HandleType const handle_)
{
	for (auto cont : { &m_actions, &m_pendingActions })
	{
		auto it = this->findAction(*cont, handle_);
		if (it != cont->end())
		{
			it->repeatsRemaining = 0;
			return true;
		}
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////
bool ActionScheduler::isRunning(HandleType const handle_) const
{
	return	this->findAction(m_actions, handle_) != m_actions.end()	||
			this->findAction(m_pendingActions, handle_) != m_pendingActions.end();
}

/////////////////////////////////////////////////////////////////////////////////////////////
void ActionScheduler::update(double const deltaTime_, IUpdatable::TimePointType const & timeMoment_)
{
	if (!m_actions.empty())
	{
		// Calculate number of actions that must be fired.
		ContainerType::size_type numReady = 0;
		for (auto const & action : m_actions)
		{
			if (action.invokeTime < timeMoment_)
				numReady++;
			else
				break;
		}

		if (numReady > 0)
		{
			auto endIt = m_actions.begin() + numReady;

			// Invoke every ready action.
			{
				// Safety TODO: consider using RAII on m_performsInvoking.

				m_performsInvocations = true;
				for (auto it = m_actions.begin(); it != endIt; ++it)
				{
					if (it->repeatsRemaining > 0)
						this->invoke(*it);
				}
				m_performsInvocations = false;
			}

			// Erase actions that mustn't be fired again.
			m_actions.erase(std::remove_if(m_actions.begin(), endIt,
					[](ActionRecord const & action_)
					{
						return action_.repeatsRemaining == 0;
					}
				), endIt);


			if (!m_pendingActions.empty())
			{
				m_actions.insert(m_actions.end(), m_pendingActions.begin(), m_pendingActions.end());

				m_pendingActions.clear();
			}

			// Keep actions sorted.
			std::sort(m_actions.begin(), m_actions.end());
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
ActionScheduler::HandleType ActionScheduler::internalSchedule(DurationType const & interval_, ActionType const & action_, std::uintmax_t const repeatCount_)
{
	ActionRecord record;
	record.interval				= interval_;
	record.invokeTime			= ClockType::now() + interval_;
	record.repeatsRemaining		= repeatCount_;
	record.action				= action_;

	HandleType uniqueHandle		= this->makeUniqueHandle();

	record.handle				= uniqueHandle;
	
	if (m_performsInvocations) {
		m_pendingActions.push_back(std::move(record));
	}
	else {
		m_actions.insert(std::upper_bound(m_actions.begin(), m_actions.end(), record), std::move(record));
	}

	return uniqueHandle;
}

/////////////////////////////////////////////////////////////////////////////////////////////
ActionScheduler::ContainerType::const_iterator ActionScheduler::findAction(ContainerType const & container_, HandleType const handle_) const
{
	return std::find_if(container_.begin(), container_.end(),
			[handle_](ActionRecord const & action_) {
				return action_.handle == handle_;
			}
		);
}

/////////////////////////////////////////////////////////////////////////////////////////////
ActionScheduler::ContainerType::iterator ActionScheduler::findAction(ContainerType & container_, HandleType const handle_)
{
	return std::find_if(container_.begin(), container_.end(),
			[handle_](ActionRecord const & action_) {
				return action_.handle == handle_;
			}
		);
}

}