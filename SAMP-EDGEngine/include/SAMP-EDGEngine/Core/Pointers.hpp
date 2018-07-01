// File description:
// Creates useful pointer aliases.
#pragma once

#include SAMP_EDGENGINE_PCH

namespace agdk
{
	template <typename T>
	using SharedPtr		= std::shared_ptr<T>;
	template <typename T, typename V = std::default_delete<T> >
	using UniquePtr		= std::unique_ptr<T, V>;
	template <typename T>
	using WeakPtr		= std::weak_ptr<T>;
} // namespace agdk