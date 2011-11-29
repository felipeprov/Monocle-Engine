#pragma once
#include "Entity.h"
#include "GwenMonocle.h"
#include "gwen\Gwen.h"
#include "Gwen/Skins/Simple.h"
#include "Gwen/Controls/Canvas.h"
#include "Gwen\Controls\Button.h"
#include "Gwen\Controls\ComboBox.h"
namespace Monocle
{
	class GweenEntity :public Entity
	{
		GUI::GwenRenderer* renderer;
		Gwen::Skin::Simple skin;
		Gwen::Controls::Canvas* pCanvas;
		Gwen::Controls::Button* pButton;
		Gwen::Controls::ComboBox* pCbox;
	public:
		GweenEntity()
		{
			renderer = new GUI::GwenRenderer;
			skin.SetDefaultFont(L"OpenSans.ttf",21);
			skin.SetRender( renderer );
			pCanvas = new Gwen::Controls::Canvas( &skin );
		    pCanvas->SetSize( 1024, 512 );
			pButton = new Gwen::Controls::Button( pCanvas );
			pButton->SetBounds( 10, 10, 200, 100 );
			pButton->SetTextColor(Gwen::Colors::Black);
			pButton->SetText( "My First Button" );

			pButton = new Gwen::Controls::Button( pCanvas );
			pButton->SetBounds( 210, 10, 200, 100 );
			pButton->SetText( "My First Button" );

			pCbox = new Gwen::Controls::ComboBox(pCanvas);
			pCbox->SetBounds(300,200,200,100);
			pCbox->AddItem(L"Testando");
			scale = Vector2::one;
		}
		void Render()
		{
			pCanvas->RenderCanvas();
		}
	};
}