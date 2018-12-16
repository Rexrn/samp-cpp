#pragma once
#include SAMPEDGENGINE_PCH



#include <SAMP-EDGEngine/Core/BasicInterfaces/Updatable.hpp>
#include <SAMP-EDGEngine/Core/Pointers.hpp>

#include <cassert>
#include <functional>
#include <vector>

namespace samp_edgengine
{

/// <summary>
///		Encapsulates single task (postponed function call).
/// </summary>
class Task
{
public:
	// Aliases:
	using FuncType = std::function<void()>;

	/// <summary>
	///		Initializes a new instance of the <see cref="Task"/> class.
	/// </summary>
	/// <param name="interval_">The interval.</param>
	/// <param name="func_">The function to be executed.</param>
	/// <param name="repeatCount_">The repeat count.</param>
	Task(IUpdatable::Duration interval_, FuncType func_, std::uintmax_t repeatCount_ = 1);

	/// <summary>
	///		Executes this task.
	/// </summary>
	void execute();

	/// <summary>
	///		Sets function to be executed by this task.
	/// </summary>
	/// <param name="func_">The function to be executed.</param>
	void setFunction(FuncType func_);

	/// <summary>
	///		Sets how many times this time will be executed.
	/// </summary>
	/// <param name="repeatCount_">The repeat count.</param>
	void setRepeatCount(std::uintmax_t repeatCount_);

	/// <summary>
	///		Stops this task from being executed (sets repeat count to 0).
	/// </summary>
	void stop();

	/// <summary>
	///		Returns function executed by this task.
	/// </summary>
	FuncType getFunction() const;

	/// <summary>
	///		Calculates and returns time point of next execution.
	/// </summary>
	IUpdatable::TimePoint getNextExecutionTime() const;

	/// <summary>
	///		Determines whether this task is currently running.
	/// </summary>
	bool isRunning() const;
	
	/// <summary>
	///		Returns remaining repeat count.
	/// </summary>
	std::uintmax_t getRepeatCount() const;

	friend class TaskScheduler;
private:

	bool 					m_running;
	IUpdatable::Duration 	m_interval;
	IUpdatable::TimePoint 	m_lastExecution;
	std::uintmax_t 			m_repeatCount;
	FuncType 				m_function;
};

/// <summary>
///		Task owner. Bounds tasks` lifetime to its own.
/// </summary>
class ITaskOwner
{
public:
	using ContainerType = std::vector< SharedPtr<Task> >;

	/// <summary>
	///		Inserts new task.
	/// </summary>
	void interceptTask(SharedPtr<Task> task_, bool cleanup_ = true);

	/// <summary>
	///		Removes every running task.
	/// </summary>
	void removeAllTasks();

	/// <summary>
	///		Removes ended or invalid tasks.
	/// </summary>
	void cleanupEndedTasks();

private:
	ContainerType m_tasks;
};

/// <summary>
/// Processes scheduled tasks.
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
		: m_performsTaskExecution{false}
	{
	}

	/// <summary>
	/// Schedules task with the specified parameters.
	/// </summary>
	/// <param name="interval_">The interval.</param>
	/// <param name="func_">The function to be executed.</param>
	/// <param name="repeatCount_">The repeat count.</param>
	/// <returns>Shared pointer to the scheduled task.</returns>
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
	/// Schedules task with specified parameters. Internal implementation of the schedule funtion.
	/// </summary>
	/// <param name="interval_">The interval.</param>
	/// <param name="func_">The function to be executed.</param>
	/// <param name="repeatCount_">The repeat count.</param>
	/// <returns>Shared pointer to the scheduled task.</returns>
	SharedPtr<Task> internalSchedule(IUpdatable::Duration interval_, Task::FuncType func_, std::uintmax_t repeatCount_);

	ContainerType	m_tasks;
	bool			m_performsTaskExecution;	// A state that informs whether tasks are now being executed and scheduling tasks will most probably invalidate iterators.
	ContainerType	m_pendingTasks;				// Tasks that were added during invoking. They must be added after the execution.
};

}
