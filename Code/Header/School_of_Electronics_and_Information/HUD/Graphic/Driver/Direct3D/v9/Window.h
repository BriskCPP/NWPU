#pragma once
#include "Direct3D9.h"
#include <Windows.h>
#include <string>

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
								HWND hwnd;
								HINSTANCE hInstance;
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

								IDirect3DDevice9 * getDevice() const;

								class InitConfig
								{

								public:
									InitConfig();
								};

								Window(int width,int height,bool fullScreen = false,
									HINSTANCE hInstance = GetModuleHandle(NULL),
									std::string title = std::string("Direct3D"),
									InitConfig initConfig = InitConfig()
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