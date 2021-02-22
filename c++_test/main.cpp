#include"gdb/jit-reader.h"
//#include"boost/thread/thread.hpp"

#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<map>

#include"red_black_tree/RedBlackTree.h"
#include"test_global.h"
using namespace std;
class Base
{

    long long a = 1;
public:   
    virtual void Func1(){
        cout << "Base: Func1" << endl;
    }
    virtual void Func2(){
        cout << "Base: Func2" << endl;
    }
    virtual void Func5(){
        cout << "Base: Func5" << endl;
    }
};
class Base1 : virtual public Base
{
public:

    long long b = 2;
    

    virtual void Func1(){
        cout << "Base1:Func1" << endl;
    }    
    virtual void Func3(){
        cout << "Base1:Func3" << endl;
    }    
};
class Base2 : virtual public Base
{
public:

    long long c = 3;
    virtual void Func2(){
        cout << "Base2 Func2" << endl;
    }
    virtual void Func3(){
        cout << "Base2 Func3" << endl;
    }
};
class Derive :  public Base1, public Base2
{
public:

    long long a = -1;
    long long b = -1;
    long long c = -1;
    long long d = 50;
    virtual void Func3(){
        cout << "Derive Func3" << endl;
    }
    virtual void Func4(){
        cout << "Derive Func4" << endl;
    }

public :
    constexpr static int func2(){
        int a = 3;
    return a;
}
};

typedef void (*Func) (void);
int main1(int argc,char*argv[])
{
    Base1 test;
    long long** class_ptr = (long long **)&test;
    cout << "[0]:"<< class_ptr[0][0] << endl;
    Func p_func; 
    for(long long i = 0;i < 3; ++i) {
        p_func = (Func)class_ptr[0][i];
        p_func();
    }
    
    system("pause");
    return 0;
}
struct edge {
    int to;
    struct edg* next;
};



int func1(int a , int b ) {
    cout << "func1-1" << a << b << endl;
    return 0;
}
int func1(int a, int b = 7);
int func1(int a = 4, int b );

int main6(int argc,char*argv[]){
    
    Derive test;
    Base base;
    long long** class_ptr = (long long **)&test;
    cout << "long long size: " << sizeof(long) << "long long* size" << sizeof(long long *) << endl ;
    cout << "[0]:"<< class_ptr[0][0] << endl;
    Func p_func; 
    for(long long i = 0;i < 3; ++i) {
        p_func = (Func)class_ptr[0][i];
        p_func();
    }
    for(long long i = 1; class_ptr[i] != nullptr; ++i) {
        cout << "[" << i << "]" << (long long)class_ptr[i] << endl;
    }

    cout << "[2]" << class_ptr[2][0] << endl;
    for(long long i = 0;i < 2; ++i) {
        p_func = (Func)class_ptr[2][i];
        p_func();
    }
    cout << "[8]" << class_ptr[8][0] << endl;
    for(long long i = 1;i < 2; ++i) {
        p_func = (Func)class_ptr[8][i+1];
        p_func();
    }
    cout << "Base1" << endl;
    Base1 *base1 = new Base1();
    class_ptr = (long long **)base1;
    for(long long i = 0; class_ptr[i] != nullptr; ++i) {
        cout << "[" << i << "]" << (long long)class_ptr[i] << "   address:" << (long long)(class_ptr+i) << endl;
    }
    cout << "[0]" << class_ptr[0][0] << endl;
    for(long long i = 0;i < 2; ++i) {
        p_func = (Func)class_ptr[0][i];
        p_func();
    }
    cout << "[2]" << class_ptr[2][0] << endl;
    for(long long i = 0;i < 2; ++i) {
        p_func = (Func)class_ptr[2][i+1];
        p_func();
    }
    // cout << "[10]" << class_ptr[10][0] << endl;
    // for(long long i = 0;i < 2; ++i) {
    //     p_func = (Func)class_ptr[10][i];
    //     p_func();
    // }
   func1();
   typedef int (*Func)(int,int);
   Func f = func1;
    f(6,7);
    string s = "fdsafdsafds";
    string* ptr_s = &s;
    constexpr int ci = Derive::func2();
    cout << ci;
    system("pause");
    return 0;

}
