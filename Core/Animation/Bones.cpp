#include "Bones.h"
#include <iostream>
#include "crtdbg.h"
#include "Graphics.h"

namespace Animations
{
	Bone::Bone(Bone* parent, float x, float y, float angle, float length):
					 parent(parent), x(x), y(y), angle(angle), length(length), childCount(0)
	{
		for(int i=0; i < MAX_BONE_CHILDS;i++)
			this->childs[i] = NULL;
	}

	Bone* Bone::create(Bone* parent, float x, float y, float angle, float length)
	{
		Bone* bone = new Bone(parent, x, y, angle, length);		
		_ASSERT(bone);
		
		if(parent)
		{
			if(parent->childCount < MAX_BONE_CHILDS)
			{
				parent->childs[parent->childCount++] =bone;
			}
			else
			{
				std::cout<<"BONE CREATE ERROR: Parent has so many childs"<<std::endl;
				exit(0);
			}
		}

		return bone;
	}

	Bone* Bone::freeTree(Bone* root)
	{
		if(root==NULL)
		{
			return NULL;
		}

		for(int i=0; i< root->childCount;i++)
			freeTree(root->childs[i]);

		return NULL;
	}

	void Bone::dumpTree(Bone* root, uint8_t level)
	{
		if(root == NULL)
		{
			return;
		}

		for(int i=0;i<level; ++i)
		{
			std::cout<<"#";
		}

		std::cout<<" "<<root->x <<" "<< root->y << " " << root->angle << " " << root->length << std::endl;

		for(int i=0; i < root->childCount; ++i)
		{
			dumpTree(root->childs[i], level+1);
		}
	}

	void Bone::Render(Bone* root)
	{
		if(root == NULL)
			return;

		Monocle::Graphics::BindTexture(NULL);
		Monocle::Graphics::PushMatrix();
		Monocle::Graphics::Translate(root->x,root->y, 0);
		Monocle::Graphics::Rotate(root->angle,0,0,1.0);
		
		Monocle::Graphics::BeginLine();
			Monocle::Graphics::SetColor(Monocle::Color::red);
			Monocle::Graphics::Vertex(0, 0);
			Monocle::Graphics::SetColor(Monocle::Color::green);
			Monocle::Graphics::Vertex(root->length,0);
		Monocle::Graphics::EndLine();
		
		Monocle::Graphics::Translate(root->length,0,0);
		for(int i =0; i < root->childCount;i++)
			Render(root->childs[i]);

		Monocle::Graphics::PopMatrix();	
	}

	void Bone::Update(Bone* root, float angle)
	{
		if(root == NULL)
			return;

		Monocle::Graphics::PushMatrix();
		Monocle::Graphics::Translate(root->x,root->y, 0);
		Monocle::Graphics::Rotate(root->angle,0,0,1.0);

		Monocle::Graphics::Translate(root->length,0,0);

		Monocle::Vector2 vec = Monocle::Graphics::GetMatrixPosition();
		root->xAbs = vec.x;
		root->yAbs = vec.y;
		root->angleAbs = angle + root->angle;

		
		for(int i=0; i< root->childCount;i++)
			Update(root->childs[i],  root->angleAbs);

		Monocle::Graphics::PopMatrix();
	}
}