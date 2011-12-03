#include "LuaBinder.h"
#include "Entity.h"
#include "FontAsset.h"
#include "Assets.h"
#include "Graphics.h"

namespace Monocle
{

class Text: public Entity
	{
	public:
		Text(const std::string& text, FontAsset* font);

		void Render();

		void SetFont(FontAsset* font) { this->font = font; }
		void SetText(const std::string& text) { this->text = text; }

	protected:
		FontAsset* font;
		std::string text;
	};

	Text::Text(const std::string& text, FontAsset* font)
		: Entity(), font(font), text(text)
	{
	}

	void Text::Render()
	{
		Graphics::PushMatrix();
		Graphics::Translate(position);
		Graphics::SetBlend(BLEND_ALPHA);
		Graphics::SetColor(Color::white);
		Graphics::BindFont(font);

		Graphics::RenderText(*font, text, 0, 0);
		Graphics::PopMatrix();
	}

	namespace Lua
	{
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
	}
}