#include <iostream>
#include <cstring>

class TextBlock{
public:
    TextBlock(const char* _text)
    {
        text = _text;
    }
    const char& operator[](std::size_t position) const
    { return text[position]; }
    // 상수 객체에 대한 operator[]

    char& operator[](std::size_t position) 
    { return text[position]; }
    // 비상수 객체에 대한 operator[]

    // const char& operator[](std::size_t position)
    // { return text[position]; }
    // operator[]가 상수 객체 함수가 아니니까 호출 X (컴파일 에러)
private:
    std::string text;
};

class CTextBlock{
    public:
        std::size_t length() const; // 멤버 함수 선언
        // 생성자
        CTextBlock(const char* text) {
            if (text) {
                pText = new char[std::strlen(text) + 1];
                std::strcpy(pText, text);
            } else {
                pText = new char[1];
                pText[0] = '\0';
            }
            lengthIsValid = false;
            textlength = 0;
        }
    
        void setText(const char* text) {
            delete[] pText;
            pText = new char[std::strlen(text) + 1];
            std::strcpy(pText, text);
            lengthIsValid = false; // 길이 캐시 무효화
        }
        
        // 특정 위치의 문자 수정 (비상수 버전)
        char& operator[](std::size_t position) {
            lengthIsValid = false; // 수정되므로 길이 캐시 무효화
            return const_cast<char&>(
                static_cast<const CTextBlock&>(*this)[position] // 비상수->상수->비상수 캐스팅으로 코드 중복 방지
            );            
        }
        
        // 특정 위치의 문자 읽기 (상수 버전)
        const char& operator[](std::size_t position) const {
            return pText[position];
        }
    
    private:
        char *pText;
        //std::size_t textlength(); // (비트수준 상수성) 수정 불가능
        //bool lengthIsVaild; // 상수 멤버에서는 수정 불가능
        mutable std::size_t textlength; // 족쇄 해제
        mutable bool lengthIsValid; 

};


std::size_t CTextBlock::length() const
{
    if (!lengthIsValid){
        textlength = std::strlen(pText); 
        lengthIsValid = true; 
    }
    return textlength;
}


int main(){
    TextBlock tb("Hello");
    std::cout << tb[0]; // 비상수 멤버를 호출

    const TextBlock ctb("World");
    std::cout << ctb[0]; // 상수 멤버를 호출

    std::cout << tb[0]; // 비상수 버전의 TextBlock 객체를 읽음 
    tb[0] = 'x'; // 비상수 버전의 TextBlock 객체를 씀

    std::cout << ctb[0]; // 상수 버전의 TextBlock 객체를 읽음
    // ctb[0] = 'x'; // 상수 버전의 TextBlock 객체에 대해 쓰기는 안됨.

    // 비상수 객체 사용 예제
    CTextBlock block("안녕하세요");
    std::cout << "텍스트 길이: " << block.length() << std::endl;
    
    // 텍스트 수정 후 길이 재계산
    block.setText("안녕하세요, 세계!");
    std::cout << "수정 후 길이: " << block.length() << std::endl;
}