#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
class Rational
{
private:
    static int objCount;    //计数
    int above;              //分子
    int denominator;        //分母
public:
    int Get_Count()
    { return objCount; }
    friend Rational operator + (const Rational &a1,const Rational &a2);
    friend Rational operator - (const Rational &a1,const Rational &a2);
    friend Rational operator * (const Rational a1,const Rational a2);
    friend Rational operator / (const Rational a1,const Rational a2);
    void print()                                       //打印有理数
    {
        cout<<above<<"/"<<denominator<<endl;
    }
    Rational(int a1,int a2){                          //赋值构造函数
        above=a1;
        denominator=a2;
        objCount++;
        // cout<<"     set____objCount:      "<<objCount<<endl;
    }
    ~Rational() {                                     //析构函数
        objCount--;
        // cout<<"     delete____objCount:   "<<objCount<<endl;
    }
};

struct Storage
{
    Rational* num;
    char opea;
    Storage *next;
};

int measure(int x, int y)     //求两个数的最大公约数
{
    int z = y;
    while(x%y!=0)
    {   z=x%y;   	x=y;   	y=z;	 }
    return z;
}

int Rational::objCount=0;            //初始化objCount
Rational operator + (const Rational &a1,const Rational &a2)
{
    int a=a1.denominator*a2.denominator;
    int b=a1.above*a2.denominator+a2.above*a1.denominator;
    int x=measure(a,b);
    a=a/x; b=b/x;
    if(b<0)
    {
        b=-b; a=-a;
    }
    return Rational(b,a);
}
Rational operator - (const Rational &a1,const Rational &a2)
{
    int a=a1.denominator*a2.denominator;
    int b=a1.above*a2.denominator-a2.above*a1.denominator;
    int x=measure(a,b);
    a=a/x; b=b/x;
    if(a<0)
    {
        b=-b; a=-a;
    }
    return Rational(b,a);
}
Rational operator * (const Rational a1,const Rational a2)
{
    int a=a1.above*a2.above;
    int b=a1.denominator*a2.denominator;
    int x=measure(a,b);
    return Rational(a/x,b/x);
}
Rational operator / (const Rational a1,const Rational a2)
{
    int a=a1.above*a2.denominator;
    int b=a1.denominator*a2.above;
    int x=measure(a,b);
    return Rational(a/x,b/x);
}

int main()
{
//    cout<<"xxd\n";
//    int a1,a2,b1,b2,c1,c2;
//    cin>>a1>>a2;
//    cin>>b1>>b2;
//    if(a2==0||b2==0)
//    {
//        cout<<"error!";
//        exit(0);
//    }
//    Rational a(a1,a2);
//    Rational b(b1,b2);
//    cout<<"\n a:";  a.print() ;
//    cout<<" b:";    b.print() ;
//
//    cout<<endl;
//    Rational c=a+b;
//    cout<<"\n c:";  c.print() ;
//
//    cout<<endl<<endl<<"________________________________________________________________________"<<endl;
    cout<<"Input your expression:"<<endl;
    string str;
    cin>>str;
    int size_s=str.size();

    // cout<<"          "<<size_s<<endl<<endl<<endl;

    Storage *head=NULL;

    int i=0;
    int abb,dena;    //abb和dena分别是用来在while里暂存分子与分母

    while(i<=size_s)
    {
        abb=0;
        while(i < size_s && str[i]!='/')
        {
            abb=abb*10+((int)str[i]-'0');
            // eat token when meeting digit
            i++;
            cout<<"i  "<<i<<endl<<"abb: "<<abb<<endl;
        }
        // skip '/'
        i += 1;
        dena = 0;
        // cout<<endl<<"i: "<<i<<endl;

        char current_oper;
        while(i<size_s && str[i]!='+' && str[i]!='-' )
        {

            dena=dena*10+((int)str[i]-48);
            i++;
            cout<<endl<<"dena: "<<dena<<endl;

            // cout<<endl<<"second"<<"i "<<i<<endl;
        }
        current_oper = str[i];
        // skip '+' or '-'
        i++;

        Storage *p=new Storage;

        Rational* rational = new Rational(abb,dena);
        p->num = rational;


        cout<<"abb "<<abb<<"  dena: "<<dena<<endl;

        // cout<<"{{{{{{{{"<<i<<endl;
        // cout<<endl<<endl<<endl<<"         "<<p->opea <<"       ";
        p->num->print();
        p->next=head;
        p->opea = current_oper;
        head=p;
    }
    //  cout<"***************";
    Storage *p = head->next;
    Rational sum = *head->num;

    for(; p != nullptr; p = p->next)
    {
        char instruction=p->opea;
        cout << p-> opea << '\n';
        if(instruction=='+')
        {
            sum = sum + *p->num;
//            p=p->next;
        }
        if(instruction=='-')
        {
            sum=sum-*(p->num);
//            p=p->next;
        }
    }
    sum.print() ;

    return 0;
}
