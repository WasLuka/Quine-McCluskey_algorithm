#include <iostream>

int stBitovEna(int num)//koliko bitov v minermu je 1
{
    int vrsta = 0;
    while(num > 0)
    {
        if(num % 2 == 1)
        {
            vrsta++;
        }
        num = num / 2;
    }
    return vrsta;
}

char bitI(int num, int bShift)//vrne ali je bit na določeni poziciji označeni z bShift 1 ali 0
{
    unsigned int i = ((num >> bShift) & 1); 
    return (i == 1 ? '1' : '0');
}

int main()
{   
    int cache;
    int count;

    std::cin >> cache;
    const int numSpremenljivke = cache;//koliko spremenljivk imamo
    std::cin >> cache;
    const int numMintermi = cache;//koliko mintermov imamo

    unsigned short int mintermi[numSpremenljivke] = {};

    for(int i = 0;i < numMintermi;i++)
    {
        std::cin >> mintermi[i];
    }

    //sortiranje mintermov po velikosti
    for(int j = 0;j < numMintermi;j++)
    {
        for(int i = 1;i < numMintermi;i++)
        {
            if(mintermi[i-1] > mintermi[i])
            {
                cache = mintermi[i];
                mintermi[i] = mintermi[i-1];
                mintermi[i-1] = cache;
            }
        }
    }

    for(int j = 0;j < numMintermi;j++)//sortiranje po stevilu bitov, narastujoče
    {
        for(int i = 1;i < numMintermi;i++)
        {
            if(stBitovEna(mintermi[i]) < stBitovEna(mintermi[i-1]))
            {
                cache = mintermi[i];
                mintermi[i] = mintermi[i-1];
                mintermi[i-1] = cache;
            }
        }
    }
    
    //do tukaj so številke razporejene po št bitov ter po velikosti
    

   
    

    return 0;
}
