///===== user.cpp =====
#ifndef NULL
#define NULL 0
#endif

const int SIZE = 1 << 12;
int bcnt, hcnt, qcnt;
int qchk[50010], blind[10001];

void strcpy(char* dest, char* src) 
{
	while ((*dest++ = *src++));
}

int strcmp(char* s, char* t) {
	while (*s && *s == *t) ++s, ++t;
	return *s - *t;
}

struct data {
	int id;
	data *prev, *next;
	data *myAlloc(int _id, data *_prev, data *_next) {
		id = _id, prev = _prev, next = _next;
		if (prev) prev->next = this;
		if (next) next->prev = this;
		return this;
	}
	void pop() {
		prev->next = next;
		if (next) next->prev = prev;
	}
} buf[220000], *head[10001];

struct STU {
	int cnt, celeb[4];
	data *adr[4];
} stu[50001];

struct HASH {
	int id;
	char name[12];
	HASH *next;
	HASH *myAlloc(int _id, char _name[], HASH *_next) {
		id = _id, strcpy(name, _name), next = _next;
		return this;
	}
} *hash[SIZE], hbuf[10010];

int djb2(char *s) {
	int hash = 5381;
	for (char c; (c = *s++);) {
		hash = ((hash << 5) + hash + c) % SIZE;
	}
	return hash;
}

int search(char* name)
{
	int key = djb2(name);
	for (HASH *p = hash[key]; p; p = p->next) {
		if (strcmp(p->name, name) == 0) return p->id;
	}
	hash[key] = hbuf[hcnt].myAlloc(hcnt, name, hash[key]);
	return hcnt++;
}
 
/// 새로운 설문조사 시작을 위한 초기화
void initUser()
{
	int i;
	bcnt = hcnt = 0;
	for (i = 0; i <= 50000; i++) stu[i].cnt = 0;
	for (i = 0; i < SIZE; i++) hash[i] = 0;
	for (i = 0; i <= 10000; i++) {
		blind[i] = 0;
		head[i] = buf[bcnt++].myAlloc(0,0,0);
	}
}
 
/// 설문조사 결과를 저장
void addSurveyResult(int stdID, int cnt, char celebID[][11])
{
	stu[stdID].cnt = cnt;
	for (int i = 0; i < cnt; i++) {
		int cid = search(celebID[i]);
		stu[stdID].celeb[i] = cid;
		stu[stdID].adr[i] = buf[bcnt++].myAlloc(stdID, head[cid], head[cid]->next);
	}
}
 
/// 설문조사 결과 등록을 취소
void cancelSurveyResult(int stdID)
{
	for (int i = 0; i < stu[stdID].cnt; i++) {
		stu[stdID].adr[i]->pop();
	}
	stu[stdID].cnt = 0;
}
 
/// 특정 유명 인물을 선택한 학생들에 대한 모든 선호도 기록을 제외시키기
/// 예를 들어 7번 학생이 A, B, C를 선호하는데 A인물을 blind한다면
/// 7번 학생이 선호하는 B, C에 대한 기록도 제외된다.
void blindCelebID(char celebID[])
{
	blind[search(celebID)] = 1; 
}
 
/// 특정 유명 인물에 대한 모든 선호도 기록이 제외되어 있다면 다시 복원
void recoverCelebID(char celebID[])
{
	blind[search(celebID)] = 0; 
}

int blind_chk(int id)
{
	for (int i = 0; i < stu[id].cnt; i++) {
		if (blind[stu[id].celeb[i]] == 1) return 1;
	}
	return 0;
}
 
/// 특정인물을 선호하는 학생수를 리턴한다.
/// 단, blind 처리된 인물을 선정하지 않은 학생이 대상이 된다.
/// mode == 0 : 단일 인물을 선호하는 학생 수
/// mode == 1 : 두 인물 모두를 선호하는 학생 수
/// mode == 2 : 둘 중 하나 이상을 선호하는 학생 수
int query(int mode, char celebID[][11])
{
	qcnt++;
	int cnt1 = 0, cnt2 = 0;
	int id = search(celebID[0]);
	if (blind[id] == 0) {
		for (data *p = head[id]->next; p; p = p->next) {
			if (blind_chk(p->id)) continue;
			cnt1++;
			qchk[p->id] = qcnt;
		}
	}
	if (mode == 0) return cnt1;
	id = search(celebID[1]);
	if (blind[id] == 0) {
		for (data* p = head[id]->next; p; p = p->next) {
			if (blind_chk(p->id)) continue;
			cnt1++;
			if (qchk[p->id] == qcnt) cnt2++;
		}
	}
	if (mode == 1) return cnt2;
	return cnt1 - cnt2;
}
