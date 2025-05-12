#include <iostream>

class WebBrowser{
    public:
        void clearCache();
        void clearHistory();
        void removeCookies();
        
        void clearEverything(); 
        // clearCache, clearHistory, removeCookies
        // 를 호출하는 멤버 함수
};

void ClearWebBrowser(WebBrowser& wb) // 이렇게 비멤버 비프렌트로 사용하면, 캡슐화가 높아지고, 패키징 유연성, 확장성이 늘어남.
{
    // clearEverything() 과 같은 역할을 함.
}

int main(){
    
}