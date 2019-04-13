#pragma once

#include <iostream>

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
					/**
					 * 在这个命名空间中的智能指针类没有防止循环引用的问题
					 */
					namespace smart_pointer
					{
						template<typename Prototype>
						class SimpleSharedPointer
						{
						private:
							//用于保存原始指针的类
							template<typename Prototype_PointerHolder>
							class ProtoPointerHolder
							{
							public:
								Prototype_PointerHolder *const protoPointer;
								unsigned int referenceCount;

								ProtoPointerHolder(Prototype_PointerHolder *protoPointer) :protoPointer(protoPointer)
								{
									referenceCount = 1;
								}
								//析构函数，释放内存
								~ProtoPointerHolder()
								{
									delete protoPointer;
								}

								//这个holder对于每一个原始指针（裸指针）应该都是唯一的
								//要转变应该也是要在外部去转变
							};

							ProtoPointerHolder<Prototype> *protoPointerHolder;
						public:


							//转换SimpleSharedPointer的类型
							//这样的抽象其实是很好的，但是就很难考虑如何实现
							//各种各样的构造函数其实都是一样的
							//那可能就要通过将cast设为友元函数去实现了
							//但是又有点肮脏，我还是应该从拷贝构造函数来入手
							/*
							template<typename DestinationPrototype>//目标类型
							SimpleSharedPointer<DestinationPrototype> cast()
							{
								
							}

							template<typename DestinationPrototype>//目标类型
							friend SimpleSharedPointer<DestinationPrototype> cast();
							*/

							//哎，所以说写代码也是需要灵感，需要灵光一闪的。
							//就是突然灵光一闪地想到了这样的功能用构造函数去实现更好，
							//因为如果用cast这种方法的话，就需要改变左要返回的另一个对象里的值(pointerHolder)
							//如果用setter methods就破坏了封装性
							//用友元好像又有点多余，有时候真的就是突然想带了用构造函数。
							//所以，我有在代码中写日记的习惯


							ProtoPointerHolder<Prototype> *getProtoPointerHolder() const
							{
								return this->protoPointerHolder;
							}


							SimpleSharedPointer(Prototype *protoPointer) :protoPointerHolder(
								new ProtoPointerHolder<Prototype>(protoPointer)
							) {}


							/*
							//拷贝构造函数要把引用数+1;
							SimpleSharedPointer(
								const SimpleSharedPointer<Prototype> &toCopy
							) :protoPointerHolder(toCopy.getProtoPointerHolder())
							{
								++this->protoPointerHolder->referenceCount;
							}
							*/
							template<typename OriginalPrototype>//原有的指针所指向的数据类型 
							SimpleSharedPointer(
								const SimpleSharedPointer<OriginalPrototype> &originalSharedPointer
							):protoPointerHolder(
								reinterpret_cast<ProtoPointerHolder<Prototype> *>(
									originalSharedPointer.getProtoPointerHolder()
									)
							)
							{
								++this->protoPointerHolder->referenceCount;
							}
							//经过实践得知要加上这样一个特化的拷贝构造函数
							//如果不存在下面这样一个默认构造函数，那么默认的拷贝构造函数会被编译器合成
							//那么引用计数就不会+1，引起错误
							SimpleSharedPointer(
								const SimpleSharedPointer<Prototype> &originalSharedPointer
							):protoPointerHolder(originalSharedPointer.getProtoPointerHolder())
							{
								++this->protoPointerHolder->referenceCount;
							}

							//重载赋值操作符
							SimpleSharedPointer<Prototype> &operator=(
								const SimpleSharedPointer<Prototype> &sharedPointer
								)
							{
								//如果是自己，则什么都不做
								if (&sharedPointer == this) return *this;
								//首先将当前类的引用计数值-1，如果减到0，就删除引用。
								if (--protoPointerHolder->referenceCount == 0)
									delete protoPointerHolder;
								protoPointerHolder = sharedPointer.getProtoPointerHolder();
								++protoPointerHolder->referenceCount;
								return *this;
							}
							//析构函数
							//引用计数减一，如果减到零，就删除引用
							~SimpleSharedPointer()
							{
								if (--protoPointerHolder->referenceCount == 0)
									delete protoPointerHolder;
							}

							//下面是模仿指针的功能类
							//因为我们的这样一个SimpleSharedPointer主要针对抽象类
							//所以不能重载解引用(*)运算符，否则无法实例化模板
							//Prototype operator*() const
							//{
							//	return *(protoPointerHolder->protoPointer);
							//}
							Prototype *operator->() const
							{
								return protoPointerHolder->protoPointer;
							}
						};
					}
				}
			}
		}
	}
}