#include <iostream>
#include <vector>
using namespace std;
vector<int> v;
vector<int> v2(5, 10);
vector<int> v3 = {1, 2, 3, 4, 5};
#define DEBUG
int main() {
#ifdef DEBUG
    cout << "Debugging is enabled." << std::endl;
#endif
    v.push_back(2);
    cout<< v.size()<<endl;
   cout << "Program running." << std::endl;
    return 0;
}

