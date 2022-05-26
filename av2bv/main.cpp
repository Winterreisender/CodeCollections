#include <iostream>
#include "bv2av.hpp"

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout << "Input av or BV number" << endl;
        return 1;
    }

    const char* input = argv[1];
    if(input[0] == 'A' || input[0] == 'a' )
        cout << av2bv(input) << endl;
    else if(input[0] == 'B' || input[0] == 'b' )
        cout << bv2av(input) << endl;
    else
        cout << "Error: Can not tell av or BV. Use avxxxxxx or BVxxxxxx" << endl;
    return 0;
}
