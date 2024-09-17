#pragma once

#include "../EnemyBase/EnemyBase.h"

class Yama :public EnemyBase
{
public:
	Yama() { Init(); }
	~Yama()override {}

	void Init()override;
	void Update()override;

	void SetTarget(const std::shared_ptr<KdGameObject>& _wpTarget) { m_wpTarget = _wpTarget; }

private:
	std::weak_ptr<KdGameObject> m_wpTarget;
	float m_gravity = {};
};