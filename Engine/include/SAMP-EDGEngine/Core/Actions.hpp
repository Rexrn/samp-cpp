#pragma once

#include <SAMP-EDGEngine/Core/BasicInterfaces/Updatable.hpp>
#include <SAMP-EDGEngine/Core/Pointers.hpp>

#include <cassert>
#include <functional>

namespace samp_edgengine
{

class Task
{
public:
	using FuncType = std::function<void()>;

	Task(IUpdatable::Duration interval_, FuncType func_, std::uintmax_t repeatCount_ = 1)
		:
		m_running{ false },
		m_interval{ interval_ },
		m_function{ func_ },
		m_repeatCount{ repeatCount_ },
		m_lastExecution{ IUpdatable::Clock::now() }
	{
	}

	void execute()
	{
		assert(m_repeatCount > 0);
		m_repeatCount--;
		m_function();
		m_lastExecution = this->getNextExecutionTime();
	}
	void setFunction(FuncType func_) {
		m_function = func_;
	}
	void setRepeatCount(std::uintmax_t repeatCount_) {
		m_repeatCount = repeatCount_;
	}
	void stop() {
		this->setRepeatCount(0);
	}
	FuncType getFunction() const {
		return m_function;
	}
	IUpdatable::TimePoint getNextExecutionTime() const {
		return m_lastExecution + m_interval;
	}
	bool isRunning() const {
		return m_running && m_repeatCount > 0;
	}
	std::uintmax_t getRepeatCount() const {
		return m_repeatCount;
	}
	friend class TaskScheduler;
private:

	bool 					m_running;
	IUpdatable::Duration 	m_interval;
	IUpdatable::TimePoint 	m_lastExecution;
	std::uintmax_t 			m_repeatCount;
	FuncType 				m_function;
};

/// <summary>
/// Processes scheduled actions.
/// </summary>
class TaskScheduler
	: public IUpdatable
{
public:
	// Methods:
	
	/// <summary>
	/// Initializes a new instance of the <see cref="TaskScheduler"/> class.
	/// </summary>
	TaskScheduler()
		: m_performsInvocations{false}
	{
	}

	/// <summary>
	/// Schedules action with the specified parameters.
	/// </summary>
	/// <param name="interval_">The interval.</param>
	/// <param name="action_">The action.</param>
	/// <param name="repeatCount_">The repeat count.</param>
	/// <returns>Handle of the scheduled action.</returns>
	template <typename Rep, typename Period>	
	SharedPtr<Task> schedule(chrono::duration<Rep, Period> const & interval_, Task::FuncType func_, std::uintmax_t repeatCount_ = 1)
	{
		assert(repeatCount_ > 0);
		return this->internalSchedule(chrono::duration_cast<IUpdatable::Duration>(interval_), func_, repeatCount_);
	}

	/// <summary>
	/// Updates object every frame.
	/// </summary>
	/// <param name="deltaTime_">Number of seconds passed since last update.</param>
	/// <param name="timeMoment_">The point of time in which update happened.</param>
	virtual void update(double deltaTime_, IUpdatable::TimePoint timeMoment_) override;

private:
	using ContainerType = std::vector<SharedPtr<Task>>;
	
	/// <summary>
	/// Schedules action with specified parameters. Internal implementation of the schedule funtion.
	/// </summary>
	/// <param name="interval_">The interval.</param>
	/// <param name="action_">The action.</param>
	/// <param name="repeatCount_">The repeat count.</param>
	/// <returns>Handle of the scheduled action.</returns>
	SharedPtr<Task> internalSchedule(IUpdatable::Duration interval_, Task::FuncType func_, std::uintmax_t repeatCount_);

	ContainerType	m_actions;
	bool			m_performsInvocations;	// A state that informs whether actions are now being invoked and scheduling tasks will most probably invalidate iterators.
	ContainerType	m_pendingActions;		// Actions that were added during invoking. They must be added after the invocation.
};

}
