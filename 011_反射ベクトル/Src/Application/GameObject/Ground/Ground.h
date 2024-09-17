﻿#pragma once

class Ground :public KdGameObject
{
public:
	Ground() { Init(); }
	~Ground()override {}

	void Init()override;
	void DrawUnLit()override;

private:
	std::shared_ptr<KdModelData> m_spModel = {};
};