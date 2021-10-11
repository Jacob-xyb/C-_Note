#include <time.h>
#include "../Jx_进阶案例.h"
//This is a function

/*
1、rand()不需要参数，它会返回一个从0到最大随机数的任意整数，最大随机数的大小通常是固定的一个大整数-> //RAND_MAX = 32767 = 2^15 - 1
1000，0000，0000，0000 表示-0，因为零已经有了，所以规定这个表示-32768，这个不是计算出来的，而是规定。1111,1111,1111,1111是-32767
*/
void Jx_rand_001()
{
	srand(time(NULL));	//set seed
	for (int i = 0; i < 10; i++)
	{
		cout << rand() << " ";
	}
	cout << endl;
	cout << RAND_MAX << endl;
}
/*
2、如果你要产生0~99这100个整数中的一个随机整数，可以表达为：int num = rand() % 100;
	 这样，num的值就是一个0~99中的一个随机数了。
	 注意：这样的随机数，概率是不同的。

3、如果要产生1~100，则是这样：int num = rand() % 100 + 1;

4、总结来说，可以表示为：int num = rand() % n +a;
	 其中的a是起始值，n-1+a是终止值，n是整数的范围。

5、一般性：rand() % (b-a+1)+ a ;    就表示  a~b 之间的一个随机整数。
*/
void Jx_rand_002()
{
	srand(time(NULL));	//set seed
	for (int i = 0; i < 10; i++)
	{
		cout << rand()%100 << " ";
	}
	cout << endl;
}
/*
6、若要产生0~1之间的小数，则可以先取得0~10的整数，然后均除以10即可得到“随机到十分位”的10个随机小数。
	 若要得到“随机到百分位”的随机小数，则需要先得到0~100的10个整数，然后均除以100，其它情况依 此类推。
*/
void Jx_rand_003()
{
	srand(time(NULL));	//set seed
	for (int i = 0; i < 10; i++)
	{
		cout << rand() % 1000 / 1000. << " ";
	}
	cout << endl;
}
/*
7、通常rand()产生的随机数在每次运行的时候都是与上一次相同的，这样是为了便于程序的调试。
	 若要产生每次不同的随机数，则可以使用srand( seed )函数进行产生随机化种子，随着seed的不同，就能够产生不同的随机数。
8、还可以包含time.h头文件，然后使用srand(time(0))来使用当前时间使随机数发生器随机化，这样就可以保证每两次运行时可以得到不同的随机数序列，同时这要求程序的两次运行的间隔超过1秒。
函数说明 :
因为rand() 的内部实现是用线性同余法做的，它不是真的随机数，只不过是因为其周期特别长，所以有一定的范围里可看成是随机的，
*/