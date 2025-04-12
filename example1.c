#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int v;
    int *vis;
    NODE **alst;
} GPH;

typedef struct Stack {
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v) {
    NODE *nn = (NODE *)malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

GPH *create_g(int v) {
    GPH *g = (GPH *)malloc(sizeof(GPH));
    g->v = v;
    g->alst = (NODE **)malloc(sizeof(NODE *) * v);
    g->vis = (int *)malloc(sizeof(int) * v);

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

STK *create_s(int scap) {
    STK *s = (STK *)malloc(sizeof(STK));
    s->arr = (int *)malloc(sizeof(int) * scap);
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int val, STK *s) {
    if (s->t < s->scap - 1) {
        s->t++;
        s->arr[s->t] = val;
    }
}

void wipe(GPH *g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

void DFS(GPH *g, STK *s, int v_nr) {
    g->vis[v_nr] = 1;
    push(v_nr, s);

    NODE *aux = g->alst[v_nr];
    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0) {
            DFS(g, s, con_ver);
        }
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest;
    printf("Adauga %d muchii (de la 0 la %d):\n", edg_nr, nrv - 1);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}

int can_be_reached(GPH *g, int src, int dest, int nrv) {
    STK *s = create_s(nrv * 2);
    DFS(g, s, src);
    for (int i = 0; i <= s->t; i++) {
        if (s->arr[i] == dest) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int nrv, edg_nr;
    int src, dest;

    printf("Cate noduri are reteaua de restaurante? ");
    scanf("%d", &nrv);

    printf("Cate muchii are reteaua? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    insert_edges(g, edg_nr, nrv);

    printf("Verifica daca exista drum intre (introdu 2 noduri): ");
    scanf("%d %d", &src, &dest);

    wipe(g, nrv);
    if (can_be_reached(g, src, dest, nrv)) {
        printf("Exista drum intre %d si %d\n", src, dest);
    } else {
        printf("NU exista drum intre %d si %d\n", src, dest);
    }

    return 0;
}
