#pragma once

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
							class ProtoPointerHolder
							{
							public:
								Prototype *protoPointer;
								unsigned int referenceCount;

								ProtoPointerHolder(Prototype *protoPointer)
								{
									this->protoPointer = protoPointer;
									referenceCount = 1;
								}
								//析构函数，释放内存
								~ProtoPointerHolder()
								{
									delete protoPointer;
								}
							};

							ProtoPointerHolder *protoPointerHolder;
						public:
							ProtoPointerHolder *getProtoPointerHolder() const
							{
								return this->protoPointerHolder;
							}


							SimpleSharedPointer(Prototype *protoPointer) :protoPointerHolder(new ProtoPointerHolder(protoPointer))
							{
								//该构造函数主要用来初始化
							}
							//拷贝构造函数要把引用数+1;
							SimpleSharedPointer(const SimpleSharedPointer &toCopy) :protoPointerHolder(toCopy.getProtoPointerHolder())
							{
								++this->protoPointerHolder->referenceCount;
							}

							//重载赋值操作符
							SimpleSharedPointer &operator=(const SimpleSharedPointer &sharedPointer)
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
							Prototype operator*() const
							{
								return *(protoPointerHolder->protoPointer);
							}
							Prototype operator->() const
							{
								return *(protoPointerHolder->protoPointer);
							}
						};
					}
				}
			}
		}
	}
}