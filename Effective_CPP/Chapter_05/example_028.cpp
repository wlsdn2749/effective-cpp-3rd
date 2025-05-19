#include <iostream>
#include <memory>
#include <string>

class Point{
public:
	Point(int x, int y): x(x), y(y) {}
	const int getX() const {return x;}
	const int getY() const {return y;}
	void setX(int newVal) { x = newVal; }
	void setY(int newVal) { y = newVal; }
private:
	int x, y;
};

struct RectData{
	Point ulhc;
	Point lrhc;
	RectData(Point ulhc, Point lrhc): ulhc(ulhc), lrhc(lrhc) {}
};

class Rectangle{
public:
	const Point& upperLeft() const {return pData->ulhc;}
	const Point& lowerRight() const {return pData->lrhc;}
	
	Rectangle(std::shared_ptr<RectData> data): pData(data) {}

	std::string toString() const
	{
		return "(" + std::to_string(pData->ulhc.getX()) + ", " +
		             std::to_string(pData->ulhc.getY()) + ") - (" +
		             std::to_string(pData->lrhc.getX()) + ", " +
		             std::to_string(pData->lrhc.getY()) + ")";
	}

private:
	std::shared_ptr<RectData> pData;
};

class GUIObject {};

const Rectangle boundingBox(const GUIObject& obj) {
    Point p1(10, 10);
    Point p2(50, 50);
    std::shared_ptr<RectData> data = std::make_shared<RectData>(p1, p2);
    return Rectangle(data);
}

int main()
{
    GUIObject obj;
    GUIObject* pgo = &obj;
    const Point* pUpperLeft = &(boundingBox(*pgo).upperLeft());
    // 임시객체 전엔 x,y가 쓰레기값. 그러다가 임시객체로 부터 할당하는데
    
    // 여기서 사라지니까, uUpperLeft는 이상한 x,y만 가리키고 있을거
    
    std::cout << "(" << pUpperLeft->getX() << ", " << pUpperLeft->getY() << ")" << std::endl;
    // 삭제된 메모리의 값을 가져오는건 컴파일러마다 다르지만
    // 여기서는 0,0으로 가져옴

    return 0;
}