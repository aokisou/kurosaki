#pragma once

#include "../EnemyBase/EnemyBase.h"

class Moto :public EnemyBase
{
public:
	Moto() { Init(); }
	~Moto()override{}

	void Init()override;
};