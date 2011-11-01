#pragma once

#include <Monocle.h>
#include "LuaEnvironment.h"

using namespace Monocle;

namespace Moonocle
{
	class GameScene: public Scene
	{
		LuaEnvironment* lEnv;
	public:
		void Begin();
		void End();
		void Update();
	};
}
