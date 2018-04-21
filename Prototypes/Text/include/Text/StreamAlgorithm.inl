// Note: this file is not meant to be included on its own.
// Include "StreamAlgorithm.hpp" instead.

namespace agdk::proto::text
{

#ifdef __cpp_template_auto
template <auto _char, typename TCharType>
inline std::basic_istream<TCharType>& skipIf(std::basic_istream<TCharType>& istream_)
{
	if ((istream_ >> std::ws).peek() == _char) {
		istream_.ignore();
	}
	else {
		istream_.setstate(std::ios_base::failbit);
	}
	return istream_;
}
#else
template <typename TCharType, TCharType _char>
inline std::basic_istream<TCharType>& skipIf(std::basic_istream<TCharType>& istream_)
{
	if ((istream_ >> std::ws).peek() == _char) {
		istream_.ignore();
	}
	else {
		istream_.setstate(std::ios_base::failbit);
	}
	return istream_;
}
#endif

} // namespace