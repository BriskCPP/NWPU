#include "School_of_Electronics_and_Information/HUD/Graphic/Engine/Component/D3D9/D3D9Component.h"

#include <iostream>


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
						namespace D3D9
						{

							void LineList::render(
								const Vector &absolutePosition /* = Vector(0,0,0) */,
								const Vector &absoluteRotation /* = Vector(0,0,0) */,
								const Vector &absoluteScale /* = Vector(1,1,1) */)
							{
								//�ⲿ�ֲ������ѵģ���ΪҪ���ݾ���λ�á�������ת�;�������
								//���㶥������
								//����Ӧ���������ģ�Ϊ�˼�������ڱ������в�ʹ��ê��anchor�ĸ���
								std::vector<std::pair<Vertex, Vertex>> vertexToRender = this->lines;
								//ѡ���½�һ�������Ǹı�ԭ������Ϊ�˿��Զ�ε���
								for (std::vector<std::pair<Vertex, Vertex>>::iterator lineIterator = vertexToRender.begin();
									lineIterator != vertexToRender.end(); lineIterator++
									)
								{
									//���������ţ�����ת����ƽ�ƣ�������Ϊ�ͷ�����
									//1.����
									lineIterator->first.x *= static_cast<float>(absoluteScale.getX());
									lineIterator->first.y *= static_cast<float>(absoluteScale.getY());
									lineIterator->first.z *= static_cast<float>(absoluteScale.getZ());
									lineIterator->second.x *= static_cast<float>(absoluteScale.getX());
									lineIterator->second.y *= static_cast<float>(absoluteScale.getY());
									lineIterator->second.z *= static_cast<float>(absoluteScale.getZ());
									//2.��ת
									//emmmmm��ת�Ļ������������Ե���Vector��rotate����ȥ��
									//ֱ��ת����Ϳ�����
									Vector temp;
									temp = Vector(
										lineIterator->first.x,
										lineIterator->first.y,
										lineIterator->first.z
									).rotate(absoluteRotation);
									lineIterator->first.x = static_cast<float>(temp.getX());
									lineIterator->first.y = static_cast<float>(temp.getY());
									lineIterator->first.z = static_cast<float>(temp.getZ());

									temp = Vector(
										lineIterator->second.x,
										lineIterator->second.y,
										lineIterator->second.z
									).rotate(absoluteRotation);
									lineIterator->second.x = static_cast<float>(temp.getX());
									lineIterator->second.y = static_cast<float>(temp.getY());
									lineIterator->second.z = static_cast<float>(temp.getZ());
									//3.ƽ��
									temp = Vector(
										lineIterator->first.x,
										lineIterator->first.y,
										lineIterator->first.z
									) + absolutePosition;
									lineIterator->first.x = static_cast<float>(temp.getX());
									lineIterator->first.y = static_cast<float>(temp.getY());
									lineIterator->first.z = static_cast<float>(temp.getZ());

									temp = Vector(
										lineIterator->second.x,
										lineIterator->second.y,
										lineIterator->second.z
									) + absolutePosition;
									lineIterator->second.x = static_cast<float>(temp.getX());
									lineIterator->second.y = static_cast<float>(temp.getY());
									lineIterator->second.z = static_cast<float>(temp.getZ());
									
								}

								//���vertexBufferָ�벻ΪNULL��һ��Ҫ�ͷţ��Ա����ڴ�й©
								if (this->vertexBuffer != NULL) this->vertexBuffer->Release();

								//����VertexBuffer
								this->window.getDevice()->CreateVertexBuffer(
									2 * vertexToRender.size() * sizeof(Vertex),
									D3DUSAGE_WRITEONLY, Vertex::format,
									D3DPOOL_MANAGED, &(this->vertexBuffer), 0
								);

								Vertex *vertexPointer = NULL;
								this->vertexBuffer->Lock(0, 0, (void **)&vertexPointer, 0);

								UINT index = 0;
								for (std::vector<std::pair<Vertex, Vertex>>::iterator lineIterator = vertexToRender.begin();
									lineIterator != vertexToRender.end(); lineIterator++)
								{
									*(vertexPointer + index) = lineIterator->first;
									++index;
									*(vertexPointer + index) = lineIterator->second;
									++index;
									//��Ȼ�����һ��д��ֻ��Ҫ���У����������һ���֪���ܲ�����������
								}
								this->vertexBuffer->Unlock();

								//������Ⱦ
								this->window.getDevice()->SetStreamSource(0, this->vertexBuffer, 0, sizeof(Vertex));
								this->window.getDevice()->SetFVF(Vertex::format);//���������ʽ
								this->window.getDevice()->DrawPrimitive(D3DPT_LINELIST, 0, vertexToRender.size());
								//����ͼԪ
							}

							//�����ⲿ��Ӧ�����������

							//ָ�������ʽ
							const DWORD LineList::Vertex::format = D3DFVF_XYZ | D3DFVF_DIFFUSE;

							LineList::LineList(
								const Window &window,
								const std::vector<std::pair<Vertex, Vertex>> &lines,
								const Vector &relativePosition /* = Vector(0,0,0) */,
								const Vector &relativeRotation /* = Vector(0,0,0) */,
								const Vector &relativeScale /* = Vector(1,1,1) */
							) :DisplayObject(relativePosition, relativeRotation, relativeScale),window(window)
							{
								this->vertexBuffer = NULL;//�ڳ�ʼ�׶ΰ������Ϊ0
								this->lines = lines;
							}

							LineList::~LineList()
							{
								//��������
								if (this->vertexBuffer != NULL)
								{
									//�ͷ�
									vertexBuffer->Release();
								}
							}
						}
					}
				}
			}
		}
	}
}