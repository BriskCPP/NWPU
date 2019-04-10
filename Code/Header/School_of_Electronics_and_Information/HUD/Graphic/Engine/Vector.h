#pragma once

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
					class Vector
					{
					private:
						double x,y,z;
					public:
						//默认构造函数
						Vector(
							double x = 0,
							double y = 0,
							double z = 0
							);
						//拷贝构造函数
						Vector(const Vector &vector);

						void set(
							const double x,
							const double y,
							const double z
							);
						void setX(const double x);
						void setY(const double y);
						void setZ(const double z);

						double getX() const;
						double getY() const;
						double getZ() const;

						//重载向量常用的运算符
						Vector operator+(const Vector &vector);
						Vector operator-(const Vector &vector);
						Vector operator*(const Vector &vector);

						//用于旋转向量
						Vector rotate(const Vector &rotation);
					};
				}
			}
		}
	}
}