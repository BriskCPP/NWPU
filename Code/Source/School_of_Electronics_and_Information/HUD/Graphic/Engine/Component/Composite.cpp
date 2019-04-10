#include "School_of_Electronics_and_Information/HUD/Graphic/Engine/Component/component.h"

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
							Vector absolutePosition /* = Vector(0,0,0) */,
							Vector absoluteRotation /* = Vector(0,0,0) */,
							Vector absoluteScale /* = Vector(1,1,1) */)
						{
							for(std::vector<DisplayObject *>::iterator childrenIterator = this->children.begin();
								childrenIterator!=this->children.end();childrenIterator++
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
							Vector relativePosition /* = Vector(0,0,0) */,
							Vector relativeRotation /* = Vector(0,0,0) */, 
							Vector relativeScale /* = Vector(1,1,1) */
							):DisplayObject(relativePosition,relativeRotation,relativeScale)
						{
							//�ҷ����Լ�Խ��Խ6�˰�
						}

						std::vector<DisplayObject *>::size_type Composite::add(DisplayObject *displayObject)
						{
							this->children.push_back(displayObject);
							return this->children.size();
						}
						void Composite::clear()
						{
							this->children.clear();
						}
						//������ⲿ��һ���ǲ����

						DisplayObject::DisplayObject(
							Vector relativePosition /* = Vector(0,0,0) */,
							Vector relativeRotation /* = Vector(0,0,0) */,
							Vector relativeScale /* = Vector(1,1,1) */ )
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