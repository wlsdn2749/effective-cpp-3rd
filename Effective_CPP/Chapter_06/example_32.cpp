#include <iostream>

class Person {};

class Student: public Person {}; // Student is a Person, but Person is not a Student

void eat(const Person& p)// 먹는것은 누구든 함
{
    std::cout << "eat";
}

void study(const Student& s) // 공부는 학생만 한다고 가정
{
    std::cout << "study";
}


void error(const std::string& msg)
{
    std::cout << msg;
}
class Bird
{
public:
	virtual void fly() = 0; // 새는 날 수 있음
};

class Penguin: public Bird{ // 펭귄도 새는 새인데, fly가 가능한가??
    
public:
    // void fly(){;}
    virtual void fly() {error("Attempt to make a penguin fly!");}
};

class Rectangle{
public:
    int _width = 0;
    int _height = 0;

    virtual void setHeight(int newHeight)  { _height = newHeight; }
    virtual void setWidth(int newWidth)  { _width = newWidth; }

    virtual int height() const  { return _height; }
    virtual int width() const  { return _width; }
};

void assert(bool a)
{
    std::cout << a;
}
void makeBigger(Rectangle& r)
{
	int oldHeight = r.height();
	r.setWidth(r.width() + 10); // 가로길이에 10 더하기
	assert(r.height() == oldHeight); // r의 세로길이가 변하지 않는다는 조건
}

class Square: public Rectangle {
public:
    virtual void setHeight(int newHeight) override {
        Rectangle::setHeight(newHeight);
        Rectangle::setWidth(newHeight);
    }
    virtual void setWidth(int newWidth) override {
        Rectangle::setWidth(newWidth);
        Rectangle::setHeight(newWidth);
    }
};

int main()
{
    Person p;
    Student s;

    eat(p); // OK
    eat(s); // OK

    study(s); // OK
    // study(p); // XX p != Student

    Penguin pen;
    pen.fly(); // 프로그램이 실행될때만 이를 알 수 있음


    Square sq;

    assert(sq.width() == sq.height());
    makeBigger(sq);
    assert(sq.width() == sq.height());
}