#include "enemy.h"

#include "../../Scene/SceneManager.h"

void Enemy::Init()
{
	m_pos = { -20,0,0 };
	m_gravity = 1;
	m_dir = { 1,0,0 };
	m_goal = 0;
	m_polygon.SetMaterial("Asset/Textures/char.png");
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon.SetSplit(6, 6);
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyCollision", { 0,0.5f,0 }, 0.2f, KdCollider::Type::TypeBump);
}

void Enemy::Update()
{
	//ポイントライト(点光源)
	//最大100個まで
	//毎フレーム追加する必要がある(毎フレームリセットされるため)
	Math::Vector3 tmpPos = { 0,0.5f,0 };
	KdShaderManager::Instance().WorkAmbientController().AddPointLight({ 3,0,0 }, 5, m_pos + tmpPos, true);

	if (m_goal >= 5)
	{
		m_dir *= -1;
		m_goal = 0;
	}

	m_goal += m_speed;
	m_pos += m_dir * m_speed;

	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	int walk[4] = { 3,4,3,5 };
	m_polygon.SetUVRect(walk[(int)m_anime]);
	m_anime += 0.1f;

	if (m_anime >= 4)
	{
		m_anime = 0;
	}
}

void Enemy::PostUpdate()
{
	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3(0, 0.5f, 0), 0.2f, kGreenColor);
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
		m_pos = hitPos + Math::Vector3(0, -0.1f, 0);
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
		//自分とは当たり判定しない
		if (obj.get() != this)
		{
			obj->Intersects(sphere, &retSphereList);
		}
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

	Math::Matrix scaleMat,transMat;
	scaleMat = Math::Matrix::CreateScale(m_dir.x,1,1);
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = scaleMat * transMat;
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

