#include <iostream>
 
class Base{
public:
    void mf() { std::cout << "Base" << std::endl;}
    virtual void vmf() { std::cout << "Virtual Base" << std::endl;}
    // virtual void omf() { std::cout << "Base Only" << std::endl;} // 이렇게 선언하면, 아래 omf는 자동으로 가상함수가 됨.
};

class Derived : public Base{
public:
    void mf() { std::cout << "Derived" << std::endl;}
    virtual void vmf() override { std::cout << "Virtual Derived" << std::endl;}
    void omf() {{std::cout << "Derived only" << std::endl;}}
};

int main()
{
    Derived x;
    Base *pB = &x; // Base 클래스의 포인터

    pB->mf(); // 같은 Derived 객체인데? Base가 호출 (???)
    pB->vmf(); // Base 클래스 포인터와는 관계없이 실제 객체가 Derived 이므로, Derived::vmf() 호출
    // pB->omf(); // pB는 Base 클래스에 소속되어있으므로, Base에 정의되지 않은 omf를 호출 할 수 없음

    Derived *pD = &x; // Derived 클래스의 포인터
    pD->mf(); 
    pD->vmf(); //
    pD->omf(); // Derived에 소속되어있는 omf 호출 가능
}