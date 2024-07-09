#include "Moto.h"

void Moto::Init()
{
	m_spModel = std::make_shared<KdModelData>();
	m_spModel->Load("Asset/Models/enemy/moto/moto.gltf");
}
