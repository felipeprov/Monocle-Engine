#include "LuaBinder.h"
#include "Pong.h"

using namespace Pong;

static int luaTextNew(lua_State *L)
{
    LuaBinder binder(L);

	FontAsset* font = Assets::RequestFont("Pong/LiberationSans-Regular.ttf", 25.0f);
	Text* scoreText = new Text(binder.checkString(1), font);
	binder.pushUserType(scoreText,"Text");
    
	return 1; 
}

static int luaTextSetPosition(lua_State *L)
{
    LuaBinder binder(L);

	Text* text = (Text*)binder.checkUserType(1,"Text");
	double x = binder.checkNumber(2);
	double y = binder.checkNumber(3);

	text->position = Vector2(x,y);
    
	return 0; 
}


luaL_reg textFunctions[] =
{
	{"new", luaTextNew},
	//{"Position", luaTextSetPosition},
	{NULL,NULL}	
};

 int luaRegisterText(lua_State *L)
{
	LuaBinder binder(L);
	binder.init("Text","Entity",textFunctions);

	return 1;
}