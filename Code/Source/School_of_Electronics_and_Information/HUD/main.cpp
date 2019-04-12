#include "School_of_Electronics_and_Information/HUD/HUD.h"
#include <iostream>
#include <cstdio>
#include <Windows.h>

#include<list>


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

class TestComponent :public NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Component::DisplayObject
{
public:
	TestComponent(
		Vector relativePosition = Vector(0, 0, 0),
		Vector relativeRotation = Vector(0, 0, 0),
		Vector relativeScale = Vector(1, 1, 1)
	);
	void render(
		const Vector &absolutePosition,
		const Vector &absoluteRotation,
		const Vector &absoluteScale);
};

//int main(_In_ int _Argc, _In_count_(_Argc) _Pre_z_ char ** _Argv, _In_z_ char ** _Env)
int main(int argc, char **argv)
{
	//Ϊʲô���������ô����
	//Visual Studio 2010�������е�����

	//�������������룬�ȵ�ȫ����ɹ���֮����Ӧ��Ǩ�Ƶ�Visual Studio 2005ȥ

	Window window(640,640);
	window.setStaticCamera();
	//��̬����������
	window.render(display);

	/*
	TestComponent testComponent1 = TestComponent(Vector(1, 0, 0));
	TestComponent testComponent2 = TestComponent(Vector(0, 1, 0));

	Composite testComposite;
	testComposite.add(&testComponent1);
	testComposite.add(&testComponent2);
	testComposite.render(Vector(1, 1, 0), Vector(0, 0, 3.1415926535897932384626433832795 / 2));
	*/

}

TestComponent::TestComponent(
	Vector relativePosition /* = Vector(0,0,0) */,
	Vector relativeRotation /* = Vector(0,0,0) */,
	Vector relativeScale /* = Vector(1,1,1) */
) :DisplayObject(relativePosition, relativeRotation, relativeScale)
{
	//
}

void TestComponent::render(
	const Vector &absolutePosition,
	const Vector &absoluteRotation,
	const Vector &absoluteScale)
{
	std::cout << absolutePosition.getX() << "," << absolutePosition.getY() << "," << absolutePosition.getZ() << "\t";
	std::cout << absoluteRotation.getX() << "," << absoluteRotation.getY() << "," << absoluteRotation.getZ() << "\t";
	std::cout << absoluteScale.getX() << "," << absoluteScale.getY() << "," << absoluteScale.getZ() << std::endl;
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
	///////////////////////////////������м佨ģ����Ⱦ
	using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Component::D3D9::LineList;

	Composite testComposite = Composite();

	std::vector<std::pair<LineList::Vertex, LineList::Vertex>> testVertexPairVector;

	LineList::Vertex vertexArray[4];

	/*
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

	//��һ���Ǵ���ģ���ΪSimpleSharedPointerʵ����һ����ʱ����
	//���ں����˳���ʱ������
	//��SimpleSharedPointer��������deleteԭʼָ�룬����μ�smart_pointer.hpp;
	
	testComposite.add<LineList>(SimpleSharedPointer<LineList>(
		new LineList(window, testVertexPairVector))
		);
	testVertexPairVector.clear();
	*/


	std::vector<SimpleSharedPointer<LineList>> tempList1;

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

	
	tempList1.push_back(SimpleSharedPointer<LineList>(
		new LineList(window, testVertexPairVector))
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
	tempList1.push_back(SimpleSharedPointer<LineList>(
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
	tempList1.push_back(SimpleSharedPointer<LineList>(
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

	tempList1.push_back(SimpleSharedPointer<LineList>(
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

	tempList1.push_back(SimpleSharedPointer<LineList>(
		new LineList(
			window,
			testVertexPairVector,
			Vector(500, -500),
			Vector(0, 0, 0.003*totalTime)
		)));
	testVertexPairVector.clear();

	

	testComposite.add<LineList>(tempList1);

	testComposite.render(Vector(), Vector(0, 0, -0.001*totalTime));

	///////////////////////////////
	window.getDevice()->EndScene();

	//����̨������������Ͷ����ǰ̨
	window.getDevice()->Present(0, 0, 0, 0);
}