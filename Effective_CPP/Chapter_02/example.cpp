#include <iostream>

#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))

void f(int num){
    std::cout <<"값: " << num << std::endl;
}

template<typename T>
inline void callWithMax(const T& a, const T& b)
{
    f(a > b ? a : b); 
}

int main(){
    int a = 5, b = 0;

    CALL_WITH_MAX(++a, b);
    std::cout << "a: " << a  << " b: "<< b << std::endl; // 예상 값: 6, 0 -> 실제 값 7, 0 (??) 

    a = 5, b = 0;
    CALL_WITH_MAX(++a, b+10);
    std::cout << "a: " << a  << " b: "<< b << std::endl;  // 예상 값 6, 0 -> OK 

// #define 매크로보다 템플릿 inline 함수를 우선 생각!
    a = 5, b = 0;
    callWithMax(++a, b);
    std::cout << "a: " << a  << " b: "<< b << std::endl;  // 예상 값 6, 0 -> OK 
}