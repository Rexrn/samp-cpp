#include SAMPCPP_PCH

#include <SAMPCpp/Core/TaskSystem.hpp>


namespace samp_cpp
{

/////////////////////////////////////////////////////////////////////////////////////////////
Task::Task(IUpdatable::Duration interval_, FuncType func_, std::uintmax_t repeatCount_)
	:
	m_running{ false },
	m_interval{ interval_ },
	m_function{ func_ },
	m_repeatCount{ repeatCount_ },
	m_lastExecution{ IUpdatable::Clock::now() }
{
}

/////////////////////////////////////////////////////////////////////////////////////////////
void Task::execute()
{
	assert(m_repeatCount > 0);
	m_repeatCount--;
	m_function();
	m_lastExecution = this->getNextExecutionTime();
}

/////////////////////////////////////////////////////////////////////////////////////////////
void Task::setFunction(FuncType func_)
{
	m_function = func_;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void Task::setRepeatCount(std::uintmax_t repeatCount_)
{
	m_repeatCount = repeatCount_;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void Task::stop()
{
	this->setRepeatCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////
Task::FuncType Task::getFunction() const
{
	return m_function;
}

/////////////////////////////////////////////////////////////////////////////////////////////
IUpdatable::TimePoint Task::getNextExecutionTime() const
{
	return m_lastExecution + m_interval;
}

/////////////////////////////////////////////////////////////////////////////////////////////
bool Task::isRunning() const
{
	return m_running && m_repeatCount > 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
std::uintmax_t Task::getRepeatCount() const
{
	return m_repeatCount;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void TaskScheduler::update(double deltaTime_, IUpdatable::TimePoint timeMoment_)
{
	if (!m_tasks.empty())
	{
		// Calculate number of actions that must be fired.
		ContainerType::size_type numReady = 0;
		for (auto const & action : m_tasks)
		{
			if (action->getNextExecutionTime() < timeMoment_)
				numReady++;
			else
				break;
		}

		if (numReady > 0)
		{
			auto endIt = m_tasks.begin() + numReady;

			// Invoke every ready action.
			{
				// Safety TODO: consider using RAII on m_performsInvoking.

				m_performsTaskExecution = true;
				for (auto it = m_tasks.begin(); it != endIt; ++it)
				{
					// *it is SharedPtr<Task>&
					// *(*it) is Task&
					if (it->use_count() > 1 && (*it)->getRepeatCount() > 0)
						(*it)->execute();
				}
				m_performsTaskExecution = false;
			}

			// Erase actions that mustn't be fired again.
			m_tasks.erase(std::remove_if(m_tasks.begin(), endIt,
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


			if (!m_pendingTasks.empty())
			{
				m_tasks.insert(m_tasks.end(), m_pendingTasks.begin(), m_pendingTasks.end());

				m_pendingTasks.clear();
			}

			// Keep actions sorted.
			std::sort(m_tasks.begin(), m_tasks.end(), 
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
	if (m_performsTaskExecution) {
		m_pendingTasks.push_back(task);
	}
	else {
		m_tasks.insert(
				std::upper_bound(m_tasks.begin(), m_tasks.end(), task, 
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

/////////////////////////////////////////////////////////////////////////////////////////////
void ITaskOwner::interceptTask(SharedPtr<Task> task_, bool cleanup_)
{
	if (cleanup_)
		cleanupEndedTasks();
	m_tasks.push_back(task_);
}

/////////////////////////////////////////////////////////////////////////////////////////////
void ITaskOwner::removeAllTasks()
{
	m_tasks.clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////
void ITaskOwner::cleanupEndedTasks()
{
	m_tasks.erase(std::remove_if(m_tasks.begin(), m_tasks.end(),
			[](auto const& t_)
			{
				return !t_ || t_.use_count() < 2 || !t_->isRunning();
			}),
			m_tasks.end()
		);
}

}