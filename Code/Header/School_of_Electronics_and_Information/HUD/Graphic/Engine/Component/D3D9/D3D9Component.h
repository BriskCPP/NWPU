#pragma once

#include "School_of_Electronics_and_Information/HUD/Graphic/Driver/Direct3D/v9/Direct3D9.h"

#include "../component.hpp"

#include <vector>


using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Driver::Direct3D::v9::Window;
using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Vector;
using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Component::DisplayObject;

namespace NWPU
{
	namespace School_of_Electronics_and_Information
	{
		namespace HUD
		{
			namespace Graphic
			{
				namespace Engine
				{
					namespace Component
					{
						namespace D3D9
						{
							//基本的线条
							class LineList:public DisplayObject
							{

							public:
								struct Vertex
								{
									float x,y,z;
									D3DCOLOR color;
									static const DWORD format;
									//static const DWORD flexibleVectorFormat;
								};


								LineList(
									const Window &window,
									const std::vector<std::pair<Vertex,Vertex>> &lines,
									const Vector &relativePosition = Vector(0,0,0),
									const Vector &relativeRotation = Vector(0,0,0),
									const Vector &relativeScale = Vector(1,1,1)
									);

								//这个析构函数的主要作用是释放VertexBuffer的内存
								~LineList();

								//todo:这里要改用带有默认值的吧
								void render(
									const Vector &absolutePosition = Vector(0,0,0),
									const Vector &absoluteRotation = Vector(0,0,0),
									const Vector &absoluteScale = Vector(1,1,1));

							private:
								const Window window;
								IDirect3DVertexBuffer9 *vertexBuffer;
								std::vector<std::pair<Vertex,Vertex>> lines;
							};
						}
					}
				}
			}
		}
	}
}