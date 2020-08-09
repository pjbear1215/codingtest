#include <iostream>
#include <string>
using namespace std;

#define MAX 40010


int bufcnt;
int px[MAX], py[MAX];
int x_len, y_len;

int area_max, area_min;
struct node {
	int x0, x1, y0, y1, color;
	node *left, *right;
	node *alloc(int _x0, int _x1, int _y0, int _y1, int _color) {
		x0 = _x0, x1 = _x1, y0 = _y0, y1 = _y1, color = _color;
		left = right = NULL;
		return this;
	}
	void cut(node *root, int px[], int py[], int n, node buf[]) {
		if (n < 0)
			return;
		if (py[n] > y0 && py[n] < y1 && px[n] > x0 && px[n] < x1) {
			if (color == 0) {
				if (left) {
					left->cut(root, px, py, n, buf);
					right->cut(root, px, py, n, buf);
				} else {
					left = buf[bufcnt++].alloc(x0, x1, y0, py[n], 1);
					right = buf[bufcnt++].alloc(x0, x1, py[n], y1, 1);
					root->cut(root, px, py, n-1, buf);
				}
			} else {
				if (left) {
					left->cut(root, px, py, n, buf);
					right->cut(root, px, py, n, buf);
				} else {
					left = buf[bufcnt++].alloc(x0, px[n], y0, y1, 0);
					right = buf[bufcnt++].alloc(px[n], x1, y0, y1, 0);
					root->cut(root, px, py, n-1, buf);
				}
			}
		}
	}
	void get_area(void) {
		int area;
		if (!left) {
			area = (x1 - x0) * (y1 - y0);
			if (area < area_min) area_min = area;
			if (area > area_max) area_max = area;
		} else {
			left->get_area();
			right->get_area();
		}
	}
#if 0
	void traverse(void) {
		cout << x0 << x1 << y0 << y1 << color << endl;
		if (left)
			left->traverse();
		if (right)
			right->traverse();
	}
#endif
} *root, buf[MAX];





int main()
{
	int N;
    scanf("%d %d", &x_len, &y_len);
	scanf("%d", &N);
	area_min = x_len * y_len;
	area_max = 0;
	for (int i = N-1; i >= 0; --i) {
		scanf("%d %d", &px[i], &py[i]);
	}
	root = buf[bufcnt++].alloc(0, x_len, 0, y_len, 0);
	root->cut(root, px, py, N-1, buf);
	//root->traverse();
	root->get_area();
	cout << area_max << " " << area_min << endl;
}
