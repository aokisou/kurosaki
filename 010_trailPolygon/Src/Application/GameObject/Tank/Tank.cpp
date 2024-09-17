#include "Tank.h"

#include "../Camera/CameraBase.h"
#include "../../main.h"
#include "../../Scene/SceneManager.h"
#include "../Bullet/Bullet.h"

void Tank::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/tank/tank.gltf");

	m_spRetTex = std::make_shared<KdTexture>();
	m_spRetTex->Load("Asset/Textures/Reticle.png");

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;

	m_spTPoly = std::make_shared<KdTrailPolygon>();
	m_spTPoly->SetMaterial("Asset/Textures/jet.png");
	m_spTPoly->SetLength(200);
}

void Tank::Update()
{
	m_moveDir = {};//回転したい方向のリセット
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_moveDir += Math::Vector3::Backward;
	}	
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_moveDir += Math::Vector3::Forward;
	}	
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_moveDir += Math::Vector3::Left;
	}	
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_moveDir += Math::Vector3::Right;
	}

	if (!m_wpCamera.expired())
	{
		m_moveDir = m_moveDir.TransformNormal(m_moveDir, m_wpCamera.lock()->GetRotationYMatrix());
	}

	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
	{
		m_bTPS = true;
	}
	else
	{
		m_bTPS = false;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		std::shared_ptr<Bullet> b = std::make_shared<Bullet>();
		if (m_bTPS)
		{
			const std::shared_ptr<CameraBase> camera = m_wpCamera.lock();
			Math::Vector3 camPos = Math::Vector3::Zero;
			Math::Vector3 rayDir = Math::Vector3::Zero;
			float range = 0.f;
			if (camera)
			{
				camPos = camera->GetPos();
				camera->GetCamera()->GenerateRayInfoFromClientPos({ 640,360 }, camPos, rayDir, range);
			}

			Math::Vector3 pos;
			pos = m_pos + m_mWorld.Backward() * Math::Vector3(3, 0, 3);
			pos.y += 2;
			b->SetParam(pos, rayDir, 1, 1000);
		}
		else
		{
			Math::Vector3 pos;
			pos = m_pos + m_mWorld.Backward() * Math::Vector3(3, 0, 3);
			pos.y += 2;
			b->SetParam(pos, m_mWorld.Backward(), 1, 1000);
		}

		SceneManager::Instance().AddObject(b);
	}

	Math::Matrix rotMat;

	if (m_bTPS)
	{
		//TPS
		m_moveDir.Normalize();

		rotMat = m_wpCamera.lock()->GetRotationYMatrix();
	}
	else
	{
		//TPV
		//移動していたら
		if (m_moveDir.LengthSquared())
		{
			m_moveDir.Normalize();

			Math::Matrix rotYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle.y));

			//キャラの正面方向ベクトル
			Math::Vector3 nowDir = Math::Vector3::TransformNormal(Math::Vector3::Backward, rotYMat);
			nowDir.Normalize();

			//移動方向のベクトル
			Math::Vector3 targetDir = m_moveDir;
			targetDir.Normalize();

			//内積
			//ベクトルA * ベクトルB * cosθ
			//	 1      *     1     * cosθ
			float d = nowDir.Dot(targetDir);

			//丸め誤差の都合上「1」を超える可能性があるクランプ(遮断)する
			d = std::clamp(d, -1.0f, 1.0f);

			float ang = DirectX::XMConvertToDegrees(acos(d));

			if (ang >= 0.1f)
			{
				if (ang > 5)
				{
					ang = 5;
				}
				//外積
				//二つのベクトルに対し垂直に伸びるベクトル
				Math::Vector3 c = targetDir.Cross(nowDir);
				c.Normalize();
				if (c.y >= 0)
				{
					m_angle.y -= ang;
					if (m_angle.y < 0)
					{
						m_angle.y += 360;
					}
				}
				else
				{
					m_angle.y += ang;
					if (m_angle.y >= 360)
					{
						m_angle.y -= 360;
					}
				}
			}
		}

		rotMat = Math::Matrix::CreateFromYawPitchRoll((DirectX::XMConvertToRadians(m_angle.y)),
			(DirectX::XMConvertToRadians(m_angle.x)),
			(DirectX::XMConvertToRadians(m_angle.z)));
	}

	m_pos += m_moveDir * 0.1f;

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = rotMat * transMat;

	if (m_moveDir.LengthSquared())
	{
		if (m_spTPoly)
		{
			Math::Vector3 pos = m_pos;
			pos.y += 0.1f;
			Math::Matrix mat = m_mWorld;
			mat.Translation(pos);
			m_spTPoly->AddPoint(mat);
		}
	}
}

void Tank::PostUpdate()
{
	if (m_moveDir.LengthSquared())
	{
		KdCollider::SphereInfo sphere;
		sphere.m_sphere.Center = m_pos;
		sphere.m_sphere.Center.y += 1.0f;
		sphere.m_sphere.Radius = 2.f;
		sphere.m_type = KdCollider::Type::TypeDamage;

		m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

		for (const auto& obj : SceneManager::Instance().GetObjList())
		{
			if (obj->Intersects(sphere, nullptr))
			{
				obj->OnHit();
			}
		}
	}
}

void Tank::DrawLit()
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

void Tank::DrawSprite()
{
	if (m_spRetTex)
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spRetTex, 0, 0);
	}
}
