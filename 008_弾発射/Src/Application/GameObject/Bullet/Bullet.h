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
private:
	Math::Vector3 m_pos = {};

	std::shared_ptr<KdModelData> m_spModel = {};
};