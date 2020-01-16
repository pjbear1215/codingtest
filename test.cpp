#include <iostream>
#include <vector>
#include <string>
using namespace::std;

int main(void) {
    vector<string> v;
    v.push_back("I");
    v.push_back("am");
    v.push_back("a");
    v.push_back("student");
    v.push_back(".");

    cout << v.front() << endl;
    cout << v.back() << endl;
    
    v.pop_back();
    vector<string>::iterator iter;
    for (iter = v.begin(); iter != v.end(); iter++) {
        if (*iter == "a") {
            cout << *iter << " is erased" << endl;
            v.erase(iter);
            break;
        }        
    }

    for (iter = v.begin(); iter != v.end(); iter++) {
        cout << *iter << endl;
    }

    cout << endl << endl;

    cout << "v.size() = " << v.size() << endl << "v.capacity() = " << v.capacity() << endl;

    return 0;
}
