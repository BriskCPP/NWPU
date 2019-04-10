#pragma once
#include <vector>
#include "../Vector.h"
//��ʾ����ĳ�����

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
						protected:
							//
							Vector relativePosition;
							Vector relativeRotation;
							Vector relativeScale;

							DisplayObject(
								Vector relativePosition = Vector(0,0,0),
								Vector relativeRotation = Vector(0,0,0),
								Vector relativeScale = Vector(1,1,1)
								);
						public:
							//�����������Ǳ����õĶ���Ŀռ����λ�ã�������ת�;������ţ�
							//�ɵ�����������ģ���һ����DisplayObject�������

							//����λ�û��ܵ���һ��ֱ����һ��������ת��Ӱ�졣
							//��ת��ȻҲ���ܵ�ֱ����һ�����ۼ���ת��Ӱ��
							virtual void render(
								Vector absolutePosition = Vector(0,0,0),
								Vector absoluteRotation = Vector(0,0,0),
								Vector absoluteScale = Vector(1,1,1)
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
								Vector absolutePosition = Vector(0,0,0),
								Vector absoluteRotation = Vector(0,0,0),
								Vector absoluteScale = Vector(1,1,1));
							
							//Ĭ�Ϲ��캯��
							Composite(
								Vector relativePosition = Vector(0,0,0),
								Vector relativeRotation = Vector(0,0,0),
								Vector relativeScale = Vector(1,1,1));
							//������������������������
							std::vector<DisplayObject *>::size_type add(
								DisplayObject *displayObject);
							void clear();//������������

							//todo:��û�������ɾ�Ĳ���
						};
					}
				}
			}
		}
	}
}