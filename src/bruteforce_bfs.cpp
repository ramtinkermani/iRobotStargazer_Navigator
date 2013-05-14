
struct cell{
    int visited, visibility, data;
    int parentx, parenty;
}environment[100][100];




void bruteforce_visit_neighbors(int curr_x, int curr_y)
{// this visits the neighbors and makes sure that there are
    // 
    
    int max_x, max_y, min_x, min_y;

    // ix the max and min values for x
    if(curr_x == 0)
    {
        min_x = 0;
    }
    else
    {
        min_x = curr_x-1;
    }
    
    if(curr_x == 99)
    {
        max_x = 99;
    }
    else
    {
        max_x = curr_x + 1;
    }
    
    
    // fix the max and min values for y
    if(curr_y == 0)
    {
        min_y = 0;
    }
    else
    {
        min_y = curr_y-1;
    }
    
    if(curr_y == 99)
    {
        max_y = 99;
    }
    else
    {
        max_y = curr_y + 1;
    }
    
    for(int i=min_x; i < max_x ; i++)
    {
        for(int j =min_y ; j < max_y ; j++)
        {
            if(environment[i][j].visited == 0)// check if already visited the node
            {// mark it as visited, also put the parent values
                environment[i][j].parentx = curr_x;
                environment[i][j].parenty = curr_y;
                environment[i][j].visited = 1;
            }
        }
    }
}


// the algo works in the following manner:
// pick the starting node and read all the neighboring ones 
// continue to do for all of them
int bruteforce_bfs(int destination)
{
    // this does the queuing part 
    int arrx = 100, arry = 100;
    // first part is to read all the nodes one by one
    for(int i=0; i < arrx ; i++)
    {// travel in the x direction
        for(int j=0; j < arry ; j++)
        {// travel in y direction
            // visit the neighbor nodes
            bruteforce_visit_neighbors(i, j);
            if(environment[i][j].data == destination)
            {
                return 1;
            }
        }
    }
    
    return 0;
}

// initialize the array before trying to manipulate it
void init_array()
{
    int arrx = 100, arry = 100;
    // first part is to read all the nodes one by one
    for(int i=0; i < arrx ; i++)
    {// travel in the x direction
        for(int y=0; y < arry ; y++)
        {
            environment[i][y].visited = 0;
            environment[i][y].visibility = 0;
            environment[i][y].parentx = 0;
            environment[i][y].parenty = 0;
        }
    }
    
}

