#include <iostream>
#include <memory>


class Investment{
public:
    bool isTaxFree() const;
};

bool Investment::isTaxFree() const
{
    return true;
}
Investment* createInvestment(){
    return new Investment();
}

// RAII 클래스의 명시적, 암시적 변환

class Resource{
public:
    Resource()
    : name("1234")
    {
        
    }
    std::string toString() const {
        return name;
    }
private:
    std::string name;
};
class Widget{
public:
    Widget(Resource r)
    : r1(r)
    {

    }
    Resource get() const { return r1;} // 명시적 변환
    operator Resource() const {return r1; } // 암시적 변환

private:
    Resource r1;
};

void print(const Resource& r1){
    std::cout << r1.toString() << std::endl;
}

int main(){
    std::shared_ptr<Investment> pi1(createInvestment());
    bool taxable1 = !(pi1->isTaxFree()); // operator->로 자원 접근
    
    std::auto_ptr<Investment> pi2(createInvestment());
    bool taxable2 = !((*pi2).isTaxFree()); // operator*로 자원 

    Resource r;
    Widget w1(r);
    std::cout << w1.get().toString() << std::endl;
    print(w1); // w1이 암시적으로 Resource&로 변환되었음 wow
}
    