#include "Render/Collide/CollisionableList.h"

namespace Katarina
{
	std::pair<bool, CollideRecord> CollisionableList::collision(const Ray& ray, const real_t& t_min, const real_t& t_max) const
	{
		CollideRecord tempRecord;		// 碰撞交点
		auto collide = false;			// 是否发生碰撞
		auto closestSoFar = t_max;		// 光线传输最远距离
		CollideRecord rec;				// 
		for (const auto& object : objects)
		{
			auto [ok, tempRecord] = object->collision(ray, t_min, closestSoFar);	// 物体与射线求交
			if (ok)
			{
				collide = true;
				closestSoFar = tempRecord.t;
				rec = tempRecord;
			}
		}

		return std::make_pair(collide, rec);
	}
}