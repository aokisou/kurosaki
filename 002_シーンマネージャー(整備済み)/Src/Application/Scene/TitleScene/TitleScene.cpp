#include "TitleScene.h"
#include "../SceneManager.h"

void TitleScene::Init()
{
	//テクスチャ読み込み
	m_titleTex.Load("Asset/Textures/title.png");
	m_startTex.Load("Asset/Textures/start.png");
}

void TitleScene::Update()
{
	m_angle += 0.05f;
	if (m_angle > 360) { m_angle -= 360; }

	m_alpha += m_alphaAdd;
	if (m_alpha > 1.f)
	{
		m_alpha = 1.f;
		m_alphaAdd *= -1;
	}
	if (m_alpha < 0.3f)
	{
		m_alpha = 0.3f;
		m_alphaAdd *= -1;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::Game);
	}
}

void TitleScene::Draw()
{
	//2D描画はSetMatrixが不要
	//※回転させる場合は必要
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_titleTex, 0, 0);
	Math::Color col = { 1,1,1,(abs)(sin(m_angle)) * 0.7f + 0.3f };
	//Math::Color col = { 1,1,1,m_alpha};
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_startTex, 0, -200, nullptr, &col);
}

void TitleScene::Release()
{
	m_titleTex.Release();
	m_startTex.Release();
}