#include "GameScene.h"

void GameScene::Update()
{

}

void GameScene::Draw()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0);
}

void GameScene::Init()
{
	m_tex.Load("Asset/Textures/player.png");
}

void GameScene::Release()
{
}