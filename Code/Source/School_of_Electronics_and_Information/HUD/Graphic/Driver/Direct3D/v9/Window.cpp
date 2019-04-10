//#include "School_of_Electronics_and_Information/HUD/Graphic/Driver/Direct3D/v9/Window.h"
//这个cpp源文件是为了实现头文件的功能

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

							//下面的函数轻易不变
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

								//清理资源
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

										//释放生命周期为一帧的资源
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



								//设计窗口类
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
								//注册窗口类
								if(!RegisterClass(&windowClass))
								{
									MessageBoxA(0,"RegisterClass Failed",0,0);
									exit(-1);//非正常退出
								}
								//创建窗口
								//这里的第一个参数必须是上面创建的类名
								//HWND hwnd = CreateWindow(TEXT("Direct3D Window"),TEXT("Direct3D project"),WS_EX_TOPMOST|WS_OVERLAPPEDWINDOW,0,0,width,height,0,0,hInstance,0);
								//这里的改变是为了禁止窗口改变大小
								//this->hwnd = CreateWindow(TEXT("Direct3D Window"),TEXT("Direct3D project"),WS_EX_TOPMOST|(WS_OVERLAPPEDWINDOW^WS_THICKFRAME),0,0,width,height,0,0,hInstance,0);
								//这里的改变是为了外部输入的窗口标题
								using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Driver::Direct3D::Util::Converter::TextConverter;

								LPWSTR windowTitle = NULL;
								TextConverter::stringToWideChar(title,windowTitle);
								this->hwnd = CreateWindow(TEXT("Direct3D Window"),windowTitle,WS_EX_TOPMOST|(WS_OVERLAPPEDWINDOW^WS_THICKFRAME),0,0,this->width,this->height,0,0,hInstance,0);
								delete[] windowTitle;
								//显示及更新窗口
								if(!this->hwnd)
								{
									MessageBoxA(0,"Direct3D CreateWindow Failed",0,0);
									exit(-1);
								}

								ShowWindow(this->hwnd,SW_SHOW);
								UpdateWindow(this->hwnd);

								//创建Direct3D 9接口
								//这是最原始的防止污染全局命名空间的方法
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

								//创建参数
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

								//DepthFormat 枚举
								//https://docs.microsoft.com/zh-cn/previous-versions/dotnet/netframework-3.5/ms129550%28v%3dvs.90%29
								//D32	一个 32 位 z 缓冲区位深度。
								//D15S1	对于 16 位 z 缓冲区位深度，其中 15 位是为深度通道保留的，1 位是为模具通道保留的。
								//D24S8	一个包含 24 位深度（使用 24 位浮点格式 - 20E4）和 8 位模具的非锁定格式。
								//D16	16 位 z 缓冲区位深度。
								//D24X8	一个将 24 位用于深度通道的 32 位 z 缓冲区位深度。
								//D24X4S4	一个 32 位 z 缓冲区位深度，其中 24 位用于深度通道，4 位用于模具通道。

								//创建设备
								//todo:在这里是不是可以改成promise那样的回调？？
								//但是又要写一个工具的话是不是问题太大了？
								
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
												//释放资源
												direct3D9->Release();
												exit(-1);
											}
										}
									}
								}
								direct3D9->Release();
							}

							//默认的窗口过程处理函数
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