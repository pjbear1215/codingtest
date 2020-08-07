#include <iostream>
#include <string>
using namespace std;
struct node {
    int val;
    node *next;
    node *alloc(int _val, node *_next) {
        val = _val;
        next = _next;
        return this;
    }
} *head, buf[100];


int cnt, bufcnt;

void push(int val)
{
    head = buf[bufcnt++].alloc(val, head);
    cnt++;
}

void size(void)
{
    cout << cnt << endl;
}

void pop(void)
{
    if (cnt <= 0) {
        cout << "empty\n";
        return;
    }
    cout << head->val << endl;
    head = head->next;
    cnt--;
}

int main()
{
    int N, val;
    char op;
    scanf ("%d", &N);
    while (N--) {
        scanf (" %c", &op);
        switch (op) {
        case 'i':
            scanf (" %d", &val);
            push(val);
            break;
        case 'o':
            pop();
            break;
        case 'c':
            size();
            break;
        default:
            cout << "wrong op\n";
            break;
        }
    }
}
