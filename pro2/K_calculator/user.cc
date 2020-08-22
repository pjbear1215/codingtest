///===== user.cpp =====
char stk[3][60], op[3];
int top, len;

void Strcpy(char a[], char b[])
{
	int i;
	for (i = 0; b[i]; i++) {
		a[i] = b[i];
	}
	a[i] = 0;
}

int Strlen(char *a)
{
	int i;
	for (i = 0; a[i]; i++);
	return i;
}

void encode(char *a, int *A)
{
	int len = Strlen(a);
	for (int i = len -1, j = 60; i >= 0; i--, j--) A[j] = a[i] - '0';
}

void decode(int *A, char *a)
{
	int i, j;
	for (i = 60; i > 0; i--) {
		while (A[i] >= 10) A[i] -= 10, A[i-1]++;
		while (A[i] < 0) A[i] += 10, A[i-1]--;
	}
	for (i = 0; i < 60; i++) if (A[i]) break;
	for (j = 0; i <= 60; i++, j++) a[j] = A[i] + '0';
	a[j] = 0;
}

void add(char *a, char *b)
{
	int A[65] = {0}, B[65] = {0};
	encode(a, A), encode(b, B);
	for (int i = 60; i > 0; i--) A[i] += B[i];
	decode(A, a);
}

void sub(char *a, char *b)
{
	int A[65] = {0}, B[65] = {0};
	encode(a, A), encode(b, B);
	for (int i = 60; i > 0; i--) A[i] -= B[i];
	decode(A, a);
}

void multi(char *a, char *b)
{
	int A[65] = {0}, B[65] = {0}, C[65] = {0};
	encode(a, A), encode(b, B);
	for (int i = 0; i <= 60; i++) {
		for (int j = 60 - i; j <= 60; j++) {
			C[i + j - 60] += A[i] * B[j];
		}
	}
	decode(C, a);
}

int minus(int *A, int *B, int an, int bn)
{
	for (int i = an - bn, j = 0; i <= an; i++, j++) {
		if (A[i] < B[j]) return 0;
		if (A[i] > B[j]) break;
	}
	for (int i = an, j = bn; j > 0; i--, j--) {
		A[i] -= B[j];
		if (A[i] < 0) A[i] += 10, A[i - 1]--;
	}
	return 1;
}

void div(char *a, char *b)
{
	int A[65] = {0}, B[65] = {0}, C[65] = {0};
	encode(a, A);
	int bn = Strlen(b);
	for (int i = 0; i < bn; i++) B[i+1] = b[i] - '0';
	for (int i = bn; i <= 60; i++) {
		while (minus(A, B, i, bn)) C[i]++;
	}
	decode(C, a);
}

int order(char a, char b)
{
	if (a == '=' || a == '+' || a == '-') return 1;
	if (b == '*' || b == '/') return 1;
	return 0;
}

void Cal(char ch, char* user)
{
	if (ch == 'C') {
		top = len = 0;
		user[0] = '0', user[1] = 0;
		return ;
	}
	if (ch >= '0' && ch <= '9') {
		stk[top][len++] = ch;
		stk[top][len] = 0;
		Strcpy(user, stk[top]);
		return;
	}
	while (top && order(ch, op[top - 1])) {
		top--;
		if (op[top] == '+') add(stk[top], stk[top + 1]);
		else if (op[top] == '-') sub(stk[top], stk[top + 1]);
		else if (op[top] == '*') multi(stk[top], stk[top + 1]);
		else div(stk[top], stk[top + 1]);
	}
	Strcpy(user, stk[top]);
	if (ch != '=') op[top++] = ch, len = 0;
}
