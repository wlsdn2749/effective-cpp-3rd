이 책의 목적은 C++를 **효과적으로** 구사하는 방법을 알려준다는데에 그 의미가 있다.

이 책을 통해 C++를 처음 접하는 독자에게는 추천하지 않으며, 기본적으로 C++를 이미 알고 있다는 전제하에 책이 전개된다.

이 책의 내용으로는 크게 두 부류가 있다
- 일반적인 설계 전략
- C++만의 언어적 특징에 관련된 실전 세부사항.

설계 전략 이슈로는 어떤 일을 해야 할 때 취할 수 있는 서로 다른 접근의 선택 방법에 초점이 맞춰저 있음. 다음과 같은 것들이 예시이다.
- 상속 vs 템플릿
- public 상속 vs private 상속
- private 상속 vs 클래스 합성
- 멤버 함수 vs 비 멤버 함수
- 값의 의한 전달 vs 참조에 의한 전달

또한 이 책은 안목을 기르자는 목표를 가지고 읽는게 좋다.
- C++가 어떻게 동작하는지
- 이것이 왜 이렇게 동작하는지
- 그리고 이러한 형태를 용도에 맞게 어떻게 써먹을 수 있는지


**선언**은 코드에 사용되는 '어떤 대상'의 이름과 타입을 컴파일러에게 알려주는 것이다.
구체적인 세부사항은 선언에 들어있지 않고, **정의**에 들어있다
```c++
extern int x; // 객체 선언

std::size_t numDigits(int number); // 함수 선언

class Widget; // 클래스 선언

template<typename T> // 템플릿 선언
class GraphNode;
```

> 정수 x의 경우
> 기본제공 형태임에도 불구하고 객체라고 부른다

> std::size_t의 경우
> C언어에서 내려온 size_t를 그대로 사용하는데, 이는 어떤  Header를 Include 하느냐에 따라 달라진다. C++ 헤더를 Include한 경우 std::size_t 
> size_t는 부호없는 정수 타입 (unsigned int)를 typedef로 정의한 것 C++에서는 개수를 셀때 size_t를 사용한다. 또한 vecotr, deque, string 의 operator[]의 함수가 취하는 타입도 size_t이다.


**정의**는 선언에서 빠진 구체적인 세부사항을 컴파일러에게 제공하는 것이다.
**객체**의 경우에 있어서 정의는 컴파일러가 그 객체에 대한 **메모리**를 마련해 놓는 부분이 된다.
**함수나 함수 템플릿**에 대한 정의는 그들에 대한 **코드 본문(body)** 를 제공하는 것이다.

**클래스 혹은 클래스 템플릿** 의 경우는 **그 클래스 혹은 템플릿의 멤버**를 넣어준 결과가 정의다.

...

**초기화(initialization)** 은 어떤 객체에 최초의 값을 부여하는 과정.
사용자 정의 타입으로 생성한 객체의 경우. 초기화는 **생성자**에 의해 이루어진다.

**기본 생성자**는 어떤 인자도 주어지지 않은 채로 호출될 수 있는 생성자이다.
원래부터 매개변수가 없거나, 모든 매개변수가 기본 값을 가지고 있으면 기본 생성자가 될 수 있다.

```c++
class A{
public:
	A(); // 기본 생성자
}

class B{
public:
	explicit B(int x = 0, bool b = true); // 모든 매개변수가 기본값을 가지고 있으므로, 기본 생성자
}
```

explicit로 선언하게 되면 암시적인 타입 변환을 막을 수 있게 된다

```c++
void doSomething(B bObject);

B bObj1;
doSomething(bObj1); // B Object가 제대로 사용됨

B bObj2;
doSomething(28); 
// doSomething은 B를 취해야 하는데, int가 들어가면 안될 뿐더러, int -> B로 가는 암시적 변환이 없음

doSomething(B(28)); // B(28)은 28을 명시적으로 B형태로  캐스팅하여 B Object가 사용되게 할 수 있다.
```

의도적으로 암시적 타입 변환에 생성자가 사용될 여지를 남겨둘 뚜렷한 이유가 없는 한
***생성자는 explicit 선언을 우선적으로***


**복사 생성자**는 어떤 객체의 초기화를 위해 그와 같은 타입의 객체로 부터 초기화할 때 사용되는 함수.

**복사 대입 연산자**는 같은 타입의 다른 객체에 어떤 객체의 값을 복사하는 용도로 쓰이는 함수

```c++
class Widget{
public:
	Widget(); // 기본 생성자
	Widget(const Widget& rhs); // 복사 생성자
	Widget& operator=(const Widget& rhs); // 복사 대입 연산자
}

Widget w1; // 기본 생성자 호출
Widget w2(w1); // 복사 생성자 호출
w1 = w2; // 복사 대입 연산자 호출
```

`=` 문법은 복사 생성자로도 쓰이고 대입 연산자로도 쓰이지만 구분하기 어려운건 아니다.

`Widget w3 = w2;` 여기서는 복사 생성자가 호출 되는 것이고
어떤 객체가 새로 정의될 때는 항상 **생성자**가 불린다. 대입 X

새로운 객체가 정의되지 않는 상황에서는 `w1 = w2` 문장 처럼 생성자가 호출 될 수 없기 때문에 자연스레 대입이 될 수 밖에 없다.

복사 생성자는 단순히 복사 생성자 그 자체로 국한되어 사용되기 보다는 
**값의 의한 객체 전달을 정의해 주는 함수**이기도 하다.

```c++
bool hasAcceptableQuality(Widget w);
...
Widget aWidget;
if(hasAcceptableQuality(aWidget)) ...
```
여기서 매개 변수 w는 hasAcceptableQuality 함수에 값으로 넘겨지도록 되어 있으므로
실제 호출에서 aWidget은 w로 복사된다. 여기서 수행되는 복사에서 Widget의 복사 생성자가 쓰인다. 
***값의 의한 전달은 복사 생성자 호출!***


이름 짓기에 대한 규약
> 이항 연산자 (lhs, rhs)
> a\*b는 operator\*(a, b)와 같고 
> `const Rational operator*(const Rational& lhs, const Rational& rhs);`와 같다.

>포인터 (pt)
```C++
Widget *pw; // pw = Widget에 대한 포인터

class Airplane;
Airplane *pa; // pa = Airplane에 대한 포인터

class GameCharacter;
GameCharacter *pgc; // pgc = GameCharacter에 대한 포인터
```

