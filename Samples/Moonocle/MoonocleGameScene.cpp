#include "MoonocleGameScene.h"
#include <Monocle.h>

using namespace Monocle;

static int pmain (lua_State* L)
{
    luaL_openlibs(L);  

	lua_pushstring(L, "1.0.3");
	lua_setglobal(L, "version");

    return 0;
}


namespace Moonocle
{
	void GameScene::Begin()
	{
		lEnv = LuaEnvironment::getLuaEnv();
		lEnv->init();
		lEnv->pushFunction(pmain);
		lEnv->loadFile("../../content/moonocle/scripts/script.lua");
	}

	void GameScene::End()
	{
	}

	void GameScene::Update()
	{
	}
}
