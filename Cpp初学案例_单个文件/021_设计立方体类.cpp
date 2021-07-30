/*
encoding: GB2312(936)
state:�����������
		������������������
		�ֱ���ȫ�ֺ����ͳ�Ա�����ж������������Ƿ����
*/

#include <iostream>
using namespace std;

class Cube
{
private:
	int m_l, m_w, m_h;
public:
	// ��������
	void setLength(int l, int w, int h)
	{
		m_l = l, m_w = w, m_h = h;
	}
	// ��ȡ����
	int getLength()
	{
		return m_l;
	}
	int getWidth()
	{
		return m_w;
	}
	int getHeight()
	{
		return m_l;
	}
	// ���㺯��
	int getFaceArea()
	{
		return 2 * (m_l * m_w + m_w * m_h + m_h * m_l);
	}
	int getVolume()
	{
		return m_l * m_w * m_h;
	}
	// ��Ա�����ж��Ƿ����
	bool isSame(Cube& a)
	{
		if (m_l == a.getLength() &&
			m_w == a.getWidth() &&
			m_h == a.getHeight())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

bool CubeisSame(Cube &a, Cube &b)
{
	if (a.getLength() == b.getLength() &&
		a.getWidth() == b.getWidth() &&
		a.getHeight() == b.getHeight())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	Cube c1;
	c1.setLength(10, 20, 30);
	cout << "������c1�ı����Ϊ��" << c1.getFaceArea() << endl;
	cout << "������c1�����Ϊ��" << c1.getVolume() << endl;

	Cube c2;
	c2.setLength(10, 20, 30);
	if (CubeisSame(c1,c2))
	{
		cout << "�������������" << endl;
	}
	else
	{
		cout << "���������岻���" << endl;
	}
	system("pause");
	return 0;
}

