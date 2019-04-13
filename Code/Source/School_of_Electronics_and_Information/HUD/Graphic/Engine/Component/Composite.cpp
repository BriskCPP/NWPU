#include "School_of_Electronics_and_Information/HUD/Graphic/Engine/Component/component.hpp"

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
						//�����������Ǳ����õĶ���Ŀռ����λ�ã�������ת�;������ţ�
						//�ɵ�����������ģ���һ����DisplayObject�������

						//����λ�û��ܵ���һ��ֱ����һ��������ת��Ӱ�졣
						//��ת��ȻҲ���ܵ�ֱ����һ�����ۼ���ת��Ӱ��
						void Composite::render(
							const Vector &absolutePosition /* = Vector(0,0,0) */,
							const Vector &absoluteRotation /* = Vector(0,0,0) */,
							const Vector &absoluteScale /* = Vector(1,1,1) */)
						{
							for(std::vector<SimpleSharedPointer<DisplayObject>>::const_iterator childrenIterator = this->childrenPointerVector.begin();
								childrenIterator!=this->childrenPointerVector.end();++childrenIterator
								)
							{
								//��ס�����Ԫ�صľ���λ�û��ܵ��ۼ���ת��Ӱ��
								/*
								Vector currentChildAbsolutePosition;
								Vector currentChildAbsoluteRotation;
								Vector currentChildAbsoluteScale;

								//�����ϵӦ���ǳ����ģ�ҪдDemoȥ��֤
								currentChildAbsoluteRotation =
								absolutePosition + ((*childrenIterator)->getRelativePosition()).rotate(absoluteRotation);
								currentChildAbsoluteRotation =
								absoluteRotation + ((*childrenIterator)->getRelativeRotation());
								currentChildAbsoluteScale =
								absoluteScale * ((*childrenIterator)->getRelativeScale());

								(*childrenIterator)->render(
								currentChildAbsolutePosition,
								currentChildAbsoluteRotation,
								currentChildAbsoluteScale
								);
								*/
								(*childrenIterator)->render(
									absolutePosition + ((*childrenIterator)->getRelativePosition()).rotate(absoluteRotation),
									absoluteRotation + ((*childrenIterator)->getRelativeRotation()),
									absoluteScale * ((*childrenIterator)->getRelativeScale()));
							}
						}

						//�����⼸���������ǳ��ǳ��ؼ�
						Composite::Composite(
							const Vector &relativePosition /* = Vector(0,0,0) */,
							const Vector &relativeRotation /* = Vector(0,0,0) */,
							const Vector &relativeScale /* = Vector(1,1,1) */
							):DisplayObject(relativePosition,relativeRotation,relativeScale)
						{
							//�ҷ����Լ�Խ��Խ6�˰�
						}

						void Composite::clear()
						{
							this->childrenPointerVector.clear();
						}
						//������ⲿ��һ���ǲ����

						DisplayObject::DisplayObject(
							const Vector &relativePosition /* = Vector(0,0,0) */,
							const Vector &relativeRotation /* = Vector(0,0,0) */,
							const Vector &relativeScale /* = Vector(1,1,1) */ )
						{
							this->relativePosition = relativePosition;
							this->relativeRotation = relativeRotation;
							this->relativeScale = relativeScale;
						}
						//the following getter methods are virtual method
						//instead of pure virtual methods
						//which means different type of DisplayObject
						//may have different implementation
						//and will easily be able to override
						Vector DisplayObject::getRelativePosition()
						{
							return this->relativePosition;
						}

						Vector DisplayObject::getRelativeRotation()
						{
							return this->relativeRotation;
						}

						Vector DisplayObject::getRelativeScale()
						{
							return this->relativeScale;
						}
					}
				}
			}
		}
	}
}