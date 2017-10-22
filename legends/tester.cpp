#include <string>
#include <fstream>
void test(std::string acFile, std::string myFile){
    std::fstream acF(acFile), myF(myFile);
    std::string ac, mine;
    int numWA = 0;
    while ( acF>>ac && myF >> mine) {
        if (ac != mine) {
            printf("WA\n");
            ++numWA;
        }
    }
    printf("Total WA: %d\n", numWA);
}