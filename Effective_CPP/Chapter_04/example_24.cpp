#include <iostream>
class Rational{
public:
    Rational(int numerator = 0, int denominator = 1)
    :_numerator(numerator), _denomiator(denominator)
    {

    };
    // 생성자에 explicit이 없는 이유가, int -> Rational의 암시적 변환 허용

    int numerator() const; // 분자 및 분모에 대한 접근용 함수
    int denomiator() const; 

    // const Rational operator*(const Rational& rhs) const
    // {
    //     return Rational(numerator() * rhs.numerator(),
    //                     denomiator() * rhs.denomiator());
    // }

private:
    int _numerator;
    int _denomiator;
};

Rational operator*(const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.numerator() * rhs.numerator(),
                    lhs.denomiator() * rhs.denomiator());
} // 현대의 c++에는 값을 반환할때 const를 붙이지 않음

// 그 이유는 임시객체에 할당할때만 쓰이는데, 거의 일어나지 않을 뿐더러
// move 같은 연산을 방해함

int Rational::numerator() const
{
    return _numerator;
}


int Rational::denomiator() const
{
    return _denomiator;
}


int main()
{
    Rational oneEighth(1, 8);
    Rational oneHalf(1, 2);
    
    Rational result = oneHalf * oneEighth; // ok
    result = result * oneEighth; // ok

    result = oneHalf * 2; // ok
    result = 2 * oneHalf; 

    2 * oneHalf = result;  // 이게 가능하긴 한데, 이정도는 Clang-tidy로 검사가능

    // 함수 내부에 선언하면? Int * Rational 타입이 없음!!
    // 비멤버 함수로 선언하면 암시적 변환가능.
    
}