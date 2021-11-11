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
}