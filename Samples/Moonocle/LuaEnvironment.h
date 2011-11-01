#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace Moonocle
{
	class LuaEnvironment
	{
	private:
		lua_State *L;
		static LuaEnvironment* luaenv;
		LuaEnvironment();
	public:
		~LuaEnvironment();
		void init();
		void loadFile(char* s);
		void pushFunction(lua_CFunction f);
		void callLuaFunction(char *s);

		static LuaEnvironment* getLuaEnv();
	};
}