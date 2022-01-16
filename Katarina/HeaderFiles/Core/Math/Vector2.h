#pragma once
#include"TypeDefines.h"
namespace Katarina
{
	class KATARINA_API Vector2
	{
	public:
		Vector2() = default;
		Vector2(real_t a, real_t b) :x(a), y(b) {}
		_FORCE_INLINE_ real_t Vector2::dot(const Vector2& v) const 
		{
			return x * v.x + y * v.y;
		}

		_FORCE_INLINE_ real_t Vector2::cross(const Vector2& v) const
		{
			return x * v.y - y * v.x;
		}

		_FORCE_INLINE_ real_t& operator[](int p_idx)
		{
			return p_idx ? y : x;
		}
		_FORCE_INLINE_ const real_t& operator[](int p_idx) const
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
					real_t x;
					real_t width;
				};
				union {
					real_t y;
					real_t height;
				};
			};

			real_t coord[2] = { 0 };
		};
	};

	using Point2 = Vector2;
	using Trangle2 = Vector2[3];
}


