#pragma once

#include "../BaseScene/BaseScene.h"

class GameScene :public BaseScene
{
public:
	GameScene() { Init(); }
	~GameScene() { Release(); }

	void Update()override;
	void Draw()override;

private:
	void Init()override;
	void Release()override;

	KdTexture m_tex;
};