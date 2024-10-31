#include "Yama.h"

void Yama::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/enemy/yama/yama.gltf");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("HitBox", m_spModel, KdCollider::Type::TypeDamage);
}

void Yama::Update()
{
	if (!m_wpTarget.expired())
	{
		Math::Vector3 pos = m_wpTarget.lock()->GetPos() - GetPos();

		Math::Vector3 dir = pos;
		dir.Normalize();

		//m_degAngY = DirectX::XMConvertToDegrees();

		m_pos += dir * 0.05f;
	}

	m_gravity += 0.01f;
	m_pos.y -= m_gravity;
	if (m_pos.y < 0)
	{
		m_gravity = -0.3f;
		m_pos.y = 0;
	}

	EnemyBase::Update();
}
