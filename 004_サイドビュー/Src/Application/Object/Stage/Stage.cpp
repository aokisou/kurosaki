#include "Stage.h"

void Stage::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/SideViewMap/SideViewMap.gltf");
	Math::Matrix scaleMat, transMat;
	scaleMat = Math::Matrix::CreateScale(5.0f, 1.0f, 1.0f);
	transMat = Math::Matrix::CreateTranslation(0, -1.5f, 0);
	m_mWorld = scaleMat * transMat;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("StageCollision", m_model,KdCollider::Type::TypeGround);
}

void Stage::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}
