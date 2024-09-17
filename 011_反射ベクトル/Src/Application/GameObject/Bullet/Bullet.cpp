#include "Bullet.h"

#include "../../Scene/SceneManager.h"

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

void Bullet::PostUpdate()
{
	if (m_isExpired) { return; }

	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Radius = 0.5f;
	sphere.m_type = KdCollider::Type::TypeGround | KdCollider::Type::TypeDamage;

	std::list<KdCollider::CollisionResult> retList;

	float maxOverLap = 0.f;
	Math::Vector3 normal = Math::Vector3::Zero;
	bool isHit = false;

	for (const auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, &retList))
		{
			isHit = true;

			for (const auto& ret : retList)
			{
				if (maxOverLap < ret.m_overlapDistance)
				{
					maxOverLap = ret.m_overlapDistance;
					normal = ret.m_hitNormal;
				}
			}

			retList.clear();
		}
	}

	if (isHit)
	{
		//反射ベクトルを求める
		float a = -m_dir.Dot(normal);

		Math::Vector3 r = m_dir + 2 * a * normal;

		r.Normalize();

		m_dir = r;
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
