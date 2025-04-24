#include <iostream>

class Empty{};
// class Empty{ // 와 대동소이하다는 의미이다.
// public:
// 	Empty(){}
// 	Empty(const Empty& rhs){}
// 	~Empty(){}
// 	Empty& operator=(const Empty& rhs){}
// };

template<typename T>
class NamedObject{
public:
	NamedObject(const char *name, const T& value);
	NamedObject(const std::string& name, const T& value);


private:
	std::string nameValue;
	T objectValue;
};


template<typename T>
NamedObject<T>::NamedObject(const char *name, const T& value)
    : nameValue(name), objectValue(value) {
}

template<typename T>
NamedObject<T>::NamedObject(const std::string& name, const T& value)
    : nameValue(name), objectValue(value) {
}

int main(){
    // Empty e1; // 기본 생성자, 그리고 소멸자

    // Empty e2(e1); // 복사 생성자

    // e2 = e1; // 복사 대입 연산자

    NamedObject<int> no1("Smallest Prime Number", 2);
    NamedObject<int> no2(no1); // 여기서 암시적 복사생성자 호출
}
