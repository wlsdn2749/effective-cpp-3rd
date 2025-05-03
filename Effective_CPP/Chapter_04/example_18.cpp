#include <iostream>
#include <memory>

struct Day{
    public:
        explicit Day(int d)
        : val(d) {}
    
        int get() const {return val;}
    private:
        int val;
    };
    
    struct Month{
    public:
        explicit Month(int d)
        : val(d) {}
        int get() const {return val;}
    private:
        int val;
    };
    
    struct Year{
    public:
        explicit Year(int d)
        : val(d) {}
        int get() const {return val;}
    private:
        int val;
    };

class Date{
public:
    // Date(int month, int day, int year)
    //     :month(month), day(day), year(year)
    // {};

    Date(const Month &m,
        const Day &d,
        const Year &y)
    :month(m.get()), day(d.get()), year(y.get())
    {};

private:
    int month;
    int day;
    int year;
};

class Investment{};

Investment* createInvestment(){
    return new Investment;
}

void getRidOfInvestment(Investment* iv)
{
    delete iv;
}
std::shared_ptr<Investment> createInvestmentSharedPtr(){
    // std::shared_ptr<Investment> pInv(0); // 이것도 nullptr이나 명시적 캐스팅이 좋다
    std::shared_ptr<Investment> pInv(static_cast<Investment*>(0), getRidOfInvestment); // 이게 나음
    // std::shared_ptr<Investment> pInv2(nullptr); // 이거나
    pInv = std::make_shared<Investment>(); // 새 객체 할당
    return pInv;
}

int main()
{
    // Date d(1999, 2, 3); // 매개변수가 잘못 입력되었는데... 잘됨 ??
    // Date d1(Year(9), Day(1), Month(1999)); // 매개변수 잘못 입력
    Date d1(Month(9), Day(1), Year(1999));

    Investment* p1 = createInvestment(); // 나중에 p1 해제 안하면 loss남
    delete p1; // 이러면 오류 안나는데? 사용자에게 이걸 떠넘겨버리면 문제..

    std::shared_ptr<Investment> sp1(createInvestment()); // 이렇게 하면 OK 근데
    // 이렇게 할때마다 선언해줘야하나?
    // 그냥 반환값을 shared_ptr로 해보자

    auto pInv = createInvestmentSharedPtr(); // 알아서 만들어지고, custom deleter로 알아서 해제됨.
}