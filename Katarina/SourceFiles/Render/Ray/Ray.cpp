#include "Render/Ray/Ray.h"
#include "Render/Collide/Collisionable.h"
namespace Katarina
{
	Vector3 Ray::spread(const Collisionable& world, int depth)const
	{
		// 限制光线传播次数，即递归次数
		if (depth <= 0)
			return Vector3(0, 0, 0);
		auto [collide, rec] = world.collision(*this, 0.001, INFINITY);
		if (collide) {
			auto [ok, attenuation, scattered] = rec.material->scatter(*this, rec);			// 如果当前射线有碰撞，则根据碰撞点的材质进行反射/折射
			if (ok)
				return attenuation * (scattered.spread(world, depth - 1));
			return Vector3(0, 0, 0);
		}

		Vector3 unit_direction = this->direction.normalize();
		auto t = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
	}

}