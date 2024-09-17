#include "Ground.h"

void Ground::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Ground_r/Ground_r.gltf");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("ground", m_spModel, KdCollider::Type::TypeGround);

	Math::Matrix scaleMat,transMat;
	scaleMat = Math::Matrix::CreateScale(100);
	transMat = Math::Matrix::CreateTranslation(0,0,0);
	m_mWorld = scaleMat * transMat;
}

void Ground::DrawUnLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}
