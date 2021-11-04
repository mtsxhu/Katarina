#pragma once
#include "Render/Collide/Collisionable.h"
#include "Render/Collide/CollideRecord.h"
namespace Katarina
{
	class KATARINA_API CollisionableList : public Collisionable {
	public:
		CollisionableList() {}
		CollisionableList(std::shared_ptr<Collisionable> object) { add(object); }

		void clear() { objects.clear(); }
		void add(std::shared_ptr<Collisionable> object) { objects.push_back(object); }

		virtual std::pair<bool, CollideRecord> collision(const Ray& ray, const real_t& t_min, const real_t& t_max) const override;

	private:
		std::vector<std::shared_ptr<Collisionable>> objects;
	};

	std::pair<bool, CollideRecord> CollisionableList::collision(const Ray& ray, const real_t& t_min, const real_t& t_max) const
	{
		CollideRecord temp_rec;
		auto hit_anything = false;
		auto closest_so_far = t_max;
		CollideRecord rec;
		for (const auto& object : objects) {
			auto [ok, temp_rec] = object->collision(ray, t_min, closest_so_far);
			if (ok) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}

		return std::make_pair(hit_anything, rec);
	}
}