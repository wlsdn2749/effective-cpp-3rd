class Base{
private:
    int x;
public:
    virtual void mf1() = 0;
    virtual void mf1(int);
    virtual void mf2();

    void mf3();
	void mf3(double);
};

class Derived: public Base{
public:
    using Base::mf1;
    using Base::mf3;
    virtual void mf1();
    void mf3();
    void mf4();
};
    
void Derived::mf4()
{
    mf2();
}
class PDerived: private Base{
public:
    virtual void mf1() {Base::mf1();} // 전달되며 암시적으로 인라인 함수가됨
};

int main()
{
    Derived d;
    PDerived pd;
    int x;

    d.mf1(); // Derived::mf1을 호출한다.
   
    d.mf1(x); // 에러 -> Derived::mf1이 base::mf1을 가립니다.

    d.mf2(); // Base::mf2를 호출한다

    d.mf3(); // Derived::mf3을 호출한다.
    d.mf3(x); // Derived::mf3이 Base::mf3을 가린다.

    // pd.mf1(x); // private상속으로 public에 있는 내용을 가렸음에도, 
    pd.mf1(); // private상속으로 public에 있는 내용을 가렸음에도, 사용 가능
    // 만약 using 을 사용하게 되면, 그 이름에 해당하는 모든 것들이 파생 클래스로 내려오므로
    // 매개변수 있는 버전, 없는 버전 모두 사용가능하다.
}