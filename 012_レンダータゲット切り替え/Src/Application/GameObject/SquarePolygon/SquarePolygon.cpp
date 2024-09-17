#include "SquarePolygon.h"

#include "../../Scene/SceneManager.h"

void SquarePolygon::Init()
{
	m_spPoly = std::make_shared<KdSquarePolygon>();

	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 25, 0);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(50);
	m_mWorld = scaleMat * transMat;
}

void SquarePolygon::Update()
{
	if (m_spPoly)
	{
		m_spPoly->SetMaterial(SceneManager::Instance().GetRenderTargetTexture());
	}
}

void SquarePolygon::DrawLit()
{
	if (m_spPoly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly,m_mWorld);
	}
}
