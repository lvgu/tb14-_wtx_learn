#include <iostream>
#include <string>
#include <iostream>
#include "boost/predef/version.h"
#include "boost/predef.h"
#include <memory>
#include <functional>
#include <vector>
#include <map>
#include <deque>

#if 0
int testBoostExist() {

    std::cout << "BOOST_PREDEF_VERSION : " << BOOST_PREDEF_VERSION << std::endl;
    // fs::path p("test.txt");
    // if (fs::exists(p)) {
    //     std::cout << p.filename() << " 存在！" << std::endl;
    // } else {
    //     std::cout << p.filename() << " 不存在！" << std::endl;
    // }
    return 0;
}

// ./b2.exe toolset=gcc address-model=64 link=static threading=multi variant=release --layout=versioned --prefix=D:/wtx_dev_workspace/boost_install install

void test()
{
        std::cout << "hello world\n";
    std::cout << "hello world\n";
    testBoostExist();

}
#endif

class Animal
{

public:
    virtual ~Animal() {}
    virtual void eat()
    {
        printf("animal eat..\n");
    }
};

class Dog : public Animal
{
private:
    /* data */
public:
    Dog(/* args */) {}
    virtual ~Dog() {}
    virtual void eat()
    {
        printf("dog eat..\n");
    }
};
class Cat : public Animal
{
private:
    /* data */
public:
    Cat(/* args */) {}
    virtual ~Cat() {}
    virtual void eat()
    {
        printf("Cat eat..\n");
    }
};

void test()
{
    auto animal1 = std::make_unique<Dog>();
    animal1->eat();
    auto animal2 = std::make_unique<Cat>();
    animal2->eat();
}

int main()
{
    test();
    return 0;
}
