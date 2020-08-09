#include <iostream>
#include <string>
using namespace std;

#define MAX 40010
enum color {
	WHITE,
	BLACK
};

int px[MAX], py[MAX];
int x_len, y_len;

int area_max, area_min;

int get_area(int x0, int x1, int y0, int y1)
{
	return (x1 - x0) * (y1 - y0);
}

int cut_max(int color, int x0, int x1, int y0, int y1, int n)
{
	if (n < 0) {
		return get_area(x0, x1, y0, y1);
	}
	if (px[n] < x0 || px[n] > x1 || py[n] < y0 || py[n] > y1) {// out of range
		return cut_max(color, x0, x1, y0, y1, n-1);
	}

	int area[2];

	if (color == WHITE) {
		area[0] = cut_max(BLACK, x0, x1, y0, py[n], n-1);
		area[1] = cut_max(BLACK, x0, x1, py[n], y1, n-1);
	} else {
		area[0] = cut_max(WHITE, x0, px[n], y0, y1, n-1);
		area[1] = cut_max(WHITE, px[n], x1, y0, y1, n-1);
	}
	if (area[0] < area[1]) {
		return area[1];
	} else {
		return area[0];
	}
}
int cut_min(int color, int x0, int x1, int y0, int y1, int n)
{
	if (n < 0) {
		return get_area(x0, x1, y0, y1);
	}
	if (px[n] < x0 || px[n] > x1 || py[n] < y0 || py[n] > y1) {// out of range
		return cut_min(color, x0, x1, y0, y1, n-1);
	}

	int area[2];

	if (color == WHITE) {
		area[0] = cut_min(BLACK, x0, x1, y0, py[n], n-1);
		area[1] = cut_min(BLACK, x0, x1, py[n], y1, n-1);
	} else {
		area[0] = cut_min(WHITE, x0, px[n], y0, y1, n-1);
		area[1] = cut_min(WHITE, px[n], x1, y0, y1, n-1);
	}
	if (area[0] || area[1]) {
		if (area[0] < area[1]) {
			if (area[0]) return area[0];
			else return area[1];
		} else {
			if (area[1]) return area[1];
			else return area[0];
		}
	}
	return 40000*40000;
}

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
	area_max = cut_max(WHITE, 0, x_len, 0, y_len, N-1);
	area_min = cut_min(WHITE, 0, x_len, 0, y_len, N-1);
	cout << area_max << " " << area_min << endl;
}
