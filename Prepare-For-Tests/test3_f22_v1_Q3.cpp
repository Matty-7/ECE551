#include <cstdlib>
#include <iostream>

class Thing {
    int x;
    
    public:
    Thing() : x(0) { std::cout << "Thing(" << x << ")\n"; }
    explicit Thing(int _x) : x(_x) { std::cout << "Thing(" << x << ")\n"; }
    ~Thing() { std::cout << "Destroying Thing(" << x << ")\n"; }
    int getX() { return x; }
    void setX(const int & r) { x = r; }
    int & f(Thing * tp) {
        x = 2 * x - tp->x;
        return x;
    }
};

int g(Thing & t, const int & r) {
    std::cout << "In g\n";
    Thing s(r);
    if (t.getX() > r) {
    t.setX(r);
    }
    else {
    s.setX(r + 5);
    }
    return t.getX() + r;
}
int main(void) {
    Thing t1(3);
    Thing * tp = new Thing();
    int & r = tp->f(&t1);
    Thing t2(*tp);
    t1.setX(g(t2, 5));
    std::cout << "Back in main\n";
    r += 7;
    delete tp;
    return EXIT_SUCCESS;
}
