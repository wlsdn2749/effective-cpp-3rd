#include <iostream>

class TimeKeeper{
    public:
        TimeKeeper(){ std::cout << "TimeKeeper 생성됨 \n";};
        virtual ~TimeKeeper(){ std::cout << "TimeKeeper 소멸됨 \n";};
        
};
class AtomicClock: public TimeKeeper {
private:
    int* resource;

public:
    AtomicClock(){
        std::cout << "AtomicClock 생성됨\n";
        // 큰 배열 할당
        resource = new int[100000]; 
        for(int i = 0; i < 100000; i++) {
            resource[i] = i; // 메모리 사용
        }
        std::cout << "AtomicClock 메모리 할당: " << resource << "\n";
    }

    ~AtomicClock() {
        std::cout << "AtomicClock 소멸 시작\n";
        delete[] resource; // 이 코드가 실행되지 않으면 메모리 누수 발생
        std::cout << "AtomicClock 메모리 해제 완료\n";
    }
};
class WaterClock: public TimeKeeper {};
class WristClock: public TimeKeeper {};

// 전역 변수로 AtomicClock 객체 저장 (최적화 방지)
TimeKeeper* global_ptr = nullptr;

TimeKeeper* getTimeKeeper() {
    AtomicClock* ptr = new AtomicClock();
    global_ptr = ptr; // 전역 변수에 저장하여 최적화 방지
    return ptr;
}


int main() {
    std::cout << "프로그램 시작\n";
    TimeKeeper* ptr = getTimeKeeper();
    
    // 출력으로 실제 소멸자 호출 확인
    std::cout << "객체 삭제 전\n";
    delete ptr;
    std::cout << "객체 삭제 후\n"; // 소멸자가 호출되지 않았음
    
    // 이 시점에서 AtomicClock의 소멸자가 호출되지 않았다면
    // resource 배열의 메모리는 해제되지 않은 상태임
    // valgrind --leak-check=full output/example_07로 확인 가능

    // virtual을 붙였을 경우에 AtomicClock의 메모리가 정상적으로 해제 되고
    // valgrind로 확인했을때도 leak가 없다.
    
    std::cout << "프로그램 종료\n";
    return 0;
}
