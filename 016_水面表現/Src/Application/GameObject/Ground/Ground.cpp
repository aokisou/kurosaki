#include "Ground.h"

void Ground::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Ground/Ground.gltf");

	// 水面シェーダー5
	m_spNormalTex = std::make_shared<KdTexture>();
	m_spNormalTex->Load("Asset/Textures/water.png");

	KdShaderManager::Instance().m_StandardShader.WaterNormalTexture(*m_spNormalTex);

	Math::Matrix scaleMat,transMat;
	scaleMat = Math::Matrix::CreateScale(100);
	transMat = Math::Matrix::CreateTranslation(0,0,0);
	m_mWorld = scaleMat * transMat;
}

void Ground::DrawLit()
{
	if (m_spModel)
	{
		// 水面シェーダー8
		static Math::Vector2 offSet = Math::Vector2::Zero;
		offSet.x += 0.0001f;
		offSet.y += 0.0001f;
		if (offSet.x > 1)
		{
			offSet.x -= 1.f;
			offSet.y -= 1.f;
		}

		KdShaderManager::Instance().m_StandardShader.SetWaterUVOffSet(offSet);
		KdShaderManager::Instance().m_StandardShader.SetUVTiling({ 5, 5 });

		KdShaderManager::Instance().m_StandardShader.SetWaerEnable(true);
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}
