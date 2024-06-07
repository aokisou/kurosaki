#include "Back.h"

void Back::Init()
{
	m_polygon.SetMaterial("Asset/Textures/back.png");

	Math::Matrix scaleMat, transMat;
	scaleMat = Math::Matrix::CreateScale(300.0f,100.0f,1.0f);
	transMat = Math::Matrix::CreateTranslation(0, 0, 50);
	m_mWorld = scaleMat * transMat;
}

void Back::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}
