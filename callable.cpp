#include <vector>
#include <iostream>

using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1. 함수 포인터

void global_print(){ cout << "Global Print" << endl; }

struct Object
{
    void member_print(){ cout << "Member Print" << endl; }
};

void chapter1()
{
    cout << endl << "1. 함수 포인터" << endl;
    using PFunc = void(*)();
    PFunc pFunc = &global_print;
    pFunc();

    using MFunc = void(Object::*)();
    MFunc mFunc = &Object::member_print;

    Object o;
    (o.*mFunc)();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//2. Functor 펑터 

struct Functor
{
    void operator()(const string& str)
    {
        cout << str << endl;
    }
};

void chapter2_1()
{
    cout << endl << "2.1 Functor 펑터 " << endl;
    Functor functor;
    functor("Hello Functor");   
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Functor1
{
    Functor1(const string& str) : _str(str) 
    {
    }

    void operator()()
    {
        cout << _str << endl;
    }
    
    string _str;
};

void chapter2_2()
{
    cout << endl << "2.2 Functor 펑터 " << endl;
    Functor1 functor("Second Functor");
    functor();   
}

void chapter2_3()
{
    cout << endl << "2.3 Functor 펑터 " << endl;

    class Sum
    {
        int _total;
    public:
        Sum() : _total(0) {}
        void operator()(int elem)
        {
            _total += elem;
        }
 
        int total()
        {
            return _total;
        }
    };
 
    vector<int> v = { 1, 2, 3};
    
    Sum sum = for_each(begin(v), end(v), Sum());
    cout << sum.total() << endl;

    int total = 0;

    for(auto elem : v) {
        total += elem;
    }

    cout << total << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//3. std::bind

void func(const string& str){
    cout << str << endl;
}

void mul(int& lhs, int rhs);

void chapter3() {

    cout << endl << "3. Bind " << endl;
     auto f1 = bind(func, "hello bind");
     f1();   

     auto f2 = bind(&func, placeholders::_1);
     f2("hello bind");

     vector<int> v = { 1, 2, 3};

     for_each(begin(v), end(v), bind(&mul, placeholders::_1, 2));

     for(auto elem : v) 
     { 
         cout << elem << endl; 
     }
}

void mul(int& lhs, int rhs){
    lhs *= rhs;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//4. Lambda expression
void chapter4_1() {
    cout << endl << "4.1 Lambda" << endl;
    //[](){}

    auto f1 = [](int x){ cout << x << endl;};
    
    vector<int> v = { 1, 2, 3};

    int sum = 0;
    for_each(begin(v), end(v), [&sum](int elem){
        sum += elem;
    });

    cout << sum << endl;
    int num = 2;
    for_each(begin(v), end(v), [num](int& elem){
        elem += num;
    });

    for(int elem : v)
    {
        cout << elem << endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void chapter4_2() {
    cout << endl << "4.2 Lambda" << endl;

    vector<int> v = { 1, 2, 3};

     int sum = 0;
    for_each(begin(v), end(v), [=](int elem) mutable {
        sum += elem;
    });

    cout <<"[=] " << sum << endl;

    for_each(begin(v), end(v), [&](int elem){
        sum += elem;
    });

    cout <<"[&] " << sum << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Callable {
    
    template<typename T> 
    void operator()(T x) {
        cout << x << endl;
    }
};

void chapter4_3()
{
     cout << endl << "4.3 Lambda" << endl;
    {
        auto f = [](auto x){
            cout << x << endl;
        };

        f(1);
        f("what's up lambda'");
    }
    
    {
        auto f =  Callable();

        f(2);
        f("what's up functor'");
    }
}

void chapter4_4()
{
    cout << endl << "4.4 Lambda" << endl;
    vector<int> v = { 1, 2, 3};

    int num = 5;
    for_each(begin(v), end(v), [num](auto&& elem){
        elem += num;
    });

    for_each(begin(v), end(v), [](auto elem){
        cout << elem << endl;
    });
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << "## Callable Object ##" << std::endl;
    
    chapter1();
    chapter2_1();
    chapter2_2();
    chapter2_3();
    chapter3();
    chapter4_1();
    chapter4_2();
    chapter4_3();
    chapter4_4();

    return 0;
}