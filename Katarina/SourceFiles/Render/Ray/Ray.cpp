#include "Render/Ray/Ray.h"
#include "Render/Collide/Collisionable.h"
namespace Katarina
{
	Vector3 Ray::spread(const Collisionable& world, int depth)const
	{
		// ���ƹ��ߴ������������ݹ����
		if (depth <= 0)
			return Vector3(0, 0, 0);
		auto [collide, rec] = world.collision(*this, 0.001, INFINITY);
		if (collide) {
			auto [ok, attenuation, scattered] = rec.material->scatter(*this, rec);			// �����ǰ��������ײ���������ײ��Ĳ��ʽ��з���/����
			if (ok)
				return attenuation * (scattered.spread(world, depth - 1));
			return Vector3(0, 0, 0);
		}

		Vector3 unit_direction = this->direction.normalize();
		auto t = 0.5 * (unit_direction.y + 1.0);
		return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
	}

}