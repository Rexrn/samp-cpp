#include <SAMP-EDGEngine/Core/Actions.hpp>

#include <algorithm>

namespace samp_edgengine
{

/////////////////////////////////////////////////////////////////////////////////////////////
void TaskScheduler::update(double deltaTime_, IUpdatable::TimePoint timeMoment_)
{
	if (!m_actions.empty())
	{
		// Calculate number of actions that must be fired.
		ContainerType::size_type numReady = 0;
		for (auto const & action : m_actions)
		{
			if (action->getNextExecutionTime() < timeMoment_)
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
					// *it is SharedPtr<Task>&
					// *(*it) is Task&
					if (it->use_count() > 1 && (*it)->getRepeatCount() > 0)
						(*it)->execute();
				}
				m_performsInvocations = false;
			}

			// Erase actions that mustn't be fired again.
			m_actions.erase(std::remove_if(m_actions.begin(), endIt,
					[](SharedPtr<Task> & task_)
					{
						if (task_.use_count() <= 1 || task_->getRepeatCount() == 0)
						{
							task_->m_running = false;
							return true;
						}
						return false;
					}
				), endIt);


			if (!m_pendingActions.empty())
			{
				m_actions.insert(m_actions.end(), m_pendingActions.begin(), m_pendingActions.end());

				m_pendingActions.clear();
			}

			// Keep actions sorted.
			std::sort(m_actions.begin(), m_actions.end(), 
					[](SharedPtr<Task> const& left_, SharedPtr<Task> const& right_)
					{
						return left_->getNextExecutionTime() < right_->getNextExecutionTime();
					}
				);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
SharedPtr<Task> TaskScheduler::internalSchedule(IUpdatable::Duration interval_, Task::FuncType function_, std::uintmax_t repeatCount_)
{
	auto task = std::make_shared<Task>(interval_, function_, repeatCount_);
	task->m_running = true;
	if (m_performsInvocations) {
		m_pendingActions.push_back(task);
	}
	else {
		m_actions.insert(
				std::upper_bound(m_actions.begin(), m_actions.end(), task, 
					[](SharedPtr<Task> const& left_, SharedPtr<Task> const& right_)
					{
						return left_->getNextExecutionTime() < right_->getNextExecutionTime();
					}
				),
				task
			);
	}

	return task;
}
}