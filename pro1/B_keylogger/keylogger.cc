#include <iostream>
#include <string>
using namespace std;

#define MAX_STRING_LENGTH 1000010

struct node {
    char c;
    node *prev, *next;
    void insert(char _c, node *_prev, node *_next) {
        c = _c, prev = _prev, next = _next;
		prev->next = next->prev = this;
    }
	void remove(void) {
		prev->next = next;
		next->prev = prev;
	}
} *head, *tail, *cursor, buf[MAX_STRING_LENGTH];



int bufcnt;

void insert(char c)
{
	buf[bufcnt++].insert(c, cursor->prev, cursor);
}

void backspace(void)
{
	if (cursor->prev != head) {
		cursor->prev->remove();
	}
}

void move_left(void)
{
	if (cursor->prev != head)
		cursor = cursor->prev;
}

void move_right(void)
{
	if (cursor != tail)
		cursor = cursor->next;
}

void init(void)
{
	bufcnt = 2;
	head->next = tail;
	tail->prev = head;
	cursor = tail;
}

void print_pwd(void)
{
	for (node* p = head->next; p != tail; p = p->next) {
		cout << p->c;
	}
	cout << endl;
}

int main()
{
	int nr_case;
	scanf("%d", &nr_case);
	head = &buf[0];
	tail = &buf[1];
	while (nr_case--) {
		char str[MAX_STRING_LENGTH];
		init();
		int j = 0;
		scanf("%s", str);
		while (str[j]) {
			char c = str[j++];
			switch (c) {
			case '-':
				backspace();
				break;
			case '<':
				move_left();
				break;
			case '>':
				move_right();
				break;
			default:
				insert(c);
				break;
			}
		}
		print_pwd();
	}
}
