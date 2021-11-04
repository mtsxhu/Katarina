#include "Core/Math/Vector3.h"

namespace Katarina
{
	Vector3& Vector3::normalize()
	{
		auto len = length();
		x /= len;
		y /= len;
		z /= len;
		return *this;
	}

	Vector3 Vector3::operator-() const { return Vector3(-x, -y, -z); }
	real_t Vector3::operator[](int i) const { return coord[i]; }
	real_t& Vector3::operator[](int i) { return coord[i]; }

	Vector3& Vector3::operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector3& Vector3::operator*=(const real_t t)
	{
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	Vector3& Vector3::operator/=(const real_t t)
	{
		return *this /= t;
	}

	Vector3 Vector3::operator-(const Vector3& vec) const
	{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3 Vector3::operator*(const Vector3& vec) const
	{
		return Vector3(x * vec.x, y * vec.y, z * vec.z);
	}

	Vector3 Vector3::operator+(const Vector3& vec) const
	{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}

	real_t Vector3::length() const
	{
		return sqrt(length_squared());
	}

	real_t Vector3::length_squared() const
	{
		return x * x + y * y + z * z;
	}

	_FORCE_INLINE_ Vector3 Vector3::reflect(const Vector3& n)
	{
		return *this - 2 * Vector3::dot(*this, n) * n;
	}

	_FORCE_INLINE_ Vector3 Vector3::refract(const Vector3& n, double etai_over_etat)
	{
		auto cos_theta = fmin(dot(-(*this), n), 1.0);
		Vector3 r_out_perp = etai_over_etat * (-(*this) + cos_theta * n);
		Vector3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
		return r_out_perp + r_out_parallel;
	}

	_FORCE_INLINE_  Vector3 Vector3::cross(const Vector3& u, const Vector3& v)
	{
		return Vector3(u.y * v.z - u.z * v.y,
			u.z * v.x - u.x * v.z,
			u.x * v.y - u.y * v.x);
	}
}