#include "Bullet.h"

void Bullet::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Bullet/Bullet.gltf");
	m_spTPoly = std::make_shared<KdTrailPolygon>();
	m_spTPoly->SetMaterial("Asset/Textures/jet.png");
	//m_spTPoly->SetLength(200);
}

void Bullet::Update()
{
	m_lifeSpan--;
	if (m_lifeSpan < 0)
	{
		m_isExpired = true;
		return;
	}

	m_pos += m_dir * m_speed;

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;

	if (m_spTPoly)
	{
		m_spTPoly->AddPoint(m_mWorld);
	}
}

void Bullet::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}

	if (m_spTPoly)
	{
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spTPoly);
	}
}

void Bullet::DrawBright()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	}
}

void Bullet::SetParam(const Math::Vector3& _pos, const Math::Vector3& _dir, const float& _speed, const int& _lifeSpan)
{
	m_pos = _pos;
	m_dir = _dir;
	m_speed = _speed;
	m_lifeSpan = _lifeSpan;
}
