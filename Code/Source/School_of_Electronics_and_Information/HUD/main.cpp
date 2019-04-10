#include "School_of_Electronics_and_Information/HUD/HUD.h"
#include <iostream>
#include <cstdio>
#include <Windows.h>


using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Driver::Direct3D::v9::Window;

void display(
	const double totalTime,
	const double deltaTime,
	const Window &window
	);

using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Vector;
using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Component::DisplayObject;
using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Component::Composite;

class TestComponent:public NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Component::DisplayObject
{
public:
	TestComponent(
		Vector relativePosition = Vector(0,0,0),
		Vector relativeRotation = Vector(0,0,0),
		Vector relativeScale = Vector(1,1,1)
		);
	void render(
		Vector absolutePosition ,
		Vector absoluteRotation ,
		Vector absoluteScale);
};

//int main(_In_ int _Argc, _In_count_(_Argc) _Pre_z_ char ** _Argv, _In_z_ char ** _Env)
int main(int argc,char **argv)
{
	//为什么这个字体那么诡异
	//Visual Studio 2010还真是有点难用
	
	//后来我又想了想，等到全部完成功能之后还是应该迁移到Visual Studio 2005去
	
	//Window window(640,640);
	//window.render(display);


	TestComponent testComponent1 = TestComponent(Vector(1, 0, 0));
	TestComponent testComponent2 = TestComponent(Vector(0, 1, 0));

	Composite testComposite;
	testComposite.add(&testComponent1);
	testComposite.add(&testComponent2);
	testComposite.render(Vector(1, 1, 0), Vector(0, 0, 3.1415926535897932384626433832795 / 2));
}

TestComponent::TestComponent( 
	Vector relativePosition /* = Vector(0,0,0) */,
	Vector relativeRotation /* = Vector(0,0,0) */, 
	Vector relativeScale /* = Vector(1,1,1) */
	):DisplayObject(relativePosition,relativeRotation,relativeScale)
{
	//
}

void TestComponent::render(
	Vector absolutePosition ,
	Vector absoluteRotation ,
	Vector absoluteScale)
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
	window.getDevice()->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0x80,0x80,0x80),1.0f,0
		);
	window.getDevice()->BeginScene();

	window.getDevice()->EndScene();

	//将后台缓冲区的内容投射上前台
	window.getDevice()->Present(0,0,0,0);
}