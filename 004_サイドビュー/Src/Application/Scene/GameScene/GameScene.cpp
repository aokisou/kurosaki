#include "GameScene.h"
#include"../SceneManager.h"
#include "../../Object/Stage/Stage.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	Math::Matrix transMat, rotateXMat, rotateYMat, cameraMat;
	transMat = Math::Matrix::CreateTranslation(0, 5, -5);
	rotateXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(0));
	rotateYMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(0));
	cameraMat = rotateXMat * transMat * rotateYMat;

	m_camera->SetCameraMatrix(cameraMat);
}

void GameScene::Init()
{
	m_camera = std::make_unique<KdCamera>();

	std::shared_ptr<Stage> obj;
	obj = std::make_shared<Stage>();
	AddObject(obj);
}
