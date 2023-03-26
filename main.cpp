#include <iostream>
#include <math.h>

int stBitovEna(int num)
{
    int count = 0;
    while(num > 0)
    {
        if(num % 2 == 1)
        {
            count++;
        }
        num = num / 2;
    }
    return count;
}

char bitI(int num, int bshift)
{
    unsigned int i = ((num >> bshift) & 1); 
    return (i == 1 ? '1' : '0');
}


int main()
{   
    int cache;

    std::cin >> cache;
    const int varT = cache;//koliko spremenljivk imamo
    std::cin >> cache;
    const int mT = cache;//koliko mintermov imamo

    unsigned short int mintermi[varT] = {};

    for(int i = 0;i < mT;i++)
    {
        std::cin >> mintermi[i];
    }

    for(int j = 0;j < mT;j++)//preprost bubble sort za sortiranje po stevilu bitov, padajoče
    {
        for(int i = 1;i < mT;i++)
        {
            if(stBitovEna(mintermi[i]) < stBitovEna(mintermi[i-1]))
            {
                cache = mintermi[i];
                mintermi[i] = mintermi[i-1];
                mintermi[i-1] = cache;
            }
        }
    }
    
    for(int i = 0;i < mT;i++)
    {
        std::cout << mintermi[i] << "\n";
    }

    /*
    varT je za stevilo bitov v mintermu z vrednostjo 1
    mT je za specifičen minterm kjer je njegova vrednost shranjena
    varT je za specifičen bit v mintermu ki je lahko shranjen tudi kot -
    */
    char mintermichar[varT][mT+1][varT] = {};


    for(int k = 0;k < varT+1;k++)
    {   
        for(int i = 0;i < mT;i++)
        {
            if(stBitovEna(mintermi[i]) == k)
            {
                for(int j = 0;j < varT;j++)
                {
                    cache = mintermi[i];
                    mintermichar[k][i][j] = bitI(cache,j);
                }
            }
            else
            {
                for(int j = 0;j < varT;j++)
                {
                    mintermichar[k][i][j] = 'a';
                }
            }
        }
    }


    for(int i = 0;i < varT+1;i++)
    {
        for(int j = 0;j < mT;j++)
        {
            for(int k = 0;k < varT;k++)
            {
                std::cout << mintermichar[i][j][k] << ' ';
            }
            
            std::cout << std::endl;
        }
        std::cout << "\n" << std::endl;
    }

    return 0;

}