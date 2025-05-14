#include <iostream>
#include <chrono>
#include <stdexcept>
#include <string>

//--------------------------------------------------
//  CountingString : A lightweight wrapper around
//  std::string that counts every ctor/dtor/assign
//--------------------------------------------------
struct CountingString
{
    // --- static counters ---
    static inline long long default_ctor     = 0;
    static inline long long from_literal_ctor= 0;
    static inline long long copy_ctor        = 0;
    static inline long long move_ctor        = 0;
    static inline long long copy_assign      = 0;
    static inline long long move_assign      = 0;
    static inline long long dtor             = 0;

    std::string data;

    // default
    CountingString() : data()                        { ++default_ctor; }
    // from literal / std::string
    CountingString(const char* s) : data(s)          { ++from_literal_ctor; }
    CountingString(const std::string& s) : data(s)   { ++from_literal_ctor; }
    // copy / move
    CountingString(const CountingString& o) : data(o.data)       { ++copy_ctor;  }
    CountingString(CountingString&& o) noexcept : data(std::move(o.data)) { ++move_ctor; }
    // assignment
    CountingString& operator=(const CountingString& o)           { ++copy_assign; data = o.data;   return *this; }
    CountingString& operator=(CountingString&& o) noexcept       { ++move_assign; data = std::move(o.data); return *this; }
    // dtor
    ~CountingString()                                            { ++dtor; }

    // minimal API needed for the sample
    std::size_t length() const                                   { return data.length(); }
    operator const std::string&() const                          { return data; }

    // helpers
    static void reset()
    {
        default_ctor = from_literal_ctor = copy_ctor = move_ctor =
        copy_assign  = move_assign      = dtor       = 0;
    }
    static void print(const std::string& tag, double ms)
    {
        std::cout << "=== " << tag << " ===\n";
        std::cout << "elapsed (ms)        : " << ms              << '\n';
        std::cout << "default ctor        : " << default_ctor    << '\n';
        // std::cout << "literal/std ctor    : " << from_literal_ctor << '\n';
        std::cout << "copy ctor           : " << copy_ctor       << '\n';
        std::cout << "move ctor           : " << move_ctor       << '\n';
        std::cout << "copy assign         : " << copy_assign     << '\n';
        std::cout << "move assign         : " << move_assign     << '\n';
        std::cout << "dtor                : " << dtor            << "\n\n";
    }
};

//--------------------------------------------------
//  Three variants under test
//--------------------------------------------------
CountingString encryptPassword1(const CountingString& password)
{
    using namespace std;
    constexpr int MinimumPasswordLength = 16;
    CountingString encrypted;

    if (password.length() < MinimumPasswordLength)
        throw logic_error("Password is too short");

    encrypted = password;           // copy‑assign
    return encrypted;               // NRVO or move
}

CountingString encryptPassword2(const CountingString& password)
{
    using namespace std;
    constexpr int MinimumPasswordLength = 16;

    if (password.length() < MinimumPasswordLength)
        throw logic_error("Password is too short");

    CountingString encrypted;       // default‑ctor
    encrypted = password;           // copy‑assign
    return encrypted;
}

CountingString encryptPassword3(const CountingString& password)
{
    using namespace std;
    constexpr int MinimumPasswordLength = 16;

    if (password.length() < MinimumPasswordLength)
        throw logic_error("Password is too short");

    CountingString encrypted(password); // copy‑ctor
    return encrypted;
}

//--------------------------------------------------
//  Simple micro‑benchmark driver
//--------------------------------------------------
int main()
{
    using namespace std;
    constexpr int Iterations = 1000;

    auto benchmark = [&](auto&& func, const string& tag)
    {
        CountingString::reset();
        auto t0 = chrono::high_resolution_clock::now();

        for (int i = 0; i < Iterations; ++i)
        {
            try
            {
                if (i % 2 == 0)      // even: long enough → 정상 동작
                    func(CountingString("ThisPasswordIsLongEnough"));
                else                 // odd : short → 예외 발생
                    func(CountingString("short"));
            }
            catch (const logic_error&)
            {
                // 의도적으로 무시
            }
        }

        auto dt = chrono::duration<double, milli>(chrono::high_resolution_clock::now() - t0).count();
        CountingString::print(tag, dt);
    };

    benchmark(encryptPassword1, "encryptPassword1");
    benchmark(encryptPassword2, "encryptPassword2");
    benchmark(encryptPassword3, "encryptPassword3");
    return 0;
}