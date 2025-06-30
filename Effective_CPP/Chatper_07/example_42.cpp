#include <vector>
#include <iostream>
#include <iterator>          // iterator_traits

/*-------------------------------------------------
  1) class vs typename?  (둘 다 동일 의미)
-------------------------------------------------*/
template<class    T> class Widget;
template<typename T> class Rect;

/*-------------------------------------------------
  2) Base<T>::Nested 정의를 먼저 둔다
     ⇒ Derived 가 이를 상속하기 전에 선언·정의돼 있어야 함
-------------------------------------------------*/
template<typename T>
class Base
{
public:
    class Nested
    {
    public:
        explicit Nested(int x = 0) : value{x}
        {
            std::cout << "Nested(" << value << ")\n";
        }
        int value;
    };
};

/*-------------------------------------------------
  3) Derived - 중첩 의존 타입(Dependent-nested type) 활용
-------------------------------------------------*/
template<typename T>
class Derived : public Base<T>::Nested        // base-class-list 에서는 typename 금지
{
    using BaseNested = typename Base<T>::Nested;  // 가독성용 alias

public:
    explicit Derived(int x = 0)
        : BaseNested{x}                          // 멤버 초기화 리스트
    {
        typename Base<T>::Nested temp{x};        // 지역 변수 선언 시엔 typename 필요
        std::cout << "Derived(" << temp.value << ")\n";
    }
};

/*-------------------------------------------------
  4) ‘typename’이 꼭 필요한 자리: print2nd
-------------------------------------------------*/
template<typename C>
void print2nd(const C& container)
{
    if (container.size() >= 2)
    {
        typename C::const_iterator iter(container.begin()); // 의존 이름
        ++iter;
        std::cout << "print2nd: " << *iter << '\n';
    }
}

/*-------------------------------------------------
  5) 또 다른 예: iterator_traits
-------------------------------------------------*/
template<typename IterT>
void workWithIterator(IterT iter)
{
    using ValueT = typename std::iterator_traits<IterT>::value_type;
    ValueT temp(*iter);
    std::cout << "workWithIterator: " << temp << '\n';
}

/*-------------------------------------------------
  6) 테스트 코드
-------------------------------------------------*/
class Alpha {};   // 세미콜론 필수

int main()
{
    std::vector<int> v{1, 2, 3};

    print2nd(v);                // 2 출력
    Derived<Alpha> da(42);      // Nested(42) → Derived(42) 출력

    workWithIterator(v.begin()); // 안전: 초기화된 iterator 전달
}
