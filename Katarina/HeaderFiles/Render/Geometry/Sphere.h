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
		Vector3 oc = ray.getOrigin() - this->center;

		// 光线和圆组成的一元二次方程的a,b,c参数
		real_t a = ray.getDirection().lengthSquared();
		real_t halfB = Vector3::dot(oc, ray.getDirection());
		real_t c = oc.lengthSquared() - this->radius * this->radius;
		real_t discriminant = halfB * halfB - a * c;		// delta t
		CollideRecord ret;									// 碰撞结果
		if (discriminant < 0)
		{
			return std::make_pair(false, ret);
		}

		auto sqrtd = std::sqrt(discriminant);
		real_t root = (-halfB - sqrtd) / a;					// 交点，一元二次方程的求根公式（约掉了分子分母的常数2）,光线与圆相交的t
		if (root < t_min || t_max < root)
		{
			root = (-halfB + sqrtd) / a;					// 将t设为离光源最近的点
			if (root < t_min || t_max < root)
			{
				return std::make_pair(false, ret);
			}
		}

		ret.t = root;
		ret.position = ray.pointAt(root);
		auto outwardNormal = (ret.position - this->center) / this->radius;
		ret.setFaceNormal(ray, outwardNormal);			// 让法线与入射方向相反
		ret.material = this->material;
		return std::make_pair(true, ret);
	}

}