#include <iostream>
#include <math.h>

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
    char mintermichar[2][numSpremenljivke+1][numMintermi][numSpremenljivke];
    /*
    Najprej se ga razdeli na dva dela za dve tabeli potem po številu "1" v posameznem mintermu,
    potem na število mintermov, in spet na število spremenljivk da lahko shranimo ta minterm
    */

   for(int k = 0;k < numSpremenljivke+1;k++)
   {

        count = 0;
        for(int i = 0;i < numMintermi;i++)
        {

            for(int j = 0;j < numSpremenljivke;j++)
            {
                mintermichar[0][k][i][j] = '.';
                mintermichar[1][k][i][j] = '.';
            }

            if(stBitovEna(mintermi[i]) == k)
            {
                for(int j = 0;j < numSpremenljivke;j++)
                {
                    cache = mintermi[i];
                    mintermichar[0][k][count][numSpremenljivke-j-1] = bitI(cache, j);
                }
                count++;
            }

        }

   }

    for(int i = 0;i < numSpremenljivke+1;i++)
    {
        for(int j = 0;j < numMintermi;j++)
        {
            for(int k = 0;k < numSpremenljivke;k++)
            {
                std::cout << mintermichar[0][i][j][k] << ' ';
            }
            
            std::cout << std::endl;
        }
        std::cout << "\n" << std::endl;
    }
    std::cout << "_____________________\n";

    //tukaj naprej se začne minimizacija

    bool end;
    int enakost;
    char primernik;
    char primerjeni;
    int mintermadd;
    int check;
    while(1)
    {   
        end = true;
        for(int nivo = 0;nivo < numSpremenljivke;nivo++)//st "1"
        {   
            mintermadd = 0;
            for(int minterm = 0;minterm < numMintermi;minterm++)//mintermi z tem st "1"
            {   
                if(mintermichar[0][nivo][minterm][0] == '.')
                {   
                    goto preskoci;
                }
                //dva for loopa ki gresta iz po št. "1" v mintermu in čez vse posamične minterme
                for(int minterm2 = 0;minterm2 < numMintermi;minterm2++)//mintermi z +1 st "1" za dajanje skupaj
                {   
                    enakost = 0;
                    if(mintermichar[0][nivo+1][minterm2][0] == '.')
                    {
                        goto praskoci;
                    }
                    for(int m = 0;m < numSpremenljivke;m++)//ce so enaki razen enga
                    {
                        primernik = mintermichar[0][nivo][minterm][m];
                        primerjeni = mintermichar[0][nivo+1][minterm2][m];
                        if(primernik == primerjeni)
                        {
                            enakost++;
                        }
                    }
                    if(enakost == (numSpremenljivke-1))
                    {   
                        end = false;
                        check = 0;
                        for(int m = 0;m < numSpremenljivke;m++)//primerjanje shranimo v buffer
                        {
                            primernik = mintermichar[0][nivo][minterm][m];
                            primerjeni = mintermichar[0][nivo+1][minterm2][m];
                            if(primernik == primerjeni)
                            {
                                buffer[m] = primernik;
                            }
                            else
                            {
                                buffer[m] = '-';
                            }
                        
                        }
                        for(int mintermC = 0;mintermC < numMintermi;minterm++)//tukaj preverimo ce je ta kombinacija ze vpisana
                        {
                            for(int m = 0;m < numSpremenljivke;m++)
                            {
                                if(buffer[m] == mintermichar[1][nivo][mintermC][m])
                                {
                                    check++;
                                }
                            }
                            if(check == numSpremenljivke)
                            {
                                for(int m = 0;m < numSpremenljivke;m++)
                                {
                                    mintermichar[1][nivo][mintermadd][m] = buffer[m];
                                }
                            }
                        }

                        mintermadd++;    
                        end = false;
                    }
                    praskoci:;
                }
                preskoci:;
            }
        }

        
        if(end)
        {
            goto finish;
        } 
        for(int i = 0;i < numSpremenljivke+1;i++)
        {
            for(int j = 0;j < numMintermi;j++)
            {
                for(int k = 0;k < numSpremenljivke;k++)
                {
                    std::cout << mintermichar[1][i][j][k] << ' ';
                    mintermichar[0][i][j][k] = mintermichar[1][i][j][k];
                    mintermichar[1][i][j][k] = '.';
                }
            
                std::cout << std::endl;
            }
            std::cout << "\n" << std::endl;
        }
        std::cout << "_____________________\n";  
    }
    finish:;

    //printanje rezultatov


    return 0;

}