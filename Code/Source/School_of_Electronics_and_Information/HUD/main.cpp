#include "School_of_Electronics_and_Information/HUD/HUD.h"
#include <iostream>
#include <cstdio>
#include <Windows.h>

#include<list>


#define PI 3.1415926535897932384626433832795
//这个是高精度的


using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Driver::Direct3D::v9::Window;

void display(
	const double totalTime,
	const double deltaTime,
	const Window &window
);

using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Vector;
using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Component::DisplayObject;
using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Component::Composite;
using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Util::smart_pointer::SimpleSharedPointer;

Composite getDemoComposite(const Window &window,double totalTime);

//int main(_In_ int _Argc, _In_count_(_Argc) _Pre_z_ char ** _Argv, _In_z_ char ** _Env)
int main(int argc, char **argv)
{
	//为什么这个字体那么诡异
	//Visual Studio 2010还真是有点难用

	//后来我又想了想，等到全部完成功能之后还是应该迁移到Visual Studio 2005去

	Window window(640, 640);
	window.setStaticCamera();
	//静态相机设置完毕
	window.render(display);

	/*
	std::vector<VectorTest<int>> testVector;
	VectorTest<int> origin;
	testVector.push_back(origin);
	return 0;
	*/
}




void display(
	const double totalTime,
	const double deltaTime,
	const Window &window
)
{
	window.getDevice()->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0x80, 0x80, 0x80), 1.0f, 0
	);
	window.getDevice()->BeginScene();
	///////////////////////////////在这个中间建模并渲染


	getDemoComposite(window,totalTime).render(
		Vector(), 
		Vector(0, 0, -0.001*totalTime)
	);
	///////////////////////////////
	window.getDevice()->EndScene();

	//将后台缓冲区的内容投射上前台
	window.getDevice()->Present(0, 0, 0, 0);
}

Composite getDemoComposite(const Window &window, double totalTime)
{
	using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Component::D3D9::LineList;

	Composite testComposite = Composite();

	std::vector<std::pair<LineList::Vertex, LineList::Vertex>> testVertexPairVector;
	LineList::Vertex vertexArray[4];



	vertexArray[0].x = -500;
	vertexArray[0].y = 500;
	vertexArray[0].z = 1000;
	vertexArray[0].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[1].x = 500;
	vertexArray[1].y = -500;
	vertexArray[1].z = 1000;
	vertexArray[1].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[2].x = -500;
	vertexArray[2].y = -500;
	vertexArray[2].z = 1000;
	vertexArray[2].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[3].x = 500;
	vertexArray[3].y = 500;
	vertexArray[3].z = 1000;
	vertexArray[3].color = D3DCOLOR_XRGB(0, 0, 0xff);

	testVertexPairVector.push_back(std::pair<LineList::Vertex, LineList::Vertex>(*(vertexArray + 0), *(vertexArray + 1)));
	testVertexPairVector.push_back(std::pair<LineList::Vertex, LineList::Vertex>(*(vertexArray + 2), *(vertexArray + 3)));


	testComposite.add<LineList>(
		SimpleSharedPointer<LineList>(
			new LineList(window, testVertexPairVector)
			)
		);
	testVertexPairVector.clear();



	vertexArray[0].x = -200;
	vertexArray[0].y = 200;
	vertexArray[0].z = 1000;
	vertexArray[0].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[1].x = 200;
	vertexArray[1].y = -200;
	vertexArray[1].z = 1000;
	vertexArray[1].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[2].x = -200;
	vertexArray[2].y = -200;
	vertexArray[2].z = 1000;
	vertexArray[2].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[3].x = 200;
	vertexArray[3].y = 200;
	vertexArray[3].z = 1000;
	vertexArray[3].color = D3DCOLOR_XRGB(0, 0, 0xff);

	testVertexPairVector.push_back(std::pair<LineList::Vertex, LineList::Vertex>(*(vertexArray + 0), *(vertexArray + 1)));
	testVertexPairVector.push_back(std::pair<LineList::Vertex, LineList::Vertex>(*(vertexArray + 2), *(vertexArray + 3)));
	testComposite.add<LineList>(
		SimpleSharedPointer<LineList>(
			new LineList(
				window,
				testVertexPairVector,
				Vector(-500, 500),
				Vector(0, 0, 0.003*totalTime)
			)));
	testVertexPairVector.clear();



	vertexArray[0].x = -200;
	vertexArray[0].y = 200;
	vertexArray[0].z = 1000;
	vertexArray[0].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[1].x = 200;
	vertexArray[1].y = -200;
	vertexArray[1].z = 1000;
	vertexArray[1].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[2].x = -200;
	vertexArray[2].y = -200;
	vertexArray[2].z = 1000;
	vertexArray[2].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[3].x = 200;
	vertexArray[3].y = 200;
	vertexArray[3].z = 1000;
	vertexArray[3].color = D3DCOLOR_XRGB(0, 0, 0xff);

	testVertexPairVector.push_back(std::pair<LineList::Vertex, LineList::Vertex>(*(vertexArray + 0), *(vertexArray + 1)));
	testVertexPairVector.push_back(std::pair<LineList::Vertex, LineList::Vertex>(*(vertexArray + 2), *(vertexArray + 3)));
	testComposite.add<LineList>(
		SimpleSharedPointer<LineList>(
			new LineList(
				window,
				testVertexPairVector,
				Vector(500, 500),
				Vector(0, 0, 0.003*totalTime)
			)));
	testVertexPairVector.clear();



	vertexArray[0].x = -200;
	vertexArray[0].y = 200;
	vertexArray[0].z = 1000;
	vertexArray[0].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[1].x = 200;
	vertexArray[1].y = -200;
	vertexArray[1].z = 1000;
	vertexArray[1].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[2].x = -200;
	vertexArray[2].y = -200;
	vertexArray[2].z = 1000;
	vertexArray[2].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[3].x = 200;
	vertexArray[3].y = 200;
	vertexArray[3].z = 1000;
	vertexArray[3].color = D3DCOLOR_XRGB(0, 0, 0xff);

	testVertexPairVector.push_back(std::pair<LineList::Vertex, LineList::Vertex>(*(vertexArray + 0), *(vertexArray + 1)));
	testVertexPairVector.push_back(std::pair<LineList::Vertex, LineList::Vertex>(*(vertexArray + 2), *(vertexArray + 3)));

	testComposite.add<LineList>(
		SimpleSharedPointer<LineList>(
			new LineList(
				window,
				testVertexPairVector,
				Vector(-500, -500),
				Vector(0, 0, 0.003*totalTime)
			)));
	testVertexPairVector.clear();



	vertexArray[0].x = -200;
	vertexArray[0].y = 200;
	vertexArray[0].z = 1000;
	vertexArray[0].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[1].x = 200;
	vertexArray[1].y = -200;
	vertexArray[1].z = 1000;
	vertexArray[1].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[2].x = -200;
	vertexArray[2].y = -200;
	vertexArray[2].z = 1000;
	vertexArray[2].color = D3DCOLOR_XRGB(0, 0, 0xff);
	vertexArray[3].x = 200;
	vertexArray[3].y = 200;
	vertexArray[3].z = 1000;
	vertexArray[3].color = D3DCOLOR_XRGB(0, 0, 0xff);

	testVertexPairVector.push_back(std::pair<LineList::Vertex, LineList::Vertex>(*(vertexArray + 0), *(vertexArray + 1)));
	testVertexPairVector.push_back(std::pair<LineList::Vertex, LineList::Vertex>(*(vertexArray + 2), *(vertexArray + 3)));

	testComposite.add<LineList>(
		SimpleSharedPointer<LineList>(
			new LineList(
				window,
				testVertexPairVector,
				Vector(500, -500),
				Vector(0, 0, 0.003*totalTime)
			)));
	testVertexPairVector.clear();

	return testComposite;
}