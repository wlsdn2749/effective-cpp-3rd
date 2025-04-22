#include <iostream>
#include <list>

class Point{
    int x, y;
};

class PhoneNumber{};

class ABEntry{
public:
    ABEntry();
    ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones);

private:
    std::string theName;
    std::string theAddress;
    std::list<PhoneNumber> thePhones;
    int numTimesConsulted;
};

// 멤버 초기화 리스트
ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones)
: theName(name),
  theAddress(address),
  thePhones(phones),
  numTimesConsulted(0)
  {}

// 초기화 아니고, 대입

ABEntry::ABEntry(const std::string& name, const std::string& address, const std::list<PhoneNumber>& phones)
{
    theName = name;
    theAddress = address;
    thePhones = phones;
    numTimesConsulted = 0;
}

ABEntry::ABEntry()
: theName(),
  theAddress(),
  thePhones(),
  numTimesConsulted(0)
{}



int main()
{
    Point p; // 여기서 p의 x,y값은 초기화 될까? 흠.. 

    int x = 0; // int의 직접 초기화
    const char * text = "A C-style string"; // 포인터의 직접 초기화
    double d;
    std::cin >> d; // 입력 스트림으로 읽음 으로써 "초기화" 수행
}