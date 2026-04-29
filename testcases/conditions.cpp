int add()
{
    int x = 5;
    int y = x;
    {
        int x = 5;
        int y = x;
        {
            int x = 5;
            int y = x;
        }
    }
    {
        int x = 5;
        int y = x;
    }
    int z = x;
}
int add2()
{
    int x = 5;
    int y = x;
    {
        int x = 5;
        int y = x;
        {
            int x = 5;
            int y = x;
        }
    }
    {
        int x = 5;
        int y = x;
    }
    int z = x;
}
int main()
{
    // int sum = 0;
    // for (int i = 0; i < 10; ++i)
    // {
    //     if (i == 5)
    //     {
    //         continue;
    //     }
    //     else if (i == 8)
    //     {
    //         break;
    //     }
    //     sum = sum + i;
    // }
    // int k = 0;
    // do
    // {
    //     k = k + 1;
    // } while (k < 3);
    // int x = 5;
    // if (x > 3)
    // {
    //     int x = 10;
    //     x = x + 1;
    // }
    // else
    // {
    //     int x = 20;
    //     x = x + 2;
    // }
    // x = x + 100;

    // int z = 10000;
    // while (k < 15)
    // {
    //     k = k + 1;
    //     if (k == 8)
    //         break;
    //     else
    //         continue;
    // }
    // z = 5000;
    // switch (x)
    // {
    // case 1:
    //     sum = sum + 1;
    // case 5:
    //     sum = sum + 5;
    //     break;
    // default:
    //     sum = sum + 10;
    //     break;
    // }
    return 0;
}
