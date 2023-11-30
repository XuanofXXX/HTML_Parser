/**
 * @brief Construct a new Pair object
 * @param T1 
 * @param T2 
 */

template<typename T1, typename T2>
class Pair {
private:
    T1 val1;
    T2 val2;

public:
    // 默认构造函数
    Pair() {}

    // 带参数的构造函数
    Pair(const T1& a, const T2& b) : val1(a), val2(b) {}

    // 获取first成员的方法
    T1 first() const { return val1; }

    // 获取second成员的方法
    T2 second() const { return val2; }

    // 设置first成员的方法
    void setFirst(const T1& a) { val1 = a; }

    // 设置second成员的方法
    void setSecond(const T2& b) { val2 = b; }
};
