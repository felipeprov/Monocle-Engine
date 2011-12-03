#pragma once
#include <Monocle.h>
#include <string>
#include <map>
using namespace std;

namespace Monocle
{
	namespace Lua
	{
		class LuaEntity : public Entity
		{
		protected:
			string updateScript;
			map<string, string> scripts;
		

		public:
			int luaId;
			LuaEntity();
			void addScript(string ev, string name){scripts[ev]=name;}
			virtual void Update();
			virtual void Render();
		};
	}
}