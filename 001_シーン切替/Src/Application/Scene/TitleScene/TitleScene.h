#pragma once

//継承に限りinclude OK
#include "../BaseScene/BaseScene.h"

class TitleScene:public BaseScene
{
public:
	TitleScene() { Init(); }
	~TitleScene() { Release(); }

	void Update()override;
	void Draw()override;
	
private:
	void Init()override;
	void Release()override;

	//テクスチャ(タイトル画面用)
	KdTexture m_titleTex;		//キャメル型
	//KdTexture m_title_tex;	//スネーク型
	KdTexture m_startTex;

	float m_alpha = .5f;
	float m_alphaAdd = .01f;

	float m_angle = 0.f;
};