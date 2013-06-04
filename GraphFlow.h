#ifndef __GRAPH_FLOW_H__
#define __GRAPH_FLOW_H__

#define NO_ERROR 0
#define ERROR_RANGE -1
#define ERROR_CAPACITY -2

typedef struct Graph Graph;

GraphFlow *newGraph(int numNodes);

void freeGraph(GraphFlow *g );


int getNumNodes(GraphFlow *g);
int getSource(GraphFlow *g);
int getSink(GraphFlow *g);


// returns 1 if the node is in range, 0 otherwise.
int inRange(GraphFlow *g, int node);

int addEdge(GraphFlow *g, int node1, int node2);

int deletEdge(GraphFlow *g, int node1, int node2);

int getEdge(GraphFlow *g, int node1, int node2);


// returns ERROR_RANGE if the node is out of the range of the graph. returns NO_ERROR otherwise
int setCapacity(GraphFlow *g, int node1, int node2, int value) ;

// no way to let know a error ocorred so it exits the program
int getCapacity(GraphFlow *g, int node1, int node2);

// returns ERROR_RANGE if the node is out of the range of the graph
int setFlow(GraphFlow *g, int node1, int node2, int value);

// no way to let know a error ocorred so it exits the program
int getFlow(GraphFlow *g, int node1, int node2);

int flow(GraphFlow *g);

int positiveFlowToNode(GraphFlow *g, int node);

int positiveFlowFromNode(GraphFlow *g, int node);


// uses positiveFlow functions
int flowConservative1(GraphFlow *g);

int flowConservative2(GraphFlow *g);


#endif
