#include "Render/Collide/CollisionableList.h"

namespace Katarina
{
	std::pair<bool, CollideRecord> CollisionableList::collision(const Ray& ray, const real_t& t_min, const real_t& t_max) const
	{
		CollideRecord tempRecord;		// ��ײ����
		auto collide = false;			// �Ƿ�����ײ
		auto closestSoFar = t_max;		// ���ߴ�����Զ����
		CollideRecord rec;				// 
		for (const auto& object : objects)
		{
			auto [ok, tempRecord] = object->collision(ray, t_min, closestSoFar);	// ������������
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