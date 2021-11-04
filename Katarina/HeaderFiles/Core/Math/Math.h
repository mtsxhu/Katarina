#pragma once
#include"TypeDefines.h"
#include "Core/Math/MathDefines.h"
#include "Core/Math/Vector3.h"
namespace Katarina
{
	class KATARINA_API Math
	{
	public:
		_FORCE_INLINE_ static real_t Degrees2Radians(const real_t& deg)
		{
			return deg * KT_PI / 180.0;
		}

		_FORCE_INLINE_ static bool IsEqualApprox(const real_t& a, const real_t& b)
		{
			if (a == b)
			{
				return true;
			}
			real_t tolerance = CMP_EPSILON * abs(a);
			if (tolerance < CMP_EPSILON)
			{
				tolerance = CMP_EPSILON;
			}
			return abs(a - b) < tolerance;
		}

		_FORCE_INLINE_ static real_t RandomDouble()
		{
			return rand() / (RAND_MAX + 1.0);
		}

		_FORCE_INLINE_ static real_t RandomDouble(real_t min, real_t max)
		{
			return min + (max - min) * RandomDouble();
		}

		static _FORCE_INLINE_ real_t Clamp(real_t x, real_t min, real_t max)
		{
			if (x < min) return min;
			if (x > max) return max;
			return x;
		}
		_FORCE_INLINE_ static Vector3 Random()
		{
			return Vector3(Math::RandomDouble(), Math::RandomDouble(), Math::RandomDouble());
		}

		_FORCE_INLINE_ static Vector3 Random(real_t min, real_t max)
		{
			return Vector3(Math::RandomDouble(min, max), Math::RandomDouble(min, max), Math::RandomDouble(min, max));
		}

		static inline Vector3 RandomInUnitSphere()
		{
			while (true)
			{
				auto p = Random(-1, 1);
				if (p.length_squared() >= 1) continue;
				return p;
			}
		}

		static _FORCE_INLINE_ Vector3 RandomUnitVector()
		{
			return RandomInUnitSphere();
		};

		static _FORCE_INLINE_ Vector3 RandomInUnitDisk()
		{
			while (true)
			{
				auto p = Vector3(Math::RandomDouble(-1, 1), Math::RandomDouble(-1, 1), 0);
				if (p.length_squared() >= 1) continue;
				return p;
			}
		}

		_FORCE_INLINE_ static bool  nearZero(const Vector3& vec)
		{
			return Math::IsEqualApprox(vec.x, 0) && Math::IsEqualApprox(vec.y, 0) && Math::IsEqualApprox(vec.z, 0);
		}
	};
}