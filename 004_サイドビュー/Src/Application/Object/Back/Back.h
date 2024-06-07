#pragma once

class Back :public KdGameObject
{
public:
	Back() { Init(); }
	~Back()override{}

	void Init()override;
	void DrawUnLit()override;

private:
	KdSquarePolygon m_polygon;
};