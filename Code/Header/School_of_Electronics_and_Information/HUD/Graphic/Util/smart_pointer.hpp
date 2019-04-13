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
					 * ����������ռ��е�����ָ����û�з�ֹѭ�����õ�����
					 */
					namespace smart_pointer
					{
						template<typename Prototype>
						class SimpleSharedPointer
						{
						private:
							//���ڱ���ԭʼָ�����
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
								//�����������ͷ��ڴ�
								~ProtoPointerHolder()
								{
									delete protoPointer;
								}

								//���holder����ÿһ��ԭʼָ�루��ָ�룩Ӧ�ö���Ψһ��
								//Ҫת��Ӧ��Ҳ��Ҫ���ⲿȥת��
							};

							ProtoPointerHolder<Prototype> *protoPointerHolder;
						public:


							//ת��SimpleSharedPointer������
							//�����ĳ�����ʵ�Ǻܺõģ����Ǿͺ��ѿ������ʵ��
							//���ָ����Ĺ��캯����ʵ����һ����
							//�ǿ��ܾ�Ҫͨ����cast��Ϊ��Ԫ����ȥʵ����
							//�������е㰹�࣬�һ���Ӧ�ôӿ������캯��������
							/*
							template<typename DestinationPrototype>//Ŀ������
							SimpleSharedPointer<DestinationPrototype> cast()
							{
								
							}

							template<typename DestinationPrototype>//Ŀ������
							friend SimpleSharedPointer<DestinationPrototype> cast();
							*/

							//��������˵д����Ҳ����Ҫ��У���Ҫ���һ���ġ�
							//����ͻȻ���һ�����뵽�������Ĺ����ù��캯��ȥʵ�ָ��ã�
							//��Ϊ�����cast���ַ����Ļ�������Ҫ�ı���Ҫ���ص���һ���������ֵ(pointerHolder)
							//�����setter methods���ƻ��˷�װ��
							//����Ԫ�������е���࣬��ʱ����ľ���ͻȻ������ù��캯����
							//���ԣ������ڴ�����д�ռǵ�ϰ��


							ProtoPointerHolder<Prototype> *getProtoPointerHolder() const
							{
								return this->protoPointerHolder;
							}


							SimpleSharedPointer(Prototype *protoPointer) :protoPointerHolder(
								new ProtoPointerHolder<Prototype>(protoPointer)
							) {}


							/*
							//�������캯��Ҫ��������+1;
							SimpleSharedPointer(
								const SimpleSharedPointer<Prototype> &toCopy
							) :protoPointerHolder(toCopy.getProtoPointerHolder())
							{
								++this->protoPointerHolder->referenceCount;
							}
							*/
							template<typename OriginalPrototype>//ԭ�е�ָ����ָ����������� 
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
							//����ʵ����֪Ҫ��������һ���ػ��Ŀ������캯��
							//�����������������һ��Ĭ�Ϲ��캯������ôĬ�ϵĿ������캯���ᱻ�������ϳ�
							//��ô���ü����Ͳ���+1���������
							SimpleSharedPointer(
								const SimpleSharedPointer<Prototype> &originalSharedPointer
							):protoPointerHolder(originalSharedPointer.getProtoPointerHolder())
							{
								++this->protoPointerHolder->referenceCount;
							}

							//���ظ�ֵ������
							SimpleSharedPointer<Prototype> &operator=(
								const SimpleSharedPointer<Prototype> &sharedPointer
								)
							{
								//������Լ�����ʲô������
								if (&sharedPointer == this) return *this;
								//���Ƚ���ǰ������ü���ֵ-1���������0����ɾ�����á�
								if (--protoPointerHolder->referenceCount == 0)
									delete protoPointerHolder;
								protoPointerHolder = sharedPointer.getProtoPointerHolder();
								++protoPointerHolder->referenceCount;
								return *this;
							}
							//��������
							//���ü�����һ����������㣬��ɾ������
							~SimpleSharedPointer()
							{
								if (--protoPointerHolder->referenceCount == 0)
									delete protoPointerHolder;
							}

							//������ģ��ָ��Ĺ�����
							//��Ϊ���ǵ�����һ��SimpleSharedPointer��Ҫ��Գ�����
							//���Բ������ؽ�����(*)������������޷�ʵ����ģ��
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