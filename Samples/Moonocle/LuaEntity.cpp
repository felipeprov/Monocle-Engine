
#include "LuaEntity.h"
#include "LuaEnvironment.h"

using namespace std;
namespace Moonocle
{
	LuaEntity::LuaEntity()
	{
	}

	void LuaEntity::Update()
	{
		string ev = scripts["OnUpdate"];
		if(ev !="")
		{
			LuaEnvironment *luaEnv = LuaEnvironment::getLuaEnv();
			lua_State *L = luaEnv->getLuaState();

			LUA_CALLBACK_BEGIN(L,ev.c_str());
				LUA_CALLBACK_PUSH_ENTITY(this);
				LUA_CALLBACK_PUSH_DOUBLE(Monocle::deltaTime);
			LUA_CALLBACK_END(L,2);
		}
	}

	void LuaEntity::Render()
	{
		Graphics::BindTexture(NULL);
		Graphics::PushMatrix();
		Graphics::Translate(position.x,position.y,0);
		Graphics::Rotate(rotation,0,0,1.0);
        Graphics::SetColor(Color::blue);

		Monocle::Vector2 vec = Monocle::Graphics::GetMatrixPosition();
		//std::cout<<"E:"<<" "<<vec.x<<" "<<vec.y<<std::endl;
		Graphics::RenderQuad(25, 100.0f);
		Graphics::PopMatrix();

		Entity::Render();
	}
}