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
		// ͨ�� Collisionable �̳�
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

	// ͨ�� Collisionable �̳�
	inline std::pair<bool, CollideRecord> Sphere::collision(const Ray& ray, const real_t& t_min, const real_t& t_max) const
	{
		Vector3 oc = ray.getOrigin() - this->center;

		// ���ߺ�Բ��ɵ�һԪ���η��̵�a,b,c����
		real_t a = ray.getDirection().lengthSquared();
		real_t halfB = Vector3::dot(oc, ray.getDirection());
		real_t c = oc.lengthSquared() - this->radius * this->radius;
		real_t discriminant = halfB * halfB - a * c;		// delta t
		CollideRecord ret;									// ��ײ���
		if (discriminant < 0)
		{
			return std::make_pair(false, ret);
		}

		auto sqrtd = std::sqrt(discriminant);
		real_t root = (-halfB - sqrtd) / a;					// ���㣬һԪ���η��̵������ʽ��Լ���˷��ӷ�ĸ�ĳ���2��,������Բ�ཻ��t
		if (root < t_min || t_max < root)
		{
			root = (-halfB + sqrtd) / a;					// ��t��Ϊ���Դ����ĵ�
			if (root < t_min || t_max < root)
			{
				return std::make_pair(false, ret);
			}
		}

		ret.t = root;
		ret.position = ray.pointAt(root);
		auto outwardNormal = (ret.position - this->center) / this->radius;
		ret.setFaceNormal(ray, outwardNormal);			// �÷��������䷽���෴
		ret.material = this->material;
		return std::make_pair(true, ret);
	}

}