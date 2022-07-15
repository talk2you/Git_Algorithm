#include <stdio.h>
#include <string.h>

#define Min(a, b) ((a<b)?(a):(b))

int N;

typedef struct TREE{
	union {
		struct {
			int x, y, len, idx;
		};
		int data[4];
	};
}TREE;
TREE tree[50];
TREE lensort[50];
TREE xsort[50];
TREE ysort[50];
int cut_tree[50];
int ans = 99;

int in_list[50];
int in_size;

// 나무 크기순으로 저장될 우선순위 큐 
int push(int _list[50], int *_size, int len)
{
	int temp;

	if (*_size >= 50)
		return 0;

	++(*_size);
	_list[*_size] = len;

	for (int i = *_size; i > 1; i /= 2)
	{
		if (_list[i / 2] > _list[i])
			break;

		temp = _list[i / 2];
		_list[i / 2] = _list[i];
		_list[i] = temp;
	}

	return 1;
}

int pop(int _list[50], int *_size, int *len)
{
	int temp;

	if (*_size == 0)
		return 0;

	*len = _list[1];
	_list[1] = _list[*_size];
	_list[(*_size)--] = -1;

	for (int i = 1; i*2 <= *_size;)
	{
		if (_list[i] > _list[i*2] && _list[i] > _list[i * 2 + 1])
			break;
		else if (_list[i * 2] > _list[i * 2 + 1])
		{
			temp = _list[i * 2];
			_list[i * 2] = _list[i];
			_list[i] = temp;
			i = i * 2;
		}
		else
		{
			temp = _list[i * 2 + 1];
			_list[i * 2 + 1] = _list[i];
			_list[i] = temp;
			i = i * 2 + 1;
		}
	}

	return 1;
}

// 합병 정렬
void merge(TREE dst_sort[50], int idx, int start, int end)
{
	int mid = (start + end) >> 1;
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (tree[i].data[idx] < tree[j].data[idx])
			memcpy(&dst_sort[k++], &tree[i++], sizeof(TREE));
		else
			memcpy(&dst_sort[k++], &tree[j++], sizeof(TREE));
	}
	
	while(i<=mid)
		memcpy(&dst_sort[k++], &tree[i++], sizeof(TREE));
	while(j<=end)
		memcpy(&dst_sort[k++], &tree[j++], sizeof(TREE));

	for(int i=start;i<=end;i++)
		memcpy(&tree[i], &dst_sort[i-start], sizeof(TREE));
}

void sort(TREE dst_sort[50], int idx, int start, int end)
{
	int mid = (start + end) >> 1;
	if (start >= end)
		return;

	sort(dst_sort, idx, start, mid);
	sort(dst_sort, idx, mid + 1, end);
	merge(dst_sort, idx, start, end);
}

void input()
{
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d %d", &tree[i].x, &tree[i].y, &tree[i].len);
		tree[i].idx = i;
	}

	// x, y 합병정렬
	if (N > 1)
	{
		sort(xsort, 0, 0, N - 1);
		sort(ysort, 1, 0, N - 1);
	}
	else
	{
		memcpy(&xsort[0], &tree[0], sizeof(TREE));
		memcpy(&ysort[0], &tree[0], sizeof(TREE));
	}
}

void solve()
{
	int xmin, xmax, ymin, ymax, need;
	int ntree = 0, outsum = 0, insum = 0;

	// O(N^4), 최적화 하면 O(N^3)으로 끝낼수 있음.
	for (int a = 0; a < N; a++)
	{
		for (int b = a; b < N; b++)
		{
			for (int c = 0; c < N; c++)
			{
				for (int d = c; d < N; d++)
				{
					ntree = 0, outsum = 0, insum = 0;
					// 정원의 범위를 구해주고, 울타리 개수 계산
					xmin = xsort[a].x, xmax = xsort[b].x;
					ymin = ysort[c].y, ymax = ysort[d].y;					
					need = 2 * ((xmax - xmin) + (ymax - ymin));									

					// 나무들을 돌면서 내부는 크기순으로 저장
					// 외부에 있는 나무는 울타리가 되면서 카운트 증가
					for (int i = 0; i < N; i++)
					{
						if (xmin <= tree[i].x && tree[i].x <= xmax && ymin <= tree[i].y && tree[i].y <= ymax)
						{
							ntree++;
							push(in_list, &in_size, tree[i].len);
							insum += tree[i].len;
						}
						else
							outsum += tree[i].len;
					}

					// 이 상태에서 울타리 만들수 있으면 결과값 갱신
					if (outsum >= need)
						ans = Min(ans, N - ntree);		
					else
					{
						// 내부에 있는 나무도 울타리가 되는 조건을 찾는다
						if (outsum + insum >= need)
						{
							int temp_size = in_size;
							for (int i = 0; i < temp_size; i++)
							{
								ntree--;
								int in_len;
								// 저장된 내부 나무정보들을 크기가 큰 순으로 하나씩 꺼내서 저장
								pop(in_list, &in_size, &in_len);
								outsum += in_len;
								
								if (outsum >= need)
								{
									ans = Min(ans, N - ntree);
									break;
								}
							}
						}
					}
					// 큐 비우기
					int dummy;
					while (pop(in_list, &in_size, &dummy));
				}
			}
		}
	}

	printf("%d\n", ans);
}

int main(void)
{
	input();
	solve();
    
    return 0;
}