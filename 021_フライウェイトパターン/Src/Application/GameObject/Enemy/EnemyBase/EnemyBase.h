#pragma once

class EnemyBase :public KdGameObject
{
public:
	EnemyBase(){}
	virtual ~EnemyBase()override{}

	void Init()override;
	void Update()override;
	void DrawLit()override;

	void OnHit()override { m_isExpired = true; }

	void SetPos(const Math::Vector3& _pos) { m_pos = _pos; }

protected:
	Math::Vector3 m_pos = {};
	float m_degAngY = {};

	std::shared_ptr<KdModelData> m_spModel = {};
};