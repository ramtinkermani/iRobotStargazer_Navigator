/* 
 * File:   main.cpp
 * Author: papandya
 *
 * Created on August 8, 2012, 7:32 PM
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "interface.h"
#include "ros/ros.h"
#include <std_msgs/Int8.h>
#include "stargazer_cu/Pose2DTagged.h"
#include "robot_mover.h"
//#include <glut.h>

using namespace std;

/*
 * 
 */

// code beyond this has implementation for using triangulation and creating
// creating the environment for the use of getting coordinates and setting them
// code beyond this point will be towards solving BFS for graph nodes


#define SEGSIZE 200

struct node
{
    int visited, visible, data, num_neighbor;
    float a_x, a_y, b_x, b_y, c_x, c_y;// x,y coordinates for point A B C of triangle
    float centre_x, centre_y; // x,y coordinates of centroid
    node *neighbor[3], *parent; // restricted to 20 right now, look into later
};

struct queue
{
    void *data;
    struct queue *next;
};
/*
enum node_properties
{
    NONE,
    PARENT,
    VISIBILE,
    VISITED,
    DATA
};
*/
// have a queue that can be used to create the breadth first search
struct queue *search_queue = NULL; // 
pthread_mutex_t search_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t destination_lock = PTHREAD_MUTEX_INITIALIZER;

int triangulate[SEGSIZE][3], ntriangles; // create a
int cntr[20], ncontours; // vertices per contour, #contours that can be specified
double vertices[SEGSIZE][2]; // the vertices specified by the 
node *node_arr;

struct coordinate destination;// dont use this without destination_lock mutex
void fill_set_event();

void set_element(struct node* data)
{// add an event at the start
    pthread_mutex_lock(&search_mutex);
    struct queue *temp = search_queue;

    printf("locked the mutex\n");
    if(temp != NULL)
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
    // add the event to the end of the event queue
        printf("the temp \n");
        temp->next = (struct queue *) malloc(sizeof(queue));
        temp->next->data = (void *)data;
        temp->next->next = NULL;
    }
    else
    {// if this is the first event
        search_queue = (struct queue *) malloc(sizeof(queue));
        search_queue->data = (void *) data;
        search_queue->next = NULL;
        printf("first one\n");
    }
    pthread_mutex_unlock(&search_mutex);
}

struct node* get_element()
{// reads the last element present in the 
    struct queue *temp = NULL;
    struct node *result = NULL;
    pthread_mutex_lock(&search_mutex);
    //printf("getting a new event\n");
    if(search_queue != NULL)
    {// store to the event and return back
        temp = search_queue;
        search_queue = search_queue->next;
        result = (struct node*)temp->data;
        free(temp);
        printf("read event going now\n");
    }
    pthread_mutex_unlock(&search_mutex);
    return result;
}

struct node* bfs(struct node *root, node *destination)
{
    struct node *temp, *temp2;
    int count;

    set_element(root);
    
    root->visited = 1;
    count = 0;
    while((temp = get_element())!= NULL)
    {
        count = 0;
        if(temp == destination)
        {// the queue should be emptied for next time
            while(get_element()!=NULL)
            {
                // nothing needs to be done in this
                count++;// in case we need the number of elements present
            }
            return temp;// return this pointer as the starting point
        }
        for(count = 0; count < temp->num_neighbor ; count++)
        {
            temp2 = temp->neighbor[count];

            // this node should only be added to queue if its visible
            if(temp2->visible == true && temp2->visited != true)
            {
                temp2->parent = temp;
                temp2->visited = 1;
                set_element(temp2);
                cout<<"node visited"<<temp2->data<<endl;
            }
        }
    }
    
    //warning : the next time you do a bfs dont forget to refresh the nodes
    // and make all the parents to NULL
    // ran out of nodes before finding the destination
    return NULL;
    
}

// this function is to be called to set all the array values of neighbor
// in all the nodes
void populate_neighbors()
{
    int matches, count;
    node *nodes;
    
    count = ntriangles;
    nodes = node_arr;
    if(count == 0 || nodes == NULL)
    {
        printf("the nodes array or ntriangles is not done\n");
        return;
    }
    
    for(int i = 0; i < count ; i++)
    {
        for(int j = i; j < count; j++)
        {
            matches = 0;
            // match all three points to each other and check if there are matches
            if((nodes[i].a_x == nodes[j].a_x  && nodes[i].a_y == nodes[j].a_y)||
                 (nodes[i].a_x == nodes[j].b_x  && nodes[i].a_y == nodes[j].b_y)||
                    (nodes[i].a_x == nodes[j].c_x  && nodes[i].a_y == nodes[j].c_y))
            {
                matches++;
            }

            if((nodes[i].b_x == nodes[j].a_x  && nodes[i].b_y == nodes[j].a_y)||
                 (nodes[i].b_x == nodes[j].b_x  && nodes[i].b_y == nodes[j].b_y)||
                    (nodes[i].b_x == nodes[j].c_x  && nodes[i].b_y == nodes[j].c_y))
            {
                matches++;
            }
            if((nodes[i].c_x == nodes[j].a_x  && nodes[i].c_y == nodes[j].a_y)||
                 (nodes[i].c_x == nodes[j].b_x  && nodes[i].c_y == nodes[j].b_y)||
                    (nodes[i].c_x == nodes[j].c_x  && nodes[i].c_y == nodes[j].c_y))
            {
                matches++;
            }    
            
            if(matches == 2)
            {// its means that there is a neighbor found
                nodes[i].neighbor[nodes[i].num_neighbor] = &(nodes[j]);
                nodes[j].neighbor[nodes[j].num_neighbor] = &(nodes[i]);
                nodes[j].num_neighbor++;
                nodes[i].num_neighbor++;
            }
        }
    }
}

//this creates a node array which provides the graph structure
void create_node()
{
    int count;
    node *nodes;
    
    count = ntriangles;
    nodes = node_arr;
    if(count == 0 || nodes == NULL)
    {
        printf("the nodes array or ntriangles is not done\n");
        return;
    }
    
    for(int i = 0; i < count; i++)
    {
        nodes[i].parent = NULL;
        nodes[i].visible = 1; // by default make all nodes visible
        nodes[i].visited = 0; // all nodes are unvisited the first time
        
        nodes[i].num_neighbor = 0; // the number of neighbors present
        nodes[i].a_x = vertices[triangulate[i][0]][0];
        nodes[i].a_y = vertices[triangulate[i][0]][1];
        nodes[i].b_x = vertices[triangulate[i][1]][0];
        nodes[i].b_y = vertices[triangulate[i][1]][1];
        nodes[i].c_x = vertices[triangulate[i][2]][0];
        nodes[i].c_y = vertices[triangulate[i][2]][1];
        // calculate and store the centroids which will be the point to move to
        nodes[i].centre_x = (nodes[i].a_x + nodes[i].b_x + nodes[i].c_x)/3;
        nodes[i].centre_y = (nodes[i].a_y + nodes[i].b_y + nodes[i].c_y)/3;
        
        nodes[i].data = 0;
    }
}

// this reads the input of contours and populates the 
void read_input()
{
    FILE *fp = NULL;
    char str[80];
    int total_contours, total_vertices, contour_vertices, i , j;
    float x_cord, y_cord;
    
    total_vertices = 1; //  this is because v[0] is not used in triangulation
    fp = fopen("./data_2.txt","r" );
    if(fp == NULL)
    {
        printf("no map available\n");
        exit(0);
    }
    
    fscanf(fp, "%d", &total_contours);
    
    for( i=0; i < total_contours; i++)
    {
        fscanf(fp, "%d", &contour_vertices);
        
        cntr[i] = contour_vertices;
        
        for( j=total_vertices; j < (total_vertices+contour_vertices); j++)
        {
            fscanf(fp, "%f %f", &x_cord, &y_cord);
            vertices[j][0] = x_cord;
            vertices[j][1] = y_cord;
        }
        total_vertices += contour_vertices;
        
    }
    
    // adding a print functionality to know whether it worked correctly or not
    ncontours = total_contours;
    for(i = 0; i < total_contours; i++)
    {
        printf("number of vertices: %d\n", cntr[i]);
    }
    
    for(j =0; j < total_vertices; j++)
    {
        printf("vertex: %f %f\n", vertices[j][0],vertices[j][1]);
    }
}

// this function will reset a certain property of the nodes and will do it 
// for all of them',  it needs to be used once we are done running a BFS algo
// on the set, then we can reuse all the nodes
void reset_node(int property)
{
    int count;
    node *nodes;
    
    count = ntriangles;
    nodes = node_arr;
    if(count == 0 || nodes == NULL)
    {
        printf("the nodes array or ntriangles is not done\n");
        return;
    }
    
    for(int i=0; i < count; i++)
    {//do it for all the nodes in the entire structure
       switch(property)
       {
           case PARENT:
               nodes[i].parent = NULL;
               break;
           case VISITED:
               nodes[i].visited  = 0;
               break;
           case DATA:
               nodes[i].data = 0;
               break;
           default:
               break;
       }
    }
    
}

// this function gets the input of polygon points and get it to do triangualtion
// it also takes care of creating nodes and then dispatching
void get_input()
{
    // create an array for triangualtion 
    
    // warning: allocate vertices here first
    read_input();
    
    // warning: allocate triangulate array first
    printf("going to do triangulation\n");
    ntriangles = triangulate_polygon(ncontours, cntr, vertices, triangulate); // 
    
    // warning: allocate node_arr same number as triangulate
    printf("about to allocate node_arr\n");
    node_arr = (node *)malloc(sizeof(node)*ntriangles);
    
    create_node();
    
    // free triangulate and vertices once they are finished with
    
    populate_neighbors();
  
    
}

// generate points based on the nodes from the graph and post them to the
// lower_planner group
void generate_points(struct node *start_node)
{
    struct move_event temp, arr[200];
    node *nodes;
    int i=0;
    FILE *fp;

    fp = fopen("/home/cpslab/debug.txt", "a+");   
 
    nodes = start_node;
    if(nodes == NULL)
    {
        printf("the nodes array is not done\n");
        return;
    }

    while( nodes != NULL)
    {
        temp.move_to.x = nodes->centre_x;
        temp.move_to.y = nodes->centre_y;
        temp.move_to.angle = 0;
        arr[i] = temp;
        i++;
        nodes = nodes->parent;
    }
    while(i>0)
    {
        i--;
        fprintf(fp,"the node point is: %f %f\n", arr[i].move_to.x, arr[i].move_to.y);
        set_event(arr[i]);
    }
    fclose(fp);
}

// function will determine which triangle is the closest one
int nearest_triangle(double coord[2])
{
//    float distance=0, temp;
    int count, result= 0;
    node *nodes;
    
    count = ntriangles;
    nodes = node_arr;
    if(count == 0 || nodes == NULL)
    {
        printf("the nodes array or ntriangles is not done\n");
        return 0;
    }

/*    distance  = sqrt(((nodes[0].centre_x - coord[0])*(nodes[0].centre_x - coord[0]))+
            ((nodes[0].centre_y-coord[1])*(nodes[0].centre_y-coord[1])));
    // find the centroid thats closest and begin from there
    for(int i=1; i < count; i++)
    {
        temp = sqrt(((nodes[i].centre_x - coord[0])*(nodes[i].centre_x - coord[0]))+
                ((nodes[i].centre_y-coord[1])*(nodes[i].centre_y-coord[1])));
        if(temp < distance)
        {
            distance = temp;
            result = i;
        }
    }**/
    
 
  bool b1, b2, b3;

  for(int i = 0; i < count; i++)
  {
    b1 = (((coord[0]-nodes[i].b_x)*(nodes[i].a_y-nodes[i].b_y))-
            ((nodes[i].a_x-nodes[i].b_x)*(coord[1]-nodes[i].b_y))<0);

    b2 = ((((coord[0]-nodes[i].c_x)*(nodes[i].b_y-nodes[i].c_y))-
            ((nodes[i].b_x-nodes[i].c_x)*(coord[1]-nodes[i].c_y)))<0);

    b3 = ((((coord[0]-nodes[i].a_x)*(nodes[i].c_y-nodes[i].a_y))-
            ((nodes[i].c_x-nodes[i].a_x)*(coord[1]-nodes[i].a_y)))<0);

    if((b1 == b2) && (b2 == b3))
    {// this implies the point is inside the triangle
        result = i;
        break;
    }
  } 
    
    return result;// gives the node position in the nodes array
}


// this function accepts the source and destination and tries to navigate to it
void navigate_to(double source[2], double destination[2])
{
    bool sanity_check;
    int index_source, index_dest;
    struct node* temp_dest;
    node *nodes;
    struct move_event temp;// this is added to make it reach its final destination
    
    nodes = node_arr;
    if(nodes == NULL)
    {
        printf("the nodes array or ntriangles is not done\n");
        return;
    }

    reset_node(PARENT);
    reset_node(VISITED);
    
    /*/sanity_check = is_point_inside_polygon(source);
    if(!sanity_check)
    {
        printf("invalid source\n");
        return;
    }
    
    //sanity_check = is_point_inside_polygon(destination);
    if(!sanity_check)
    {
        printf("invalid destination\n");
        return;
    }**/
    
    index_source = nearest_triangle(source);
    printf("source coordinates: a:%f %f b:%f %f c:%f %f\n",
    nodes[index_source].a_x,nodes[index_source].a_y, nodes[index_source].b_x,
    nodes[index_source].b_y,nodes[index_source].c_x, nodes[index_source].c_y );

    index_dest = nearest_triangle(destination);
    printf("destination coordinates: a:%f %f b:%f %f c:%f %f\n",
    nodes[index_dest].a_x,nodes[index_dest].a_y, nodes[index_dest].b_x,
    nodes[index_dest].b_y,nodes[index_dest].c_x, nodes[index_dest].c_y );

    
    temp_dest = bfs(&nodes[index_source], &nodes[index_dest]);


    generate_points(&nodes[index_dest]); // this takes care of navigation in triangles

    temp.move_to.x = destination[0];
    temp.move_to.y = destination[1];
    temp.move_to.angle = 0;
    //set_event(temp);
}


void get_destination(const stargazer_cu::Pose2DTagged::ConstPtr& data)
{
    printf("destination is: %f, %f, %f\n", data->x+2, data->y+2, data->theta);
    pthread_mutex_lock(&destination_lock);
    destination.x = data->x+2;
    destination.y = data->y+2;
    destination.angle = 0;
    pthread_mutex_unlock(&destination_lock);
    
}


int main(int argc, char* argv[]) {

    double source[2], destine[2];
    struct coordinate locate; // warning: added to get the source
    int s;
    pthread_attr_t attr;
    pthread_t threads[3];
    printf("robot_init about to happen\n");
    
    ros::init(argc, argv, "irobot_stargazer");
    ros::NodeHandle nh; 
    ros::Subscriber sub;
    ros::spinOnce();
    sub = nh.subscribe("/cu/stargazer_marker_cu", 1, get_stargazer_coord);
    //sub2 = nh.subscribe("/destXYT", 10, get_destination);
    if(!sub)
    {// the subscribe did not work
        printf("could not subscribe to stargazer\n");
        exit(0);
    }

    robot_init();
    printf("pthread_init about to happen\n");
    s = pthread_attr_init(&attr);
    if(s != 0)
    {
        printf("there is a problem with attributes\n");
        return -1;
    }
    printf("about to create thread\n");
    s = pthread_create(&threads[0], &attr, event_reader, NULL);
   /**/ 
    printf("about to get_input\n");
    //get_input();
    source[0] = 0.1;
    source[1] = 0.1;
    destine[0] = 0.5;
    destine[1] = 4.8;
    
    locate.x = 0;
    locate.y = 0;
    locate.angle = 0;
    printf("about to get curr _location\n");

    printf("calliing get_curr_location\n");
    get_curr_location(&locate);

    source[0] = locate.x;
    source[1] = locate.y;
/*    
    locate.x = 0;
    locate.y = 0;
    locate.angle = 0;
    printf("about to get the destination\n");
    while(locate.x == 0)
    {
        sleep(1);
        ros::spinOnce();
        pthread_mutex_lock(&destination_lock);
        locate.x = destination.x;
        locate.y = destination.y;
        pthread_mutex_unlock(&destination_lock);
    }

    destine[0] = locate.x;
    destine[1] = locate.y;**/
    printf("navigate to called\n");
    //navigate_to(source, destine);
    
    fill_set_event();
    //free(node_arr); warning: temp it has been tkaen out
    pthread_join(threads[0], NULL);
    return 0;
}
/*
void display(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(1,0,0);
	glVertex2f(100,100);
	glVertex2f(200,200);
	glVertex2f(300,100);
	
	glEnd();
	glFlush();
}

int main(int argc, char* argv[])
{
	int id=0;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(0,0);
	id=glutCreateWindow("test");
	hello();
	glOrtho(0,799,0,599,-499,499);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
**/

// this function fills in the set event queue 
void fill_set_event()
{
    FILE *fp = NULL;
    move_event new_move;
    new_move.move_to.angle = 0;
    fp = fopen("./coordinates.txt", "r");
    while(!feof(fp))
    {
        fscanf(fp,"%f %f",&new_move.move_to.x, &new_move.move_to.y);
        set_event(new_move);
    }
    fclose(fp);
}
