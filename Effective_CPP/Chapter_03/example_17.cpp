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
}