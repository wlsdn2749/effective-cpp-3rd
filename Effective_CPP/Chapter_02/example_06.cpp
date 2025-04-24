#include <iostream>

// class HomeForSale{};
class HomeForSale{
    public:
        HomeForSale();
        void copyFrom(const HomeForSale& other) {
            *this = other; // private 복사 대입 연산자를 멤버 함수 내에서 호출
        }
        
    private:
        HomeForSale(const HomeForSale&);
        HomeForSale& operator=(const HomeForSale&);

    friend class RealEstateAgent;
};

class RealEstateAgent {
    public:
        // friend 클래스에서 private 복사 생성자 사용
        HomeForSale duplicateHome(const HomeForSale& original) {
            return HomeForSale(original); // private 복사 생성자 호출
        }
        
        // friend 클래스에서 private 복사 대입 연산자 사용
        void assignHome(HomeForSale& target, const HomeForSale& source) {
            target = source; // private 복사 대입 연산자 호출
        }
        void assignRealHome(RealHomeForSale& target, const RealHomeForSale& source) {
            target = source; // 여기서 막히는구나?
        }
    };


class Uncopyable{
protected:
    Uncopyable();
    ~Uncopyable();
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

class RealHomeForSale : private Uncopyable{
public:
    void copyFrom(const HomeForSale& other) {
        *this = other; // Uncopyable을 private 상속시켰기 때문에, operator=가 없다고 컴파일 에러
    }
    friend class RealEstateAgent;
};

int main(){
    HomeForSale h1;
    HomeForSale h2;
    RealEstateAgent r1;
    
    // HomeForSale h3(h1); // private로 막았기 때문에 컴파일 에러
    // h1 = h2; // 컴파일 에러

    h2.copyFrom(h1); // h2에 h1을 복사 대입 생성자를 통해 넣기 
    r1.assignHome(h2, h1); // friend class r1에서 h2에 h1를 넣도록 사용 (우회)

    RealHomeForSale rh1;
    RealHomeForSale rh2;
    RealHomeForSale rh3(rh1); // RealHomeForSale을 Uncopyable로 부터 private 상속 시켰기 떄문에, 복사 생성자 사용 X
    rh2 = rh1; // 복사 대입 연산자 또한 사용 x
    r1.assignHome(rh2, rh1); // friend class r1에서 h2에 h1를 넣도록 사용 (우회)

}