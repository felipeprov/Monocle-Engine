#pragma once

#include <Monocle.h>
#include "LuaEnvironment.h"
#include "LevelEditor\LevelEditor.h"
#include "BoneRenderEntity.h"

using namespace Monocle;

namespace Moonocle
{
	class GameScene: public Scene
	{
		LuaEnvironment* lEnv;
		LevelEditor* levelEditor;
		BoneRender *boneRender;
		LuaEntity *testeEntity;
	public:
		void Begin();
		void End();
		void Update();
	};
}
