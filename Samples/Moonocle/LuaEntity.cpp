
#include "LuaEntity.h"

namespace Moonocle
{
	LuaEntity::LuaEntity()
	{
	}

	void LuaEntity::Update()
	{
	}

	void LuaEntity::Render()
	{
		Graphics::PushMatrix();
		Graphics::Translate(position);
        Graphics::SetColor(Color::white);
		Graphics::RenderQuad(25, 100.0f);
		Graphics::PopMatrix();
	}
}