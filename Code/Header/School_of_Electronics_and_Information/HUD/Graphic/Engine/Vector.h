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
						//Ĭ�Ϲ��캯��
						Vector(
							double x = 0,
							double y = 0,
							double z = 0
							);
						//�������캯��
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

						//�����������õ������
						Vector operator+(const Vector &vector);
						Vector operator-(const Vector &vector);
						Vector operator*(const Vector &vector);

						//������ת����
						Vector rotate(const Vector &rotation);
					};
				}
			}
		}
	}
}