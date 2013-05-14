#ifndef _CROSS_PROD_H_
#define _CROSS_PROD_H_

#define TRANSIT_LABEL   1000
#define TRIANGLE_LABEL  40
#define PROP_LABEL      100
#define LTL_LABEL       100
#define NO_OF_ENVIRONMENT_NODES no_of_labels
#define NO_OF_BA_NODES          total_ba_count
#define BOOL                    1
#define LTL                     0

struct queue
{
    void *data;
    struct queue *next;
};

struct transitions
{
    void *node;
    char label[TRANSIT_LABEL];
    struct transitions *next;
};

struct node_triangle
{
    int visited, visible, data, num_neighbor;
    char label[TRIANGLE_LABEL];
    float a_x, a_y, b_x, b_y, c_x, c_y;/* x,y coordinates for point A B C of triangle*/
    float centre_x, centre_y; /* x,y coordinates of centroid*/
    struct node_triangle* neighbor[3], *parent; /* restricted to 20 right now, look into later*/
};

struct ba_nodes
{
    int visited;
    char label[LTL_LABEL];
    struct transitions *neighbors;
    int final;
};

struct environ_node
{
    int location, visited, no_of_coord;
    float **coordinates;
    char *label;
    struct transitions *neighbors;
};

struct cross_prod_nodes
{
    int final, visited;
    char label[80];
    struct environ_node *env_node;
    struct ba_nodes *ba_node;
    struct transitions *neighbors;
    struct cross_prod_nodes *parent;
};

struct atomic_prop
{
    char label[PROP_LABEL];
    bdd value;
};

#ifdef __cplusplus
/*this is a function from trial.c*/
extern "C" int eval_labels(char *, char *);
extern "C" void create_atomic_prop(char **list);
extern "C" void create_crossproduct();
extern "C" int start_ltl_parse(char *label, int length);
extern "C" void print_ba_sm();
extern "C" void print_cross_prod();
extern "C" int find_ba_start();
#else
int eval_labels(char *, char *);
void create_atomic_prop(char **list);
void create_crossproduct();
int start_ltl_parse(char *label, int length);
void print_ba_sm();
void print_cross_prod();
int find_ba_start();
#endif



/*this function belongs to main.cpp inside current_src*/
void populate_neighbors();
/*set functions from new_env.cpp*/
void create_env_array(FILE *input);
char * composite_label(char *node_label, char *parent_label, int);
void add_env_transitions(struct environ_node *node, char *neighbor_label);
void create_label_arr(FILE *input);
void create_ltl(FILE *input);
void triangle_generation();
void create_triangle_nodes(struct node_triangle **node_point,int existing_trianlges,
        int new_triangles, double (*vertices)[2], int (*triangulate)[3], char *label);
int find_start_polygon();
int find_label_index(char *label);
struct cross_prod_nodes* bfs_crossprod(struct cross_prod_nodes *root);
void set_element(struct queue **start_obj, void *data);
void * get_element(struct queue **start_obj);
void * get_stack_element(struct queue **start_obj);
int find_polygon_index(char *label);
void post_polygon_coords(struct cross_prod_nodes *end_node);
int nearest_poly_triangle(double coord[2], char *label);
void navigate_to_poly(double source[], double destination[]);
void reset_node(int property);
int nearest_triangle(double coord[2]);
struct node_triangle* bfs(struct node_triangle *root, struct node_triangle *destination);
void generate_points(struct node_triangle *start_node);
#ifdef TEST
struct queue *search_queue = NULL; // 

void set_event(move_event post);
void get_curr_location( struct coordinate *locate);
void generate_points(struct node_triangle *start_node);
#endif

#endif
