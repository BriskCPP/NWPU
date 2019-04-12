#pragma once
#include <vector>
#include "../Vector.h"
//显示对象的抽象类

#include <iostream>

#include "School_of_Electronics_and_Information/HUD/Graphic/Util/smart_pointer.hpp"
using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Util::smart_pointer::SimpleSharedPointer;

//Direct3D 9特定的组件实现

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
					namespace Component
					{
						using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Engine::Vector;
						//该类相当于所有显示组件的基类
						class DisplayObject
						{
						
						private:
							Vector relativePosition;
							Vector relativeRotation;
							Vector relativeScale;
						protected:
							DisplayObject(
								const Vector &relativePosition = Vector(0,0,0),
								const Vector &relativeRotation = Vector(0,0,0),
								const Vector &relativeScale = Vector(1,1,1)
								);
						public:
							//这三个参数是被调用的对象的空间绝对位置，绝对旋转和绝对缩放，
							//由调用这个函数的（上一级）DisplayObject计算而来

							//绝对位置会受到上一级直到上一级的总旋转的影响。
							//旋转显然也会受到直到上一级的累加旋转的影响
							virtual void render(
								const Vector &absolutePosition = Vector(0,0,0),
								const Vector &absoluteRotation = Vector(0,0,0),
								const Vector &absoluteScale = Vector(1,1,1)
								) = 0;

							//每一个显示组件都必须有这三个getter methods
							//不然没法计算绝对参数

							//设置成虚函数是因为不同的组件可能有不同的实现方式
							virtual Vector getRelativePosition();
							virtual Vector getRelativeRotation();
							virtual Vector getRelativeScale();
						};

						//Composite 组合模式
						class Composite:public DisplayObject
						{
						private:
							std::vector<DisplayObject *> children;
						public:
							void render(
								const Vector &absolutePosition = Vector(0,0,0),
								const Vector &absoluteRotation = Vector(0,0,0),
								const Vector &absoluteScale = Vector(1,1,1));
							
							//默认构造函数
							explicit Composite(
								const Vector &relativePosition = Vector(0,0,0),
								const Vector &relativeRotation = Vector(0,0,0),
								const Vector &relativeScale = Vector(1,1,1));
							//增加子组件，返回子组件总数
							std::vector<DisplayObject *>::size_type add(
								DisplayObject *displayObject
							);


							template<typename DisplayObjectPrototype>
							std::vector<DisplayObject *>::size_type add(
								const SimpleSharedPointer<DisplayObjectPrototype> &displayObjectSimpleSharedPointer
							)
							{
								this->children.push_back(displayObjectSimpleSharedPointer.getProtoPointerHolder()->protoPointer);
								return this->children.size();
							}

							template<typename  DisplayObjectPrototype>
							std::vector<DisplayObject *>::size_type add(
								const std::vector<SimpleSharedPointer<DisplayObjectPrototype>> &displayObjectSimpleSharedPointersVector
							)
							{
								//内嵌依赖类型名 要加typename关键字
								for (typename std::vector<SimpleSharedPointer<DisplayObjectPrototype>>::const_iterator sharedPointerVectorIterator = displayObjectSimpleSharedPointersVector.begin();
									sharedPointerVectorIterator != displayObjectSimpleSharedPointersVector.end(); ++sharedPointerVectorIterator
									)
								{
									this->add(*sharedPointerVectorIterator);
								}
								return this->children.size();
							}

							void clear();//清除所有子组件

							//todo:还没有完成增删改查呢
						};
					}
				}
			}
		}
	}
}