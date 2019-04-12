#pragma once
#include <vector>
#include "../Vector.h"
//��ʾ����ĳ�����

#include <iostream>

#include "School_of_Electronics_and_Information/HUD/Graphic/Util/smart_pointer.hpp"
using NWPU::School_of_Electronics_and_Information::HUD::Graphic::Util::smart_pointer::SimpleSharedPointer;

//Direct3D 9�ض������ʵ��

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
						//�����൱��������ʾ����Ļ���
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
							//�����������Ǳ����õĶ���Ŀռ����λ�ã�������ת�;������ţ�
							//�ɵ�����������ģ���һ����DisplayObject�������

							//����λ�û��ܵ���һ��ֱ����һ��������ת��Ӱ�졣
							//��ת��ȻҲ���ܵ�ֱ����һ�����ۼ���ת��Ӱ��
							virtual void render(
								const Vector &absolutePosition = Vector(0,0,0),
								const Vector &absoluteRotation = Vector(0,0,0),
								const Vector &absoluteScale = Vector(1,1,1)
								) = 0;

							//ÿһ����ʾ�����������������getter methods
							//��Ȼû��������Բ���

							//���ó��麯������Ϊ��ͬ����������в�ͬ��ʵ�ַ�ʽ
							virtual Vector getRelativePosition();
							virtual Vector getRelativeRotation();
							virtual Vector getRelativeScale();
						};

						//Composite ���ģʽ
						class Composite:public DisplayObject
						{
						private:
							std::vector<DisplayObject *> children;
						public:
							void render(
								const Vector &absolutePosition = Vector(0,0,0),
								const Vector &absoluteRotation = Vector(0,0,0),
								const Vector &absoluteScale = Vector(1,1,1));
							
							//Ĭ�Ϲ��캯��
							explicit Composite(
								const Vector &relativePosition = Vector(0,0,0),
								const Vector &relativeRotation = Vector(0,0,0),
								const Vector &relativeScale = Vector(1,1,1));
							//������������������������
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
								//��Ƕ���������� Ҫ��typename�ؼ���
								for (typename std::vector<SimpleSharedPointer<DisplayObjectPrototype>>::const_iterator sharedPointerVectorIterator = displayObjectSimpleSharedPointersVector.begin();
									sharedPointerVectorIterator != displayObjectSimpleSharedPointersVector.end(); ++sharedPointerVectorIterator
									)
								{
									this->add(*sharedPointerVectorIterator);
								}
								return this->children.size();
							}

							void clear();//������������

							//todo:��û�������ɾ�Ĳ���
						};
					}
				}
			}
		}
	}
}