#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class LuaBinder
{
	lua_State *L;
public:
	LuaBinder(lua_State *L);
	~LuaBinder(void);

	void init(const char* tname, const char* bname, const luaL_reg* flist);
	void pushNumber(double v);
	double checkNumber(int index);

	void pushString(const char* s);
	const char* checkString(int index);

	void pushUserType(void *udata, const char* tname);
	void *checkUserType(int index, const char* tname);

	int checktype(void* udata, const char* name);
};

