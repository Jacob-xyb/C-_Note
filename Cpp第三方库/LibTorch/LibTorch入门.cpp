#include "../������_LibTorch/LibTorch.h"
#include "torch/torch.h"
#include "torch/script.h"


//torch�����ĳ�ʼ������1
void LibTorch_introduction_test001()
{
    torch::Tensor data = torch::rand(2);
    cout << data << endl;
    cout << data.sizes() << endl;
    //data.print();     // �ᱨ��
    cout << data.size(0) << " " << data.sizes()[0] << endl;     //���ַ�ʽ�ǵ�Ч��

    auto data1 = torch::rand({ 2 });
    cout << data1 << endl;
    // torch::rand(2) == torch::rand({ 2 })

    auto data2 = torch::rand({ 1, 2 });
    cout << data2 << endl;
}


void LibTorch_Dim_test()
{
    //auto x1 = torch::rand();    //error
    //auto x2 = torch::rand(1).view({ 0 });   //error
    auto x3 = torch::tensor(2);      //scalar ; Ŀǰֻ�����������������ķ�ʽ
    cout << x3 << endl;
}


  
//torch�������������*/
void LibTorch_introduction_test002()
{
    auto x = torch::tensor({ 1,2,3 }, torch::kDouble).view({ 1, -1 });
    cout << x * 2 << endl;          // tensor * scalar is ok
    auto num = torch::tensor({ 2 }, torch::kDouble);
    cout << x * num << endl;        // tensor(1x3) * tensor(1) is ok
    auto y = x.view({ -1, 1 }).to(torch::kDouble);
    cout << x * y << endl;          // (1x3) * (3*1) = (3x3); ok, fine.

    cout << x * x << endl;          // (1x3) * (1x3) = (1x3); of, fine.

    cout << x.mul(y) << endl;       // x.mul(y) == x*y

    cout << x.mm(y) << endl;        // mm ���Ǿ���˷���������ǵ��
}

//ƴ�ӣ�cat
void LibTorch_introduction_cat()
{
    auto x = torch::rand({ 2,3 });
    auto y = torch::rand({ 2,3 });
    cout << torch::cat({ x,y }, 1) << endl;
    cout << torch::cat({ x,y }, 0) << endl;

    //cat ������ʵ��vector<torch::Tensor>
    vector<torch::Tensor> m = { x,y };
    cout << torch::cat(m, 1) << endl;
}

//reshape
void LibTorch_introduction_reshape()
{
    // reshape() is not inplace
    auto x = torch::linspace(1, 10, 10);
    cout << x << endl;
    cout << x.reshape({ 2,5 }) << endl;
    cout << x << endl;
}

//index�йز���
void LibTorch_introduction_index()
{
    /*
    select ��ǳ������ ֻ��ָ��ȡĳһ�л�ĳһ��
    index ��ǳ������ ֻ��ָ��ȡĳһ�л�ĳ��ֵ
    */
    auto x = torch::linspace(1, 9, 9).reshape({ 3,3 });
    auto x_index = x.index({ 2 });
    cout << x_index << endl;

}
