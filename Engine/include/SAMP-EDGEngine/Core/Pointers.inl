#ifndef SAMP_EDGENGINE_SKIP_NAMESPACE
namespace samp_edgengine
{
#endif
template <typename T>
using SharedPtr		= std::shared_ptr<T>;
template <typename T, typename V = std::default_delete<T> >
using UniquePtr		= std::unique_ptr<T, V>;
template <typename T>
using WeakPtr		= std::weak_ptr<T>;
#ifndef SAMP_EDGENGINE_SKIP_NAMESPACE
} // namespace samp_edgengine
#endif