#include "EnemyBase.h"

void EnemyBase::Init()
{
}

void EnemyBase::Update()
{
	Math::Matrix rotateMat,transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void EnemyBase::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}
