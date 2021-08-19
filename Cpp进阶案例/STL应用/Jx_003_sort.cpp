#include "../Jx_���װ���.h"

void sort_Jxtest001()
{
	vector<int> vec_v1{ 6,8,2,9,1,5 };
	sort(vec_v1.begin(), vec_v1.end());
	for (int i = 0; i < vec_v1.size(); i++) cout << vec_v1[i] << " ";
	cout << endl;
}

//==================================================
//ʵ��ԭ��
//	sort����������ʽ������/����/����
/*STL��sort()�㷨��������һ��SORT_MAX�����������жϣ��������SORT_MAX�Ͳ���Quick Sort���ֶεݹ�����һ���ֶκ��SORT_MAXС��ĳ����ֵ��Ϊ����Quick Sort�ĵݹ���ô�������Ķ��⿪�����͸���Insertion Sort���������򣩡�����ݹ��ι���������Heap Sort��
* 
����������ؼ��ĵط����������ѡ�������������ڷָ�ʱ������һ���յ����䣬��������ȫû�дﵽ�ָ��Ч����STL���õ�������Ϊmedian-of-three����ȡ�������е��ס�β�����������ط���Ԫ�أ�������ֵ��Ϊ���ᡣ
*/

//	��������Quick Sort�� 
void sort_Qsort001(vector<int>& a, int L,int H)
{
	//������������	//L >= H �ͽ���
	if (L < H)
	{
		//�Ե�ǰ��������
		//	����׼
		int pivot = a[L];
		//	��������
		int privotIndex = L;	//������׼��ǩ
		for (int i = L+1; i <= H; i++)
		{
			if (a[i] < pivot)
			{
				if (i - privotIndex == 1)
				{
					privotIndex++;
					continue;
				}
				privotIndex++;
				int temp = a[privotIndex];
				a[privotIndex] = a[i];
				a[i] = temp;
			}
		}
		//	����׼�����û�׼λ��
		a[L] = a[privotIndex];
		a[privotIndex] = pivot;

		//��С��Χ
		sort_Qsort001(a, L, privotIndex - 1);
		sort_Qsort001(a, privotIndex + 1,H);
	}
}

//		���߱ƽ��ķ���
void sort_Qsort002(vector<int>& a, int L, int H)
{
	//������������
	if (L < H)
	{
		// ��ȡ����׼
		int pivot = a[L];
		int lIndex = L;
		int hIndex = H;

		while(lIndex < hIndex)
		{
			//��H����ֱ��������pivotС��
			while (lIndex < hIndex && !(a[hIndex] < pivot))
			{
				hIndex--;
			}
			a[lIndex] = a[hIndex];
			//��L���ң�ֱ��������pivot���
			while (lIndex < hIndex && !(a[lIndex] > pivot))
			{
				lIndex++;
			}
			a[hIndex] = a[lIndex];
		}
		//��ʱlIndex == hIndex
		//	����׼�����û�׼λ��
		a[lIndex] = pivot;

		//��С��Χ
		sort_Qsort002(a, L, lIndex - 1);
		sort_Qsort002(a, lIndex + 1, H);
	}
}

//		�ɹ� ��nice
void sort_Qsort_test()
{
	vector<int> vec_v1{ 20,40,10,70,10,30 };
	//sort_Qsort001(vec_v1, 0, vec_v1.size() - 1);
	sort_Qsort002(vec_v1, 0, vec_v1.size() - 1);
	for (int i = 0; i < vec_v1.size(); i++)
	{
		cout << vec_v1[i] << " ";
	}
	cout << endl;
}

//	��������Insertion Sort��
void sort_Isort001(vector<int>& a)
{
	if (a.size() < 2) return;
	for (int i = 1; i < a.size(); i++)
	{
		while (true)
		{

		}
	}
}
//==================================================