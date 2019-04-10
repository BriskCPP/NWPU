//#include "School_of_Electronics_and_Information/HUD/Graphic/Driver/Direct3D/v9/Window.h"
//���cppԴ�ļ���Ϊ��ʵ��ͷ�ļ��Ĺ���

#include "School_of_Electronics_and_Information/HUD/HUD.h"

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
							IDirect3DDevice9 * Window::getDevice() const
							{
								return this->device;
							}

							Window::InitConfig::InitConfig()
							{
								//
							}

							//����ĺ������ײ���
							void Window::render(void (*displayFunction)(
								const double totalTime,
								const double deltaTime,
								const Window &window
								)) const
							{
								MSG message;
								ZeroMemory(&message,sizeof(MSG));

								double appStartTime  = (double)timeGetTime();
								double lastDisplayFunctionEnterTime = appStartTime;

								//������Դ
								//Direct3D::v9::resource::OneFrameLifecycleResource::getInstance()->clear(device);

								while(message.message!=WM_QUIT)
								{
									if(PeekMessage(&message,0,0,0,PM_REMOVE))
									{
										TranslateMessage(&message);
										DispatchMessage(&message);
									}
									else
									{
										double currentDisplayFunctionEnterTime = (double)timeGetTime();
										displayFunction(
											currentDisplayFunctionEnterTime - appStartTime,
											currentDisplayFunctionEnterTime - lastDisplayFunctionEnterTime,
											*this);
										lastDisplayFunctionEnterTime = currentDisplayFunctionEnterTime;

										//�ͷ���������Ϊһ֡����Դ
										//Direct3D::v9::resource::OneFrameLifecycleResource::getInstance()->clear(device);
									}
								}
								//
							}

							Window::Window(
								int width,int height,bool fullScreen /* = false */,
								HINSTANCE hInstance /* = GetModuleHandle(NULL) */,
								std::string title /* = std::string("Direct3D") */,
								InitConfig initConfig /* = InitConfig() */ 
								)
							{
								this->width = width;
								this->height = height;
								this->hInstance = hInstance;



								//��ƴ�����
								WNDCLASS windowClass;
								windowClass.style = CS_HREDRAW | CS_VREDRAW;
								windowClass.lpfnWndProc = (WNDPROC)defaultWindowProc;
								windowClass.cbClsExtra = 0;
								windowClass.cbWndExtra = 0;
								windowClass.hInstance = hInstance;
								windowClass.hIcon = LoadIcon(0,IDI_APPLICATION);
								windowClass.hCursor = LoadCursor(0, IDC_ARROW);
								windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
								windowClass.lpszMenuName = 0;
								windowClass.lpszClassName = TEXT("Direct3D Window");
								//ע�ᴰ����
								if(!RegisterClass(&windowClass))
								{
									MessageBoxA(0,"RegisterClass Failed",0,0);
									exit(-1);//�������˳�
								}
								//��������
								//����ĵ�һ���������������洴��������
								//HWND hwnd = CreateWindow(TEXT("Direct3D Window"),TEXT("Direct3D project"),WS_EX_TOPMOST|WS_OVERLAPPEDWINDOW,0,0,width,height,0,0,hInstance,0);
								//����ĸı���Ϊ�˽�ֹ���ڸı��С
								//this->hwnd = CreateWindow(TEXT("Direct3D Window"),TEXT("Direct3D project"),WS_EX_TOPMOST|(WS_OVERLAPPEDWINDOW^WS_THICKFRAME),0,0,width,height,0,0,hInstance,0);
								//����ĸı���Ϊ���ⲿ����Ĵ��ڱ���
								using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Driver::Direct3D::Util::Converter::TextConverter;

								LPWSTR windowTitle = NULL;
								TextConverter::stringToWideChar(title,windowTitle);
								this->hwnd = CreateWindow(TEXT("Direct3D Window"),windowTitle,WS_EX_TOPMOST|(WS_OVERLAPPEDWINDOW^WS_THICKFRAME),0,0,this->width,this->height,0,0,hInstance,0);
								delete[] windowTitle;
								//��ʾ�����´���
								if(!this->hwnd)
								{
									MessageBoxA(0,"Direct3D CreateWindow Failed",0,0);
									exit(-1);
								}

								ShowWindow(this->hwnd,SW_SHOW);
								UpdateWindow(this->hwnd);

								//����Direct3D 9�ӿ�
								//������ԭʼ�ķ�ֹ��Ⱦȫ�������ռ�ķ���
								IDirect3D9 *direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
								if(!direct3D9)
								{
									MessageBoxA(0,"Direct3DCreate9() Failed",0,0);
									exit(-1);
								}

								D3DCAPS9 caps;
								direct3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
								//DWORD vertexProcessingByHardwareOrSoftwareFlag = (caps.DevCaps&D3DDEVCAPS_HWTRANSFORMANDLIGHT)?D3DCREATE_HARDWARE_VERTEXPROCESSING:D3DCREATE_SOFTWARE_VERTEXPROCESSING;
								DWORD vertexProcessingByHardwareOrSoftwareFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
								if(caps.DevCaps&D3DDEVCAPS_HWTRANSFORMANDLIGHT)
									vertexProcessingByHardwareOrSoftwareFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
								else vertexProcessingByHardwareOrSoftwareFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

								//��������
								D3DPRESENT_PARAMETERS presentParameters;
								presentParameters.BackBufferWidth = width;
								presentParameters.BackBufferHeight = height;
								presentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
								presentParameters.BackBufferCount = 1;
								//presentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
								presentParameters.MultiSampleType = D3DMULTISAMPLE_16_SAMPLES;;
								presentParameters.MultiSampleQuality = 0;
								presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
								presentParameters.hDeviceWindow = hwnd;
								presentParameters.Windowed = !fullScreen;
								presentParameters.EnableAutoDepthStencil = true;
								presentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
								presentParameters.Flags = 0;
								presentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
								presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

								//DepthFormat ö��
								//https://docs.microsoft.com/zh-cn/previous-versions/dotnet/netframework-3.5/ms129550%28v%3dvs.90%29
								//D32	һ�� 32 λ z ������λ��ȡ�
								//D15S1	���� 16 λ z ������λ��ȣ����� 15 λ��Ϊ���ͨ�������ģ�1 λ��Ϊģ��ͨ�������ġ�
								//D24S8	һ������ 24 λ��ȣ�ʹ�� 24 λ�����ʽ - 20E4���� 8 λģ�ߵķ�������ʽ��
								//D16	16 λ z ������λ��ȡ�
								//D24X8	һ���� 24 λ�������ͨ���� 32 λ z ������λ��ȡ�
								//D24X4S4	һ�� 32 λ z ������λ��ȣ����� 24 λ�������ͨ����4 λ����ģ��ͨ����

								//�����豸
								//todo:�������ǲ��ǿ��Ըĳ�promise�����Ļص�����
								//������Ҫдһ�����ߵĻ��ǲ�������̫���ˣ�
								
								D3DDEVTYPE deviceType = D3DDEVTYPE_HAL;
								//long
								HRESULT hResult = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, this->hwnd, vertexProcessingByHardwareOrSoftwareFlag, &presentParameters, &(this->device));
								if (FAILED(hResult))
								{
									presentParameters.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
									hResult = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, this->hwnd, vertexProcessingByHardwareOrSoftwareFlag, &presentParameters, &(this->device));
									if(FAILED(hResult))
									{
										presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
										presentParameters.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
										hResult = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, this->hwnd, vertexProcessingByHardwareOrSoftwareFlag, &presentParameters, &(this->device));
										if (FAILED(hResult))
										{
											presentParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
											hResult = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, this->hwnd, vertexProcessingByHardwareOrSoftwareFlag, &presentParameters, &(this->device));
											if (FAILED(hResult))
											{
												MessageBoxA(0, "Direct3D9CreateDeviceFailed", 0, 0);
												//�ͷ���Դ
												direct3D9->Release();
												exit(-1);
											}
										}
									}
								}
								direct3D9->Release();
							}

							//Ĭ�ϵĴ��ڹ��̴�����
							LRESULT CALLBACK  Window::defaultWindowProc(
								HWND hwnd,
								UINT uMessage,
								WPARAM wParam,
								LPARAM lParam
								)
							{
								switch(uMessage)
								{
								case WM_DESTROY:
									::PostQuitMessage(0);
									break;
								case WM_KEYDOWN:
									if(wParam == VK_ESCAPE)
										::DestroyWindow(hwnd);
									break;
								}
								return DefWindowProc(hwnd,uMessage,wParam,lParam);
							}
						}
					}
				}
			}
		}
	}
}