#include "GwenMonocle.h"
#include <Gwen/Structures.h>
#include <Gwen/TextObject.h>
#include <Gwen/Texture.h>
#include <TextureAsset.h>
#include <FontAsset.h>
#include <Graphics.h>
#include <Assets.h>
#include <iostream>
#include <cmath>
#include "GL\glew.h"

namespace Monocle
{
	namespace GUI
	{
		GwenRenderer::GwenRenderer() {}
		GwenRenderer::~GwenRenderer() {}

		void GwenRenderer::Begin() 
		{
		}
		void GwenRenderer::End() {}

		void GwenRenderer::SetDrawColor( Gwen::Color color )
		{
			Monocle::Graphics::SetColor( Monocle::Color(color.r/255.f, color.g/255.f, color.b/255.f, color.a/255.f) );
		}

		void GwenRenderer::DrawLine( int x, int y, int a, int b )
		{
			Translate(x,y);
			Translate(a,b);
			Monocle::Graphics::RenderLine( Monocle::Vector2(x,y), Monocle::Vector2(a,b) );
		}

		void GwenRenderer::DrawFilledRect( Gwen::Rect rect )
		{

			Translate(rect);
			Graphics::PushMatrix();
			Monocle::Graphics::BindTexture(NULL);
			Graphics::SetBlend(BLEND_ALPHA);
			Graphics::IdentityMatrix();
			Monocle::Graphics::RenderQuad(rect.w,rect.h,Vector2(0,0),Vector2::one,Vector2(rect.x+rect.w/2,rect.y+rect.h/2));

			Graphics::PopMatrix();
		}

		void GwenRenderer::LoadTexture( Gwen::Texture *pTexture )
		{
			std::cout << "[GwenRenderer] LoadTexture" << std::endl;
			Monocle::TextureAsset *tex = Monocle::Assets::RequestTexture( pTexture->name.Get(),FILTER_LINEAR );

			if(tex)
			{
				pTexture->data = tex;
				pTexture->width = tex->width;
				pTexture->height = tex->height;
			}
			else
			{
				pTexture->failed = true;
			}
		}

		void GwenRenderer::FreeTexture( Gwen::Texture *pTexture )
		{
			TextureAsset *tex = (TextureAsset *)pTexture->data;
			tex->Unload();
			delete tex;
			tex = NULL;
		}

		void GwenRenderer::LoadFont( Gwen::Font *pFont )
		{
			pFont->realsize = pFont->size * Scale();

#pragma warning NOT SAFE!
			std::string filename;
			filename.assign(pFont->facename.begin(), pFont->facename.end());

			pFont->data = Monocle::Assets::RequestFont( filename, pFont->realsize );

			if(!pFont->data) pFont->data =  Assets::RequestFont("micross.ttf", 15);
		}

		void GwenRenderer::FreeFont( Gwen::Font *pFont )
		{
			std::cout << "[GwenRenderer] FreeFont" << std::endl;
			Monocle::FontAsset *font = (Monocle::FontAsset *)pFont->data;

#pragma warning needs fontAsset->Unload or something
			delete font;
			font = NULL;
		}

		Gwen::Point GwenRenderer::MeasureText( Gwen::Font *pFont, const Gwen::UnicodeString& text )
		{
			if(!pFont->data || std::fabs( pFont->realsize - pFont->size * Scale() ) > 2)
			{
				FreeFont(pFont);
				LoadFont(pFont);
			}

			Monocle::FontAsset *font = (Monocle::FontAsset *)pFont->data;

			Gwen::Point pt;

#pragma warning NOT SAFE!
			std::string txt;
			txt.assign(text.begin(), text.end());

			if(font)
			{
				pt.x = font->GetTextWidth( txt );
				pt.y = font->GetTextHeight( txt );
			}

			return pt;
		}

		void GwenRenderer::StartClip()
		{
			Gwen::Rect rect = ClipRegion();
			Graphics::BeginScissor(Rect(Vector2(rect.x-1,rect.y-1),Vector2(rect.x+rect.w+1,rect.y+rect.h+1)));               
		}

		void GwenRenderer::EndClip()
		{
             Monocle::Graphics::EndScissor();
		}

		void GwenRenderer::DrawTexturedRect(Gwen::Texture *tex, Gwen::Rect rect, float u1, float v1, float u2, float v2)
		{
			Translate(rect);
			Graphics::PushMatrix();
			TextureAsset *data = (TextureAsset*)tex->data;
			Monocle::Graphics::BindTexture( data );
			Graphics::IdentityMatrix();
		
			Monocle::Graphics::RenderQuad( rect.w, rect.h, Vector2(u1,v1), Vector2((u2-u1),(v2-v1)), Monocle::Vector2( rect.x + (rect.w / 2), rect.y + (rect.h / 2)) );
			Graphics::PopMatrix();
		}

		 Gwen::Color GwenRenderer::PixelColour( Gwen::Texture* pTexture, unsigned int x, unsigned int y, const Gwen::Color& col_default )
        {
			TextureAsset *pdata = (TextureAsset*)pTexture->data;

			unsigned char *data = pdata->ReadRect(Vector2(x,y), Vector2(1,1));
           
			Gwen::Color c;
			c.r = data[0];
			c.g = data[1];
			c.b = data[2];
			c.a = data[3];

            return c;
        }


		void GwenRenderer::RenderText( Gwen::Font *font, Gwen::Point pos, const Gwen::UnicodeString& text )
		{
			Translate(pos.x, pos.y);
			Color color = Graphics::GetCurrentColor();

			if(!font->data || std::fabs( font->realsize - font->size * Scale()) > 2)
			{
				FreeFont(font);
				LoadFont(font);
			}

#pragma warning NOT SAFE!
			std::string txt;
			txt.assign(text.begin(), text.end());

			FontAsset *f;
			if(font->data)
				f = (FontAsset *)font->data;
			else
				f = Assets::RequestFont("AudioTest/LiberationSans-Regular.ttf", 11);
			
			Graphics::PushMatrix();
			Graphics::IdentityMatrix();

			Graphics::BindFont(f);

			Graphics::RenderText(*f, txt, pos.x, pos.y +f->GetTextHeight(txt)-1);
			Graphics::PopMatrix();
		}
	}
}