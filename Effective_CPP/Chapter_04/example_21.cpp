class Rational{
public:
    Rational(int n = 0, int d = 1): n(n), d(d){};
    ~Rational(){};

    inline friend const Rational operator*(const Rational& lhs, const Rational& rhs)
    {
        return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
    } // XX


private:
    int n;
    int d;
};

int main(){
    Rational a(1, 2);
    Rational b(3, 4);
    Rational c = a*b;
}