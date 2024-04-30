#include "SceneManager.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"

void SceneManager::PreUpdate()
{
	//シーン切り替え
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	//次のシーンを作成し、現在のシーンにする
	switch (_sceneType)
	{
	case SceneType::Title:
		//タイトルシーンを実体化
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::Game:
		//ゲームシーンを実体化
		m_currentScene = std::make_shared<GameScene>();
		break;
	}

	m_currentSceneType = _sceneType;
}
