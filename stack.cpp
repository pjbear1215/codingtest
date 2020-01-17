#include <iostream>
#include <stack>
#include <string>

using namespace::std;

void showstack(stack <int> s) {
    while (!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }
    cout << "stack is empty" << endl;
}

int main(void) {
    stack <int> s;
    showstack(s);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    showstack(s);
    
}