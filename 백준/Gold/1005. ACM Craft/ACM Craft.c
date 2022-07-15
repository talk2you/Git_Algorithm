#include <stdio.h>
#include <stdlib.h>

typedef unsigned int    uint16;
typedef unsigned long   uint32;
typedef struct node
{
    int v;
    struct node* next;
} NODE;

// N = uint16
// K = uint32

uint16 T,N;
uint32 K;

uint32 time[1001];
uint32 tmp_t[1001] = {0,};
uint16 cnt[1001];
uint16 goal;
uint16 sum;

NODE** graph;
NODE* que;

void mk_que()
{
    que = (NODE*)malloc(sizeof(NODE));
    que->next = NULL;
    que->v = -1;
}
void insert(NODE* parent, uint16 val)
{
    NODE* temp;
    temp = (NODE*)malloc(sizeof(NODE));
    temp->v = val;
    temp->next = NULL;

    if(parent->next != NULL)
        temp->next = parent->next;

    parent->next = temp;
}

uint16 pull(NODE* ptr_node)
{
    NODE* pre_node;
    uint16 val;

    if(ptr_node->next == NULL)
        return ptr_node->v;

    while(ptr_node->next  != NULL)
    {
        pre_node = ptr_node;
        ptr_node = ptr_node->next;
    }

    pre_node->next = NULL;
    val = ptr_node->v;
        free(ptr_node);
    return val;
}


uint32 max(uint16 x, uint16 y)
{
    return x >= y ? x : y;
}

uint32 search_go(void)
{
    NODE* temp;
    uint16 pop,i;

    mk_que();

    for(i=0;i<N;i++)
    {
        if(cnt[i] == 0)
        {
            insert(que,i);
            tmp_t[i] = time[i];
        }
    }

    while(que->next != NULL)
    {
        pop = pull(que);

        if(pop == goal-1)
            return tmp_t[pop];

        for(temp = graph[pop]->next;temp != NULL;temp=temp->next)
        {
            cnt[temp->v] -= 1;
            tmp_t[temp->v] = max(tmp_t[temp->v],tmp_t[pop]+time[temp->v]);

            if(cnt[temp->v] == 0)
            {
                cnt[temp->v] -=1;
                insert(que,temp->v);
            }
        }
    }
}

int main(void)
{
    uint32 j;
    uint16 i;
    uint16 in,out;

    scanf("%d",&T);

    while(T--)
    {
        sum = 0;
        scanf("%d %ld",&N, &K);

        graph = (NODE**)malloc(sizeof(NODE*)*N);

        for(i=0;i<N;i++)
        {
            time[i] = 0;
            tmp_t[i] = 0;
            cnt[i] = 0;
            graph[i] = (NODE*)malloc(sizeof(NODE));
            graph[i]->v = -1;
            graph[i]->next = NULL;
            scanf("%ld",&time[i]);
            sum += time[i];
        }
        for(j=0;j<K;j++)
        {
            scanf("%d %d",&in,&out);
            insert(graph[in-1],out-1);
            cnt[out-1] += 1;
        }
        scanf("%d",&goal);

        if(sum != 0) printf("%ld\n",search_go());
        else printf("0\n");
    }
    return 0;
}
