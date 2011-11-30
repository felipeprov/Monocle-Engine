#include "MoonocleGameScene.h"
#include <Monocle.h>
#include "Pong.h"
#include "LuaEntity.h"
#include "BoneRenderEntity.h"
#include "GwenEntity.h"

using namespace Monocle;
int luaRegisterGameScene(lua_State *L);
int luaRegisteEntity(lua_State *L);
int luaRegisterText(lua_State *L);

static int pmain (lua_State* L)
{
    luaL_openlibs(L);  

	luaRegisterGameScene(L); 
	luaRegisteEntity(L);
	luaRegisterText(L);

	lua_pushstring(L, "1.0.3");
	lua_setglobal(L, "version");

    return 0;
}


namespace Moonocle
{
	void GameScene::Begin()
	{
		Scene::Begin();

		lEnv = LuaEnvironment::getLuaEnv();
		lEnv->init();
		lEnv->pushFunction(pmain);
		lEnv->loadFile("../../content/moonocle/scripts/script.lua");

		levelEditor = new LevelEditor;

		Add(levelEditor);
		Graphics::SetBackgroundColor(Color::blue*0.2f + Color::white*0.8);

		boneRender = new BoneRender;
		Add(boneRender);
		boneRender->Begin();
		testeEntity = new LuaEntity;
		Add(testeEntity);

		Add(new GweenEntity);
	}

	void GameScene::End()
	{
	}

	void GameScene::Update()
	{
		Scene::Update();
		/*if(Input::IsKeyPressed(KEY_TAB))
		{
			isPaused = !isPaused;

			if(isPaused)
			{
				levelEditor->Enable();
			}
			else
			{
				levelEditor->Disable();
			}
		}*/

		testeEntity->position.x = boneRender->tmp->xAbs;
		testeEntity->position.y = boneRender->tmp->yAbs;
		testeEntity->rotation = boneRender->tmp->angleAbs;
		boneRender->tmp->angle += 1;
		boneRender->rotation += 0.01;
		//boneRender->root->length += 3*sin(2*3.14/360*boneRender->tmp->angle);
	}
}
