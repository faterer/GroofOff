#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

typedef struct node *link;
struct node { int v; link next; };
struct graph { int V; int E; link *adj; };

Edge EDGE(int v, int w)
{	
	Edge E = {v , w};
	return E;
}

Graph GRAPHinit(int V)
{ 
	int v;
	Graph G = malloc(sizeof *G);
	G->V = V; G->E = 0;
	G->adj = malloc(V*sizeof(link));
	for (v = 0; v < V; v++) G->adj[v] = NULL;
	return G;
}


link NEW(int v, link next)
{ 
	link x = malloc(sizeof *x);
	x->v = v; x->next = next;     
	return x;                         
}

void GRAPHinsertE(Graph G, Edge e)
{ 
	int v = e.v, w = e.w;
	G->adj[v] = NEW(w, G->adj[v]);
	G->adj[w] = NEW(v, G->adj[w]); 
	G->E++;
}

int GRAPHedges(Edge a[], Graph G)
{ 
	int v, E = 0; link t;  
	for (v = 0; v < G->V; v++)
		for (t = G->adj[v]; t != NULL; t = t->next)
			if (v < t->v) a[E++] = EDGE(v, t->v); 
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
	int i; 
	printf("%d vertices, %d edges\n", G->V, G->E);
	for (i = 0; i < G->V; i++)
	{
		printf("%2d:", i);
		link curr = ((link)(G->adj[i]));
		while(curr) {
			printf(" %2d", curr->v);
			curr = curr->next;
		}
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
	printf("./graph_adj_list [V] [E]\n");
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