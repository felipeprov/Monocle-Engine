#include "GuiGameScene.h"
#include <Monocle.h>
#include <GUI/GwenEntity.h>
#include <Gwen/UnitTest/UnitTest.h>


using namespace Monocle;

namespace Moonocle
{
	void GameScene::Begin()
	{
		Scene::Begin();
		Graphics::SetBackgroundColor(Color::blue*0.2f + Color::white*0.8);
		GUI::GweenEntity* gwenEnt = new GUI::GweenEntity;
		UnitTest *pUnit = new UnitTest( gwenEnt->GetCanvas() );

		Add(gwenEnt);
	}

	void GameScene::End()
	{
	}

	void GameScene::Update()
	{
		Scene::Update();
	}
}
