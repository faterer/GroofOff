#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct graph { int V; int E; int **adj; };

Edge EDGE(int v, int w)
{	
	Edge E = {v , w};
	return E;
}

int **MATRIXint(int r, int c, int val)
{ 
	int i, j;
	int **t = malloc(r * sizeof(int *));
	for (i = 0; i < r; i++)
		t[i] = malloc(c * sizeof(int));
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			t[i][j] = val;
	return t;
}


Graph GRAPHinit(int V)
{ 
	Graph G = malloc(sizeof *G);
	G->V = V; G->E = 0;
	G->adj = MATRIXint(V, V, 0);
	return G;
}

void GRAPHinsertE(Graph G, Edge e)
{ 
	int v = e.v, w = e.w;
	if (G->adj[v][w] == 0) G->E++;
	G->adj[v][w] = 1; 
	G->adj[w][v] = 1;
}

void GRAPHremoveE(Graph G, Edge e)
{ 
	int v = e.v, w = e.w;
	if (G->adj[v][w] == 1) G->E--;
	G->adj[v][w] = 0; 
	G->adj[w][v] = 0;
}

int GRAPHedges(Edge a[], Graph G)
{ 
	int v, w, E = 0;
	for (v = 0; v < G->V; v++)
		for (w = v+1; w < G->V; w++)
			if (G->adj[v][w] == 1) 
				a[E++] = EDGE(v, w); 
	return E;
}

Graph GRAPHrand(int V, int E)
  { int i, j;
    double p = 2.0*E/V/(V-1);
    Graph G = GRAPHinit(V);
    for (i = 0; i < V; i++)
      for (j = 0; j < i; j++)
        if (rand() < p*RAND_MAX)
          GRAPHinsertE(G, EDGE(i, j));
    return G;
  }

void GRAPHshow(Graph G)
{ 
	int i, j; 
	printf("%d vertices, %d edges\n", G->V, G->E);
	for (i = 0; i < G->V; i++)
	{
		printf("%2d:", i);
		for (j = 0; j < G->V; j++)
		if (G->adj[i][j] == 1) printf(" %2d", j);
		printf("\n");
	}
}

// int GRAPHcc(Graph G)
// { 
// 	int v, id = 0;
// 	G->cc = malloc(G->V * sizeof(int));
// 	for (v = 0; v < G->V; v++) 
// 	G->cc[v] = -1;
// 	for (v = 0; v < G->V; v++)
// 	if (G->cc[v] == -1) dfsRcc(G, v, id++);
// 	return id;
// }

void GRAPHHelp()
{
	printf("./graph [V] [E]\n");
}

int main(int argc, char *argv[])
{ 
	if (argv[1] == NULL || argv[2] == NULL) {
		GRAPHHelp();
		return 0;
	}

	int V = atoi(argv[1]), E = atoi(argv[2]);

	Graph G = GRAPHrand(V, E);
	if (V < 20) 
	     GRAPHshow(G);
	else printf("%d vertices, %d edges, ", V, E);
	// printf("%d component(s)\n", GRAPHcc(G));
	return 0;
}