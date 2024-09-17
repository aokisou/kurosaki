#include "GameScene.h"
#include"../SceneManager.h"
#include "../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include "../../GameObject/Ground/Ground.h"
#include "../../GameObject/Tank/Tank.h"
#include "../../GameObject/SquarePolygon/SquarePolygon.h"

void GameScene::Event()
{
}

void GameScene::Init()
{
	std::shared_ptr<Tank> tank = std::make_shared<Tank>();
	AddObject(tank);

	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	AddObject(ground);

	std::shared_ptr<SquarePolygon> poly = std::make_shared<SquarePolygon>();
	poly->Init();
	AddObject(poly);

	std::shared_ptr<TPSCamera> camera = std::make_shared<TPSCamera>();
	camera->Init();
	tank->SetCamera(camera);
	camera->SetTarget(tank);
	AddObject(camera);
}
