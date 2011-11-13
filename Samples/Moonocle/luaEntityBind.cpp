
#include "LuaBinder.h"
#include "LuaEntity.h"

using namespace Monocle;
using namespace Moonocle;
static int luaEntityCreate(lua_State *L)
{
	LuaBinder binder(L);

	LuaEntity* entity = new LuaEntity;
	binder.pushUserType(entity,"Entity");
    
	return 1; 
}

static int luaEntitySetPosition(lua_State *L)
{
	LuaBinder binder(L);

	LuaEntity* entity = (LuaEntity*)binder.checkUserType(1, "Entity");

	double x = binder.checkNumber(2);
	double y = binder.checkNumber(3);

	entity->position = Vector2(x,y);

	return 0;
}

static int luaEntityGetPosition(lua_State *L)
{
	LuaBinder binder(L);

	LuaEntity* entity = (LuaEntity*)binder.checkUserType(1, "Entity");

	binder.pushNumber(entity->position.x);
	binder.pushNumber(entity->position.y);

	return 2;
}

luaL_reg entityFunctions[] =
{
	{"new", luaEntityCreate},
	{"setPosition", luaEntitySetPosition},
	{"getPosition", luaEntityGetPosition},
	{NULL,NULL}	
};

int luaRegisteEntity(lua_State *L)
{
	LuaBinder binder(L);
	binder.init("Entity",0,entityFunctions);

	return 1;
}