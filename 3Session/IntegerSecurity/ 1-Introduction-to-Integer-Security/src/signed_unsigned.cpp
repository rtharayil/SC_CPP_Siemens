#include <iostream>
using namespace std;

int main() {
    int signed_val = -1;
    unsigned int unsigned_val = 1;

    if (signed_val < unsigned_val) {
        cout << "signed < unsigned" << endl;
    } else {
        cout << "signed >= unsigned" << endl;
    }

    cout << "signed_val as unsigned: " << (unsigned int)signed_val << endl;
    return 0;
}