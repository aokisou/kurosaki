﻿#pragma once

class Ground :public KdGameObject
{
public:
	Ground() { Init(); }
	~Ground()override {}

	void Init()override;
	void DrawLit()override;
	void DrawSprite()override;

private:
	std::shared_ptr<KdModelData> m_spModel = {};
};