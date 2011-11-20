#include "LuaBinder.h"
#include <cstring>

LuaBinder::LuaBinder(lua_State *L)
{
	this->L = L;
}


LuaBinder::~LuaBinder(void)
{
}

void LuaBinder::init(const char* tname, const char* bname, const luaL_reg* flist)
{
	lua_newtable(L);
	lua_pushstring(L,"v");
	lua_setfield(L,-2,"__mode");
	lua_pushvalue(L,-1);
	lua_setmetatable(L,-2);
	lua_replace(L,LUA_ENVIRONINDEX);
	luaL_register(L,tname, flist);
	luaL_newmetatable(L,tname);
	lua_pushvalue(L,-2);
	lua_setfield(L,-2,"__index");
//	lua_pushcfunction(L,0);
//    lua_setfield(L,-2,"__gc");  
	if (bname) {
        luaL_getmetatable(L,bname);
        lua_setfield(L,-2,"_base");   // mt._base = base mt
     }
     lua_pop(L,1);                    // pop metatable
     if (bname) {
		lua_getfield(L,LUA_GLOBALSINDEX,bname);
		lua_setfield(L,-2,"__index"); // libtable.__index = base libtable
		lua_pushvalue(L,-1);          // duplicate libtable
		lua_setmetatable(L,-2);       // set itself as metatable
	 }
}

void LuaBinder::pushNumber(double v)
{
	lua_pushnumber(L,v);
}

double LuaBinder::checkNumber(int index)
{
	return luaL_checknumber(L, index);
}

void LuaBinder::pushString(const char* s)
{
	lua_pushstring(L,s);
}

const char* LuaBinder::checkString(int index)
{
	return luaL_checkstring(L,index);
}

int LuaBinder::pushUserType(void *udata, const char* tname)
{
	lua_pushlightuserdata(L,udata);
	lua_rawget(L,LUA_ENVIRONINDEX);

	int reference=0;
	if( lua_isnil(L,-1))
	{
		lua_newtable(L);
		lua_pushlightuserdata(L,udata);
		lua_setfield(L,-2,"_pointer");
		luaL_getmetatable(L,tname);
		lua_setmetatable(L,-2);
		lua_pushlightuserdata(L,udata);
		lua_pushvalue(L,-2);
		lua_rawset(L,LUA_ENVIRONINDEX);
	}
	int id = luaL_ref(L, LUA_REGISTRYINDEX);
	lua_rawgeti(L, LUA_REGISTRYINDEX, id);
	return id;
}

void* LuaBinder::checkUserType(int index, const char* tname)
{

#if 0
	void **udata = (void**)luaL_checkudata(L,index,tname);

	if(udata==0 )
		luaL_typerror(L, index, tname);
	return *udata;
#else

	lua_getfield(L,LUA_REGISTRYINDEX,tname);
	lua_getmetatable(L,index);

	while(lua_istable(L,-1))
	{
		if(lua_rawequal(L,-1,-2))
		{
			lua_pop(L,2);
			lua_getfield(L,index,"_pointer");
			void* udata =lua_touserdata(L,-1);
			return udata;
		}
		lua_getfield(L,-1,"_base");          // get mt._base
        lua_replace(L,-2);                   // replace: mt = mt._base
	}

	luaL_typerror(L,index,tname);
	return NULL;
#endif
}

int LuaBinder::checktype(void* udata, const char* tname)
{
	lua_pushlightuserdata(L,udata);
	lua_rawget(L,LUA_ENVIRONINDEX);
	const char* stored_tname = lua_tostring(L,-1);
	int result  = stored_tname && strcmp(stored_tname, tname) == 0;;
	lua_pop(L,1);
	return result;
};
