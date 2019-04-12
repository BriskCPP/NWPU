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
					 * ����������ռ��е�����ָ����û�з�ֹѭ�����õ�����
					 */
					namespace smart_pointer
					{
						template<typename Prototype>
						class SimpleSharedPointer
						{
						private:
							//���ڱ���ԭʼָ�����
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
								//�����������ͷ��ڴ�
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
								//�ù��캯����Ҫ������ʼ��
							}
							//�������캯��Ҫ��������+1;
							SimpleSharedPointer(const SimpleSharedPointer &toCopy) :protoPointerHolder(toCopy.getProtoPointerHolder())
							{
								++this->protoPointerHolder->referenceCount;
							}

							//���ظ�ֵ������
							SimpleSharedPointer &operator=(const SimpleSharedPointer &sharedPointer)
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