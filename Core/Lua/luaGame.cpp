
#include "LuaBinder.h"
#include "Game.h"

using namespace Monocle;
using namespace Lua;
namespace Monocle
{
	namespace Lua
	{
		static int luaGetGameScene(lua_State *L)
		{
			LuaBinder binder(L);

			Scene* scene = Game::GetScene();
			binder.pushUserType(scene,"GameScene");
    
			return 1; 
		}

		static int luaGameSceneAdd(lua_State *L)
		{
			LuaBinder binder(L);

			Scene* scene = (Scene*)binder.checkUserType(1,"GameScene");
			Entity* entity = (Entity*)binder.checkUserType(2,"Entity");
    
			scene->Add(entity);
			return 0; 
		}

		luaL_reg gameSceneFunctions[] =
		{
			{"GetCurrentScene", luaGetGameScene},
			{"Add", luaGameSceneAdd},
			{NULL,NULL}	
		};

		int luaRegisterGameScene(lua_State *L)
		{
			LuaBinder binder(L);
			binder.init("GameScene",0,gameSceneFunctions);

			return 1;
		}
	}
}