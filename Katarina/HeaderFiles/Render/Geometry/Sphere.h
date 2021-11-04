#pragma once
#include"Core/Math/Vector3.h"
#include "Render/Collide/Collisionable.h"
#include "Render/Collide/CollideRecord.h"
#include "Render/Ray/Ray.h"
#include "Render/Material/Material.h"
#include <tuple>
#include <memory>
namespace Katarina
{
	class KATARINA_API Sphere : public Collisionable
	{
	public:
		Sphere(const Vector3& vec, real_t r, std::shared_ptr<Material> mat) :radius(r), material(mat), center(vec) {}
		// 通过 Collisionable 继承
		virtual std::pair<bool, CollideRecord> collision(const Ray& ray, const real_t& t_min, const real_t& t_max) const override;

		_FORCE_INLINE_ Vector3 getCenter()const
		{
			return this->center;
		}

		_FORCE_INLINE_ real_t getRadius()const
		{
			return this->radius;
		}

	private:
		real_t radius;
		std::shared_ptr<Material> material;
		Vector3 center;
	};

	// 通过 Collisionable 继承
	inline std::pair<bool, CollideRecord> Sphere::collision(const Ray& ray, const real_t& t_min, const real_t& t_max) const
	{
		Vector3 oc = ray.getOrigin() - this->center;		// 光源到圆心的向量

		real_t a = Vector3::dot(ray.getDirection(), ray.getDirection());
		real_t b = Vector3::dot(oc, ray.getDirection());		// oc在射线方向上的投影
		real_t c = Vector3::dot(oc, oc) - this->radius * this->radius;	// 光线穿过圆的弦
																		// discriminant
		real_t discriminant = b * b - a * c;
		if (discriminant > 0)
		{
			real_t t = (-b - sqrt(discriminant)) / a;
			if (t < t_min || t > t_max)
			{
				t = (-b + sqrt(discriminant)) / a;
			}
			if (t > t_min && t < t_max)
			{
				CollideRecord ret;
				ret.t = t;
				auto position = ray.pointAt(t);
				ret.position = position;
				ret.normal = (position - this->center) / this->radius;
				ret.material = this->material;
				return std::make_pair(true, ret);
			}
		}
		return std::make_pair(false, CollideRecord());
	}

}