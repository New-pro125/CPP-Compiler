int p = 0;
int func1(int p)
{
    {
        int p = 5;
    }
    return p;
}

void func()
{
    int x = 0, y = 0;
    for (int i = 0; i < 7; i++)
    {
        int x = i;
        y += x;
    }
}
string concat(string a, string b)
{
    return a + b;
}

int add_half(float x, float y = 0.5)
{
    return x + y;
}
int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

int do_something(const int x)
{
    return x + 1;
}

bool compare(int x = 0, int y = 0)
{
    return x > y;
}
int main()
{
    string res = concat("b", "c");
    int result = gcd(func1(10), 4);
    float resu = add_half(4);
    func();
    int c_val = do_something(5);
    bool flag = compare();
    bool flag2 = compare(result);
    bool flag3 = compare(result, c_val);
    return 0;
}
