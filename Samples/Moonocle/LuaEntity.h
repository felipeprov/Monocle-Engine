#pragma once
#include <Monocle.h>
#include <string>
#include <map>
using namespace Monocle;
using namespace std;

namespace Moonocle
{
	class LuaEntity : public Entity
	{
	protected:
		string updateScript;

	public:
		LuaEntity();
		virtual void Update();
		virtual void Render();
	};
}