#include "Bullet.h"

void Bullet::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/Bullet/Bullet.gltf");
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
}

void Bullet::DrawLit()
{
	if (m_spModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
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
