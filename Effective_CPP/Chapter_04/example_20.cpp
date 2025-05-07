#include <iostream>

class String{
public:
    String()
    {
        std::cout << " String 생성자 호출!" << "\n";
    }
    ~String(){
        std::cout << " String 소멸자 호출!" << "\n";
    }

    String(const String& other)
    {
        std::cout << "String 복사생성자 호출" << "\n";
    }
private:
    char* value;
};


class Person{
public:
    Person(){}
    virtual ~Person(){}
    Person(const Person& other)
    : name(other.name), address(other.address)
    {
        std::cout << "Person 복사 생성자 호출" << "\n";
    }

private:
    String name;
    String address;
};
    
class Student : public Person{
public:
    Student(){}
    ~Student(){}
    Student(const Student& other)
    : schoolName(other.schoolName), schoolAddress(other.schoolAddress), Person(other)
    {
        std::cout << "Student 복사 생성자 호출" << "\n";
    }
private:
    String schoolName;
    String schoolAddress;
};

bool validateStudent(Student s) // Student를 값으로 전달하는 함수
{
    return true;
}

bool validateStudentRef(const Student& s)
{
    return true;
}


class Window{
    public:
        virtual void display() const;
};

void Window::display() const
{
    std::cout << "Window Display " << std::endl;
}
    
class WindowWithScrollbars: public Window{
public:
    virtual void display() const;
};

void WindowWithScrollbars::display() const
{
    std::cout << "wwsb" << std::endl;
}

void printNameAndDisplay(Window w) // 매개변수가 복사손실에 당함
{
    // std::cout << w.name();
    w.display();
}

void printNameAndDisplayRef(const Window& w) // 매개변수가 복사손실에 당함
{
    w.display();
}
    
int main(){

    Student plato; // 여기서 생성자
    
    std::cout << "-------값에의한전달------" << "\n";
    bool platoIsOK = validateStudent(plato); // 여기서 복사 생성자 
    // 객체의 복사생성자, 멤버변수의 복사생성자가 같이 호출됨
    // 소멸할때는 각각의 객체에 대해 모두 실행

    std::cout << "--------상수객체 참조--------s" << "\n";
    bool paltoIsOKRef = validateStudentRef(plato);

    // 값에 의한 전달로 6번의 필요없는 복사생성자가 호출이 되버림.


    WindowWithScrollbars wwsb;
    printNameAndDisplay(wwsb); // window 
    printNameAndDisplayRef(wwsb); // wwsb
}
