#include "GameScene.h"
#include"../SceneManager.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/Tank/Tank.h"
#include "../../GameObject/Enemy/Moto/Moto.h"
#include "../../GameObject/Enemy/Yama/Yama.h"
#include "../../GameObject/Bullet/Bullet.h"
#include "../../main.h"

void GameScene::Event()
{
	Application::Instance().m_log.Clear();
	Application::Instance().m_log.AddLog("objList : %d\n", (int)m_objList.size());
}

void GameScene::Init()
{
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	AddObject(ground);

	std::shared_ptr<Moto> m = std::make_shared<Moto>();
	m->SetPos({ 10,0,10 });
	AddObject(m);
	std::shared_ptr<Yama> y = std::make_shared<Yama>();
	y->SetPos({ -10,0,10 });
	AddObject(y);

	std::shared_ptr<Tank> tank = std::make_shared<Tank>();
	m->SetTarget(tank);
	y->SetTarget(tank);
	AddObject(tank);

	//std::shared_ptr<Bullet> b = std::make_shared<Bullet>();
	//AddObject(b);

	std::shared_ptr<TPSCamera> camera = std::make_shared<TPSCamera>();
	camera->Init();
	tank->SetCamera(camera);
	camera->SetTarget(tank);
	AddObject(camera);
}
