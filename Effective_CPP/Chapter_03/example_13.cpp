#include <iostream>
#include <memory>

class Investment{};

Investment* createInvestment()
{
    return new Investment();
}

void f()
{
    Investment *pInv = createInvestment();
    
    return; // 여기서 리턴해버리면? pInv 삭제가 안됌
    // valgrind --leak-check=full ./example_13
    // 1 bytes in 1 blocks are definitely lost in loss record 1 of 1

    delete pInv; // 객체 해제
}

void f1()
{
    std::auto_ptr<Investment> pInv(createInvestment());
    
    // auto_ptr이 알아서 자원 삭제를 해주므로 자원 누수가 없다.
}

void f2() // auto_ptr에 대한 예제
{
    std::auto_ptr<Investment> pInv1(createInvestment());
    
    std::auto_ptr<Investment> pInv2(pInv1); // 여기서 pInv2가 소유권을 가지게 됨.

    if(pInv1.get() == nullptr) // pInv가 가리키는 객체가 nullptr이 됨.
    {
        std::cout << "auto_ptr에서pInv1은 nullptr임" << std::endl;
    }
    
}

void f3()
{
	std::shared_ptr<Investment> pInv1(createInvestment());
    std::shared_ptr<Investment> pInv2(pInv1);

    if(pInv1.get() == nullptr) // shared_ptr에서는 가리키는 객체가 여러개가 될 수 있음.
    {
        std::cout << "shared_ptr에서 pInv1은 nullptr임" << std::endl;
    }

} //  shared_ptr이 알아서 삭제

int main()
{
    f();
    f1();
    f2();
    f3();
    std::cout << "end" << std::endl;

}