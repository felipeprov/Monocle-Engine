#pragma once

//author: Felipe Provenzano
//

#include "stdint.h"

#define MAX_BONE_CHILDS 8
#define MAX_BONE_NAME	32

namespace Animations
{
	struct Bone
	{
		Bone(Bone* parent, float x, float y, float angle, float length);
		
		enum BoneOptions
		{
			BONE_ABSOLUTE_ANGLE = 0x1,
			BONE_ABSOULUTE_POSITION =0x2,
			BONE_ABSOLUTE = BONE_ABSOLUTE_ANGLE|BONE_ABSOULUTE_POSITION
		};

		char name[MAX_BONE_NAME];
		float x;
		float y;
		float angle;				
		float length;
		Bone* childs[MAX_BONE_CHILDS];
		uint8_t flags;
		uint8_t childCount;
		Bone* parent;
		float xAbs;
		float yAbs;
		float angleAbs;

		static Bone* create(Bone* parent, float x, float y, float angle, float length);
		static Bone* freeTree(Bone* root);
		static void dumpTree(Bone* root, uint8_t level);
		static void Render(Bone* root);
		static void Update(Bone* root,float angle);
	};
}