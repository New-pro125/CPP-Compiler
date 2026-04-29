int add(int a, int b)
{
    return a + b;
}

void vfun()
{
    return 1;
}

int nfun()
{
    return;
}
float vfun2()
{
    return 1;
}
int bad_default_type(float x = "hi")
{
    int y = 0;
    return y;
}

int bad_default_order(int a = 1)
{
    return a;
}
int bad_default_order(int a, int b = 2)
{
    return a + b;
}
int x = 1;

x = x + 1;

const string b = "Hello,World!";
int main()
{
    int x = 7;
    int v = add("bad", 2);
    int u = add(1);
    int w = add(1, 2, 3);
    void badVar;
    x(4);
    vfun = 4;

    break;
    continue;
    float k = 3.9;
    k = k % 8;
    k <<= 2;
    k >>= 2;
    k ^= 1;
    k &= 2;
    k = ~k;
    k |= 8;
    switch (x)
    {
    case "z":
        x = 3;
        break;
    case 2.5:
        x = 4;
        break;
    default:
        x = 5;
        break;
    }
    string c = "de";
    switch (c)
    {
    case 4:
        x = 2;
        break;
    case 4:
        x = 3;
        break;
    default:
        int y = 0;
        break;
    default:
        int z = 0;
        break;
    }
    b = "Ahmed";
    const float a;
    int y = x + c;
    int c = 7;
    s -= "3";
    string s = "y";
    string t = "dd";
    string g = vfun();
    bool flat = s > t;
<<<<<<< HEAD
    char h = 'w';
    h += t;
=======

>>>>>>> c65c73a21822f070e50c0b5fc4be4b93061eba4f
    s *= "1";

    int m = 10 x = m + 1;

    int n = 20 if (s)
    {
    }
    int = 42;

    return 0;
}
