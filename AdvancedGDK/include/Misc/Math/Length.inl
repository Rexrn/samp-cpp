#include <ratio>
#include <limits>

namespace agdk
{
	namespace impl
	{
		template<class _Ty>
		constexpr bool is_ratio_v = false;

		template<intmax_t _R1, intmax_t _R2>
		constexpr bool is_ratio_v<std::ratio<_R1, _R2>> = true;

		/// <summary>
		/// Provides implementation of base length unit.
		/// </summary>
		template <typename _Ty, class _Ratio = std::ratio<1, 1>>
		class BaseLength
		{
		public:
			using RatioType		= std::remove_cv_t<std::remove_reference_t<_Ratio>>;
			using ValueType		= std::remove_cv_t<std::remove_reference_t<_Ty>>;

			static_assert(is_ratio_v<RatioType>, "Second template parameter must be a valid std::ratio type.");
			static_assert(std::is_floating_point_v<ValueType>, "Length can only be represented by floating point values.");

			ValueType value;
			
			/// <summary>
			/// Returns maximal possible value.
			/// </summary>
			/// <returns>Maximal possible value.</returns>
			constexpr static ValueType max()
			{
				return std::numeric_limits<ValueType>::max();
			}

			/// <summary>
			/// Returns minimal possible value.
			/// </summary>
			/// <returns>Minimal possible value.</returns>
			constexpr static ValueType min()
			{
				return std::numeric_limits<ValueType>::min();
			}

			/// <summary>
			/// Returns zero-length.
			/// </summary>
			/// <returns>Zero-length object.</returns>
			constexpr static BaseLength<ValueType, RatioType> zero()
			{
				return {};
			}

			/// <summary>
			/// Default constructor.
			/// </summary>
			constexpr BaseLength(ValueType value_ = ValueType{ 0 })
				: value(value_)
			{
			}

			/// <summary>
			/// Copy constructor.
			/// </summary>
			/// <param name="rhs_">Other length object.</param>
			template <typename _Ty1, typename _Ratio1>
			constexpr BaseLength(const BaseLength<_Ty, _Ratio1> &rhs_)
				: value(rhs_.value
						* std::ratio_divide<_Ratio1, RatioType>::num
						/ std::ratio_divide<_Ratio1, RatioType>::den)
			{
			}

			/// <summary>
			/// Copy assignment operator.
			/// </summary>
			/// <param name="rhs_">Other length object.</param>
			template <typename _Ty1, typename _Ratio1>
			constexpr BaseLength<ValueType, RatioType>& operator=(const BaseLength<_Ty1, _Ratio1> &rhs_)
			{
				value = rhs_.value
					* std::ratio_divide<_Ratio1, RatioType>::num
					/ std::ratio_divide<_Ratio1, RatioType>::den;
			}

			/// <summary>
			/// Converts value to other length unit.
			/// </summary>
			template <typename _Ty1, typename _Ratio1>
			constexpr explicit operator BaseLength<_Ty1, _Ratio1>() const
			{
				using div_ratio = std::ratio_divide<_Ratio1, RatioType>;
				return { static_cast<_Ty1>(value) * div_ratio::num / div_ratio::den };
			}

			/// <summary>
			/// Determines whether rhs length is *exactly* equal.
			/// </summary>
			/// <param name="rhs">The right hand side length.</param>
			/// <returns>
			///   <c>true</c> if equal; otherwise, <c>false</c>.
			/// </returns>
			template <typename _Ty1, typename _Ratio1>
			constexpr bool isEqual(const BaseLength<_Ty1, _Ratio1> &rhs) const
			{
				using div_ratio = std::ratio_divide<_Ratio1, RatioType>;
				return value == (static_cast<_Ty1>(rhs.value) * div_ratio::num / div_ratio::den);
			}

			/// <summary>
			/// Determines whether rhs length is nearly equal.
			/// </summary>
			/// <param name="rhs">The right hand side length.</param>
			/// <param name="tolerance">The tolerance.</param>
			/// <returns>
			///   <c>true</c> if nearly equal; otherwise, <c>false</c>.
			/// </returns>
			template <typename _Ty1, typename _Ratio1>
			constexpr bool isNearlyEqual(const BaseLength<_Ty1, _Ratio1> &rhs, ValueType tolerance = Math::Tolerance::Medium<ValueType>) const
			{
				using div_ratio = std::ratio_divide<_Ratio1, RatioType>;
				return Math::nearlyEqual(value, (static_cast<_Ty1>(rhs.value) * div_ratio::num / div_ratio::den), tolerance);
			}
		};
		
		/// <summary>
		/// Adds rhs length to lhs.
		/// </summary>
		/// <param name="lhs">The left hand side length.</param>
		/// <param name="rhs">The right hand side length.</param>
		/// <returns>Sum of two lengths.</returns>
		/// <remarks>
		/// <para>Resulting type matches lhs type.</para>
		/// </remarks>
		template <typename _Ty1, typename _Ratio1, typename _Ty2, typename _Ratio2>
		constexpr BaseLength<_Ty1, _Ratio1> operator+(const BaseLength<_Ty1, _Ratio1> &lhs, const BaseLength<_Ty2, _Ratio2> &rhs)
		{
			using div_ratio = std::ratio_divide<_Ratio2, _Ratio1>;
			return { lhs.value + (static_cast<_Ty1>(rhs.value) * div_ratio::num / div_ratio::den) };
		}

		/// <summary>
		/// Subtracts rhs length from lhs.
		/// </summary>
		/// <param name="lhs">The left hand side length.</param>
		/// <param name="rhs">The right hand side length.</param>
		/// <returns>Difference of two lengths.</returns>
		/// <remarks>
		/// <para>Resulting type matches lhs type.</para>
		/// </remarks>
		template <typename _Ty1, typename _Ratio1, typename _Ty2, typename _Ratio2>
		constexpr BaseLength<_Ty1, _Ratio1> operator-(const BaseLength<_Ty1, _Ratio1> &lhs, const BaseLength<_Ty2, _Ratio2> &rhs)
		{
			using div_ratio = std::ratio_divide<_Ratio2, _Ratio1>;
			return { lhs.value - (static_cast<_Ty1>(rhs.value) * div_ratio::num / div_ratio::den) };
		}

		/// <summary>
		/// Returns lhs multiplied by a scalar.
		/// </summary>
		/// <param name="lhs">The left hand side length.</param>
		/// <param name="scalar">The scalar.</param>
		/// <returns>Product of lhs length and scalar.</returns>
		/// <remarks>
		/// <para>Resulting type matches length type.</para>
		/// </remarks>
		template <typename _Ty, typename _Ratio, typename _FTy,
			typename = std::enable_if_t< std::is_floating_point_v< std::remove_reference_t< std::remove_cv_t<_FTy> > > > >
		constexpr BaseLength<_Ty, _Ratio> operator*(const BaseLength<_Ty, _Ratio> &lhs, _FTy scalar)
		{
			return { lhs.value * scalar };
		}

		/// <summary>
		/// Returns lhs divided by a scalar.
		/// </summary>
		/// <param name="lhs">The left hand side length.</param>
		/// <param name="scalar">The scalar.</param>
		/// <returns>Quotient of lhs length and scalar.</returns>
		/// <remarks>
		/// <para>Resulting type matches length type.</para>
		/// </remarks>
		template <typename _Ty, typename _Ratio, typename _FTy,
			std::enable_if_t< std::is_floating_point_v< std::remove_reference_t< std::remove_cv_t<_FTy> > > > >
		constexpr BaseLength<_Ty, _Ratio> operator/(const BaseLength<_Ty, _Ratio> &lhs, _FTy scalar)
		{
			return { lhs.value / scalar };
		}

		/// <summary>
		/// Returns rhs multiplied by a scalar.
		/// </summary>
		/// <param name="scalar">The scalar.</param>
		/// <param name="rhs">The right hand side length.</param>
		/// <returns>Product of rhs length and scalar.</returns>
		/// <remarks>
		/// <para>Resulting type matches length type.</para>
		/// </remarks>
		template <typename _FTy, typename _Ty, typename _Ratio,
			typename = std::enable_if_t< std::is_floating_point_v< std::remove_reference_t< std::remove_cv_t<_FTy> > > > >
		constexpr BaseLength<_Ty, _Ratio> operator*(_FTy scalar, const BaseLength<_Ty, _Ratio> &rhs)
		{
			return { rhs.value * scalar };
		}

		/// <summary>
		/// Returns lhs divided by a scalar.
		/// </summary>
		/// <param name="scalar">The scalar.</param>
		/// <param name="rhs">The right hand side length.</param>
		/// <returns>Quotient of rhs length and scalar.</returns>
		/// <remarks>
		/// <para>Resulting type matches length type.</para>
		/// </remarks>
		template <typename _FTy, typename _Ty, typename _Ratio,
			typename = std::enable_if_t< std::is_floating_point_v< std::remove_reference_t< std::remove_cv_t<_FTy> > > > >
		constexpr BaseLength<_Ty, _Ratio> operator/(_FTy scalar, const BaseLength<_Ty, _Ratio> &rhs)
		{
			return { rhs.value / scalar };
		}

		/// <summary>
		/// Checks if lhs length is *nearly* equal rhs length.
		/// </summary>
		/// <param name="lhs">The left hand side length.</param>
		/// <param name="rhs">The right hand side length.</param>
		/// <returns>
		///   <c>true</c> if nearly equal; otherwise, <c>false</c>.
		/// </returns>
		template <typename _Ty1, typename _Ratio1, typename _Ty2, typename _Ratio2>
		constexpr bool operator==(const BaseLength<_Ty1, _Ratio1> &lhs, const BaseLength<_Ty2, _Ratio2> &rhs)
		{
			return lhs.isNearlyEqual(rhs);
		
		}

		/// <summary>
		/// Checks if lhs length is not *nearly* equal rhs length.
		/// </summary>
		/// <param name="lhs">The left hand side length.</param>
		/// <param name="rhs">The right hand side length.</param>
		/// <returns>
		///   <c>false</c> if nearly equal; otherwise, <c>true</c>.
		/// </returns>
		template <typename _Ty1, typename _Ratio1, typename _Ty2, typename _Ratio2>
		constexpr bool operator!=(const BaseLength<_Ty1, _Ratio1> &lhs, const BaseLength<_Ty2, _Ratio2> &rhs)
		{
			return !lhs.isNearlyEqual(rhs);
		}

		/// <summary>
		/// Checks if lhs length is greater than rhs length.
		/// </summary>
		/// <param name="lhs">The left hand side length.</param>
		/// <param name="rhs">The right hand side length.</param>
		/// <returns>
		///   <c>true</c> if lhs is greater; otherwise, <c>false</c>.
		/// </returns>
		template <typename _Ty1, typename _Ratio1, typename _Ty2, typename _Ratio2>
		constexpr bool operator>(const BaseLength<_Ty1, _Ratio1> &lhs, const BaseLength<_Ty2, _Ratio2> &rhs)
		{
			using div_ratio = std::ratio_divide<_Ratio2, _Ratio1>;
			return lhs.value > (static_cast<_Ty1>(rhs.value) * div_ratio::num / div_ratio::den);
		}

		/// <summary>
		/// Checks if lhs length is greater or equal than rhs length.
		/// </summary>
		/// <param name="lhs">The left hand side length.</param>
		/// <param name="rhs">The right hand side length.</param>
		/// <returns>
		///   <c>true</c> if lhs is greater or equal; otherwise, <c>false</c>.
		/// </returns>
		template <typename _Ty1, typename _Ratio1, typename _Ty2, typename _Ratio2>
		constexpr bool operator>=(const BaseLength<_Ty1, _Ratio1> &lhs, const BaseLength<_Ty2, _Ratio2> &rhs)
		{
			using div_ratio = std::ratio_divide<_Ratio2, _Ratio1>;
			return lhs.value >= (static_cast<_Ty1>(rhs.value) * div_ratio::num / div_ratio::den);
		}

		/// <summary>
		/// Checks if lhs length is less than rhs length.
		/// </summary>
		/// <param name="lhs">The left hand side length.</param>
		/// <param name="rhs">The right hand side length.</param>
		/// <returns>
		///   <c>true</c> if lhs is less; otherwise, <c>false</c>.
		/// </returns>
		template <typename _Ty1, typename _Ratio1, typename _Ty2, typename _Ratio2>
		constexpr bool operator<(const BaseLength<_Ty1, _Ratio1> &lhs, const BaseLength<_Ty2, _Ratio2> &rhs)
		{
			return !(lhs >= rhs);
		}

		/// <summary>
		/// Checks if lhs length is less or equal than rhs length.
		/// </summary>
		/// <param name="lhs">The left hand side length.</param>
		/// <param name="rhs">The right hand side length.</param>
		/// <returns>
		///   <c>true</c> if lhs is less or equal; otherwise, <c>false</c>.
		/// </returns>
		template <typename _Ty1, typename _Ratio1, typename _Ty2, typename _Ratio2>
		constexpr bool operator<=(const BaseLength<_Ty1, _Ratio1> &lhs, const BaseLength<_Ty2, _Ratio2> &rhs)
		{
			return !(lhs > rhs);
		}
	}


	using Nanometers	= impl::BaseLength<double, std::nano>;		// 0.000'000'001m
	using Micrometers	= impl::BaseLength<double, std::micro>;		// 0.000'001m
	using Millimeters	= impl::BaseLength<double, std::milli>;		// 0.001m
	using Centimeters	= impl::BaseLength<double, std::centi>;		// 0.01m
	using Decimeters	= impl::BaseLength<double, std::deci>;		// 0.1m
	using Meters		= impl::BaseLength<double>;					// 1m
	using Decameters	= impl::BaseLength<double, std::deca>;		// 10m
	using Hectometers	= impl::BaseLength<double, std::hecto>;		// 100m
	using Kilometers	= impl::BaseLength<double, std::kilo>;		// 1'000m
	using Megameters	= impl::BaseLength<double, std::mega>;		// 1'000'000m
	using Gigameters	= impl::BaseLength<double, std::giga>;		// 1'000'000'000m
	using Miles			= impl::BaseLength<double, std::ratio_multiply<std::kilo, std::ratio<1609, 1000>>>; // 1609m
	using Yards			= impl::BaseLength<double, std::ratio<9144, 10000>>;		// 0.9144m
	using Lightyears	= impl::BaseLength<double, std::ratio<9460730472580800>>;	// 9460730472580800m
}
