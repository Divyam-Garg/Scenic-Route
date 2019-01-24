/* Solution to comp10002 Assignment 2, 2018 semester 2.

   Authorship Declaration:

   (1) I certify that the program contained in this submission is completely
   my own individual work, except where explicitly noted by comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students,
   or by non-students as a result of request, solicitation, or payment,
   may not be submitted for assessment in this subject.  I understand that
   submitting for assessment work developed by or in collaboration with
   other students or non-students constitutes Academic Misconduct, and
   may be penalized by mark deductions, or by other penalties determined
   via the University of Melbourne Academic Honesty Policy, as described
   at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will
   I do so until after the marks are released. I understand that providing
   my work to other students, regardless of my intention or any undertakings
   made to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring
   service, or drawing the attention of others to such services and code
   that may have been made available via such a service, may be regarded
   as Student General Misconduct (interfering with the teaching activities
   of the University and/or inciting others to commit Academic Misconduct).
   I understand that an allegation of Student General Misconduct may arise
   regardless of whether or not I personally make use of such solutions
   or sought benefit from such actions.

   Signed by: Divyam Garg - 976443
   Dated:     [FILL THIS IN!!!!!!!!!!!!!!!!!!!]

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

/* Constants -----------------------------------------------------------------*/

#define SECOND_ARG 1
#define FIRST_CHAR 0
#define MAX_NO_VERTEX 52
#define NO_ALPHABETS 26
#define TRUE 1
#define FALSE 0
#define TRAVERSABLE_ODD_DEGREE 2

/* type definitions ----------------------------------------------------------*/

typedef struct {
	char vertex;
	int edge_wt;
	int walked;
} data_t;

typedef struct node node_t;

struct node {
	data_t data;
	node_t *next;
};

typedef struct {
	node_t *head;
	node_t *foot;
} list_t;

typedef struct {
	list_t *graph[MAX_NO_VERTEX];
} multigraph_t;

typedef struct {
	char start_v;
	list_t *path;
} path_t;

/* function prototypes -------------------------------------------------------*/

// list operations
list_t *make_empty_list(void);
int    is_empty_list(list_t*);
void   free_list(list_t*);
list_t *insert_at_head(list_t*, data_t);
list_t *insert_at_foot(list_t *list, data_t value);
data_t get_head(list_t *list);
list_t *get_tail(list_t *list);

// My list ops
list_t
*copy_list(list_t *list);

//my functions
int
v_to_mappos(char vertex);
char
mappos_to_v (int mappos);
int
stage0(multigraph_t *map, char start_v);
multigraph_t
*make_empty_multigraph(void);
void
print_map(multigraph_t *map);
int
count_v(multigraph_t *map);
int
min_edge(multigraph_t *map);
int
max_edge(multigraph_t *map);
int
sum_edges(multigraph_t *map);
int
odd_deg(list_t *list, char vertex);
int
no_even_deg_v(multigraph_t *map);
int
no_odd_deg_v(multigraph_t *map);
void
print_list(char *array, int no_elem);
/* main program --------------------------------------------------------------*/

int
main(int argc, char *argv[]) {

	char start_v;
	multigraph_t *map;

	map = make_empty_multigraph();

	start_v = argv[SECOND_ARG][FIRST_CHAR];

	if (stage0(map, start_v)) {
	}

	return 0;
}
/*----------------------------------------------------------------------------*/

/*Stage 0 solution. Returns TRUE if map is eulerian, FALSE otherwise*/

int
stage0(multigraph_t *map, char start_v) {
	char ch, v1, v2;
	int edge_wt, no_edges=0;
	data_t *data_v1, *data_v2;

	/*Allocate memory to data_v1 and data_v2*/
	data_v1 = (data_t *)malloc(sizeof(*data_v1));
	assert(data_v1!=NULL);
	data_v2 = (data_t *)malloc(sizeof(*data_v2));
	assert(data_v2!=NULL);

	printf("a");
	/*Extract inforamtion line by line from input*/
	while(scanf("%c %c %d", &v1, &v2, &edge_wt) != EOF) {

		/*Put input info into data_t struct*/
		data_v1->vertex = v2;
		data_v1->edge_wt = edge_wt;
		data_v1->walked = FALSE;

		data_v2->vertex = v1;
		data_v2->edge_wt = edge_wt;
		data_v2->walked = FALSE;

		/*Add data_v1 to linked list of vertice v1*/
		insert_at_foot(map->graph[v_to_mappos(v1)], *data_v1);
		insert_at_foot(map->graph[v_to_mappos(v2)], *data_v2);
		
		/*Eat newline char at end of every line which also indicates one 
		  complete edge has been read. Eat any whitespaces before the 
		  newline char as well.*/
		while((ch=getchar() == ' ')){
			/*do nothing*/
		}
		no_edges += 1;
	}

	/*Print Stage 0 output format and required information*/
	printf("Stage 0 Output\n--------------");
	printf("\nS0: Map is composed of %d vertices and %d edges",count_v(map), 
																	 no_edges);
	printf("\nS0: Min. edge value: %d", min_edge(map));
	printf("\nS0: Max. edge value: %d", max_edge(map));
	printf("\nS0: Total value of edges: %d", sum_edges(map));
	printf("\nS0: Route starts at \"%c\"\n", start_v);
	printf("S0: Number of vertices with odd degree: %d\n", no_odd_deg_v(map));
	printf("S0: Number of vertices with even degree: %d\n", no_even_deg_v(map));
	

	if (no_even_deg_v(map) == count_v(map)) {
		printf("S0: Multigraph is Eulerian\n");
		return TRUE;
	}
	else if (no_odd_deg_v(map) == TRAVERSABLE_ODD_DEGREE) {
		printf("S0: Multigraph is traversable\n");
	}
	
	return FALSE;
}
/*----------------------------------------------------------------------------*/

/*Stage 1 solution*/
int
stage1(multigraph_t *map, char start_v) {

}
/*----------------------------------------------------------------------------*/

/*Recursively finds walk for stage1*/
find_walk(multigraph_t *map, char start_v, list_t *path) {
	/*call lowest unwalked edge on the last element in path. if the edge returned
	has as vertex start_v, return that path.
}
/*----------------------------------------------------------------------------*/

/*Returns the incident edge with lowest value*/
data_t
lowest_unwalked_edge(multigraph_t *map, char start_v) {
	int i;
	list_t *curr;
	data_t min_edge, curr_edge;

	curr = copy_list(map->graph[v_to_mappos(start_v)]);
	assert(!is_empty_list(curr));

	/*
	min_edge = (data_t *)malloc(sizeof(min_edge));
	assert(edge!=NULL);*/

	/*Assign the first unwalked incident edge of start_v as the min scenic
	  value edge*/
	while (!is_empty_list(curr)) {
		if (!get_head(curr).walked) {
			min_edge = get_head(curr);
		}
		curr = get_tail(curr);
	}

	/*Go over all the incident edges and find one with lowest scenic value 
	  which has not been walked*/
	while (!is_empty_list(curr)) {
		curr_edge = get_head(curr);

		/*If edge has been walked, dont bother*/
		if (!curr_edge.walked) {

			/*Select edge with lower scenic value*/
			if (curr_edge.edge_wt < min_edge.edge_wt) {
				min_edge = curr_edge;
			}

			/*If both min value edge and the edge being reviewed have the same
			  scenic value, choose the one whose vertex has lower ascii value*/
			else if (curr_edge.edge_wt == min_edge.edge_wt) {
				if ((int)curr_edge.vertex < (int)min_edge.vertex) {
					min_edge = get_head(curr);
				}
			}
		}
		curr = get_tail(curr);
	}
	return min_edge;
}
/*----------------------------------------------------------------------------*/

/*Finds if given vertex has an unwalked incident path*/
int
unwalked_incident_edge(multigraph_t *map, char vertex) {
	list_t *curr;

	curr = copy_list(map->graph[v_to_mappos(vertex)]);
	assert(curr!=NULL);

	/*
	if (is_empty_list(curr)){
		return FALSE;
	}*/

	while (!is_empty_list(curr)) {
		if (!get_head(curr).walked) {
			return TRUE;
		}
		curr = get_tail(curr);
	}
	return FALSE;
}
/*----------------------------------------------------------------------------*/

void
print_list(char *array, int no_elem) {
	int i;

	printf("\n[");
	for (i=0; i<no_elem; i++) {
		printf("%c", array[i]);
	}
	printf("]");
}
/*----------------------------------------------------------------------------*/

/*Calculates the number of vertices in map with an even degree*/

int
no_even_deg_v(multigraph_t *map) {
	int result=0, i;
	list_t *vertex;

	for (i=0; i<MAX_NO_VERTEX; i++) {
		vertex = map->graph[i];
		if (vertex!=NULL && !is_empty_list(vertex)) {
			if (!odd_deg(vertex, mappos_to_v(i))) {
				result++;
			}
		}
	}
	return result;
}
/*----------------------------------------------------------------------------*/

/*Calculates the number of vertices in map with an odd degree*/

int
no_odd_deg_v(multigraph_t *map) {
	int result=0, i;

	for (i=0; i<MAX_NO_VERTEX; i++) {
		if (odd_deg(map->graph[i], mappos_to_v(i))) {
			result++;
		}
	}
	return result;
}
/*----------------------------------------------------------------------------*/

/*Returns True if the degree of the vertex passed in is odd, False otherwise*/

int
odd_deg(list_t *list, char vertex) {
	int no_edge=0, no_loop_edge=0;
	char neighbour_v;
	list_t *curr;

	assert(list!=NULL);

	/*Create a copy of the vertex so I can use get_tail later
	  without editing the original information in map*/
	curr = copy_list(list);

	/*Go over every edge in curr and increment the value of no_edge. Beware
	  of loops between a single vertex*/
	while (curr!=NULL && !is_empty_list(curr)) {
		neighbour_v = get_head(curr).vertex;

		/*If the edge is a loop between vertex and itself, only count every
		  second such loop as they are encoded twice in the vertex*/
		if ((neighbour_v == vertex)) {
			if (!(no_loop_edge%2)) {
				no_edge++;
			}
		}

		/*Else the edge is not a loop, increment no_edge*/
		else {
			no_edge++;
		}
		curr = get_tail(curr);
	}
	
	/*Return 1 if no_edge odd, 0 otherwise*/
	return no_edge%2;
}
/*----------------------------------------------------------------------------*/

/*Finds the edge with minimum value in map*/

int
min_edge(multigraph_t *map) {
	int min_edge_wt, i;
	list_t *curr;

	/*Find the first vertex from a-Z thats present in the map, then find the 
	  first edge in its linked list and assign the edge's value to min_edge_wt
	  */
	for (i=0; i<MAX_NO_VERTEX; i++) {
		curr = copy_list(map->graph[i]);
		if (curr!=NULL && !is_empty_list(curr)) {
			min_edge_wt = get_head(curr).edge_wt;
			break;
		}
	}

	/*Go over every vertex in map*/
	for (i=0; i<MAX_NO_VERTEX; i++) {

		/*Create a copy of the apt list in map so I can use get_tail later
		  without editing the original information in map*/
		curr = copy_list(map->graph[i]);

		/*Get every node in curr and compare the value of edge with the min*/
		while (curr!=NULL && !is_empty_list(curr)) {
			if (min_edge_wt > get_head(curr).edge_wt) {
				min_edge_wt = get_head(curr).edge_wt;
			}
			curr = get_tail(curr);
		}
	}
	return min_edge_wt;
}
/*----------------------------------------------------------------------------*/

/*Finds the edge with max value in map*/
int
max_edge(multigraph_t *map) {
	int max_edge_wt, i;
	list_t *curr;

	/*Find the first vertex from a-Z thats present in the map, then find the 
	  first edge in its linked list and assign the edge's value to max_edge_wt
	  */
	for (i=0; i<MAX_NO_VERTEX; i++) {
		curr = copy_list(map->graph[i]);
		if ((curr!=NULL) && (!is_empty_list(curr))) {
			max_edge_wt = get_head(curr).edge_wt;
			break;
		}
	}

	for (i=0; i<MAX_NO_VERTEX; i++) {

		/*Create a copy of the apt list in map so I can use get_tail later
		  without editing the original information in map*/
		curr = copy_list(map->graph[i]);

		/*Get every node in curr and compare the value of edge with the max*/
		while (curr!=NULL && !is_empty_list(curr)) {
			if (max_edge_wt < get_head(curr).edge_wt) {
				max_edge_wt = get_head(curr).edge_wt;
			}
			curr = get_tail(curr);
		}
	}
	return max_edge_wt;
}
/*----------------------------------------------------------------------------*/

/*Calculates the sum of all edges in a multigraph*/
int
sum_edges(multigraph_t *map) {
	int sum=0, i;
	list_t *curr;

	for (i=0; i<MAX_NO_VERTEX; i++) {

		/*Create a copy of the apt list in map so I can use get_tail later
		  without editing the original information in map*/
		curr = copy_list(map->graph[i]);

		/*Get every node in curr and add the value of edge to sum*/
		while(curr!=NULL && !is_empty_list(curr)) {
			sum += get_head(curr).edge_wt;
			curr = get_tail(curr);
		}
	}

	/*Returning sum/2 as each edge is represented twice in the map*/
	return sum/2;
}
/*----------------------------------------------------------------------------*/

/*Counts the number of vertices in a multigraph */
int
count_v(multigraph_t *map) {
	int count=0, i;

	for (i=0; i<52; i++) {
		count += !(is_empty_list(map->graph[i]));
	}
	return count;
} 
/*----------------------------------------------------------------------------*/

/*Prints multigraph out*/
void
print_map(multigraph_t *map) {
	int i;
	list_t *curr;

	/*Go over each vertex in map and print its connected vertices with edge
	  values*/
	for (i=0; i<MAX_NO_VERTEX; i++) {
		curr = map->graph[i];

		/*Print the vertex name whose edges are about to be printed*/
		printf("\nvertex:%c\n", mappos_to_v(i));

		/*Print the neighbouring vertex name and the edge value connecting them
		*/
		while(!is_empty_list(curr)) {
			printf("%c %d|", get_head(curr).vertex, get_head(curr).edge_wt);
			curr = get_tail(curr);
		}
	}
}
/*----------------------------------------------------------------------------*/

/*Converts an integer position in the multigraph array to the alphabetic 
  vertex it corresponds to*/
char
mappos_to_v (int mappos) {
	int ascii_val_a, ascii_val_A;
	char vertex;

	ascii_val_a = (int)'a';
	ascii_val_A = (int)'A';
	
	if (mappos>= 0 && mappos <= 25) {
		vertex = (char)(ascii_val_a + mappos);
	}
	else {
		vertex = (char)(ascii_val_A + mappos - NO_ALPHABETS);
	}

	return vertex;

}
/*----------------------------------------------------------------------------*/

/*Creates an empty multigraph. Basically initializes all the lists in the
  graph*/

multigraph_t
*make_empty_multigraph(void) {
	multigraph_t *map;
	int i;

	/*Allocate memory for a multigraph_t and store pointer to it in map. Ensure
	  memory actually got allocated*/
	map = (multigraph_t *)malloc(sizeof(*map));
	assert(map!=NULL);

	/*Store pointer to empty lists in each element of graph*/
	for (i=0; i<MAX_NO_VERTEX; i++) {
		map->graph[i] = make_empty_list();
	}

	return map;
}
/*----------------------------------------------------------------------------*/

/*Relates vertice name to its position in the array in multigraph*/
int
v_to_mappos(char vertex) {
	int ascii_val, ascii_val_a, ascii_val_A;

	/*Store ascii values of 'a', 'A' and argument char vertex*/
	ascii_val_a = (int)'a';
	ascii_val_A = (int)'A';
	ascii_val = (int)vertex;

	/*If vertex is lower case alphabetic char*/
	if ('a'<= ascii_val && ascii_val <='z') {
		return ascii_val-ascii_val_a;
	}

	/*else vertex is upper case alphabetic char*/
	else {
		return ascii_val-ascii_val_A + NO_ALPHABETS;
	}
}
/*----------------------------------------------------------------------------*/

/*Returns pointer to a copy of list*/
list_t
*copy_list(list_t *list) {
	list_t *new_list;
	node_t *curr;

	/*Cant copy non-existent list*/
	assert(list!=NULL);

	/*Create new_list*/
	new_list = make_empty_list();

	/*Go over each node in list and insert its data at foot of new_list*/
	if (list->head!=NULL) {
		curr = list->head;
		while(curr) {
			insert_at_foot(new_list, curr->data);
			curr = curr->next;
		}
	}

	return new_list;
}


/*------------------------------------------------------------------------------
   Code that follows is written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
------------------------------------------------------------------------------*/

list_t
*make_empty_list(void) {
	list_t *list;
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}

int
is_empty_list(list_t *list) {
	assert(list!=NULL);
	return list->head==NULL;
}

void
free_list(list_t *list) {
	node_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;
	while (curr) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(list);
}

list_t
*insert_at_head(list_t *list, data_t value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = value;
	new->next = list->head;
	list->head = new;
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->foot = new;
	}
	return list;
}

list_t
*insert_at_foot(list_t *list, data_t value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = value;
	new->next = NULL;
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}

data_t
get_head(list_t *list) {
	assert(list!=NULL && list->head!=NULL);
	return list->head->data;
}

list_t
*get_tail(list_t *list) {
	node_t *oldhead;
	assert(list!=NULL && list->head!=NULL);
	oldhead = list->head;
	list->head = list->head->next;
	if (list->head==NULL) {
		/* the only list node just got deleted */
		list->foot = NULL;
	}
	free(oldhead);
	return list;
}



/*algorithms are fun*/