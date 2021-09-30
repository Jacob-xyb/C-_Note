#include "../Jx_���װ���.h"

// string�Ĺ��캯��
//	`string();`		// ����һ���յ��ַ��� ���磺string str;
//	`string(const char* s); `		// ʹ���ַ���s��ʼ��
void string_001()
{
	string s1;	// Ĭ�Ϲ���
	const char* str = "hello world";		// C���Է���ַ���
	string s2(str);
	cout << "������ַ���Ϊ��" << s2 << endl;
}
//	`string(const string& str);`		// ʹ��һ��string�����ʼ����һ��string����
void string_002()
{	
	string str = "hello world";
	string s3(str);
	cout << "string��ʼ���Ķ���Ϊ��" << s3 << endl;
}
//	`string(int n, char c);`		    // ʹ��n���ַ�c��ʼ��
void string_003()
{
	string s4(10, 's');
	cout << s4 << endl;
}


// string ��ֵ���� ���Ⱥţ���Ա������
/*- `string& operator=(const char* s);`		// `char*`�����ַ��� ��ֵ����ǰ�ַ���
- `string& operator=(const string& s);`		// �ַ���s ��ֵ����ǰ�ַ���
- `string& operator=(char c);`		// �ַ�c ��ֵ����ǰ�ַ���
- `string& assign(const char* s);`		// �ַ���s ��ֵ����ǰ�ַ���
- `string& assign(const char* s, int n);`		// �ַ���s ��ǰn���ַ� ��ֵ����ǰ�ַ���
- `string& assign(const string& s);`		// �ַ���s  ��ֵ����ǰ�ַ���
- `string& assign(int n, char c);`		// n���ַ�c  ��ֵ����ǰ�ַ���*/
void string_004()
{
	string jx;
	// `string& operator=(const char* s);`
	jx = "hello world";
	cout << "string& operator=(const char* s);" << jx << endl;
	// `string& operator=(const string & s); `
	string jx2;
	jx2 = jx;
	cout << "string& operator=(const string & s); " << jx2 << endl;
	// `string& operator=(char c); `
	jx2 = 'x';
	cout << "string& operator=(char c); " << jx2 << endl;
	
	// `string& assign(const char* s); `
	jx2.assign("hello world");
	cout << "string& assign(const char* s); " << jx2 << endl;
	// `string& assign(const char* s, int n); `
	jx2.assign("hello world", 8);
	cout << "string& assign(const char* s, int n); " << jx2 << endl;
	// `string& assign(const string & s); `
	jx2.assign(jx);
	cout << "string& assign(const string & s); " << jx2 << endl;
	// `string& assign(int n, char c); `
	jx2.assign(5, 'x');
	cout << "string& assign(int n, char c);" << jx2 << endl;
}


// string�ַ���ƴ��
/*- `string& operator+=(const char* str);`		// ����+=������
- `string& operator+=(const char c);`		// ����+=������
- `string& operator+=(const string& str);`		// ����+=������
- `string& append(const char* s);`		// ���ַ���s���ӵ���ǰ�ַ�����β
- `string& append(const char* s,int n);`		// ���ַ���s��ǰn���ַ����ӵ���ǰ�ַ�����β
- `string& append(const string& s);`		// ͬ `operator+=(const string& str)`
- `string& append(const string&s, int pos, int n);`		// �ַ���s�д�pos��ʼ��n���ַ����ӵ��ַ�����β*/
void string_005()
{
	string jx = "I";
	// `string& operator+=(const char* str);`
	jx += " have ";
	cout << "string& operator+=(const char* str);" << jx << endl;
	//-`string& operator+=(const char c); `		// ����+=������
	jx += " a";
	cout << "string& operator+=(const char c); " << jx << endl;
	//-`string& operator+=(const string & str); `		// ����+=������
	string str = " hobby";
	jx += str;
	cout << "string& operator+=(const string & str); " << jx << endl;

	string jxa = "I";
	//-`string& append(const char* s); `		// ���ַ���s���ӵ���ǰ�ַ�����β
	jxa.append(" have");
	cout << "string& append(const char* s); " << jxa << endl;
	//-`string& append(const char* s, int n); `		// ���ַ���s��ǰn���ַ����ӵ���ǰ�ַ�����β
	jxa.append(" a hobby", 2);
	cout << "string& append(const char* s, int n); " << jxa << endl;
	//-`string& append(const string & s); `		// ͬ `operator+=(const string& str)`
	jxa.append(str);
	cout << "string& append(const string & s); " << jxa << endl;
	//-`string& append(const string & s, int pos, int n); `		// �ַ���s�д�pos��ʼ��n���ַ����ӵ��ַ�����β*/
	str = "I have a hobby that is coding!";
	jxa.append(str, 14, 16);
	cout << "string& append(const string & s, int pos, int n); " << jxa << endl;
	//		if `int n > len`,what will happen?
	jxa.append(str, 14, 26);
	cout << "string& append(const string & s, int pos, int n); " << jxa << endl;
	//		no error happend
}


// string���Һ��滻
/*- `int find(const string& str, int pos = 0) const;`		// ����str��һ�γ��ֵ�λ�ã���pos��ʼ����
- `int find(const char* s, int pos = 0) const;`		// ����s��һ�γ��ֵ�λ�ã���pos��ʼ����
- `int find(const char* s, int pos, int n) const;`		// ��posλ�ò���s��ǰn���ַ���һ��λ��
- `int find(const char c, int pos = 0) const;`		// �����ַ�c��һ�γ��ֵ�λ��
- `int rfind(const string& str, int pos = npos) const;`		// ����str���һ��λ�ã���pos��ʼ����
- `int rfind(const char* s, int pos = npos) const;`		// ����s���һ��λ�ã���pos��ʼ����
- `int rfind(const char* s, int pos, int n) const;`		// ��posλ�ò���s��ǰn���ַ����һ��λ��
- `int rfind(const char c, int pos =0) const;`		// �����ַ�c���һ��λ��
- `string& replace(int pos, int n, const string& str);`		// �滻��pos��ʼn���ַ�Ϊ�ַ���str
- `string& replace(int pos, int n, cosnt char* s);`		// �滻��pos��ʼn���ַ�Ϊ�ַ���s*/
void string_006()
{
	string jx = "aaabbbcccddd";
	int res;
	//`int find(const string& str, int pos = 0) const;`		// ����str��һ�γ��ֵ�λ�ã���pos��ʼ����
	res = jx.find("bb");
	cout << "int find(const string& str, int pos = 0) const; " << res << endl;
	//-`int find(const char* s, int pos, int n) const; `		// ��posλ�ò���s��ǰn���ַ���һ��λ��
	res = jx.find("bb", 3);
	cout << "int find(const char* s, int pos, int n) const; " << res << endl;
	//		if nofonud, function will return -1;
	res = jx.find("bb", 5);
	cout << "int find(const char* s, int pos, int n) const; " << res << endl;
	//		���ص�λ����λ������string��λ�ã����صĽ����pos�޹�
	res = jx.find("bb", 5, 1);
	cout << "int find(const char* s, int pos, int n) const; " << res << endl;

	// rfind �����������
	//-`int rfind(const string & str, int pos = npos) const; `		// ����str���һ��λ�ã���pos��ʼ����
	res = jx.rfind("bb");
	cout << "int rfind(const string & str, int pos = npos) const; " << res << endl;
	//		if `npos>len`;what will happen?
	//res = jx.rfind("bb",100);
	cout << "int rfind(const string & str, int pos = npos) const; " << res << endl;
	//		no error happend
	//		`npos<0`ʱ �����൱���ҵ���󣬺�python��index����ͬ��
	res = jx.rfind("ddd", -3);
	cout << "int rfind(const string & str, int pos = npos) const; " << res << endl;

	//-`string& replace(int pos, int n, const string & str); `		// �滻��pos��ʼn���ַ�Ϊ�ַ���str
	jx.replace(0, 10, "bb");
	cout << "string& replace(int pos, int n, const string & str); " << jx << endl;
}


// string�ַ����Ƚ�
/*- `int compare(const string& s) const;`
- `int compare(const char* s) const;`*/
void string_007()
{
	string str01 = "hello world";
	string str02 = "hello ";
	string str03 = "world";
	cout << "��һ�αȽϵķ���ֵ�� " << str01.compare(str02) << endl;
	str02 += str03;
	cout << "�ڶ��αȽϵķ���ֵ�� " << str01.compare(str02) << endl;
}


// string�����ַ���ȡ
/*- `char& operator[](int n);`		// ͨ�� [] ��ʽȡ�ַ�
- `char& at(int n);`		// ͨ�� at ����ȡ�ַ�*/
void string_008()
{
	string str = "hello world";
	///*- `char& operator[](int n);`		// ͨ�� [] ��ʽȡ�ַ�
	for (int i = 0; i < str.size(); i++)
	{
		cout << str[i];
	}
	cout << endl;

	//-`char& at(int n); `		// ͨ�� at ����ȡ�ַ�*/
	for (int i = 0; i < str.size(); i++)
	{
		cout << str.at(i);
	}
	cout << endl;

	// �޸ĵ����ַ�
	str[0] = 'x';
	cout << "���ĵ�һ���ַ���" << str << endl;
}


// string �����ɾ��
/*- `string& insert(int pos, const char* s);`		// �����ַ���
- `string& insert(int pos, const string& str);`		// �����ַ���
- `string& insert(int pos, int n, char c);`		// ����n���ַ�c
- `string& erase(int pos, int n = npos);`		// ɾ����pos��ʼ��n���ַ�*/
void string_009()
{
	string str = "hello";
	// ����
	str.insert(0, "Jx ");
	cout << "���������" << str << endl;
	// ɾ��
	str.erase(2, 100);
	cout << "ɾ��������" << str << endl;
	//		if ����npos��д�����ʲôЧ��
	str.erase(0);		// erase() == erase(0)
	cout << "ֻд��ʼλ��ɾ����" << str << endl;
	//		��ɾ��pos�������е��ַ�
}



// string�Ӵ�	//substr
/*`string substr(int pos = 0, inte n = npos) const;`		// ������pos��ʼ��n���ַ���װ�ɵ��ַ���*/
void string_010()
{
	string str = "abcdefg";
	string jx = str.substr(2, 2);
	cout << "��õ��Ӵ���" << jx << endl;			//cd
	jx = str.substr(2);
	cout << "ֻд��ʼλ�ò�����" << jx << endl;		//cdefg
}

/*==================================================*/
/*-- �й��ַ�����ת������ --*/
//	�ַ�����Сдת��	
void string_transform001()
{
	string str1 = "Hello World!";
	std::transform(str1.begin(), str1.end(), str1.begin(), tolower);
	cout << str1 << endl;	//hello world!
	std::transform(str1.begin(), str1.end(), str1.begin(), toupper);
	cout << str1 << endl;	//HELLO WORLD!

							
	/*-- Tips: --*/
	//test:ǰ���begin����һ�£�����error
	cout << endl;
	//std::transform(str1.begin() + 1, str1.end(), str1.begin() + 1, tolower);
	std::transform(str1.begin() + 1, str1.end()-4, str1.begin() + 1, tolower);
	cout << str1 << endl;
}
/*==================================================*/



/*-- С���� --*/
//	�������ַ�л�ȡ�û���Ϣ
void stringEg_001()
{
	string email = "zhangsan@sina.cn";
	int endIndex = email.find('@');
	cout << "�����û���Ϊ��" << email.substr(0, endIndex) << endl;
}