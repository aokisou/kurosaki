#include "Moto.h"

void Moto::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/enemy/moto/moto.gltf");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("HitBox", m_spModel, KdCollider::Type::TypeDamage);
}

void Moto::Update()
{
	if (!m_wpTarget.expired())
	{
		Math::Vector3 pos = m_wpTarget.lock()->GetPos() - GetPos();

		Math::Vector3 dir = pos;
		dir.Normalize();

		//m_degAngY = DirectX::XMConvertToDegrees();

		m_pos += dir * 0.06f;
	}

	EnemyBase::Update();
}
