#include <iostream>
#define MAX 10000

int add[MAX << 2], sum[MAX << 2], num[MAX];

int build(int l, int r, int rt)
{
	if (r == l)
		return sum[rt] = num[l];
	int m = (r + l) >> 1;
	return sum[rt] = build(l, m, rt << 1) + build(m + 1, r, rt << 1 | 1);
}
void update(int L, int C, int l, int r, int rt)				//ÒªÇór<L<l
{
	if (r == l && r == L)
	{
		sum[rt] += C;
		return;
	}
	int m = (r + l) >> 1;
	if (L > m)
	{
		sum[rt] += C;
		update(L, C, m+1, r, rt << 1 | 1);
		return;
	}
	if (L <= m)
	{
		sum[rt] += C;
		update(L, C, l, m, rt << 1);
		return;
	}
}
void update(int L, int R, int C, int l, int r, int rt)
{
	if (r == l)
	{
		sum[rt] += C;
		return;
	}
	if (r <= R && l >= L)
	{
		sum[rt] += C*(r - l + 1);
		add[rt] += C;
		return;
	}
	int m = (r + l) >> 1;
	sum[rt] += C*(L - R + 1);
	if (m >= R)
	{
		update(L, R, C, l, m, rt << 1);
		return;
	}
	if (m <= L)
	{
		update(L, R, C, m, r, rt << 1);
		return;
	}
	if (m > L && m < R)
	{
		update(L, R, C, l, m, rt << 1);
		update(L, R, C, m+1, r, rt << 1);
		return;
	}
}
void pushdown(int l, int r, int rt)
{
	if (!add[rt])
		return;
	if (l == r)
	{
		add[rt] = 0;
		return;
	}
	int m = (r + l) >> 1;
	sum[rt << 1] += add[rt]*(m - r + 1);
	sum[rt << 1|1] += add[rt]*(l - m);
	add[rt << 1] = add[rt << 1 | 1] = add[rt];
	add[rt] = 0;
}
int query(int L, int R, int l, int r, int rt)
{
	if (l <= L && r >= R)
		return sum[rt];
	int m = (r + l) >> 1;
	pushdown(l, r, rt);
	if (m >= R)
		return query(L, R, l, m, rt << 1);
	if (m <= L)
		return query(L, R, m, r, rt << 1);
	if (m > L && m < R)
		return query(L, R, l, m, rt << 1) + query(L, R, m + 1, r, rt << 1);
}
int main()
{
	int i, n;
	std::cin >> n;
	for (i = 1; i <= n; i++)
	{
		std::cin >> num[i];
	}
	build(1, n, 1);
	std::cout << query(3, 5, 1, n, 1) << std::endl;
	update(4,5,1,n,1);
	std::cout << query(3, 5, 1, n, 1) << std::endl;
	update(2, 6, 5, 1, n, 1);
	std::cout << query(3, 5, 1, n, 1) << std::endl;
	return 0;
}