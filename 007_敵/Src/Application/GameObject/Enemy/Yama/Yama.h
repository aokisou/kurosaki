#pragma once

#include "../EnemyBase/EnemyBase.h"

class Yama :public EnemyBase
{
public:
	Yama() { Init(); }
	~Yama()override {}

	void Init()override;
};