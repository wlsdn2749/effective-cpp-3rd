#include<iostream>
#include<string>

void logCall(const std::string& funcName)
{
    std::cout << "Calling: " << funcName << std::endl;
}

class Customer{
public:
	Customer() = default;
	Customer(std::string _name, int age);
	Customer(const Customer& rhs);
	Customer& operator=(const Customer& rhs);
	void print();
private:
	std::string name;
	int age;
};

void Customer::print()
{
	std::cout << "your name is " << name << "your age is " << age << std::endl;
}
Customer::Customer(std::string _name, int _age)
: name(_name), age(_age){}

Customer::Customer(const Customer& rhs)
: name(rhs.name), age(rhs.age)
{
	logCall("Customer copy assignment operator");
}

Customer& Customer::operator=(const Customer& rhs)
{
	logCall("Customer copy assignment operator");
	name = rhs.name;
	age = rhs.age;
	return *this;
}


class PriorityCustomer : public Customer{
	public:
		PriorityCustomer() = default;
		PriorityCustomer(int _priority);
		PriorityCustomer(const PriorityCustomer& rhs);
		PriorityCustomer& operator=(const PriorityCustomer& rhs);
	
	private:
		int priority;
	};
PriorityCustomer::PriorityCustomer(int _priority)
: priority(_priority){}
PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
: 	Customer(rhs), // 기본 클래스의 복사 생성자 호출
	priority(rhs.priority)
{
	logCall("PriorityCustomer copy constructor");
}

PriorityCustomer&
PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
	logCall("PriorityCustomer copy assignment operator");
	Customer::operator=(rhs); // 기본 클래스의 복사 대입 연산자 호출
	priority = rhs.priority;
	return *this;
}
int main()
{
    Customer c1;
    Customer c2;
    Customer c3(c1); // 이러면 문제가 생기지 않는데
    c2 = c1;

	Customer c4("Kurby", 1234);
	Customer c5 = c4;
	Customer c6(c4);
	c4.print();
	c5.print(); // 복사를 헀음에도 불구하고? 쓰레기값으로 초기화
	c6.print(); // 복사를 헀음에도 불구하고? 쓰레기값으로 초기화

	PriorityCustomer pc1(10);
	PriorityCustomer pc2(pc1);
	PriorityCustomer pc3 = pc1; 
	pc1.print();
	pc2.print();
	pc3.print();

}