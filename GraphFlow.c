#include <stdlib.h>
#include "GraphFlow.h"

struct Graph {
	int numNodes;
	int source;
	int sink;
	int *e;
	int *c;
	int *f;
}


// num nodes includes s and t. s is the SOURCE node and t is the SINK node
GraphFlow *newGraph(int numNodes, int source, int sink) {
	int i=0;
	Graph *newGraph = malloc( sizeof( GraphFlow ) );
	
	newGraph->numNode = numNodes;
	newGraph->source = source;
	newGraph->sink = sink;
	newGraph->e = malloc( sizeof(int*) * numNodes );
	newGraph->c = malloc( sizeof(int*) * numNodes );
	newGraph->f = malloc( sizeof(int*) * numNodes );
	
	for(i = 0; i < newGraph; i++) {
		newGraph->e[i] = malloc( sizeof(int) * numNodes );
		newGraph->c[i] = malloc( sizeof(int) * numNodes );
		newGraph->f[i] = malloc( sizeof(int) * numNodes );
	}
	
	cleanEdges(newGraph);
	cleanFlow(newgraph);
	
	return newGraph;
}


void freeGraph(GraphFlow *g ) {
	free( g->c );
	free( g->f );
	free( g );
}


int getNumNodes(GraphFlow *g) {
	return g->numNodes;
}

// private
void cleanEdges(GraphFlow *g) {
	int numNodes = getNumNodes(g);
	int a = 0, b = 0;
	
	for(a = 0; a < numNodes; a++) {
		for(b = 0; b < numNodes; b++) {
			g->e[a][b] = NO_EDGE;
		}
	}
}

// private
void cleanFlow(GraphFlow *g) {
	int numNodes = getNumNodes(g);
	int a = 0, b = 0;
	for(a = 0; a < numNodes; a++) {
		for(b = 0; b < numNodes; b++) {
			g->f[a][b] = 0;
		}
	}
}


int getSource(GraphFlow *g) {
	return g->source;
}

int getSink(GraphFlow *g) {
	return g->sink;
}


// returns 1 if the node is in range, 0 otherwise0
int inRange(GraphFlow *g, int node) {
	return node < g->numNodes && node >= 0;
}

int addEdge(GraphFlow *g, int node1, int node2) {
	if(inRange(g,node1) && inRange(g,node2)) {
		g->e[node1][node2] = EDGE;
	} else {
		return ERROR_RANGE;
	}
	return NO_ERROR;
}

int deletEdge(GraphFlow *g, int node1, int node2) {
	if(inRange(g,node1) && inRange(g,node2)) {
		g->e[node1][node2] = NO_EDGE;
	} else {
		return ERROR_RANGE;
	}
	return NO_ERROR;
}

int getEdge(GraphFlow *g, int node1, int node2) {
	if(!inRange(g,node1) || !inRange(g,node2)) {
		printf("Error range in getEdge of GraphFlow!\n");
		exit(-1);
	}
	
	return g->e[node1][node2];
}


// returns ERROR_RANGE if the node is out of the range of the graph. returns NO_ERROR otherwise
int setCapacity(GraphFlow *g, int node1, int node2, int value) {
	if(inRange(g,node1) && inRange(g,node2)) {
		g->c[node1][node2] = value;
	} else {
		return ERROR_RANGE;
	}
	return NO_ERROR;
}

// no way to let know a error ocorred so it exits the program
int getCapacity(GraphFlow *g, int node1, int node2) {
	if(!inRange(g,node1) || !inRange(g,node2)) {
		printf("Error range in getCapacity of GraphFlow!\n");
		exit(-1);
	}
	
	return g->c[node1][node2];

}

// returns ERROR_RANGE if the node is out of the range of the graph
int setFlow(GraphFlow *g, int node1, int node2, int value) {
	if(inRange(g,node1) && inRange(g,node2)) {
		if( getCapacity(g,node1,node2) >= value
		    && getCapacity(g,node2,node1) >= value )
		{
			g->f[node1][node2] = value;
			g->f[node2][node1] = -value;
		} else {
			return ERROR_CAPACITY;
		}
	} else {
		return ERROR_RANGE;
	}
	return NO_ERROR;
}

// no way to let know a error ocorred so it exits the program
int getFlow(GraphFlow *g, int node1, int node2) {
	if(!inRange(g,node1) || !inRange(g,node2) ) {
		printf("Error range in getFlow of GraphFlow!\n");
		exit(-1);
	}

	return g->f[node1][node2];
}


int flow(GraphFlow *g) {
	int result = 0;
	int node = 0;
	
	for(node = 0; node < getNumNodes(g); node++) {
		result += getFlow(getSource(g),node);
	}
	
	return result;
}

int positiveFlowToNode(GraphFlow *g, int node) {
	int i = 0;
	int result = 0;
	
	if(!inRange(g,node)) {
		printf("Error range in positiveFlowToNode!\n");
		exit(-1);
	}
	
	for(i=0; i < getNumNodes(g); i++) {
		flow = getFlow(g,i,node);
		if(flow > 0)
			result += flow;
	}
	
	return result;
}

int positiveFlowFromNode(GraphFlow *g, int node) {
	int i = 0;
	int result = 0;
	
	if(!inRange(g,node)) {
		printf("Error range in positiveFlowFromNode!\n");
		exit(-1);
	}
	
	for(i=0; i < getNumNodes(g); i++) {
		flow = getFlow(g,i,node);
		if(flow < 0)
			result += -flow;
	}
	
	return result;
}

int flowConservative1(GraphFlow *g) {
	int i = 0;

	for( i =0; i < getNumNodes(g); i++) {
		if( i != getSink(g)
		    && i != getSource(g)
		    && positiveFlowToNode(g,i) != positiveFlowFromNode(g,i) )
		{
		   return FALSE;
		}
	}
	
	return TRUE;
}

int flowConservative2(GraphFlow *g) {
	int i = 0;
	int j = 0;
	
	for( i=0; i < getNumNodes(g); i++) {
		if( i != getSource(g) && i != getSink(g) ) {
			for(j=0, balance =0; j < getNumNodes(g); j++) {
				balance += getFlow(g,i,j);
			}
			if(balance != 0)
				return FALSE;
		}
	}
	
	return TRUE;
}


