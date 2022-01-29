#pragma once
#include <cmath>
#include <iostream>
#include "TypeDefines.h"
namespace Katarina {
	class KATARINA_API Vector3
	{
	public:
		Vector3() = default;
		Vector3(real_t x, real_t y, real_t z) : coord{ x, y, z } {}
		Vector3(real_t x) : x(x), y(x), z(x) {}
		_FORCE_INLINE_ bool nearZearo()
		{
			const auto s = 1e-8;
			return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
		}
		Vector3& normalize();
		Vector3& normalize()const;
		Vector3 operator-() const;
		real_t operator[](int i) const;
		real_t& operator[](int i);

		Vector3& operator+=(const Vector3& v);

		Vector3& operator*=(const real_t t);

		Vector3& operator/=(const real_t t);

		Vector3 operator-(const Vector3& vec)const;
		Vector3 operator*(const Vector3& vec)const;
		Vector3 operator+(const Vector3& vec)const;
		real_t length() const;

		real_t lengthSquared() const;

		_FORCE_INLINE_ static real_t dot(const Vector3& u, const Vector3& v);


		_FORCE_INLINE_ Vector3 reflect(const Vector3& n);

		_FORCE_INLINE_ Vector3 refract(const Vector3& n, double etai_over_etat);

		_FORCE_INLINE_ static Vector3 cross(const Vector3& u, const Vector3& v);

	public:
		enum Axis
		{
			AXIS_X,
			AXIS_Y,
			AXIS_Z,
		};

		union
		{
			struct
			{
				real_t x;
				real_t y;
				real_t z;
			};
			real_t coord[3] = { 0 };
		};
	};

	_FORCE_INLINE_ Vector3 operator*(const real_t& t, const Vector3& v)
	{
		return Vector3(t * v.x, t * v.y, t * v.z);
	}

	_FORCE_INLINE_ Vector3 operator*(const Vector3& v, real_t t)
	{
		return t * v;
	}

	_FORCE_INLINE_ Vector3 operator/(Vector3 v, real_t t)
	{
		return (1 / t) * v;
	}

	_FORCE_INLINE_ real_t Vector3::dot(const Vector3& u, const Vector3& v)
	{
		return u.x * v.x
			+ u.y * v.y
			+ u.z * v.z;
	}

	_FORCE_INLINE_ std::ostream& operator<<(std::ostream& os, const Vector3& vec)
	{
		return os << vec.x << " " << vec.y << " " << vec.z;
	}
}

