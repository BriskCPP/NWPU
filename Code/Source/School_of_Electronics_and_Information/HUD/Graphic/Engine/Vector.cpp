#include "School_of_Electronics_and_Information/HUD/Graphic/Engine/Vector.h"
#include <cmath>

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
					Vector::Vector(
						double x /* = 0 */,
						double y /* = 0 */,
						double z /* = 0 */
						)
					{
						this->x = x;
						this->y = y;
						this->z = z;
					}

					Vector::Vector(const Vector &vector)
					{
						this->x = vector.getX();
						this->y = vector.getY();
						this->z = vector.getZ();
					}

					//setter methods
					void Vector::set(
						const double x,
						const double y,
						const double z
						)
					{
						this->x = x;
						this->y = y;
						this->z = z;
					}
					void Vector::setX(const double x)
					{
						this->x = x;
					}

					void Vector::setY(const double y)
					{
						this->y = y;
					}

					void Vector::setZ(const double z)
					{
						this->z = z;
					}

					//getter methods
					double Vector::getX() const
					{
						return this->x;
					}
					double Vector::getY() const
					{
						return this->y;
					}
					double Vector::getZ() const
					{
						return this->z;
					}

					Vector Vector::operator+(const Vector &vector)
					{
						return Vector(
							this->x + vector.getX(),
							this->y + vector.getY(),
							this->z + vector.getZ()
							);
					}
					Vector Vector::operator-(const Vector &vector)
					{
						return Vector(
							this->x - vector.getX(),
							this->y - vector.getY(),
							this->z - vector.getZ()
							);
					}
					Vector Vector::operator*(const Vector &vector)
					{
						return Vector(
							this->x * vector.getX(),
							this->y * vector.getY(),
							this->z * vector.getZ()
							);
					}

					Vector Vector::rotate(const Vector &rotation)
					{
						double x, y, z;
						//绕x轴旋转，x轴不变
						y = this->y*cos(rotation.getX()) - this->z*sin(rotation.getX());
						z = this->y*sin(rotation.getX()) + this->z*cos(rotation.getX());
						this->y = y;
						this->z = z;
						//绕y轴旋转，y轴不变
						x = this->x*cos(rotation.getY()) + this->z*sin(rotation.getY());
						z = 0 - this->x* sin(rotation.getY()) + this->z*cos(rotation.getY());
						this->x = x;
						this->z = z;
						//绕z轴旋转,z 轴不变
						x = this->x*cos(rotation.getZ()) - this->y*sin(rotation.getZ());
						y = this->x*sin(rotation.getZ()) + this->y*cos(rotation.getZ());
						this->x = x;
						this->y = y;

						return Vector(*this);
					}
				}
			}
		}
	}
}