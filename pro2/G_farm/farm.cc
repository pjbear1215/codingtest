#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
 
#include <stdio.h>
#include <string.h>
 
#define INIT       0
#define SETFARM    1
#define GETCROP    2
#define MERGECELL  3
#define CNTCELL    4
#define CNTAREA    5
 
extern void init(int Row, int Col);
extern void setFarm(int row, int col, char crop[]);
extern void getCrop(int row, int col, char crop[]);
extern void mergeCell(int row1, int col1, int row2, int col2, int sw);
extern int cntCell(char crop[]);
extern int cntArea(char crop[]);


typedef long long LL;

const int SIZE = (1 << 15);
const int MOD = SIZE - 1;

struct Cell {
	int root;
	int mr, mc;
	int crop, area;
} cell[151][151];

struct Crop {
	char name[11];
	int cell_cnt; // cel count
	int area_size; // area size
} cropdata[SIZE];
 
struct Hash {
	int id;
	LL cropnum;
	Hash *next;
	Hash *alloc(int _id, LL _cropnum, Hash *_next) {
		id = _id, cropnum = _cropnum, next = _next;
		return this;
	}
} buf[SIZE], *hash[SIZE];

int bcnt, cropcnt;

void strcpy(char *a, char *b) {
	int i;
	for (i = 0; b[i]; i++) a[i] = b[i];
	a[i] = 0;
}

void init(int Row, int Col)
{
	bcnt = cropcnt = 0;
	for (int i = 0; i < SIZE; i++) {
		hash[i] = 0;
		cropdata[i].area_size = cropdata[i].cell_cnt = 0;
	}
	for (int i = 1; i <= Row; i++) {
		for (int j = 1; j <= Col; j++) {
			cell[i][j].mr = i, cell[i][j].mc = j;
			cell[i][j].crop = 0, cell[i][j].root = cell[i][j].area = 1;
		}
	}
}

int crop_calc(char str[])
{
	LL cropnum = 0L;
	for (int i = 0; str[i]; i++) cropnum = (cropnum << 5) + str[i] - 96;
	int key = (cropnum & MOD);
	for (Hash* p = hash[key]; p; p = p->next) {
		if (p->cropnum == cropnum) return p->id;
	}
	cropcnt++;
	hash[key] = buf[bcnt++].alloc(cropcnt, cropnum, hash[key]);
	strcpy(cropdata[cropcnt].name, str);
	return cropcnt;
}

void findroot(int& row, int& col)
{
	int r, c;
	while (!cell[row][col].root) {
		r = cell[row][col].mr, c = cell[row][col].mc;
		row = r, col = c;
	}
}

void setFarm(int row, int col, char crop[])
{
	findroot(row, col);
	int cropid = cell[row][col].crop;
	cropdata[cropid].cell_cnt--;
	cropdata[cropid].area_size -= cell[row][col].area;
	cropid = crop_calc(crop);
	cell[row][col].crop = cropid;
	cropdata[cropid].cell_cnt++;
	cropdata[cropid].area_size += cell[row][col].area;
}

void getCrop(int row, int col, char crop[])
{
	findroot(row, col);
	strcpy(crop, cropdata[cell[row][col].crop].name);
}

int cntCell(char crop[])
{
	int cropid = crop_calc(crop);
	return cropdata[cropid].cell_cnt;
}

int cntArea(char crop[])
{
	int cropid = crop_calc(crop);
	return cropdata[cropid].area_size;
}

void swap(int &x, int &y) { int z = x; x = y; y = z;}

void mergeCell(int row1, int col1, int row2, int col2, int sw)
{
	if (sw == 2) swap(col1, col2), swap(row1, row2);
	findroot(row1, col1);
	findroot(row2, col2);
	Cell *a = &cell[row1][col1], *b = &cell[row2][col2];
	a->area += b->area;
	b->root = 0, b->mr = row1, b->mc = col1;
	cropdata[b->crop].cell_cnt--;
	cropdata[b->crop].area_size -= b->area;
	cropdata[a->crop].area_size += b->area;
}

static int run()
{
    int score = 100;
    int N, cmd, row1, col1, row2, col2, op, usercnt;
    char str[12], user[12];
 
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &cmd);
        switch (cmd) {
        case INIT:
            scanf("%d %d", &row1, &col1);
            init(row1, col1);
            break;
        case SETFARM:
            scanf("%d %d %s", &row1, &col1, str);
            setFarm(row1, col1, str);
            break;
        case GETCROP:
            scanf("%d %d %s", &row1, &col1, str);
            getCrop(row1, col1, user);
            if (str[0] == 'N') str[0] = '\0';
            if (strcmp(str, user) != 0) score = 0;
            break;
        case MERGECELL:
            scanf("%d %d %d %d %d", &row1, &col1, &row2, &col2, &op);
            mergeCell(row1, col1, row2, col2, op);
            break;
        case CNTCELL:
            scanf("%d %s", &op, str);
            usercnt = cntCell(str);
            if (usercnt != op) score = 0;
            break;
        case CNTAREA:
            scanf("%d %s", &op, str);
            usercnt = cntArea(str);
            if (usercnt != op) score = 0;
            break;
        default:
            break;
        }
    }
 
    return score;
}
 
int main()
{
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);
 
    int T;
    scanf("%d", &T);
 
    for (int tc = 1; tc <= T; tc++) {
        printf("#%d %d\n", tc, run());
    }
 
    return 0;
} 

