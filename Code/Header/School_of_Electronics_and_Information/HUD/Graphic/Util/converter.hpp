#pragma once
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
				namespace Util
				{
					namespace converter
					{
						class TextConverter
						{
						public:
							static int multiByteToWideChar(const char *toConvert, LPWSTR &result);
							static int stringToWideChar(const std::string &toConvert, LPWSTR &result);
						};
					}
				}
			}
		}
	}
}