#include "Cannon.h"

void Cannon::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Cannon2/Cannon.gltf");
	Math::Matrix scaleMat, rotateYMat, transMat;
	scaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 2.0f);
	rotateYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));
	transMat = Math::Matrix::CreateTranslation(-1.0f, -2.0f, 0);
	m_mWorld = scaleMat * rotateYMat * transMat;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("CannonCollision", m_model, KdCollider::Type::TypeGround);
}

void Cannon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
