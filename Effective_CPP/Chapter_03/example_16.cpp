#include <iostream>


struct MyString {
    std::string s;

    MyString() : s("default") {
        std::cout << "[생성자] " << s << "\n";
    }

    ~MyString() {
        std::cout << "[소멸자] " << s << "\n";
    }

    void* operator new[](std::size_t size) {
        std::cout << "[new[]] size: " << size << "\n";
        void* p = malloc(size + 8);
        std::cout << "[new[]] allocated at: " << p << "\n";
        return static_cast<char*>(p) + 8;  // 앞에 8바이트 여유
    }
    
    void operator delete[](void* p) {
        std::cout << "[delete[]] raw ptr: " << p << "\n";
    
        void* real_ptr = static_cast<char*>(p) - 8;
    
        // 배열 길이 정보 복원
        std::size_t count = *(reinterpret_cast<std::size_t*>(real_ptr));
        std::cout << "[delete[]] count: " << count << "\n";
    
        MyString* typed_ptr = static_cast<MyString*>(p);
        for (std::size_t i = 0; i < count; ++i) {
            typed_ptr[i].~MyString();  // ✅ 소멸자 직접 호출
        }
    
        free(real_ptr);  // 마지막에 메모리 해제
    }
};

int main()
{
    std::string *stringArray = new std::string[100];
    
    delete[] stringArray;   // 실행은 되는데 segmentation fault 뜸
                            // valgrind로 실행해보면?

                            // new[]가 내부적으로 할당하는 offset이 있는데, 이게 8byte(배열의 크기)
                            // delete는 이를 이해하지 못하므로 애초부터 삭제 불가
                            // 수정된 버전 delete[]는 제대로 해제함
                            // 총 metadata(배열의 크기) 8byte + 3200 (100*32) loss

    MyString *stringPtr1 = new MyString;
    std::string *stringPtr2 = new std::string[100];

    delete[] stringPtr1;    // new로 생성한 객체는, 메타데이터가 필요없어서, 앞에 8byte를 할당x
                            // 그러나 delete[]는 -8byte 부터 시작하는데, 여기가 할당되어있지 않는 부분이므로
                            // segfault 혹은 invaild free가 뜨는게 맞다.
                            // 실제로 valgrind로 확인해도, -8 을 읽으려하는데, 여기서 invalid free가 나타남

    delete[] stringPtr2;    // 객체의 배열 삭제, 아까위와 마찬가지!
                            
}