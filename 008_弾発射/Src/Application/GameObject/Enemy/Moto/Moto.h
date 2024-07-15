#pragma once

#include "../EnemyBase/EnemyBase.h"

class Moto :public EnemyBase
{
public:
	Moto() { Init(); }
	~Moto()override{}

	void Init()override;
	void Update()override;

	void SetTarget(const std::shared_ptr<KdGameObject>& _wpTarget) { m_wpTarget = _wpTarget; }

private:
	std::weak_ptr<KdGameObject> m_wpTarget;
};