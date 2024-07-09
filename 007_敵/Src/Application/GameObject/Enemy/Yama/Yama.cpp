#include "Yama.h"

void Yama::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/enemy/yama/yama.gltf");
}
