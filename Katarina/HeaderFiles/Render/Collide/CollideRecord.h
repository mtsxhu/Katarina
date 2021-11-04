#pragma once
#include "TypeDefines.h"
#include "Core/Math/Vector3.h"
#include "Render/Material/Material.h"
#include <memory>
namespace Katarina
{
	struct KATARINA_API CollideRecord
	{
		real_t t;			// ���߷��̵�t
		Vector3 position;	// ��ײ�����λ��
		Vector3 normal;		// ��ײ����ķ���
		std::shared_ptr<Material> material; // ��ײ����Ĳ���
		bool frontFace;
		real_t u;
		real_t v;
	};
}