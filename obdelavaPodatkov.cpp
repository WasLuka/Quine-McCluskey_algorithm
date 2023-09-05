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
    char buffer[4] = {0,0,0,0};

    std::cin >> cache;
    const int numSpremenljivke = cache;//koliko spremenljivk imamo
    std::cin >> cache;
    const int numMintermi = cache;//koliko mintermov imamo

    unsigned short int mintermi[numSpremenljivke] = {};

    for(int i = 0;i < numMintermi;i++)
    {
        std::cin >> mintermi[i];
    }

    for(int j = 0;j < numMintermi;j++)//preprost bubble sort za sortiranje po stevilu bitov, padajoče
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
    

    /*
    2 je tam zato da imam "dve tabeli" med katerima preklapljamo med poenostavljanjem
    numSpremenljivke je za stevilo bitov v mintermu z vrednostjo 1
    numMintermi je za specifičen minterm kjer je njegova vrednost shranjena
    numSpremenljivke je za specifičen bit v mintermu ki je lahko shranjen tudi kot -
    */
    char mintermichar[numSpremenljivke+1][numMintermi][numSpremenljivke];
    /*
    Najprej se ga razdeli na dva dela za dve tabeli potem po številu "1" v posameznem mintermu,
    potem na število mintermov, in spet na število spremenljivk da lahko shranimo ta minterm
    */

   for(int k = 0;k < numSpremenljivke+1;k++)//tukaj se jih zapiše v spremenljivko
   {

        count = 0;
        for(int i = 0;i < numMintermi;i++)
        {

            for(int j = 0;j < numSpremenljivke;j++)
            {
                mintermichar[k][i][j] = '.';
            }

            if(stBitovEna(mintermi[i]) == k)
            {
                for(int j = 0;j < numSpremenljivke;j++)
                {
                    cache = mintermi[i];
                    mintermichar[k][count][numSpremenljivke-j-1] = bitI(cache, j);
                }
                count++;
            }

        }

   }

    //dodaj še ignoriranje pik
    for(int i = 0;i < numSpremenljivke+1;i++)//printanje spremenljivke
    {
        for(int j = 0;j < numMintermi;j++)
        {   
            if(mintermichar[i][j][0] == '.')
            {
            }
            else
            {
                for(int k = 0;k < numSpremenljivke;k++)
                {
                    std::cout << mintermichar[i][j][k] << ' ';
                }
                std::cout << "\n";
            }
            
        }
        std::cout << "\n\n";
    }

    //treba je še dodati pisanje v .txt minimizacija v drugem programu
    //mogoče bi se v conzoli nardil input.txt > obdelavapodatkov.exe > out.txt
    //in potem out.txt > minimizacija.txt > rezultati.txt

    system("pause");
    return 0;

}