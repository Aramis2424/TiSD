#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "defines.h"
#include "errors.h"
#include "functions.h"
#include "processing.h"
#include "string.h"

int find_elem(int arr[], int len, int num);
int max(int x1, int x2);

void dfs(node_t *node, node_t gra[], int dp[], int vis[], int *lenv, int n, int way[], int m)
{
    vis[*lenv] = node->num;  //посещенные вершины
    *lenv += 1;
    way[m++] = node->num;

    node_t *cur = node->next;
    while (cur)
    {
        if (!find_elem(vis, n, cur->num) && cur->num != node->num)
            dfs(cur, gra, dp, vis, lenv, n, way, m);
        dp[node->num] = max(dp[node->num], cur->num + 1);
        cur = cur->next;
    }
}

int mаx_wаy(node_t gra[], int n, int way[], int *lenw)
{
    int maxlen[n];
    memset(maxlen, 0, sizeof(maxlen));

    int vis[n];
    int lenv = 0;
    memset(vis, 0, sizeof(vis));

    for (int i = 0; i < n; i++)
        if (!vis[i])
            dfs(&gra[i], gra, maxlen, vis, &lenv, n, way, *lenw);

    int ans = 0;

    for (int i = 1; i <= n; i++)
        ans = max(ans, maxlen[i]);

    return ans;

}

int find_elem(int arr[], int len, int num)
{
    for (int j = 0; j < len; j++)
        if (arr[j] == num)
            return TRUE;

    return FALSE;
}

int max(int x1, int x2)
{
    return x1 > x2 ? x1 : x2;
}
























int DFS(int matr[][MAX_N], int n, int num, int *vis, int *vislen, int *lenway, int *path_cur, int *path_cur_len)
{
    int now_len;

    for (int i=0; i < n; i++)
        if (matr[num][i] == 1 && num != i)
        {
            now_len = lenway[num]+1;
            if (now_len > lenway[i])
            {
                lenway[i] = now_len;
                if (find_elem(vis, *vislen, i) == 0)
                {
                    vis[(*vislen)++] = i;
                    DFS(matr, n, i, vis, vislen, lenway, path_cur, path_cur_len);
                }
            }
        }

    if (*path_cur_len < *vislen)
    {
        *path_cur_len = *vislen;
        for (int i=0; i < *path_cur_len; i++)
            path_cur[i] = vis[i];
    }

    (*vislen)--;

    return 0;
}

int max_way(int matr[][MAX_N], int n, int max_path[], int *max_len)
{
    int lenway[n];
    int vis[n], vislen;

    int *path_cur = malloc(n*sizeof(int));
    int path_cur_len;
    if (path_cur == NULL)
        return -1;

    for (int i=0; i < n; i++)
    {
        vislen = 0;
        path_cur_len = 0;

        if (find_elem(path_cur, path_cur_len, i) == 0)
        {

            for (int j=0; j < n; j++)
                lenway[j] = 0;
            vis[vislen++] = i;

            DFS(matr, n, i, vis, &vislen, lenway, path_cur, &path_cur_len);
        }

        if (path_cur_len > *max_len)
        {
            *max_len = path_cur_len;
            for (int i=0; i < *max_len; i++)
                max_path[i] = path_cur[i];
        }
    }

    free(path_cur);
    return 0;
}
