#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int result;

typedef struct NODE{
    int n;
    struct NODE* next;
}NODE;
NODE pool[200003];
NODE head[100003];
int pool_size;
int list[100003];

void add_node(int idx, int n)
{
    pool[pool_size].n = n;
    pool[pool_size].next = head[idx].next;
    head[idx].next = &pool[pool_size];
    pool_size++;
    list[idx]++;
}

void del_node(int idx)
{
    // 켜질 등대로 선택된 노드 주변 노드 연결 해제
    NODE* lh_ptr = &head[idx];
    while(lh_ptr->next)
    {
        lh_ptr = lh_ptr->next;    
        
        // 삭제할 길이 있으면 길 개수 1씩 감소
        if(list[idx] > 0)
            list[idx]--;
        
        // 켜질 등대와 이어진 노드번호
        int near_node = lh_ptr->n;
        
        NODE* ptr = &head[near_node];
        NODE* prev_ptr = ptr;
        
        if(list[near_node] > 0)
            list[near_node]--;
        
        // 켜질 등대와 이어진 길 삭제
        while(ptr->next)
        {
            ptr = ptr->next;
            if(ptr->n == idx)
            {
                prev_ptr->next = ptr->next;
                break;
            }
            prev_ptr = ptr;
        }
    }
    
    head[idx].next = NULL;
}

// lighthouse_rows는 2차원 배열 lighthouse의 행 길이, lighthouse_cols는 2차원 배열 lighthouse의 열 길이입니다.
int solution(int n, int** lighthouse, size_t lighthouse_rows, size_t lighthouse_cols) {
    
    for(int i=0;i<n-1;i++)
    {
        add_node(lighthouse[i][0], lighthouse[i][1]);
        add_node(lighthouse[i][1], lighthouse[i][0]);
    }
    
    while(1)
    {
        int cnt = 0;
        for(int i=1;i<=n;i++)
        {
            if(list[i] == 1)
            {
                cnt++;
                int next_idx = (head[i].next)->n;
                result++;
                del_node(next_idx);
            }
        }
        if(cnt == 0)
            break;
    }
    
    /*for(int i=1;i<=n;i++)
    {
        NODE* ptr = &head[i];
        
        printf("%d : ", i);
        
        while(ptr->next)
        {
            ptr = ptr->next;
            printf("%d ", ptr->n);
        }
        
        printf("\n");
    }*/
    
    return result;
}