#include <iostream>

class Bitmap{
public:
    int value = 1;
};
class Widget{
public:
	// Widget& operator=(const Widget& rhs);
    Widget& operator=(Widget rhs);
    // Widget(const Widget& rhs);
    void swap(Widget& rhs);
private:
	Bitmap *pb;
};

// Widget& Widget::operator=(const Widget& rhs)
// {
//     if(this == &rhs) return *this; // 해결법 1. 일치성 검사

// 	delete pb;
// 	pb = new Bitmap(*rhs.pb); // segfault, 삭제된 객체에 new()
// 	return *this;
// }

// 해결법 2. 문장 순서를 조절하는 것으로 해결
// Widget& Widget::operator=(const Widget& rhs)
// {
//     Bitmap *pOrig = pb;
//     pb = new Bitmap(*rhs.pb);
//     delete pOrig;

//     return *this;
// }
void Widget::swap(Widget& rhs)
{
    std::swap(pb, rhs.pb);
}
// Widget::Widget(const Widget& rhs)
// {
//     pb = new Bitmap(*rhs.pb);
// }
// 해결법 3. 복사 후 맞바꾸기 기법 사용
// Widget& Widget::operator=(const Widget& rhs)
// {
//     Widget temp(rhs);
//     swap(temp);
//     return *this;
// }

// 해결법 3.a 복사 후 맞바꾸기 기법에서, 값에 의한 전달 사용
Widget& Widget::operator=(Widget rhs) // 여기서 rhs의 사본이 생성됨. 
{
    swap(rhs);
    return *this;
}
Widget w;

int main()
{
    w = w; // 이 코드 자체는 논리적으로 문제가 없음!
}