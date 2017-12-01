#ifndef ADVANCEDGDK_POINTERS_HPP_INCLUDED
#define ADVANCEDGDK_POINTERS_HPP_INCLUDED

#include <memory>

namespace agdk
{
	template <typename T>	using s_ptr = std::shared_ptr<T>;
	template <typename T>	using u_ptr = std::unique_ptr<T>;
	template <typename T>	using w_ptr = std::weak_ptr<T>;
	
	template <typename T>	using observer	= T *;

} // namespace agdk

#endif //!ADVANCEDGDK_POINTERS_HPP_INCLUDED