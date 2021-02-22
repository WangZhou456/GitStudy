#include<iostream>
#include<map>
#include <vector>

#include"boost/thread/thread.hpp"
#include "boost/coroutine/coroutine.hpp"
#include "boost/context/fiber.hpp"
using namespace std;
std::vector<int> merge(const std::vector<int>& a,const std::vector<int>& b)
{
    std::vector<int> c;
    std::size_t idx_a=0,idx_b=0;
    boost::coroutines::symmetric_coroutine<void>::call_type* other_a=0,* other_b=0;

    boost::coroutines::symmetric_coroutine<void>::call_type coro_a(
        [&](boost::coroutines::symmetric_coroutine<void>::yield_type& yield) {
            while(idx_a<a.size())
            {
                if(b[idx_b]<a[idx_a])    // test if element in array b is less than in array a
                    yield(*other_b);     // yield to coroutine coro_b
                c.push_back(a[idx_a++]); // add element to final array
            }
            // add remaining elements of array b
            while ( idx_b < b.size())
                c.push_back( b[idx_b++]);
        });

    boost::coroutines::symmetric_coroutine<void>::call_type coro_b(
        [&](boost::coroutines::symmetric_coroutine<void>::yield_type& yield) {
            while(idx_b<b.size())
            {
                if (a[idx_a]<b[idx_b])   // test if element in array a is less than in array b
                    yield(*other_a);     // yield to coroutine coro_a
                c.push_back(b[idx_b++]); // add element to final array
            }
            // add remaining elements of array a
            while ( idx_a < a.size())
                c.push_back( a[idx_a++]);
        });


    other_a = & coro_a;
    other_b = & coro_b;

    coro_a(); // enter coroutine-fn of coro_a

    return c;
}

void pull_type_test() {
    int c = 7;
    boost::coroutines::asymmetric_coroutine<int>::pull_type source(
        [&](boost::coroutines::asymmetric_coroutine<int>::push_type& sink) {
            int first = 1, second = 1;
            sink(first);
            sink(second);
            for(int i = 0; i < 5; ++i) {
                cout << i << "time into pull_type";
                int third = first + second;
                first = second;
                second = third;
                sink(third);
            }
        }
    );
    cout << c << "middle context execute now !!!";
    for(auto i : source) {
        std::cout << i << "\t";
    }
}
struct FinalEOL {
    ~FinalEOL() {
        cout << endl;
    }
};
void push_type_test() {
    const int num = 5, width = 5;
    boost::coroutines::asymmetric_coroutine<std::string>::push_type writer(
        [&](boost::coroutines::asymmetric_coroutine<std::string>::pull_type& in) {
            FinalEOL eol;
            for(;;) {
                for(int i = 0; i < num; ++i) {
                    if(!in) return;
                    std::cout << std::setw(width) << in.get();
                    in();
                }
                std::cout << endl;
            }
        }
    );
    std::vector<std::string> words {
        "peas", "porridge", "hot", "peas",
        "porridge", "cold", "peas", "porridge",
        "in", "the", "pot", "nine",
        "days", "old"
    };
    std::copy(boost::begin(words), boost::end(words), boost::begin(writer));
}


int main1() {
    cout << "main:: boost::coroutine test!!!" << endl;
    // int data = 0;
    // namespace ctx = boost::context;
    // ctx::fiber f1([&data](ctx::fiber&& f2) {
    //     cout << "into fiber " << "first time" << endl;
    //     ++data;
    //     f2 = std::move(f2).resume();
    //     cout << "into fiber " << "second time" << endl;
    //     ++data;
    //     f2 = std::move(f2).resume();
    //     cout << "into fiber " << "third time" << endl;
    //     ++data;
    //     f2 = std::move(f2).resume();         
    // });
    // f1 = std::move(f1).resume();
    // cout << "return first time, data: " << data << endl;
    // f1 = std::move(f1).resume();
    // cout << "return second time, data: " << data << endl;
    // f1 = f1.resume_with([&data](ctx::fiber&& f2) ->ctx::fiber{
    //     cout << "into deep lambda data: " << data << endl;
    //     data = -1;
    //     return std::move(f2);
    // });
    // cout << "return third time data: " << data << endl;
    namespace ctx=boost::context;
    int data=0;
    ctx::fiber f1{[&data](ctx::fiber&& f2) {
        std::cout << "f1: entered first time: " << data << std::endl;
        data+=1;
        f2=std::move(f2).resume();
        std::cout << "f1: entered second time: " << data << std::endl;
        data+=1;
        f2=std::move(f2).resume();
        std::cout << "f1: entered third time: " << data << std::endl;
        return std::move(f2);
    }};
    f1=std::move(f1).resume();
    std::cout << "f1: returned first time: " << data << std::endl;
    data+=1;
    f1=std::move(f1).resume();
    std::cout << "f1: returned second time: " << data << std::endl;
    data+=1;
    ctx::fiber f2 {[&data](ctx::fiber&& f2){
        std::cout << "f2: entered: " << data << std::endl;
        data=-1;
        return std::move(f2);
    }};

    f1=std::move(f1).resume_with([&data](ctx::fiber&& f2){
        std::cout << "f2: entered: " << data << std::endl;
        data=-1;
        return std::move(f2);
    });

    cin.get();
    
}

int TestNameLookup(int a, int b, int c = 3) {
    cout << "function 1" << endl;
}
int TestNameLookup(int a, double b) {
    cout << "function 2" << endl;
}
int main2(int argc, char* argv[])
{
    TestNameLookup(2,3);
    getchar();
    return 0;

}