#include <iostream>

class DBConnection{
public:
    static DBConnection create(){
        DBConnection conn;
        conn.data = new int[10];
        return conn;
    }
    void close() {
        delete[] data;
        data = nullptr;
        std::cout << "DBConnection의 소멸자 호출" << std::endl;
    }

    int get(int position){
        if(data == nullptr)
            throw std::runtime_error("data가 이미 null임");
        return data[position];
    }
private:
    int* data;
};

class DBConn{
public:
    DBConn(DBConnection connection) : db(connection) {}
    ~DBConn()
    {
        try{
            db.close();
            std::cout << db.get(1) << std::endl;  // 예외 발생
        }
        // catch(std::exception e){
        //     std::cout << "예외 삼킴" << e.what() << std::endl;   
        //     std::abort; // 이렇게 하면 프로그램을 바로 종료
        // }
        catch(const std::exception& e){
            std::cout << "예외 삼킴" << e.what() << std::endl;   
            // 이렇게 하면 예외를삼킴
        }

        // 일반적으로 여기서 segfault 에러가 발생하는데,
        // 다른 객체가 값을 재할당함으로써 에러가 발생하지 않을 수 있음
        
    }
private:
    DBConnection db;
};


class MyDBCon{
public:
    MyDBCon(DBConnection connection) : db(connection) {}
    void close()
    {
        db.close();
        closed = true;
    }
    ~MyDBCon()
    {
        if(!closed)
        {
            try{
                db.close();
            }
            catch(const std::exception& e){
                std::cout << "close() 호출이 실패" << std::endl;
            }
        }
    }
private:
    DBConnection db;
    bool closed;
};
    
int main()
{
    DBConn dbc(DBConnection::create());  // 객체 생성후, DBConn 객체가 관리
    MyDBCon mydbc(DBConnection::create()); // 객체 생성후 MyDBCon 객체가 관리
    mydbc.close(); // 사용자에게 close를 할 수 있고, 적지 않아도 자동으로 호출되어 실행됨.
} // 여기서 DBConn 객체가 소멸되면서 소멸자 자동으로 호출