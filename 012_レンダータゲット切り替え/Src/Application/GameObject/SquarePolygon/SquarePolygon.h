#pragma once

class SquarePolygon :public KdGameObject
{
public:
	SquarePolygon() {}
	~SquarePolygon()override {}

	void Init()override;
	void Update()override;
	void DrawLit()override;
private:
	std::shared_ptr<KdSquarePolygon> m_spPoly;
};