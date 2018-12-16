#pragma once
#include SAMPEDGENGINE_PCH



#include <SAMP-EDGEngine/Core/Pointers.hpp>

#include <typeinfo>
#include <typeindex>

namespace samp_edgengine
{

class IEventReceiver;
class EventDispatcherInterface;
template <typename... _Args>
class EventDispatcher;

/// <summary>
/// Class representing hooked object method.
/// </summary>
template <typename... _Args>
class EventHook
{
	/// <summary>
	/// It is impossible to create template of a pointer-to-member-variable, so this class wraps it.
	/// Used only for correct type-erasure.
	/// </summary>
	template <typename _Class>
	struct FunctionWrapper
	{
		using Type = void(_Class::*)(_Args...);

		FunctionWrapper(Type method_)
			: fn{ method_ }
		{
		}
		Type fn;
	};
	
	// Type of an invoker function.
	using InvokerFn = void(*)(EventHook&, _Args const&...);
	// Type of a comparing function.
	using CompareFn = bool(*)(void*, void*);
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="EventHook"/> class.
	/// </summary>
	/// <param name="receiver_">The receiver object.</param>
	/// <param name="method_">The receiver method.</param>
	template <typename _Class,
		typename = std::enable_if_t< std::is_base_of_v<IEventReceiver, _Class> > >		// allow only derivatives of IEventReceiver		
	EventHook(_Class &receiver_, void (_Class::*method_)(_Args...))
		:
		m_receiver{ &receiver_ },														// store pointer to receiver
		m_fnWrapper{																	// store wrapper to method
		new FunctionWrapper<_Class>(method_),
			[](void *deletedObject) {													// type-erasure forces to use custom deleter
				delete (static_cast< FunctionWrapper<_Class>* >(deletedObject));
			}
		},
		m_recvType{ typeid(_Class) },													// store receiver typeid code (used when comparing EventHooks)
		m_invoker{ invoker<_Class> },													// store pointer to invoker function (we cannot directly call object's method because of type erasure)
		m_compare{ compare<_Class> }													// store pointer to comparing function
	{
	}
			
	/// <summary>
	/// Copy constructing a <see cref="EventHook"/> object is forbidden.
	/// </summary>
	/// <param name="other_">The other event hook.</param>
	EventHook(EventHook const &other_) = delete;
	
	/// <summary>
	/// Copy assigning a <see cref="EventHook"/> object is forbidden.
	/// </summary>
	/// <param name="other_">The other event hook.</param>
	/// <returns>Reference to self; but deleted.</returns>
	EventHook& operator=(EventHook const &other_) = delete;
	
	/// <summary>
	/// Initializes a new instance of the <see cref="EventHook"/> class from moved hook.
	/// </summary>
	/// <param name="moved_">The moved hook.</param>
	EventHook(EventHook &&moved_)
		:
		m_receiver{ moved_.m_receiver },
		m_fnWrapper{ std::move(moved_.m_fnWrapper) },
		m_recvType{ moved_.m_recvType },
		m_invoker{ moved_.m_invoker },
		m_compare{ moved_.m_compare }
	{
		moved_.m_receiver = nullptr;
		moved_.m_fnWrapper = nullptr;
		moved_.m_invoker = nullptr;
		moved_.m_compare = nullptr;
	}
	
	/// <summary>
	/// Performs move assignment.
	/// </summary>
	/// <param name="moved_">The moved.</param>
	/// <returns>Reference to self.</returns>
	EventHook& operator=(EventHook &&moved_)
	{
		m_receiver = moved_.m_receiver;
		m_fnWrapper = moved_.m_fnWrapper;	// original automatically deleted, no need for move-swap idiom.
		m_recvType = moved_.m_recvType;
		m_invoker = moved_.m_invoker;
		m_compare = moved_.m_compare;
		return *this;
	}
	
	/// <summary>
	/// Compares two event hooks - equal only when methods they point to have the same address.
	/// </summary>
	/// <param name="other_">The other hook.</param>
	/// <returns></returns>
	bool operator==(EventHook const & other_) const
	{
		// Two hooks cannot match when their receiver type is not exactly the same.
		if (m_recvType != other_.m_recvType)
			return false;

		// If two tyles match up compare them using special compare function.
		return m_compare(m_fnWrapper.get(), other_.m_fnWrapper.get());
	}
	
	/// <summary>
	/// Returns the receiver object.
	/// </summary>
	/// <returns>Receiver object.</returns>
	IEventReceiver* getReceiver() const {
		return m_receiver;
	}

	/// Dispatcher calls `invoke` method that is private.
	friend class EventDispatcher<_Args...>;
private:
	
	/// <summary>
	/// Invokes the method with specified args.
	/// </summary>
	/// <param name="args_">The method parameters.</param>
	void invoke(_Args const&... args_)
	{
		m_invoker(*this, args_...);
	}

	/// <summary>
	/// Invokes the specified hook.
	/// </summary>
	/// <param name="hook_">The hook.</param>
	/// <param name="args_">The method parameters.</param>
	/// <remarks>
	/// <para>Perfect forwarding here is probably impossible (needs verification)</para>
	/// </remarks>
	template <typename _Class>
	static void invoker(EventHook& hook_, _Args const&... args_)
	{
		// Recover types back from type-erasure.
		auto fnWrapper		= static_cast< FunctionWrapper<_Class>* >(hook_.m_fnWrapper.get());
		auto recvObject		= static_cast<_Class*>(hook_.m_receiver);
		auto fn				= fnWrapper->fn;
		// Call the proper method.
		(recvObject->*fn)(args_...);
	}

	/// <summary>
	/// Compares the specified function wrappers.
	/// </summary>
	/// <param name="leftFnWrapper_">The left function wrapper.</param>
	/// <param name="rightFnWrapper_">The right function wrapper.</param>
	/// <returns>
	///		<c>true</c> if wrappers refer to the same method; otherwise <c>false</c>.
	/// </returns>
	template <typename _Class>
	static bool compare(void* leftFnWrapper_, void* rightFnWrapper_)
	{
		// At this point we can safely cast void* to FunctionWrapper<_Class>*, because std::type_index is stored.
		return 	static_cast< FunctionWrapper<_Class>* >(leftFnWrapper_)->fn ==
				static_cast< FunctionWrapper<_Class>* >(rightFnWrapper_)->fn;
	}

	IEventReceiver* 						m_receiver;		// pointer to receiver object
	UniquePtr<void, void(*)(void*)> 	m_fnWrapper;	// pointer to wrapper of the method
	std::type_index 						m_recvType;		// receiver type_index used when comparing
	InvokerFn 								m_invoker;		// invoker function
	CompareFn								m_compare;		// compare function
};

/// <summary>
/// Interface for every EventDispatcher. Allows us to flatten template to one basic type.
/// </summary>
class EventDispatcherInterface
{
public:

	// Event receiver needs to access `removeReceiver` method.
	friend class IEventReceiver;
protected:
	
	/// <summary>
	/// Adds the method hook
	/// </summary>
	/// <param name="hook_">The hook.</param>
	virtual void addHook(void* hook_) = 0;	

	/// <summary>
	/// Removes the receiver and all of its hooks.
	/// </summary>
	/// <param name="recv_">The receiver.</param>
	virtual void removeReceiver(IEventReceiver& recv_) = 0;
	
	/// <summary>
	/// Removes the method hook.
	/// </summary>
	/// <param name="hook_">The hook.</param>
	virtual void removeHook(void* hook_) = 0;
};

/// <summary>
/// Base class for every object that can receive event notification.
/// </summary>
class IEventReceiver
{
public:	
	/// <summary>
	/// Finalizes an instance of the <see cref="IEventReceiver"/> class.
	/// </summary>
	virtual ~IEventReceiver()
	{
		for (auto &disp : m_dispatchers)
			disp->removeReceiver(*this);
	}

	// Event dispatcher needs to access `addDispatcher` and `removeDispatcher` methods.
	template <typename... _Args>
	friend class EventDispatcher;
private:
	
	/// <summary>
	/// Adds the dispatcher.
	/// </summary>
	/// <param name="disp_">The dispatcher.</param>
	void addDispatcher(EventDispatcherInterface &disp_)
	{
		auto it = std::find(m_dispatchers.begin(), m_dispatchers.end(), &disp_);
		if (it == m_dispatchers.end()) // protect from multiple records
			m_dispatchers.push_back(&disp_);
	}
	
	/// <summary>
	/// Removes the dispatcher.
	/// </summary>
	/// <param name="disp_">The dispatcher.</param>
	void removeDispatcher(EventDispatcherInterface &disp_)
	{
		auto it = std::find(m_dispatchers.begin(), m_dispatchers.end(), &disp_);
		if (it != m_dispatchers.end())
			m_dispatchers.erase(it);
	}

	// Stores every dispatcher, so when objects get destroyed it can notify them.
	std::vector<EventDispatcherInterface*> m_dispatchers;
};


/// <summary>
/// A class that can inform IEventReceiver that some event occurred.
/// </summary>
/// <remarks>
/// <para>
///		Event have always form of a procedure with specified args, so when you create dispatcher like this:
///		<code>
///			EventDispatcher<Player&, Vehicle&> playerEntersVehicle;
///		</code>
///		it means, that event method must look like that:
///		<code>
///			struct MyRecv
///				: public IEventReceiver
///			{
///				void whenPlayerEntersVehicle(Player & player_, Vehicle & vehicle_)
///				{
///					// your code
///				}
///			};
///		</code>
/// </para>
/// </remarks>
template <typename... _Args>
class EventDispatcher
	: public EventDispatcherInterface
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="EventDispatcher"/> class.
	/// </summary>
	EventDispatcher() { }
	
	/// <summary>
	/// Finalizes an instance of the <see cref="EventDispatcher"/> class.
	/// </summary>
	~EventDispatcher() {
		this->clear();
	}
		
	/// <summary>
	/// Copy constructing a <see cref="EventDispatcher"/> object is forbidden.
	/// </summary>
	/// <param name="other_">The other dispatcher.</param>
	EventDispatcher(EventDispatcher const & other_) = delete;
	
	/// <summary>
	/// Copy assigning a <see cref="EventDispatcher"/> object is forbidden.
	/// </summary>
	/// <param name="other_">The other dispatcher.</param>
	/// <returns>Reference to self; but deleted.</returns>
	EventDispatcher& operator=(EventDispatcher const & other_) = delete;
	
	/// <summary>
	/// Emits the event with specified arguments.
	/// </summary>
	/// <param name="args_">The arguments.</param>
	void emit(_Args const&... args_)
	{
		for (auto &hook : m_hooks)
			hook->invoke(args_...);
	}
	
	/// <summary>
	/// Adds specified hook.
	/// </summary>
	/// <param name="hook_">The hook.</param>
	void operator+=(EventHook<_Args...> hook_)
	{
		// This is safe, since `hook_` life extends beyond usage of void* ptr.
		this->addHook(static_cast<void*>(&hook_));
		// `hook_` was moved!
	}
	
	/// <summary>
	/// Removes the specified hook.
	/// </summary>
	/// <param name="hook_">The hook.</param>
	void operator-=(EventHook<_Args...> hook_)
	{
		// This is safe, since `hook_` life extends beyond usage of void* ptr.
		this->removeHook(static_cast<void*>(&hook_));
	}
	
	/// <summary>
	/// Removes every existing hook.
	/// </summary>
	void clear()
	{
		// OPTIMIZE TODO: this can get more optimized
		while (!m_hooks.empty()) {
			this->removeReceiver(*m_hooks[0]->getReceiver());
		}
	}
private:
	
	/// <summary>
	/// Adds method the hook.
	/// </summary>
	/// <param name="hook_">The hook.</param>
	virtual void addHook(void* hook_) override
	{
		// Type was erased, so we must recover it.
		// The original type was EventHook<_Args...> and since we cannot copy it, we must take a reference.
		// See operator += and operator-= : the object (with automatic storage duration) life extends beyond current function, so its safe.
		auto &deHook = *static_cast< EventHook<_Args...>* >(hook_);
		// Add dispatcher reference to receiver.
		deHook.getReceiver()->addDispatcher(*this);
		// Push hook
		m_hooks.push_back(std::make_unique< EventHook<_Args...> >(std::move(deHook)));
	}
	
	/// <summary>
	/// Removes the receiver and all of its hooks.
	/// </summary>
	/// <param name="recv_">The receiver.</param>
	virtual void removeReceiver(IEventReceiver& recv_) override
	{
		m_hooks.erase(
			std::remove_if(m_hooks.begin(), m_hooks.end(),
				[&recv_](UniquePtr< EventHook<_Args...> > const & element_) {
			return element_->getReceiver() == &recv_;
		}),
			m_hooks.end());
		recv_.removeDispatcher(*this);
	}
	
	/// <summary>
	/// Removes the method hook.
	/// </summary>
	/// <param name="hook_">The hook.</param>
	virtual void removeHook(void* hook_) override
	{
		// Type was erased, so we must recover it.
		// The original type was EventHook<_Args...> and since we cannot copy it, we must take a reference.
		// See operator += and operator-= : the object (with automatic storage duration) life extends beyond current function, so its safe.
		auto &deHook = *static_cast<EventHook<_Args...>*>(hook_);
		auto it = std::find_if(m_hooks.begin(), m_hooks.end(),
			[&deHook](UniquePtr< EventHook<_Args...> > const & element_) {
			return *element_ == deHook;
		});
		if (it != m_hooks.end())
			m_hooks.erase(it);

		// At this point reference to a dispatcher inside receiver is still stored.
		// We need to check if there is any other hook from that receiver; if not - remove ref.
		std::size_t howManyHooks = std::count_if(m_hooks.begin(), m_hooks.end(),
			[&deHook](UniquePtr< EventHook<_Args...> > const & element_) {
			return element_->getReceiver() == deHook.getReceiver();
		});
		if (howManyHooks == 0)
			deHook.getReceiver()->removeDispatcher(*this);
	}

	// Stores every hook.
	std::vector< UniquePtr< EventHook<_Args...> > > m_hooks;
};

}
