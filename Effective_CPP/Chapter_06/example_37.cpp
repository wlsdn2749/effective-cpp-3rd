#include <iostream>

class Shape{
public:
	enum ShapeColor{
		Red = 1,
		Green = 2,
		Blue = 3,
	};
	// 모든 도형은 자기 자신을 그리는 함수를 제공해야 한다.
	virtual void draw(ShapeColor color = Red) const = 0;
	
};

class Rectangle: public Shape{
public:
	// 기본 매개 변수 값이 달라졌으면?
	virtual void draw(ShapeColor color = Green) const
    {
        std::cout << "Rectangle : " << color << std::endl;
    }
	
};

class Circle: public Shape{
public:
	// 마찬가지
	virtual void draw(ShapeColor color)const
    {
        std::cout << "Circle : " << color << std::endl;
    }
	
};


// class Shape{
// public:
// 	enum ShapeColor { Red, Green, Blue };

// 	void draw(ShapeColor color = Red) const
// 	{
// 		doDraw(color);
// 	}
// private:
// 	virtual void doDraw(ShapeColor color) const = 0; // 진짜 작업은 여기서 이루어짐
// };

// class Rectangle : public Shape{
// public:
// private:
// 	virtual void doDraw(ShapeColor color) const; // 기본값 없음
// }
int main()
{
    Shape *ps; 
    std::cout << typeid(ps).name() << std::endl; // 정적 타입 : Shape*
    // std::cout << typeid(*ps).name() << std::endl; // 동적 타입 : Shape* <- 초기화가 안되서 크래시sㅏㅁ
    Shape *pc = new Circle; // 정적 타입 : Shape*, 동적 타입 Circle*
    std::cout << typeid(pc).name() << std::endl; // 정적 타입 : Shape*
    std::cout << typeid(*pc).name() << std::endl; // 동적 타입 : Shape*
    Shape *pr = new Rectangle; // 정적 타입 : Shape*, 동적 타입 Rectangle*
    std::cout << typeid(pr).name() << std::endl; // 정적 타입 : Shape*
    std::cout << typeid(*pr).name() << std::endl; // 동적 타입 : Shape*

    // ps->draw();
    pc->draw();
    pr->draw(); // 기본 매개변수 값이 Green 인데도, Red가 나옴

    // 비가상함수의 기본 매개변수를 고정시키려면
    // 파생 클래스에서 재정의할 수 있는 가상 함수를 private로 두고
    // 이 가상함수를 호출하는 public 비가상 함수를 기본 클래스에 만들어 두는 것
    // 이 방법을 응용 한다면, 비가상 함수가 기본 매개변수를 지정하도록 할 수 있다.
    // 비가상 함수의 내부에서는 진짜 일을 맏는 가상 함수를 호출하도록 할 수 있다.
    
}