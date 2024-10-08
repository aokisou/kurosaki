﻿#pragma once

class CameraBase;

class Tank :public KdGameObject
{
public:
	Tank() { Init(); }
	~Tank()override{}

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void DrawSprite()override;

	void SetCamera(const std::shared_ptr<CameraBase>& _spCamera) { m_wpCamera = _spCamera; }
private:
	Math::Vector3 m_pos = {};
	Math::Vector3 m_moveDir = {};

	Math::Vector3 m_angle = {};

	std::shared_ptr<KdModelData> m_spModel = {};
	std::weak_ptr<CameraBase> m_wpCamera;
	std::shared_ptr<KdTexture> m_spRetTex;

	bool m_bTPS = false;

	std::shared_ptr<KdTrailPolygon> m_spTPoly = nullptr;
};