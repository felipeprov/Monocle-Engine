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
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
                        glAlphaFunc( GL_GREATER, 1.0f );        
                        glEnable ( GL_BLEND );

		}
		void GwenRenderer::End() {}

		void GwenRenderer::SetDrawColor( Gwen::Color color )
		{
			//glColor4ubv( GLubyte*)&color );
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
			Monocle::Graphics::BindTexture(NULL);
			Monocle::Graphics::RenderQuad(rect.w,rect.h,Vector2(0,0),Vector2::one,Vector2(rect.x+rect.w/2,rect.y+rect.h/2));
			//Monocle::Graphics::RenderQuad( rect.w, rect.h, Monocle::Vector2::zero, Monocle::Vector2::one, Monocle::Vector2( rect.x + (rect.w/2), rect.y + (rect.h / 2) ) );
		}

		void GwenRenderer::LoadTexture( Gwen::Texture *pTexture )
		{
			std::cout << "[GwenRenderer] LoadTexture" << std::endl;
			Monocle::TextureAsset *tex = Monocle::Assets::RequestTexture( pTexture->name.Get() );

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

			if(!pFont->data) pFont->data =  Assets::RequestFont("AudioTest/LiberationSans-Regular.ttf", 12);
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

            // OpenGL's coords are from the bottom left
            // so we need to translate them here.
            {
                    GLint view[4];
                    glGetIntegerv( GL_VIEWPORT, &view[0] );
                    rect.y = view[3] - (rect.y + rect.h);
            }

            glScissor( rect.x * Scale(), rect.y * Scale(), rect.w * Scale(), rect.h * Scale() );
            glEnable( GL_SCISSOR_TEST );
               
		}

		void GwenRenderer::EndClip()
		{
			//Flush();
          //   Monocle::Graphics::EndScissor();
			 glDisable( GL_SCISSOR_TEST );

		}

		void GwenRenderer::DrawTexturedRect(Gwen::Texture *tex, Gwen::Rect rect, float u1, float v1, float u2, float v2)
		{
			//Graphics::PushMatrix();
			Graphics::IdentityMatrix();
			TextureAsset *data = (TextureAsset*)tex->data;
			Translate(rect);
			Monocle::Graphics::BindTexture( data );
			rect.w+=1;
			rect.h+=1;
			//Monocle::Graphics::RenderQuad( Rect(rect.x, rect.y, rect.w, rect.h), Rect( u1,v1, u2-u1, v2-v1) );
			Monocle::Graphics::RenderQuad( rect.w, rect.h, Vector2(u1,v1), Vector2(u2-u1,v2-v1), Monocle::Vector2( rect.x + (rect.w / 2), rect.y + (rect.h / 2)) );
			//Graphics::PopMatrix();
		}

		 Gwen::Color GwenRenderer::PixelColour( Gwen::Texture* pTexture, unsigned int x, unsigned int y, const Gwen::Color& col_default )
                {
                        GLuint* tex = (GLuint*)pTexture->data;
                        if ( !tex ) return col_default;

                        unsigned int iPixelSize = sizeof(unsigned char) * 4;

                        glBindTexture( GL_TEXTURE_2D, *tex );

                        unsigned char* data = (unsigned char*) malloc( iPixelSize * pTexture->width * pTexture->height );

                                glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

                                unsigned int iOffset = (y * pTexture->width + x) * 4;

                                Gwen::Color c;
                                c.r = data[0 + iOffset];
                                c.g = data[1 + iOffset];
                                c.b = data[2 + iOffset];
                                c.a = data[3 + iOffset];

                        //
                        // Retrieving the entire texture for a single pixel read
                        // is kind of a waste - maybe cache this pointer in the texture
                        // data and then release later on? It's never called during runtime
                        // - only during initialization.
                        //
                        free( data );

                        return c;
                }


		void GwenRenderer::RenderText( Gwen::Font *font, Gwen::Point pos, const Gwen::UnicodeString& text )
		{
			if(!font->data || std::fabs( font->realsize - font->size * Scale()) > 2)
			{
				FreeFont(font);
				LoadFont(font);
			}

			Translate(pos.x, pos.y);

#pragma warning NOT SAFE!
			std::string txt;
			txt.assign(text.begin(), text.end());

			FontAsset *f;
			if(font->data)
				f = (FontAsset *)font->data;
			else
				f = Assets::RequestFont("AudioTest/LiberationSans-Regular.ttf", 11);

			Monocle::Graphics::SetColor(Monocle::Color::black);
		//	Monocle::Graphics::SetBlend(Monocle::BLEND_ALPHA);
			Monocle::Graphics::BindFont((FontAsset*)font->data);
			Monocle::Graphics::RenderText( *f, txt, (float)pos.x, (float)pos.y + f->GetTextHeight(txt) );
			
	//		Graphics::PushMatrix();
	//		Graphics::IdentityMatrix();
	//		Graphics::Translate( (float)pos.x, (float)pos.y + f->GetTextHeight(txt),0);
	//		Graphics::SetBlend(BLEND_ALPHA);
	////		Graphics::SetColor(Color::black);
	//		Graphics::BindFont(f);

	//		Graphics::RenderText(*f, txt, 0, 0);
	//		Graphics::PopMatrix();
		}
	}
}