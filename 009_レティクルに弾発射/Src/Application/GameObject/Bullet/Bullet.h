#pragma once

class Bullet:public KdGameObject
{
public:
	Bullet() { Init(); }
	~Bullet()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void DrawBright()override;

	void SetPos(const Math::Vector3& _pos) { m_pos = _pos; }

	void SetParam(const Math::Vector3& _pos, const Math::Vector3& _dir, const float& _speed, const int& _lifeSpan);

private:
	Math::Vector3 m_pos = {};
	Math::Vector3 m_dir = {};
	float m_speed = {};
	int m_lifeSpan = {};

	std::shared_ptr<KdModelData> m_spModel = {};
};