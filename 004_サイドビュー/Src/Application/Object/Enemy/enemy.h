#pragma once

class Enemy :public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy() override{}

	void Update()override;
	void PostUpdate()override;
	
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

	void SetPos(int _i) { m_pos.x = _i; }

private:
	void Init()override;

	KdSquarePolygon m_polygon;

	Math::Vector3 m_pos;

	float m_anime = 0;

	float m_gravity = 0;

	float m_goal;
	Math::Vector3 m_dir = {};
	const float m_speed = 0.005f;
};