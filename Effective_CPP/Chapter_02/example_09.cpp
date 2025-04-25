#include <iostream>

// class Transaction{
//     public:
//         Transaction();
//         virtual void logTransaction() const = 0; // 타입에 따라 달라지는 로그 기록
// };
    
// Transaction::Transaction()
// {
//     logTransaction(); // 생성시킬때, 로깅
// }


// class BuyTransaction: public Transaction{
// public:
//     virtual void logTransaction() const;
// };

    

// class Transaction_A{
//     public:
//         Transaction_A()
//         { init(); }
//         virtual void logTransaction() const = 0;
//     private:
//         void init(){logTransaction();}
// };

// class BuyTransaction_A: public Transaction_A{
// public:
//     virtual void logTransaction() const; 
// };


class Transaction_B{
    public:
        explicit Transaction_B(const std::string& logInfo);
        void logTransaction(const std::string& logInfo) const;
};
    
Transaction_B::Transaction_B(const std::string& logInfo)
{
    logTransaction(logInfo);
}

void Transaction_B::logTransaction(const std::string& logInfo) const {
    std::cout << "Transaction_B logging: " << logInfo << std::endl;
}

class BuyTransaction_B: public Transaction_B{
public:
    BuyTransaction_B(std::string params) : Transaction_B(createLogString(params))
    {}

private:
    // 매개변수 타입을 일치시킴
    static std::string createLogString(std::string params);
};
    
std::string BuyTransaction_B::createLogString(std::string params){
    return params;
}

int main()
{
    // BuyTransaction b; 
    // BuyTransaction 객체를 생성할때, Transaction의 생성자도 같이 호출 되는데
    // Transaction의 생성자는, 기본 클래스에서 실행되므로, 순수가상함수를 실행한다는 에러뿐만 아니라, 
    // 구현부를 찾을수 없다고 뜬다.

    // BuyTransaction_A ba;

    BuyTransaction_B btb(std::string("123"));
}
    