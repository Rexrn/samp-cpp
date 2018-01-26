// File description:
// Creates useful pointer aliases.
#pragma once

namespace agdk
{
	template <typename T>	using s_ptr = std::shared_ptr<T>;
	template <typename T>	using u_ptr = std::unique_ptr<T>;
	template <typename T>	using w_ptr = std::weak_ptr<T>;
} // namespace agdk