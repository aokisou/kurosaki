#pragma once

class Player :public KdGameObject
{
public:
	Player() { Init(); }
	~Player()override{}

	void Update()override;
	void PostUpdate()override;

	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

private:
	void Init()override;

	KdSquarePolygon m_polygon;

	Math::Vector3 m_pos;

	float m_anime = 0;

	float m_gravity = 0;
};