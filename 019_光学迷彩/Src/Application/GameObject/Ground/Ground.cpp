#include "Ground.h"
#include "../../Scene/SceneManager.h"

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
	}
}

void Ground::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(SceneManager::Instance().GetRenderTargetTexture(), 300, 200, 360, 180);
}
