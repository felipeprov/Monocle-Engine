#include "BoneRenderEntity.h"

namespace Moonocle
{
	BoneRender::BoneRender():root(0), tmp(0)
	{
		position.x = 200;
		position.y = 200;
	}

	void BoneRender::Begin()
	{
		root = Bone::create(NULL, 200, 200, 0,100); 
		tmp  = Bone::create(root, 0,0, 0, 100);
		tmp  = Bone::create(root, 0,0, 70, 100);
	}
	void BoneRender::Update()
	{
		Bone::Update(root, 0);
		root->x = position.x;
		root->y = position.y;
		root->angle = rotation*180/3.14;
	}
	void BoneRender::Render()
	{
		Bone::Render(root);
		Entity::Render();
	}
}
