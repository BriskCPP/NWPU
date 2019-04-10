#include "School_of_Electronics_and_Information/HUD/Graphic/Driver/Direct3D/Util/Converter.h"
//���cppԴ�ļ�����Ϊ��ʵ��ͷ�ļ��Ĺ������Ե�ȻҪ�������ͷ�ļ�

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
						namespace Util
						{
							namespace Converter
							{
								int TextConverter::multiByteToWideChar(
									const char *toConvert,LPWSTR &result
									)
								{
									int resultLength = MultiByteToWideChar(CP_ACP,0,toConvert,-1,NULL,0);
									result = (WCHAR *)malloc( resultLength*sizeof(wchar_t) );
									MultiByteToWideChar(CP_ACP,0, toConvert, -1, result, resultLength);
									return resultLength;
								}

								int TextConverter::stringToWideChar(
									const std::string &toConvert,LPWSTR &result
									)
								{
									return multiByteToWideChar(toConvert.c_str(),result);
								}
							}
						}
					}
				}
			}
		}
	}
}