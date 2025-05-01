#include <mutex>
#include <iostream>
#include <memory>
#include <vector>
#include <utility>

class Lock{
public:
    explicit Lock(std::mutex *pm)
    : mutexPtr(pm)
    {
        std::cout << "Lock 락 잠금" << std::endl;
        mutexPtr->lock();
    }
    ~Lock() 
    {
        std::cout << "Lock 락 해제" << std::endl;
        mutexPtr->unlock();
    }
private:
    std::mutex *mutexPtr;
};


class Uncopyable{
protected:
    Uncopyable(){};
    ~Uncopyable(){};

private:
    Uncopyable(const Uncopyable& rhs);
    Uncopyable& operator=(const Uncopyable& rhs);
};


class UncopyableLock : private Uncopyable{
    public:
    explicit UncopyableLock(std::mutex *pm)
    : mutexPtr(pm)
    {
        std::cout << "UncopyableLock 락 잠금" << std::endl;
        mutexPtr->lock();
    }
    ~UncopyableLock() 
    {
        std::cout << "UncopyableLock 락 해제" << std::endl;
        mutexPtr->unlock();
    }

private:
    std::mutex *mutexPtr;
};

// 관리하고 있는 자원에 대해 참조카운팅
// 소멸자가 없는 이유는, SharedLock이 소멸될때, 
// 비정적 멤버에 대해서 소멸자를 호출하기 떄문
class SharedLock{
public:
    explicit SharedLock(std::mutex *pm)
    : mutexPtr(pm, [](std::mutex* pm){
        std::cout << "SharedLock 삭제자에서 락 해제" << std::endl;
        pm->unlock();
    })
    // shared_ptr의 생성자로, 두번째 매개변수는 삭제자 지정
    {
        std::cout << "SharedLock 락 잠금 " << std::endl;
        mutexPtr.get()->lock();
    }

private:
    std::shared_ptr<std::mutex> mutexPtr;
};


class DeepCopyVector{
public:
    explicit DeepCopyVector(const std::vector<int>& data)
    : dataPtr(new std::vector<int>(data)) {
        std::cout << "DeepCopyVector 생성, 깊은 복사 수행" << std::endl;
    }
    // 복사 생성자 (깊은 복사)
    DeepCopyVector(const DeepCopyVector& other)
    : dataPtr(new std::vector<int>(*other.dataPtr)) {
        std::cout << "DeepCopyVector 복사 생성자 호출" << std::endl;
    }

    // 복사 대입 연산자 (깊은 복사)
    DeepCopyVector& operator=(const DeepCopyVector& other) {
        std::cout << "DeepCopyVector 복사 대입 연산자 호출" << std::endl;
        if (this != &other) {
            delete dataPtr;
            dataPtr = new std::vector<int>(*other.dataPtr);
        }
        return *this;
    }

    ~DeepCopyVector() {
        std::cout << "DeepCopyVector 소멸자 호출" << std::endl;
        delete dataPtr;
    }   
    void push(int value) {
        dataPtr->push_back(value);
    }
    void print() const {
        std::cout << "Vector 데이터: ";
        for (int val : *dataPtr)
            std::cout << val << ' ';
        std::cout << std::endl;
    }

private:
    std::vector<int>* dataPtr;
};

struct NamedMutex {
    std::mutex m;
    std::string name;

    NamedMutex(const std::string& n) : name(n) {}
};

// AutoLock은 하나의 클래스만 이 객체를 가리킬 수 있음
class AutoLock {
    public:
        explicit AutoLock(NamedMutex* pm)
            : mutexPtr(&pm->m), name(pm->name)
        {
            std::cout << "AutoLock [" << name << "] 락 획득" << std::endl;
            mutexPtr->lock();
        }
    
        AutoLock(AutoLock&& rhs)
            : mutexPtr(rhs.mutexPtr), name(std::move(rhs.name))
        {
            std::cout << "이동 연산자 호출" << name << std::endl;
            rhs.mutexPtr = nullptr;
        }
    
        AutoLock& operator=(AutoLock&& rhs) {
            std::cout << "AutoLock 이동 대입 연산자 호출" << std::endl;
            if (this != &rhs) {
                if (mutexPtr) {
                    std::cout << "기존 락 [" << name << "] 해제" << std::endl;
                    mutexPtr->unlock();
                }
                mutexPtr = rhs.mutexPtr;
                name = std::move(rhs.name);
                rhs.mutexPtr = nullptr;
            }
            return *this;
        }
    
        ~AutoLock() {
            std::cout << "AutoLock [" << name << "] 락 해제 시도" << std::endl;
            if (mutexPtr) {
                std::cout << "AutoLock [" << name << "] 락 해제 성공" << std::endl;
                mutexPtr->unlock();
            } else {
                std::cout << "AutoLock [" << name << "] 락 해제 실패 (소유권 없음)" << std::endl;
            }
        }
    
    private:
        std::mutex* mutexPtr;
        std::string name;
    };

int main(){
    std::mutex m;
    {
        Lock l(&m); // m 참조를 넘김
    } // 여기서 락 해제

    std::mutex m1;
    {
        Lock l2(&m);
        Lock l3(l2); // 락을 1번 잠구는데, 2번 해제 해버림..
    } 

    // 복사를 금지하는 기법
    std::mutex m2;
    {
        UncopyableLock ul1(&m2); // 복사 방지 
        // UncopyableLock ul2(ul1); // 복사가 방지되어 컴파일 에러가 남 
    }

    std::mutex m3;
    {
        SharedLock sl1(&m3);
        SharedLock sl2(sl1); // 복사함, 락 잠금과 해제가 1번씩 일어남, 복사를 했음에도.
    }

    // 자원을 진짜로 복사하는 예제
    {
        DeepCopyVector v1(std::vector<int>{1, 2, 3});
        DeepCopyVector v2 = v1; // 복사 대입 연산자
        DeepCopyVector v3(v2); // 복사 생성자
        v1.push(4);
        v2.push(5);
        v3.push(6);
        v1.print(); // 1 2 3 4
        v2.print(); // 1 2 3 5
        v3.print(); // 1 2 3 6
    }

    // 자원 이동
    {
        NamedMutex m4("m4");
        NamedMutex m5("m5");

        AutoLock al1(&m4); // al1이 m4에 대한 락 잠금
        AutoLock al2(std::move(al1)); // al1의 락(m4)를 al2에게 이전
        AutoLock al3(&m5); // al3가 m5에 대한 락 잠금
        al3 = std::move(al2); // al2의 락(m4)을 al3한테 이전, (이전의 a3의 락(m5) 해제해야함)
    } // 여기서 m4 락 해제
}

