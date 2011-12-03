#pragma once
#include "LuaEntity.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#define LUA_CALLBACK_BEGIN(L,function) lua_getglobal(L,function)
#define LUA_CALLBACK_PUSH_ENTITY(ent) lua_rawgeti(L,LUA_REGISTRYINDEX, ent->luaId)
#define LUA_CALLBACK_PUSH_DOUBLE(d) lua_pushnumber(L,d)
#define LUA_CALLBACK_END(L, arg) if (lua_pcall(L,arg, 0, 0) != 0)\
		{\
			 fprintf(stderr, "error running function `f': %s",\
                 lua_tostring(L, -1));\
			 exit(1);\
		}
namespace Monocle
{
	namespace Lua
	{
		class LuaEnvironment
		{
		private:
			lua_State *L;
			static LuaEnvironment* luaenv;
			LuaEnvironment();
		public:
			~LuaEnvironment();
			lua_State* getLuaState(){return L;}
			void init();
			void loadFile(char* s);
			void pushFunction(lua_CFunction f);
			void callLuaFunction(char *s);
			static LuaEnvironment* getLuaEnv();

			void luaCallback(const char *function, LuaEntity* obj, char *type);
		};
	}
}