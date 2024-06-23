#include "Player.h"
#include "../../Scene/SceneManager.h"

void Player::Init()
{
	m_pos = {-10,0,0};
	m_gravity = 1;
	m_polygon.SetMaterial("Asset/Textures/char.png");
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon.SetSplit(6, 6);
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 0.1f;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_gravity = -0.1f;
	}

	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	int run[4] = { 24,25,24,26 };
	m_polygon.SetUVRect(run[(int)m_anime]);
	//m_anime += 0.1f;

	//if (m_anime >= 4)
	//{
	//	m_anime = 0;
	//}
}

void Player::PostUpdate()
{
	//===================
	//レイ判定
	//===================

	//レイ判定用の変数
	KdCollider::RayInfo ray;
	//レイの発射位置を設定
	ray.m_pos = m_pos;
	//レイの発射方向を設定
	ray.m_dir = Math::Vector3::Down;//真下
	//当たり判定をしたいタイプを設定
	ray.m_type = KdCollider::Type::TypeGround;

	//レイの長さを設定
	float enableStepHigh = 0.2f;
	//少し高いところから設定
	ray.m_pos.y += enableStepHigh;
	ray.m_range = m_gravity + enableStepHigh;
	//レイに当たったオブジェクト情報
	std::list<KdCollider::CollisionResult> retRayList;

	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	//レイと当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(ray, &retRayList);
	}

	//レイリストから一番近いオブジェクトを検出
	float maxOverLap = 0;	//はみ出たレイの長さ
	Math::Vector3 hitPos;	//レイが遮断された座標(当たった座標
	bool isHit = false;		
	for (auto& ret : retRayList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			isHit = true;
		}
	}

	if (isHit)
	{
		m_pos = hitPos + Math::Vector3(0,-0.1f,0);
		m_gravity = 0;
	}

	//===================
	//球判定
	//===================
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Radius = 0.3f;
	
	sphere.m_sphere.Center.y += 0.5f;

	sphere.m_type = KdCollider::Type::TypeGround | KdCollider::Type::TypeBump;

	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	std::list<KdCollider::CollisionResult> retSphereList;

	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(sphere, &retSphereList);
	}

	//球リストから一番近いオブジェクトを検出
	maxOverLap = 0;	//はみ出たレイの長さ
	isHit = false;
	Math::Vector3 hitDir;
	for (auto& ret : retSphereList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			isHit = true;
		}
	}

	if (isHit)
	{
		//ステージよりも後ろや前に行ってしまうのを防ぐために
		//奥行きをなくす
		hitDir.z = 0;
		//方向ベクトルの長さは1にする必要がある
		hitDir.Normalize();
		m_pos += hitDir * maxOverLap;
		//当たったときにy軸にめり込んでいたら
		if (hitDir.y > 0)
		{
			m_gravity = 0;
		}
	}

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Player::DrawLit()
{
	//ディゾルブ(解けた感じの表現)
	static float d = 0;
	//d += 0.01f;
	//if (d > 1.0f)
	//{
	//	d = 0.0f;
	//}

	d -= 0.01f;
	if (d < 0.0f)
	{
		d = 1.0f;
	}

	KdShaderManager::Instance().m_StandardShader.SetDissolve(d);

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}
