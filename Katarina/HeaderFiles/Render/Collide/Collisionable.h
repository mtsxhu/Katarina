#pragma once
#include "Core/Math/Vector3.h"
#include "Render/Ray/Ray.h"
#include "Render/Material/Material.h"
#include <tuple>
#include <memory>
namespace Katarina
{
	class KATARINA_API Collisionable
	{
	public:
		Collisionable() = default;
		virtual ~Collisionable() {}
		// tMin��tMax�����������߳���
		virtual std::pair<bool, CollideRecord> collision(const Ray& ray, const real_t& t_min, const real_t& t_max) const = 0;
	};




}

