/**
 * Header: Vector2.inl
 * Author: Pawe³ Syska aka RazzorFlame.
 * Description:
 * Implements base class for 2D vector manipulation.
**/

namespace agdk
{
	namespace impl
	{
		template <typename _Ty>
		class BaseVector2
		{
		public:
			using ValueType = std::remove_cv_t< std::remove_reference_t<_Ty> >;

			// Allow every arithmetic type but bool.
			static_assert(std::is_arithmetic_v<ValueType> && !std::is_same_v<ValueType, bool>, "ValueType of a vector must be scalar type.");

			// This is basic component of a Vector2
			ValueType x, y;

			/// <summary>
			/// Initializes a new instance of the <see cref="BaseVector2"/> class.
			/// </summary>
			BaseVector2()
				: x{ 0 }, y{ 0 }
			{
			}

			/// <summary>
			/// Initializes a new instance of the <see cref="BaseVector2"/> class.
			/// </summary>
			/// <param name="x_">The x value.</param>
			/// <param name="y_">The y value.</param>
			BaseVector2(const ValueType &x_, const ValueType &y_)
				: x{ x_ }, y{ y_ }
			{
			}

			/// <summary>
			/// Initializes a new instance of the <see cref="BaseVector2"/> class.
			/// </summary>
			/// <param name="rhs_">The other vector.</param>
			template <typename _Ty2>
			BaseVector2(const BaseVector2<_Ty2> &rhs_)
				: x{ static_cast<ValueType>(rhs_.x) }, y{ static_cast<ValueType>(rhs_.y) }
			{
			}
			
			/// <summary>
			/// Sets values of the vector.
			/// </summary>
			/// <param name="x_">The x value.</param>
			/// <param name="y_">The y value.</param>
			void set(const ValueType x_, const ValueType y_)
			{
				x = static_cast<ValueType>(x_);
				y = static_cast<ValueType>(y_);
			}
			
			/// <summary>
			/// Returns length of the vector.
			/// </summary>
			/// <returns>Length of the vector.</returns>
			template <typename _LenTy,
				typename = std::enable_if_t< std::is_floating_point_v<_LenTy> > >
			_LenTy length() const
			{
				return std::sqrt(x * x + y * y);
			}

			/// <summary>
			/// Returns squared length of the vector.
			/// </summary>
			/// <returns>Squared length of the vector.</returns>
			template <typename _LenTy,
				typename = std::enable_if_t< std::is_floating_point_v<_LenTy> > >
			_LenTy lengthSquared() const
			{
				return static_cast<_LenTy>(x * x + y * y);
			}

			/// <summary>
			/// Computes distance between two instances.
			/// </summary>
			/// <param name="other_">The other vector.</param>
			/// <returns>Distance between two instances.</returns>
			template <typename _DistTy, typename _Ty2>			
			_DistTy distance(const BaseVector2<_Ty2> & other_) const
			{
				return (*this - other_).length();
			}

			/// <summary>
			/// Computes squared distance between two instances.
			/// </summary>
			/// <param name="other_">The other vector.</param>
			/// <returns>Squared distance between two instances.</returns>
			template <typename _DistTy, typename _Ty2>
			_DistTy distanceSquared(const BaseVector2<_Ty2> & other_) const
			{
				return (*this - other_).lengthSquared();
			}

			/// <summary>
			/// Computes dot product of two vectors (this and other).
			/// </summary>
			/// <param name="other_">The other vector.</param>
			/// <returns>Dot product of two vectors.</returns>
			template <typename _DotTy, typename _Ty2>			
			_DotTy dot(const BaseVector2<_Ty2> & other_) const
			{
				return static_cast<_DotTy>(x * ValueType(v.x) + y * ValueType(v.y));
			}

			/// <summary>
			/// Computes cross product of two vectors (this and rhs).
			/// </summary>
			/// <param name="other_">The other vector.</param>
			/// <returns>Cross product of two vectors.</returns>
			template <typename _CrossTy, typename _Ty2>
			_CrossTy cross(const BaseVector2<_Ty2> & other_) const
			{
				return static_cast<_CrossTy>(x * ValueType(v.y) + y * ValueType(v.x));
			}

			/// <summary>
			/// Computes reflection vector of specified normal.
			/// </summary>
			/// <param name="normal_">The surface normal.</param>
			/// <returns>Reflection vector of specified normal</returns>
			template <typename _Ty2>
			BaseVector2<_Ty> reflect(const BaseVector2<_Ty2> &normal_) const
			{
				auto normal = normal_.normalize().convert<_Ty>();
				return (*this) - (normal * normal.dot(*this) * 2.f);
			}
			
			/// <summary>
			/// Computes reflection vector of specified normal and assigns it to self.
			/// </summary>
			/// <param name="normal_">The normal.</param>
			/// <returns>Reference to self after computing reflection of specified normal.</returns>
			template <typename _Ty2>		
			BaseVector2<_Ty> & reflectSelf(const BaseVector2<_Ty2> &normal_)
			{
				auto normal = normal_.normalize().convert<_Ty>();
				*this = (*this) - (normal * normal.dot(*this) * 2.f);
				return *this;
			}
			
			/// <summary>
			/// Computes normalized vector.
			/// </summary>
			/// <returns>Normalized vector</returns>
			BaseVector2<_Ty> normalize() const
			{
				auto len = this->length<ValueType>();
				if (len != 0)
				{
					return { x / len, y / len };
				}
				return *this;
			}
			
			/// <summary>
			/// Normalizes self and returns reference.
			/// </summary>
			/// <returns>Reference to normalized self.</returns>
			BaseVector2<_Ty> & normalizeSelf()
			{
				auto len = this->length<ValueType>();
				if (len != 0)
				{
					x /= len; y /= len;
				}
				return *this;
			}

			/// <summary>
			/// Checks if two vectors are equal.
			/// </summary>
			/// <param name="other_">The other vector.</param>
			/// <param name="EqualityTolerance">The equality tolerance.</param>
			/// <returns>
			///  <c>true</c> if vectors are equal; otherwise, <c>false</c>.
			/// </returns>
			template <typename _Ty2, typename _EqTy,
						typename = std::enable_if_t< std::is_floating_point_v<_EqTy> > >
			bool equals(const BaseVector2<_Ty2> &other_, const _EqTy equalityTolerance_ = Math::Tolerance::Low<_EqTy>) const
			{
				return (std::abs(static_cast<_EqTy>(x) - static_cast<_EqTy>(other_.x)) <= equalityTolerance_
					&& std::abs(static_cast<_EqTy>(y) - static_cast<_EqTy>(other_.y)) <= equalityTolerance_);
			}

			/// <summary>
			/// Computes minimal vector of the two specified.
			/// </summary>
			/// <param name="lhs">The lhs vector.</param>
			/// <param name="rhs">The rhs vector.</param>
			/// <returns>Minimal vector of the two specified.</returns>
			template <typename _Ty2>
			static BaseVector2<_Ty> min(const BaseVector2<_Ty> &lhs_, const BaseVector2<_Ty2> &rhs_)
			{
				return BaseVector2<_Ty>(Math::min(lhs_.x, rhs_.x), Math::min(lhs_.y, rhs_.y));
			}

			/// <summary>
			/// Computes maximal vector of the two specified.
			/// </summary>
			/// <param name="lhs">The lhs vector.</param>
			/// <param name="rhs">The rhs vector.</param>
			/// <returns>Maximal vector of the two specified.</returns>
			template <typename _Ty2>
			static BaseVector2<_Ty> max(const BaseVector2<_Ty> &lhs_, const BaseVector2<_Ty2> &rhs_)
			{
				return BaseVector2<_Ty>(Math::max(lhs_.x, rhs_.x), Math::max(lhs_.y, rhs_.y));
			}

			/// <summary>
			/// Computes minimal and maximal vector of the two specified.
			/// </summary>
			/// <param name="minVec_">The minimum vec.</param>
			/// <param name="maxVec_">The maximum vec.</param>
			/// <remarks>
			/// <para>Uses arguments as output, changes its values.</para>
			/// </remarks>
			template <typename _Ty2>
			static void minMax(BaseVector2<_Ty> &minVec_, BaseVector2<_Ty2> &maxVec_)
			{
				auto tempMin = minVec_;
				minVec_ = BaseVector2<_Ty>::min(minVec_, maxVec_);
				maxVec_ = BaseVector2<_Ty2>::max(tempMin, maxVec_);
			}

			
			/// <summary>
			/// Converts vector to other type.
			/// </summary>
			/// <returns>Vector of other value type.</returns>
			template <typename _Ty2>
			BaseVector2<_Ty2> convert() { return BaseVector2<_Ty2>{*this}; }

			//////////// OPERATORS /////////////
			
			/// <summary>
			/// Assigns vector to self.
			/// </summary>
			/// <param name="rhs_">The rhs vector.</param>
			/// <returns></returns>
			template <typename _Ty2>
			BaseVector2<_Ty> & operator = (const BaseVector2<_Ty2> &rhs_) { x = ValueType(rhs_.x); y = ValueType(rhs_.y); return *this; }
			
			/// <summary>
			/// Negates vector.
			/// </summary>
			/// <returns>Negated vector.</returns>
			BaseVector2<_Ty> operator - () const { return BaseVector2<_Ty>(-x, -y); }

			
			/// <summary>
			/// Checks if lhs vector is equal to rhs vector (with low tolerance).
			/// </summary>
			/// <param name="rhs_">The other vector.</param>
			/// <returns>
			///  <c>true</c> if vectors are equal; otherwise, <c>false</c>.
			/// </returns>
			template <typename _Ty2>
			bool operator == (const BaseVector2<_Ty2> &rhs_) const { return equals(rhs_); }

			/// <summary>
			/// Checks if lhs vector is not equal to rhs vector (with low tolerance).
			/// </summary>
			/// <param name="rhs_">The other vector.</param>
			/// <returns>
			///  <c>true</c> if vectors are not equal; otherwise, <c>false</c>.
			/// </returns>
			template <typename _Ty2>
			bool operator != (const BaseVector2<_Ty2> &rhs_) const { return !equals(rhs_); }

			////////////////////////////////////////////////////////////////////////////////////////////////////

			/// <summary>
			/// Adds two vectors together.
			/// </summary>
			/// <param name="lhs_">The lhs vector.</param>
			/// <param name="rhs_">The rhs vector.</param>
			/// <returns>Reference to self, after operation.</returns>
			template <typename _Ty2>
			BaseVector2<_Ty> & operator += (const BaseVector2<_Ty2> &rhs_)
			{
				x += ValueType(rhs_.x);	y += ValueType(rhs_.y);
				return *this;
			}

			/// <summary>
			/// Subtracts rhs vector from lhs one.
			/// </summary>
			/// <param name="lhs_">The lhs vector.</param>
			/// <param name="rhs_">The rhs vector.</param>
			/// <returns>Reference to self, after operation.</returns>
			template <typename _Ty2>
			BaseVector2<_Ty> & operator -= (const BaseVector2<_Ty2> &rhs_)
			{
				x -= ValueType(rhs_.x);	y -= ValueType(rhs_.y);
				return *this;
			}

			/// <summary>
			/// Multiplies two vectors.
			/// </summary>
			/// <param name="lhs_">The lhs vector.</param>
			/// <param name="rhs_">The rhs vector.</param>
			/// <returns>Reference to self, after operation.</returns>
			template <typename _Ty2>
			BaseVector2<_Ty> & operator *= (const BaseVector2<_Ty2> &rhs_)
			{
				x *= ValueType(rhs_.x);	y *= ValueType(rhs_.y);
				return *this;
			}

			/// <summary>
			/// Adds two vectors together.
			/// </summary>
			/// <param name="lhs_">The lhs vector.</param>
			/// <param name="rhs_">The rhs vector.</param>
			/// <returns>Reference to self, after operation.</returns>
			template <typename _Ty2>
			BaseVector2<_Ty> & operator /= (const BaseVector2<_Ty2> &rhs_)
			{
				x /= ValueType(rhs_.x);	y /= ValueType(rhs_.y);
				return *this;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////

			/// <summary>
			/// Adds scalar to a vector.
			/// </summary>
			/// <param name="rhs_">The scalar.</param>
			/// <returns>Vector plus a scalar.</returns>
			BaseVector2<_Ty> & operator += (const ValueType rhs_)
			{
				x += rhs_; y += rhs_;
				return *this;
			}

			/// <summary>
			/// Substracts scalar from a vector.
			/// </summary>
			/// <param name="rhs_">The scalar.</param>
			/// <returns>Vector minus a scalar.</returns>
			BaseVector2<_Ty> & operator -= (const ValueType rhs_)
			{
				x -= rhs_; y -= rhs_;
				return *this;
			}

			/// <summary>
			/// Multiplies vector by a scalar.
			/// </summary>
			/// <param name="rhs_">The scalar.</param>
			/// <returns>Vector times a scalar.</returns>
			BaseVector2<_Ty> & operator *= (const ValueType rhs_)
			{
				x *= rhs_; y *= rhs_;
				return *this;
			}

			/// <summary>
			/// Divides vector by a scalar.
			/// </summary>
			/// <param name="rhs_">The scalar.</param>
			/// <returns>Vector divided by a scalar.</returns>
			BaseVector2<_Ty> & operator /= (const ValueType rhs_)
			{
				x /= rhs_; y /= rhs_;
				return *this;
			}
		};
		
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Adds two vectors together.
		/// </summary>
		/// <param name="lhs_">The lhs vector.</param>
		/// <param name="rhs_">The rhs vector.</param>
		/// <returns>Sum of two vectors.</returns>
		template <typename _Ty1, typename _Ty2>
		BaseVector2<_Ty1> operator + (const BaseVector2<_Ty1> &lhs_, const BaseVector2<_Ty2> &rhs_)
		{
			return BaseVector2<_Ty1>(lhs_.x + BaseVector2<_Ty1>::ValueType(rhs_.x), lhs_.y + BaseVector2<_Ty1>::ValueType(rhs_.y));
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Subtracts rhs vector from lhs one.
		/// </summary>
		/// <param name="lhs_">The lhs vector.</param>
		/// <param name="rhs_">The rhs vector.</param>
		/// <returns>Difference of two vectors.</returns>
		template <typename _Ty1, typename _Ty2>
		BaseVector2<_Ty1> operator - (const BaseVector2<_Ty1> &lhs_, const BaseVector2<_Ty2> &rhs_)
		{
			return BaseVector2<_Ty1>(lhs_.x - BaseVector2<_Ty1>::ValueType(rhs_.x), lhs_.y - BaseVector2<_Ty1>::ValueType(rhs_.y));
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Multiplies two vectors.
		/// </summary>
		/// <param name="lhs_">The lhs vector.</param>
		/// <param name="rhs_">The rhs vector.</param>
		/// <returns>Product of two vectors.</returns>
		template <typename _Ty1, typename _Ty2>
		BaseVector2<_Ty1> operator * (const BaseVector2<_Ty1> &lhs_, const BaseVector2<_Ty2> &rhs_)
		{
			return BaseVector2<_Ty1>(lhs_.x * BaseVector2<_Ty1>::ValueType(rhs_.x), lhs_.y * BaseVector2<_Ty1>::ValueType(rhs_.y));
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Adds two vectors together.
		/// </summary>
		/// <param name="lhs_">The lhs vector.</param>
		/// <param name="rhs_">The rhs vector.</param>
		/// <returns>Sum of two vectors.</returns>
		template <typename _Ty1, typename _Ty2>
		BaseVector2<_Ty1> operator / (const BaseVector2<_Ty1> &lhs_, const BaseVector2<_Ty2> &rhs_)
		{
			return BaseVector2<_Ty1>(lhs_.x / BaseVector2<_Ty1>::ValueType(rhs_.x), lhs_.y / BaseVector2<_Ty1>::ValueType(rhs_.y));
		}


		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Adds scalar to a vector.
		/// </summary>
		/// <param name="lhs_">The lhs vector.</param>
		/// <param name="rhs_">The scalar.</param>
		/// <returns>Vector plus a scalar.</returns>
		template <typename _Ty>
		BaseVector2<_Ty> operator + (const BaseVector2<_Ty> &lhs_, typename const BaseVector2<_Ty>::ValueType rhs_)
		{
			return BaseVector2<_Ty>(lhs_.x + rhs_, lhs_.y + rhs_);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Substracts scalar from a vector.
		/// </summary>
		/// <param name="lhs_">The lhs vector.</param>
		/// <param name="rhs_">The scalar.</param>
		/// <returns>Vector minus a scalar.</returns>
		template <typename _Ty>
		BaseVector2<_Ty> operator - (const BaseVector2<_Ty> &lhs_, typename const BaseVector2<_Ty>::ValueType rhs_)
		{
			return BaseVector2<_Ty>(lhs_.x - rhs_, lhs_.y - rhs_);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Multiplies vector by a scalar.
		/// </summary>
		/// <param name="lhs_">The lhs vector.</param>
		/// <param name="rhs_">The scalar.</param>
		/// <returns>Vector times a scalar.</returns>
		template <typename _Ty>
		BaseVector2<_Ty> operator * (const BaseVector2<_Ty> &lhs_, typename const BaseVector2<_Ty>::ValueType rhs_)
		{
			return BaseVector2<_Ty>(lhs_.x * rhs_, lhs_.y * rhs_);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>
		/// Divides vector by a scalar.
		/// </summary>
		/// <param name="lhs_">The lhs vector.</param>
		/// <param name="rhs_">The scalar.</param>
		/// <returns>Vector divided by a scalar.</returns>
		template <typename _Ty>
		BaseVector2<_Ty> operator / (const BaseVector2<_Ty> &lhs_, typename const BaseVector2<_Ty>::ValueType rhs_)
		{
			return BaseVector2<_Ty>(lhs_.x / rhs_, lhs_.y / rhs_);
		}

		
	}
}
