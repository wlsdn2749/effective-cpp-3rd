#include <iostream>
// #include <format>

class Widget{
public:
    Widget(int value): value(value) 
    {}
    Widget& operator=(const Widget& rhs) // 복사 대입 연산자
    {
        value = rhs.value;
        return *this;
    }
    
    Widget& operator+=(const Widget& rhs)
    {
        value += rhs.value;
        return *this;
    }
    Widget& operator=(int rhs)
    {
        value = rhs;
        return *this;
    }

    std::string toString()
    {
        return std::to_string(value);
    }

private:
    int value;
};

int main()
{
    int x,y,z;

    x=y=z=15; // 대입이 사슬처럼 이어진다
    x = (y = ( z = 15)); //와 같은 의미

    Widget w1(5);
    Widget w2(0);

    w2 = w1;
    std::cout << w2.toString();

    
    
}