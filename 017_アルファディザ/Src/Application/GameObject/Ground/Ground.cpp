#include "Ground.h"

void Ground::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Ground/Ground.gltf");

	m_spModelObj = std::make_shared<KdModelData>();
	m_spModelObj->Load("Asset/Models/map/map.gltf");

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
	}
	if (m_spModelObj)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModelObj);
	}
}
