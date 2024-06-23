#include "GameScene.h"

#include"../SceneManager.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Cannon/Cannon.h"
#include "../../Object/Back/Back.h"
#include "../../Object/Enemy/enemy.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	//プレイヤーの座標が必要
	//オブジェクトリストからプレイヤー情報を取得する
	//プレイヤー情報がゲームシーンが持っておく

	Math::Vector3 plyPos = {};
	//プレイヤーにまだアドレスはありますか？
	//期限は有効ですか？ true:はい false:いいえ
	if (!m_player.expired())
	{
		plyPos = m_player.lock()->GetPos();
	}

	Math::Matrix transMat;
	Math::Vector3 cameraPos = { 2, 1.5f, -5.0f };
	transMat = Math::Matrix::CreateTranslation(cameraPos + plyPos);
	
	m_camera->SetCameraMatrix(transMat);

	//被写界深度
	//m_camera->SetFocus(5,2,8);

	//ブルーム
	//KdShaderManager::Instance().m_postProcessShader.SetBrightThreshold(0.7f);
}

void GameScene::Init()
{
	m_camera = std::make_unique<KdCamera>();

	//平行光(ディレクショナルライト)                                方向	//色
	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0,-1,0.1f }, { 3,3,3 });

	//画面全体が暗いとき
	//環境光(アンビエントライト)
	//KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 1,1,1,1 });

	//フォグ(霧)
	//KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
	//																	//霧の色　　密度
	//KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 1,1,1 }, 0.05f);
	//																//霧の色　　上　下　カメラとの距離
	//KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 1,1,1 }, 0, -2, 0);

	std::shared_ptr<Stage> stg;
	for (int i = 0; i < 5; i++)
	{
		stg = std::make_shared<Stage>();
		stg->SetPos({ 0,-2.0f,3.0f * i });
		AddObject(stg);
	}

	for (int i = 0; i < 5; i++)
	{
		stg = std::make_shared<Stage>();
		stg->SetPos({ 0,-2.0f + 5.0f * i,0 });
		AddObject(stg);
	}

	std::shared_ptr<Player> ply;
	ply = std::make_shared<Player>();
	AddObject(ply);
	m_player = ply;

	std::shared_ptr<Cannon> cannon;
	cannon = std::make_shared<Cannon>();
	AddObject(cannon);

	std::shared_ptr<Back> back;
	back = std::make_shared<Back>();
	AddObject(back);

	float posX = -25;
	std::shared_ptr<Enemy> enemy;
	for (int i = 0; i < 5; i++)
	{
		enemy = std::make_shared<Enemy>();
		enemy->SetPos(posX + i);
		AddObject(enemy);
	}
}
