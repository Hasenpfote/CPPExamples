#include <iostream>

class Foo final
{
public:
    Foo() = default;
    ~Foo() = default;

private:
    int value;
    struct
    {
        int x;
        int y;
    };
    union
    {
        int a;
        float b;
    };
    union
    {
        int v[2];
        struct
        {
            int z;
            int w;
        };
    };
};

struct point {
    point(int x, int y) : x_(x), y_(y) {}
    int x() const { return x_; }
    int y() const { return y_; }
    int hash() const { return hash_; }

private:
    union {
        int hash_;
        struct {
            short x_;
            short y_;
        };
    };
};

void main()
{
    Foo foo;
    //foo.value;  // NG.
    //foo.x = 10; // NG
    //foo.a = 10; // NG

    // foo.v[0] = 10;  // NG
    // foo.v[1] = 10;  // NG

    foo.z = 10; // !?
    foo.w = 11; // !?
    std::cout << foo.z << std::endl;    // !?
    std::cout << foo.w << std::endl;    // !?
}