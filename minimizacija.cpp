#include <iostream>

int main()
{
    int iCache;
    char cCache;
    int numSpremenljivke;
    int numMintermi;
    //iz datoteke output.txt vzamemo te vrednosti ki smo jih
    //prej zapisali s programom obdelavaPodatkov.exe
    std::cin >> numSpremenljivke;
    std::cin >> numMintermi;
    
    int vhMintermi[numMintermi];
    std::string mintermi[numMintermi];
    std::string cacheMintermi[numMintermi];
    std::string sCache = "";
    
    //vzamemo vrednosti in jih damo v str obliko
    for(int m = 0;m < numMintermi;m++)
    {
        for(int s = 0;s < numSpremenljivke;s++)
        {
            std::cin >> cCache;
            sCache = sCache + cCache;
        }
        mintermi[m] = sCache;
        sCache = "";
    }
    //vzamemo še vhodne vrednosti ki so bile dane v obdelavaPodatkov.exe
    for(int i = 0;i < numMintermi;i++)
    {
        std::cin >> iCache;
        vhMintermi[i] = iCache;
    }

    //tukaj se začne minimiziranje

    

    return 0;
}
