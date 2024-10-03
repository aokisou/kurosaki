#include "Ground.h"

void Ground::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Ground/Ground.gltf");

	Math::Matrix scaleMat,transMat;
	scaleMat = Math::Matrix::CreateScale(100);
	transMat = Math::Matrix::CreateTranslation(0,0,0);
	m_mWorld = scaleMat * transMat;
}

void Ground::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
		Math::Matrix mat = m_mWorld * Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, mat);
	}
}
