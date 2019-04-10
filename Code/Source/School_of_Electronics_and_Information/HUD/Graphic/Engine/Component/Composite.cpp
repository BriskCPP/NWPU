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
						//这三个参数是被调用的对象的空间绝对位置，绝对旋转和绝对缩放，
						//由调用这个函数的（上一级）DisplayObject计算而来

						//绝对位置会受到上一级直到上一级的总旋转的影响。
						//旋转显然也会受到直到上一级的累加旋转的影响
						void Composite::render(
							Vector absolutePosition /* = Vector(0,0,0) */,
							Vector absoluteRotation /* = Vector(0,0,0) */,
							Vector absoluteScale /* = Vector(1,1,1) */)
						{
							for(std::vector<DisplayObject *>::iterator childrenIterator = this->children.begin();
								childrenIterator!=this->children.end();childrenIterator++
								)
							{
								//记住：这个元素的绝对位置会受到累加旋转的影响
								/*
								Vector currentChildAbsolutePosition;
								Vector currentChildAbsoluteRotation;
								Vector currentChildAbsoluteScale;

								//这个关系应该是成立的，要写Demo去验证
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
						//下面这几个函数都非常非常地简单
						Composite::Composite(
							Vector relativePosition /* = Vector(0,0,0) */,
							Vector relativeRotation /* = Vector(0,0,0) */, 
							Vector relativeScale /* = Vector(1,1,1) */
							):DisplayObject(relativePosition,relativeRotation,relativeScale)
						{
							//我发现自己越来越6了啊
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
						//下面的这部分一般是不变的

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