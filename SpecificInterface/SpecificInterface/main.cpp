#include "iostream"

class SpecificInterface
{
public:
    SpecificInterface() = default;
    virtual ~SpecificInterface() = default;

    virtual void SpecificMethod1(){}
    virtual void SpecificMethod2(){}
    virtual void SpecificMethod3(){}
};

class Base
{
    int a;
public:
    virtual void DoSomething() = 0;
    virtual SpecificInterface* GetSpecificInterface(){ return nullptr; }
};

class Derived1 : public Base, public SpecificInterface
{
public:
    void DoSomething() override
    {
        std::cout << __func__ << std::endl;
    }
    SpecificInterface* GetSpecificInterface() override
    {
        return this;
    }
    void SpecificMethod1() override
    {
        std::cout << __func__ << std::endl;
    }
    void SpecificMethod2() override
    {
        std::cout << __func__ << std::endl;
    }
    void SpecificMethod3() override
    {
        std::cout << __func__ << std::endl;
    }
};

class Derived2 : public Base
{
public:
    void DoSomething() override
    {
        std::cout << __func__ << std::endl;
    }
};

class Foo
{
protected:
    virtual void DoSomething1()
    {
        std::cout << "[Foo]" << __func__ << std::endl;
    }
private:
    virtual void DoSomething2()
    {
        std::cout << "[Foo]" << __func__ << std::endl;
    }
};

class Bar : public Foo
{
public:
    void DoSomething2() override
    {
        this->DoSomething1();
        std::cout << "[Bar]"<< __func__ << std::endl;
    }
};

void main()
{
    Bar bar;
    bar.DoSomething2();



    std::cout << sizeof(Derived1) << std::endl;
    Base* base1 = new Derived1();
    base1->DoSomething();
    if(auto p = base1->GetSpecificInterface()){
        p->SpecificMethod1();
        p->SpecificMethod2();
        p->SpecificMethod3();
    }

    std::cout << sizeof(Derived2) << std::endl;
    Base* base2 = new Derived2();
    base2->DoSomething();
    if(auto p = base2->GetSpecificInterface()){
    }

}