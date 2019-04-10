#pragma once
#include "Direct3D9.h"
#include <Windows.h>
#include <string>

#include "School_of_Electronics_and_Information\HUD\Graphic\Engine\Vector.h"
using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Vector;

namespace NWPU
{
	namespace School_of_Electronics_and_Information
	{
		namespace HUD
		{
			namespace Graphic
			{
				namespace Driver
				{
					namespace Direct3D
					{
						namespace v9
						{

							class Window
							{
								//��ô�����������Ҫ����ǿ��֢��
								//�ɲ�����using namespace 
								//�����ٸİɣ����������﷨�ǶԵ�
							private:
								HINSTANCE hInstance;
								HWND hwnd;
								int width,height;
								IDirect3DDevice9 *device;//Direct3D �豸

								//���ڴ������
								//��ʹ��C++11��lambda�Ա�֤������
								static LRESULT CALLBACK defaultWindowProc(
									HWND hwnd,
									UINT uMessage,
									WPARAM wParam,
									LPARAM lParam
									);

							public:

								HINSTANCE getHInstance() const;
								HWND getHWND() const;
								IDirect3DDevice9 * getDevice() const;
								void getSize(int &width, int &height) const;

								class InitConfig
								{

								public:
									InitConfig();
								};

								Window(const Window &window);

								Window(int width,int height,bool fullScreen = false,
									HINSTANCE hInstance = GetModuleHandle(NULL),
									std::string title = std::string("Direct3D"),
									InitConfig initConfig = InitConfig()
									);

								//���þ�̬���
								void setStaticCamera(
									const Vector &position = Vector(0, 0, 0),
									const Vector &target = Vector(0, 0, 1),
									const double angle = 0.5f*D3DX_PI,
									const double zMin = 0.0,
									const double zMax = 1073741824.0
								);


								/**
								* ��ʾ
								*/
								void render(void (*displayFunction)(
									const double totalTime,
									const double deltaTime,
									const Window &window
									)) const;
							};
						}
					}
				}
			}
		}
	}
}