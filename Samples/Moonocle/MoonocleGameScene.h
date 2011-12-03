#pragma once

#include <Monocle.h>
#include <Lua/LuaEnvironment.h>
#include "LevelEditor\LevelEditor.h"
#include <Animation/BoneRenderEntity.h>

using namespace Monocle;

namespace Moonocle
{
	class GameScene: public Scene
	{
		Lua::LuaEnvironment* lEnv;
		LevelEditor* levelEditor;
		BoneRender *boneRender;
		Lua::LuaEntity *testeEntity;
	public:
		void Begin();
		void End();
		void Update();
	};
}
