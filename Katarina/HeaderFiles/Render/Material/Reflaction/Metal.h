#pragma once
#include "Render/Material/Material.h"
#include "Core/Math/Vector3.h"
#include "Render/Ray/Ray.h"
#include "Render/Collide/CollideRecord.h"
#include <tuple>
namespace Katarina
{
	class KATARINA_API Metal :public Material
	{
	public:
		Metal(const Vector3& albedo, real_t fuzzy)
		{
			this->albedo = albedo;
			this->fuzzy = fuzzy;
		}

		virtual std::tuple<bool, Vector3, Ray> scatter(const Ray& in, const CollideRecord& rec) const override
		{
			auto inNormal = in.getDirection().normalize();		// ��������
			Vector3 reflected = inNormal.reflect(rec.normal);	// ��������
			auto scattered = Ray(rec.position, reflected + this->fuzzy * Math::RandomInUnitSphere());			// �������
			auto attenuation = albedo;								// ��ǿ������
			auto effect = Vector3::dot(scattered.getDirection(), rec.normal) > 0;	// ��������뷨�߼нǴ���90��
			return std::make_tuple(effect, attenuation, scattered);
		}
	};
}

