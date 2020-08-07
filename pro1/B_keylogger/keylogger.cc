#include <iostream>
#include <string>
using namespace std;

#define MAX_NR_CASE 5
#define MAX_STRING_LENGTH 1000000

struct node {
    int c;
    node *prev, *next;
    node *insert(int _c, node *_prev, node *_next) {
        c = _c;
		prev = _prev;
        next = _next;
		if (
        return this;
    }
} *head, *tail, *cursor, buf[MAX_STRING_LENGTH];


int bufcnt;

int main()
{
	int nr_case;
	scanf("%d", &nr_case);
	char str[MAX_NR_CASE][MAX_STRING_LENGTH];
	for (int i = 0; i < nr_case; i++) {
		int j = 0;
		scanf("%s", str[i]);
		while (str[j]) {
			char c = str[j++];
			switch (c) {
			case '-':
				break;
			case '<':
				break;
			case '>':
				break;
			default:
				break;
			}
		}
		print_pwd();
	}
}
