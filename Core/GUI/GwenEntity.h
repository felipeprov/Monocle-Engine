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

namespace Monocle
{
	namespace GUI
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
				pCanvas->SetSize( 800, 600 );

			}

			Gwen::Controls::Canvas* GetCanvas(){return pCanvas;}
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
}