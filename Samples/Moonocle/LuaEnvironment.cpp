#include "LuaEnvironment.h"
#include <stdio.h>
#include <stdlib.h>
#include "LuaBinder.h"
#include "LuaEntity.h"
namespace Moonocle
{
	LuaEnvironment* LuaEnvironment::luaenv = NULL;

	LuaEnvironment* LuaEnvironment::getLuaEnv()
	{
		if(luaenv == NULL)
			luaenv = new LuaEnvironment;

		return luaenv;
	}

	LuaEnvironment::~LuaEnvironment()
	{
		lua_close(L);
	}
	LuaEnvironment::LuaEnvironment()
	{
		L= NULL;
	}

	void LuaEnvironment::init()
	{
		L= lua_open();
		luaL_openlibs(L);
	}

	void LuaEnvironment::loadFile(char* s)
	{
		if (luaL_loadfile(L, s) || lua_pcall(L, 0, 0, 0))
        printf("cannot run configuration file: %s",
                 lua_tostring(L, -1));
	}

	void LuaEnvironment::pushFunction(lua_CFunction f)
	{
		lua_pushcfunction(L,f);
		if (lua_pcall(L,0,0,0)) {
			fprintf(stderr,"%s\n",lua_tostring(L,-1));
			exit(1);
		}
	}

	void LuaEnvironment::callLuaFunction(char *s)
	{
		lua_getglobal(L,s);
		if (lua_pcall(L,0, 0, 0) != 0)
		{
			 fprintf(stderr, "error running function `f': %s",
                 lua_tostring(L, -1));
			 exit(1);
		}
	}

	void LuaEnvironment::luaCallback(const char *function, LuaEntity* obj, char *type)
	{
		LUA_CALLBACK_BEGIN(L,function);
		LUA_CALLBACK_PUSH_ENTITY(obj);
		//com isso podemos pegar referencias para os objetos de interesse
		LUA_CALLBACK_END(L,0);
	}
}