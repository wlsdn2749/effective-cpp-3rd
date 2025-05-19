#include <string>

class Person{
public:
	int age() const {return theAge;} // 이렇게 클래스 내부에서 정의되면
    // 암시적으로 인라인 요청을 하게됨
private:
	int theAge;
};


template<typename T>
inline const T& max(const T& a, const T& b)
{
    return a < b ? b : a;
}
// 혹은 이렇게 명시적으로 inline 화 해줄 수 있다.

inline void f(){;}
void (*pf)() = f;


class Base{
public:
private:
	std::string bm1, bm2; // base 멤버
};

class Derived: public Base{
public:
	Derived() {} // Derived의 생성자가 비어있음

    // 여기서 Derived를 inline화하게되면
    // 코드가 많아지는 과유불급 상태가 되버림
private:
	std::string dm1, dm2, dm3; // Derived 멤버
};

int main()
{
    f(); // f는 inline 함수이므로 인라인 됨
    pf(); // *pf는 인라인 안됌
}

