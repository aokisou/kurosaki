#pragma once

class Cannon :public KdGameObject
{
public:
	Cannon() { Init(); }
	~Cannon()override {}

	void Init()override;
	void DrawLit()override;

private:
	std::shared_ptr<KdModelData> m_model;
};