/**
 * Header: Vector2.inl
 * Author: Pawe³ Syska aka RazzorFlame.
 * Description:
 * Implements base class for 2D vector manipulation.
 * Note:
 * Requires important maintenance.
**/

namespace agdk
{
	namespace impl
	{
		// TODO: requires code improvement and documentation standarization (using XML style).

		template <typename T>
		class BaseVector2
		{
		public:
			// This is basic component of a Vector2
			T x, y;

			////// Function: Vector2 (default constructor)
			//// Parameters: <none>
			//// Brief: This is a Vector2's default constructor
			///////////////////////////////////////////////////////////////
			BaseVector2();

			////// Function: Vector2 (constructor)
			//// Parameters:
			//// 	1) xValue: 	Float32 		- x component of a vector
			//// 	2) yValue: 	Float32 		- y component of a vector
			//// Brief: Initializes vector from components
			///////////////////////////////////////////////////////////////
			BaseVector2(const T &xValue, const T &yValue);

			////// Function: Vector2 (copy constructor)
			//// Parameters:
			////	1) other	Vector2&		- other instance to copy from
			//// Brief: This is a Vector2's copy constructor
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector2(const BaseVector2<U> &v);

			////// Function: Vector2 (destructor)
			//// Parameters: <none>
			//// Brief: This is a Vector2's destructor [= default]
			///////////////////////////////////////////////////////////////
			~BaseVector2() = default;

			////// Function: Set
			//// Parameters:
			//// 	1) xValue: 	Float32 		- x component of a vector
			//// 	2) yValue: 	Float32 		- y component of a vector
			//// Return: 			void 		- does not return anything
			//// Brief: Sets vector components
			///////////////////////////////////////////////////////////////
			void set(const T &xValue, const T &yValue);

			////// Function: Length
			//// Parameters: <none>
			//// Return: 			Float32 	- length of vector
			//// Brief: returns vector length = sqrt(x*x + y*y)
			///////////////////////////////////////////////////////////////
			float length() const;

			////// Function: LengthSquared
			//// Parameters: <none>
			//// Return: 			Float32 	- squared length of vector
			//// Brief: return vector length squared = (x*x + y*y)
			///////////////////////////////////////////////////////////////
			float lengthSquared() const;

			////// Function: Distance
			//// Parameters:
			////	1) other	Vector2&		- other vector (to compute distance)
			//// Return: 			Float32 	- distance to vector
			//// Brief: return distance to other vector
			//// Distance = (A-B).Length()
			///////////////////////////////////////////////////////////////
			template <typename U>
			float distance(const BaseVector2<U> & v) const;

			////// Function: DistanceSquared
			//// Parameters:
			////	1) other	Vector2&		- other vector (to compute distance)
			//// Return: 			Float32 	- squared distance to vector
			//// Brief: return squared distance to other vector
			//// Distance = (A-B).LengthSquared()
			///////////////////////////////////////////////////////////////
			template <typename U>
			float distanceSquared(const BaseVector2<U> & v) const;

			////// Function: Dot (product)
			//// Parameters:
			////	1) other	Vector2&		- other vector (to compute dot product)
			//// Return: 			Float32 	- dot product of vectors
			//// Brief: return dot product of two vectors (self and 'other')
			//// Dot product = (x * other.x) + (y * other.y)
			///////////////////////////////////////////////////////////////
			template <typename U>
			float dot(const BaseVector2<U> & v) const;

			////// Function: Cross (product)
			//// Parameters:
			////	1) other	Vector2&		- other vector (to compute cross product)
			//// Return: 			Float32 	- cross product of vectors
			//// Brief: return cross product of two vectors (self and 'other')
			//// Cross product = (x * other.y) + (y * other.x)
			///////////////////////////////////////////////////////////////
			template <typename U>
			float cross(const BaseVector2<U> & v) const;

			////// Function: Reflect (vector) [const]
			//// Parameters:
			////	1) normal	Vector2		- wall normal to be reflected from
			//// Return: 		Vector2 	- reflected copy vector
			//// Brief: return reflected copy of self
			//// Reflected vector is used in for instance ball bouncing
			//// Reflected vector = self - (2 * (Normal * Dot(Normal, self)))
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector2<T> reflect(const BaseVector2<U> &Normal) const;

			////// Function: ReflectSelf
			//// Parameters:
			////	1) normal	Vector2		- wall normal to be reflected from
			//// Return: 		Vector2& 	- self as reflected vector
			//// Brief: return self as reflected vector from normal
			//// THIS METHOD MODIFIES SELF VECTOR
			//// Reflected vector is used in for instance ball bouncing
			//// Reflected vector = self - (2 * (Normal * Dot(Normal, self)))
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector2<T> & reflectSelf(const BaseVector2<U> &Normal);

			////// Function: Normal (vector) [const]
			//// Parameters: <none>
			//// Return: 		Vector2 	- normal from self
			//// Brief: return calculated normal using self vector
			//// Normal = Vector2(-y, x)
			///////////////////////////////////////////////////////////////
			BaseVector2<T> normal() const;

			////// Function: NormalizeSelf
			//// Parameters: <none>
			//// Return: 		Vector2& 	- self as normalized vector
			//// Brief: return self as normalized vector
			//// THIS METHOD MODIFIES SELF VECTOR
			//// Normalization = self / self.Length()
			///////////////////////////////////////////////////////////////
			BaseVector2<T> & normalizeSelf();

			////// Function: Normalize
			//// Parameters: <none>
			//// Return: 		Vector2 	- normalized copy of self
			//// Brief: return normalized copy of self
			//// Normalization = self / self.Length()
			///////////////////////////////////////////////////////////////
			BaseVector2<T> normalize() const;

			template <typename U>
			bool equals(const BaseVector2<U> &Other, const double EqualityTolerance = Math::Equality::LowTolerance) const
			{
				return (std::fabs(static_cast<double>(x) - static_cast<double>(Other.x)) <= EqualityTolerance
					&& std::fabs(static_cast<double>(y) - static_cast<double>(Other.y)) <= EqualityTolerance);
			}

			template <typename V, typename U>
			static BaseVector2<V> min(const BaseVector2<V> &MinVec, const BaseVector2<U> &MaxVec)
			{
				return BaseVector2<V>(Math::min(MinVec.x, MaxVec.x), Math::min(MinVec.y, MaxVec.y));
			}
			template <typename V, typename U>
			static BaseVector2<V> max(const BaseVector2<V> &MinVec, const BaseVector2<U> &MaxVec)
			{
				return BaseVector2<V>(Math::max(MinVec.x, MaxVec.x), Math::max(MinVec.y, MaxVec.y));
			}

			template <typename V, typename U>
			static void minMax(BaseVector2<V> &MinVec, BaseVector2<U> &MaxVec)
			{
				MinVec = BaseVector2<V>::min(MinVec, MaxVec);
				MaxVec = BaseVector2<U>::max(MinVec, MaxVec);
			}

			template <typename U>
			BaseVector2<U> as() { return BaseVector2<U>(*this); }

			//////////// OPERATORS /////////////


			////// Operator: Assign
			//// Brief: Assign value of other vector to self
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector2<T> & operator = (const BaseVector2<U> &Right) { x = T(Right.x); y = T(Right.y); return *this; }

			////// Operator: Negate
			//// Brief: Returns negated copy vector
			///////////////////////////////////////////////////////////////
			BaseVector2<T> operator - () const { return BaseVector2<T>(-x, -y); }

			////// Operator: Equality test
			//// Brief: Checks if self and other vector are the same
			///////////////////////////////////////////////////////////////
			template <typename U>
			bool operator == (const BaseVector2<U> &Right) const { return equals(Right); }

			////// Operator: Inequality test
			//// Brief: Checks if self and other vector are NOT the same
			///////////////////////////////////////////////////////////////
			template <typename U>
			bool operator != (const BaseVector2<U> &Right) const { return !equals(Right); }


			////////////////////////////////////////////////////////////////////////////////////////////////////


			////// Operator: Addition
			//// Brief: Creates a copy of (self + other)
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector2<T> operator + (const BaseVector2<U> &Right) const { return BaseVector2<T>(x + T(Right.x), y + T(Right.y)); }

			////// Operator: Subtraction
			//// Brief: Creates a copy of (self - other)
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector2<T> operator - (const BaseVector2<U> &Right) const { return BaseVector2<T>(x - T(Right.x), y - T(Right.y)); }

			////// Operator: Multiplication
			//// Brief: Creates a copy of (self * other)
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector2<T> operator * (const BaseVector2<U> &Right) const { return BaseVector2<T>(x * T(Right.x), y * T(Right.y)); }

			////// Operator: Division
			//// Brief: Creates a copy of (self / other)
			//// BE CAREFUL! IF 'other.x' OR 'other.y' EQUALS 0
			//// IT WILL CAUSE EXCEPTION
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector2<T> operator / (const BaseVector2<U> &Right) const { return BaseVector2<T>(x / T(Right.x), y / T(Right.y)); }


			////////////////////////////////////////////////////////////////////////////////////////////////////


			////// Operator: Addition (to self)
			//// Brief: Adds a vector to self
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector2<T> & operator += (const BaseVector2<U> &Right) { x += T(Right.x); y += T(Right.y); return *this; }

			////// Operator: Subtraction (from self)
			//// Brief: Subtracts a vector from self
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector2<T> & operator -= (const BaseVector2<U> &Right) { x -= T(Right.x); y -= T(Right.y); return *this; }

			////// Operator: Multiplication (self by other)
			//// Brief: Multiplies self by other
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector2<T> & operator *= (const BaseVector2<U> &Right) { x *= T(Right.x); y *= T(Right.y); return *this; }

			////// Operator: Division (self by other)
			//// Brief: Divides self by other vector
			//// BE CAREFUL! IF 'other.x' OR 'other.y' EQUALS 0
			//// IT WILL CAUSE EXCEPTION
			///////////////////////////////////////////////////////////////
			template <typename U>
			BaseVector2<T> & operator /= (const BaseVector2<U> &Right) { x /= T(Right.x); y /= T(Right.y); return *this; }


			////////////////////////////////////////////////////////////////////////////////////////////////////


			////// Operator: Addition (scalar to self) (return copy)
			//// Brief: Adds a scalar to both components (x, y)
			///////////////////////////////////////////////////////////////
			BaseVector2<T> operator + (const float Right) const { return BaseVector2<T>(x + T(Right), y + T(Right)); }

			////// Operator: Subtraction (scalar from self) (return copy)
			//// Brief: Suybtracts a scalar from both components (x, y)
			///////////////////////////////////////////////////////////////
			BaseVector2<T> operator - (const float Right) const { return BaseVector2<T>(x - T(Right), y - T(Right)); }

			////// Operator: Multiplication (self by scalar) (return copy)
			//// Brief: Multiplies both components (x, y) by scalar
			///////////////////////////////////////////////////////////////
			BaseVector2<T> operator * (const float Right) const { return BaseVector2<T>(x * T(Right), y * T(Right)); }

			////// Operator: Division (self by scalar) (return copy)
			//// Brief: Divides both components (x, y) by scalar
			//// BE CAREFUL! IF scalar EQUALS 0 [ZERO]
			//// IT WILL CAUSE EXCEPTION
			///////////////////////////////////////////////////////////////
			BaseVector2<T> operator / (const float Right) const { return BaseVector2<T>(x / T(Right), y / T(Right)); }


			////////////////////////////////////////////////////////////////////////////////////////////////////


			////// Operator: Addition (scalar to self) (return copy)
			//// Brief: Adds a scalar to both components (x, y)
			///////////////////////////////////////////////////////////////
			BaseVector2<T> & operator += (const float Right) { x += T(Right); y += T(Right); return *this; }

			////// Operator: Subtraction (scalar from self)
			//// Brief: Suybtracts a scalar from both components (x, y)
			///////////////////////////////////////////////////////////////
			BaseVector2<T> & operator -= (const float Right) { x -= T(Right); y -= T(Right); return *this; }

			////// Operator: Multiplication (self by scalar)
			//// Brief: Multiplies both components (x, y) by scalar
			///////////////////////////////////////////////////////////////
			BaseVector2<T> & operator *= (const float Right) { x *= T(Right); y *= T(Right); return *this; }

			////// Operator: Division (self by scalar)
			//// Brief: Divides self by scalar
			//// BE CAREFUL! IF scalar EQUALS 0 [ZERO]
			//// IT WILL CAUSE EXCEPTION
			BaseVector2<T> & operator /= (const float Right) { x /= T(Right); y /= T(Right); return *this; }
		};

		////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////// Implementation ///////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		BaseVector2<T>::BaseVector2() : x(0), y(0) { }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		BaseVector2<T>::BaseVector2(const T &xValue, const T &yValue) : x(xValue), y(yValue) { }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		BaseVector2<T>::BaseVector2(const BaseVector2<U> & v) : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) { }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		void BaseVector2<T>::set(const T &xValue, const T &yValue) { x = xValue; y = yValue; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		float BaseVector2<T>::length() const { return sqrt(static_cast<float>(x * x + y * y)); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		float BaseVector2<T>::lengthSquared() const { return x * x + y * y; }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		float BaseVector2<T>::distance(const BaseVector2<U> & v) const { return sqrt(static_cast<float>((x - T(v.x)) * (x - T(v.x))) + ((y - T(v.y)) * (y - T(v.y)))); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		float BaseVector2<T>::distanceSquared(const BaseVector2<U> & v) const { return static_cast<float>((x - T(v.x)) * (x - T(v.x))) + ((y - T(v.y)) * (y - T(v.y))); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		float BaseVector2<T>::dot(const BaseVector2<U> & v) const { return x * T(v.x) + y * T(v.y); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		float BaseVector2<T>::cross(const BaseVector2<U> & v) const { return x * T(v.y) + y * T(v.x); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		BaseVector2<T> BaseVector2<T>::reflect(const BaseVector2<U> &Normal) const
		{
			auto normal = Normal.normalize();
			return BaseVector2<T>(*this) - ((normal.template As<T>() * (normal.template As<T>.dot(*this))) * 2.f);
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		template <typename U>
		BaseVector2<T>& BaseVector2<T>::reflectSelf(const BaseVector2<U> &Normal)
		{
			*this = (reflect(Normal));
			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		BaseVector2<T> BaseVector2<T>::normal() const { return BaseVector2<T>(-y, x); }

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		BaseVector2<T> & BaseVector2<T>::normalizeSelf()
		{
			float length = length();
			if (length != 0)
			{
				x /= length; y /= length;
				return *this;
			}

			set(0, 0);
			return *this;
		}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		template <typename T>
		BaseVector2<T> BaseVector2<T>::normalize() const
		{
			BaseVector2<T> ret = *this;
			float length = length();
			if (length != 0)
			{
				ret.x /= length; ret.y /= length;
				return ret;
			}

			ret.set(0, 0);
			return ret;
		}

		///////////////////////////////////////// End of Implementation ////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
}
