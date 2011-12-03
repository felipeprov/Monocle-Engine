#pragma once
#include "Animation\Bones.h"
#include "Entity.h"

using namespace Animations;
using namespace Monocle;

namespace Monocle
{
	class BoneRender : public Entity
	{
	public:
		Bone* root;
		Bone* tmp;
		BoneRender();
		void Begin();
		virtual void Update();
		virtual void Render();
	};
}
