#pragma once
#include"TypeDefines.h"
#include<iostream>
namespace Katarina
{
	template<typename T>
	class KATARINA_API Vector2
	{
	public:
		Vector2() = default;
		Vector2(T a, T b) :x(a), y(b) {}
		_FORCE_INLINE_ T Vector2::dot(const Vector2& v) const 
		{
			return x * v.x + y * v.y;
		}

		_FORCE_INLINE_ T Vector2::cross(const Vector2& v) const
		{
			return x * v.y - y * v.x;
		}

		Vector2 operator+(const Vector2& p_v) const
		{
			return Vector2(x + p_v.x, y + p_v.y);
		}

		Vector2 operator*(const T& rvalue) const
		{
			return Vector2(x * rvalue, y * rvalue);
		}

		_FORCE_INLINE_ Vector2 operator-(const Vector2& p_v) const {
			return Vector2(x - p_v.x, y - p_v.y);
		}

		_FORCE_INLINE_ T& operator[](int p_idx)
		{
			return p_idx ? y : x;
		}
		_FORCE_INLINE_ const T& operator[](int p_idx) const
		{
			return p_idx ? y : x;
		}

		static const int AXIS_COUNT = 2;
		enum Axis {
			AXIS_X,
			AXIS_Y,
		};
		union {
			struct {
				union {
					T x;
					T width;
				};
				union {
					T y;
					T height;
				};
			};

			T coord[2] = { 0 };
		};
	};

	template<typename T>
	_FORCE_INLINE_ std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec)
	{
		return os << vec.x << " " << vec.y ;
	}

	using Point2 = Vector2<real_t>;
	using Trangle2 = Vector2<real_t>[3];
	using Point2i = Vector2<int>;
	using Trangle2i = Vector2<int>[3];
}


