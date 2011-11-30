#pragma once
#include "Entity.h"
#include "GwenMonocle.h"
#include "gwen\Gwen.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/Skins/Simple.h"
#include "Gwen/Controls/Canvas.h"
#include "Gwen\Controls\Button.h"
#include "Gwen\Controls\ComboBox.h"
#include "GwenInputMonocle.h"
#include "Gwen\Controls\WindowControl.h"
#include <Gwen/UnitTest/UnitTest.h>

namespace Monocle
{
	class GweenEntity :public Entity
	{
		GUI::GwenRenderer* renderer;
		Gwen::Skin::TexturedBase skin;
		Gwen::Controls::Canvas* pCanvas;
		Gwen::Controls::Button* pButton;
		Gwen::Controls::ComboBox* pCbox;
		Gwen::Controls::WindowControl *window;
		GUI::GwenInput input;

	public:
		GweenEntity()
		{
			renderer = new GUI::GwenRenderer;
			skin.SetDefaultFont(L"OpenSans.ttf",21);
			skin.SetRender( renderer );
			skin.Init("DefaultSkin.png");
			pCanvas = new Gwen::Controls::Canvas( &skin );
			input.Initialize(pCanvas);

			UnitTest *pUnit = new UnitTest( pCanvas );
			pCanvas->SetSize( 800, 600 );
			/*window = new Gwen::Controls::WindowControl(pCanvas);
			window->SetTitle("Testing");
			window->SetSize(400,400);
			
		    
			pButton = new Gwen::Controls::Button( window );
			pButton->SetBounds( 10, 10, 200, 50 );
			pButton->SetTextColor(Gwen::Colors::Black);
			pButton->SetText( "My First Button" );

			pCbox = new Gwen::Controls::ComboBox(window);
			pCbox->SetBounds(10,60,200,50);
			pCbox->AddItem(L"Item1");
			pCbox->AddItem(L"Item2");
			scale = Vector2::one;*/
		}

		void Update()
		{
			Monocle::Entity::Update();
			input.ProcessInput();
		}

		void Render()
		{
			pCanvas->RenderCanvas();
		}
	};
}