#include "Stage.h"

void Stage::Init()
{
	m_model.Load("Asset/Models/SideViewMap/SideViewMap.gltf");
	m_mWorld = Math::Matrix::CreateTranslation(0, 0, 10);
}

void Stage::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model,m_mWorld);
}
