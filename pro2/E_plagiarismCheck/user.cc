/// ===== user.cpp  =====
#ifndef NULL
#define NULL 0
#endif 

const int SIZE = (1 << 21);
const int MOD = SIZE - 1;

int N, bcnt, data[10010][210];

struct Hash {
	int id, pos;
	Hash *next;
	Hash* myAlloc(int _id, int _pos, Hash* _next) {
		id = _id, pos = _pos, next = _next;
		return this;
	}
} buf[1 << 21], *hash[SIZE];
 
void initUser(int soundNum){
	N = soundNum;
	bcnt = 0;
	for (int i = 0; i < SIZE; i++) hash[i] = 0;
}

int bit7(int a) {
	return (a >> 8) & ((1 << 7) - 1);
}

int key_cal(int a, int b, int c) {
	return (bit7(a) << 14) + (bit7(b) << 7) + bit7(c);
}
 
void registerSound(int ID, int Len, int Arr[200]){
	for (int i = 0; i < Len; i++) {
		data[ID][i] = Arr[i];
	}
	for (int i = 0; i <= Len - 8; i++) {
		int key = key_cal(Arr[i], Arr[i+1], Arr[i+2]);
		hash[key] = buf[bcnt++].myAlloc(ID, i, hash[key]);
	}
}

int limit[3][8] = {{-127, -127, -127, -127, 128, 128, 128, 128},
					{-127, -127, 128, 128, -127, -127, 128, 128},
					{-127, 128, -127, 128, -127, 128, -127, 128}};

int chk(int a[], int b[]) {
	for (int i = 0; i < 8; i++) {
		if (a[i] - 128 > b[i] || a[i] + 127 < b[i]) return 0;
	}
	return 1;
}
 
int  plagiarismCheck(int Data[8])
{
	for (int i = 0; i < 8; i++) {
		int key = key_cal(Data[0] + limit[0][i], Data[1] + limit[1][i], Data[2] + limit[2][i]);
		for (Hash* p = hash[key]; p; p = p->next) {
			if (chk(data[p->id] + p->pos, Data)) return p->id;
		}
	}
	return 0;
}
