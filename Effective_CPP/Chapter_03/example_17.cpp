#include <iostream>
#include <memory>

class Widget{};

int priority(){return 1;}
int priority_throwError(bool isThrow){
    if(isThrow)
        throw std::exception();
    return 1;
}
void processWidget(std::shared_ptr<Widget> pw, int priority){
    return;
}

// processWidget(new Widget, priority()); // 컴파일이 안됨
// processWidget(std::shared_ptr<Widget>(new Widget), priority());

int main()
{
    // processWidget(new Widget, priority()); // 컴파일이 안됨 암시적 변환이 없음
    processWidget(std::shared_ptr<Widget>(new Widget), priority());

    processWidget(std::shared_ptr<Widget>(new Widget), priority_throwError(true));
    // priority에서 에러 발생 시킴
    // 만약 컴파일러가 
    // 1. new Widget
    // 2. priority() 호출
    // 3. std::shared_ptr<Widget> 호출 순서로 실행했다면?
    // 4. 자원 호출이 제대로 되지 않고 Widget 자원이 누출됨

    auto pw = std::shared_ptr<Widget>(new Widget);
    processWidget(pw, priority_throwError(true)); 
    // priority()에서 에러가 나더라도, 자원 누출은 안됨.
} 