#include "StringsVault.h"
#include <iostream>

int main(void) {
    StringVault v("./lines.txt");
    if(!v.isVaultOpen()) {
        std::cout << "failed to open file vault" << std::endl;
        return -1;
    }
    for(int i = 0; i < 8; ++i) {
        std::cout << "Id: " << i << ", str: " << v.getStrById(i) << std::endl;
    }

    v.setStr(6, "value6");
    return 0;
}
