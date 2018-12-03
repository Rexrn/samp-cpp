#pragma once

#include <SAMP-EDGEngine/Core/BasicInterfaces/Updatable.hpp>

#include <functional>

namespace samp_edgengine
{

/// <summary>
/// Processes scheduled actions.
/// </summary>
class ActionScheduler
	: public IUpdatable
{
public:
	// Aliases:
	using HandleType	= std::uintmax_t;
	using ActionType	= std::function<void()>;

	// - Time measuring:
	using ClockType		= std::chrono::high_resolution_clock;
	using TimePointType = ClockType::time_point;
	using DurationType	= TimePointType::duration;

	// Methods:
	
	/// <summary>
	/// Initializes a new instance of the <see cref="ActionScheduler"/> class.
	/// </summary>
	ActionScheduler()
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
	HandleType schedule(std::chrono::duration<Rep, Period> const & interval_, ActionType const & action_, std::uintmax_t const repeatCount_ = 1)
	{
		return this->internalSchedule(std::chrono::duration_cast<DurationType>(interval_), action_, std::max(std::uintmax_t{ 1 }, repeatCount_));
	}
	
	/// <summary>
	/// Stops the specified action.
	/// </summary>
	/// <param name="handle_">The action handle.</param>
	/// <returns>
	///		<c>true</c> if action with that handle existed; otherwise, <c>false</c>.
	/// </returns>
	bool stop(HandleType const handle_);
	
	/// <summary>
	/// Determines whether action with the specified handle is running.
	/// </summary>
	/// <param name="handle_">The handle.</param>
	/// <returns>
	///		<c>true</c> if running; otherwise, <c>false</c>.
	/// </returns>
	bool isRunning(HandleType const handle_) const;

	/// <summary>
	/// Updates object every frame.
	/// </summary>
	/// <param name="deltaTime_">Number of seconds passed since last update.</param>
	/// <param name="timeMoment_">The point of time in which update happened.</param>
	virtual void update(double const deltaTime_, IUpdatable::TimePointType const & timeMoment_) override;

private:
	// Subclasses:

	/// <summary>
	/// Set of information needed to fire an action.
	/// </summary>
	struct ActionRecord
	{
		HandleType		handle;				// Unique handle of the action.
		TimePointType	invokeTime;			// Time point in which action must be invoked.
		DurationType	interval;			// Interval between each invocation.
		std::uintmax_t	repeatsRemaining;	// Number of invocations remaining.
		ActionType		action;				// The action function.
		/// <summary>
		/// Check whether lhs is lower than rhs.
		/// </summary>
		/// <param name="lhs_">The LHS record.</param>
		/// <param name="rhs_">The RHS record.</param>
		/// <returns>
		///		<c>true</c> if LHS is lower than RHS; otherwise, <c>false</c>.
		/// </returns>
		friend static bool operator<(ActionRecord const & lhs_, ActionRecord const & rhs_) {
			return lhs_.invokeTime < rhs_.invokeTime;
		}

		/// <summary>
		/// Check whether lhs is greater than rhs.
		/// </summary>
		/// <param name="lhs_">The LHS record.</param>
		/// <param name="rhs_">The RHS record.</param>
		/// <returns>
		///		<c>true</c> if LHS is greater than RHS; otherwise, <c>false</c>.
		/// </returns>
		friend static bool operator>(ActionRecord const & lhs_, ActionRecord const & rhs_) {
			return lhs_.invokeTime > rhs_.invokeTime;
		}
	};
	using ContainerType = std::vector<ActionRecord>;

	/// <summary>
	/// Invokes specified action.
	/// </summary>
	/// <param name="record_">The action.</param>
	/// <returns>
	///		<c>true</c> if action must be repeated another time; otherwise, <c>false</c>.
	/// </returns>
	bool invoke(ActionRecord & record_)
	{
		record_.action();
		record_.invokeTime += record_.interval;

		// Warning: assumed repeatsRemaining is > 0.
		record_.repeatsRemaining--;

		return record_.repeatsRemaining > 0;
	}
	
	/// <summary>
	/// Schedules action with specified parameters. Internal implementation of the schedule funtion.
	/// </summary>
	/// <param name="interval_">The interval.</param>
	/// <param name="action_">The action.</param>
	/// <param name="repeatCount_">The repeat count.</param>
	/// <returns>Handle of the scheduled action.</returns>
	HandleType internalSchedule(DurationType const & interval_, ActionType const & action_, std::uintmax_t const repeatCount_);
	
	/// <summary>
	/// Finds an action with the specified handle.
	/// </summary>
	/// <param name="handle_">The handle.</param>
	/// <returns>Const iterator pointing to the action or past-the-end iterator if not found.</returns>
	ContainerType::const_iterator findAction(ContainerType const & container_, HandleType const handle_) const;

	/// <summary>
	/// Finds an action with the specified handle.
	/// </summary>
	/// <param name="handle_">The handle.</param>
	/// <returns>Iterator pointing to the action or past-the-end iterator if not found.</returns>
	ContainerType::iterator findAction(ContainerType & container_, HandleType const handle_);

	ContainerType	m_actions;
	bool			m_performsInvocations;	// A state that informs whether actions are now being invoked and scheduling tasks will most probably invalidate iterators.
	ContainerType	m_pendingActions;		// Actions that were added during invoking. They must be added after the invocation.
	
	/// <summary>
	/// Makes the unique handle.
	/// </summary>
	/// <returns>Unique handle index.</returns>
	HandleType makeUniqueHandle() {
		return s_uniqueHandleCounter++;
	}
	inline static HandleType s_uniqueHandleCounter = 0;
};

}
