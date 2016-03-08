#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

/* For debug only: assertion macro for verifying input data */
#define ASSERT(e) { if(!(e)) throw #e; }

/* Min/max corn maze dimensions as specified in the problem statement */
#define MINSIZE 3
#define MAXSIZE 40

/* Size of the current maze */
int row_size, col_size;

/* String representation of the maze. Upper left corner is (0, 0) */
char maze[MAXSIZE][MAXSIZE];

/* Prototype for inside() which is used by coord::operator char const &() */
class coord;
inline bool inside(coord const &p);

/*
 * Represents a location within the maze of the form (row, col). It can also
 * represent a direction of the form (row offset, col offset) such as (0, +1)
 * for right and (-1, 0) for up.
 * 
 * This is specified as a class derived from pair<> instead of a simple
 * typecast because C++ requires that type conversion operators be a member
 * of the class.
 */
class coord : public pair<int, int> {
public:
    
    /* Public constructor */
    coord(int row, int col) : pair<int, int>(row, col) {}

    /* Converting to a char is a shortcut for accessing maze data */
    operator char const &(void) {
        ASSERT(inside(*this));
        return maze[first][second];
    }
};

/* Return true if coordinate is within the bounds of the maze */
inline bool inside(coord const &p) {
    if(p.first < 0 || p.first >= row_size) {
        return false;
    }
    if(p.second < 0 || p.second >= col_size) {
        return false;
    }
    return true;
}

/* Adding coordinates together adds their dimensions */
inline coord operator+(coord const &a, coord const &b) {
    return coord(a.first + b.first, a.second + b.second);
}

/* Turn 90 degrees to the left (assuming this coord is a direction) */
coord left(coord const &p) {
    return coord(-p.second, p.first);
}

/* Turn 90 degrees to the right (assuming this coord is a direction) */
coord right(coord const &p) {
    return coord(p.second, -p.first);
}        

/* Typedef for a function pointer to the above left() or right() functions */
typedef coord (*funcptr)(coord const &p);

/*
 * Read one maze representation from the input, filling in the "maze" array
 * with the string representation. This also scans the input for the 'S', and
 * returns the initial starting location.
 */
coord parse_input(void)
{
    coord start(-1, -1);
    
    /* Read in the puzzle size */
    cin >> col_size >> row_size;
    ASSERT(col_size >= MINSIZE && row_size >= MINSIZE);
    ASSERT(col_size <= MAXSIZE && row_size <= MAXSIZE);;
        
    /* Read in the puzzle and check for starting point */
    for(int row = 0; row < row_size; row++) {
        for(int col = 0; col < col_size; col++) {

            /* Read one character of input and assign to maze array */
            char c;
            cin >> c;
            ASSERT(c == '.' || c == '#' || c == 'S' || c == 'E');
            maze[row][col] = c;
                
            /* Check if this is the starting point */
            if(c == 'S') {        
                start = coord(row, col);
            }
        }
    }

    /* A starting point 'S' is required */
    ASSERT(start != coord(-1, -1));

    return start;
}

/*
 * Return the cost of always following one wall of the maze starting from
 * "pos" and until we reach the exit 'E'. The "rotate1" and "rotate2" arguments
 * are function pointers to the left() or right() functions and they determine
 * whether we follow the left or right hand wall.
 */
int follow(coord pos, funcptr rotate1, funcptr rotate2)
{
    int cost = 1;    /* 1 accounts for the initial cost of 'S' space */
    coord dir(1, 0); /* Current direction we are facing within the maze */

    /* Since we start along an edge, we always face away from that edge */
    for(int i = 0; i < 4; i++, dir = left(dir)) {
        if(inside(pos + dir) && pos + dir != '#') {
            break;
        }
    }

    /* Keep looping until we reach the exit */
    while(pos != 'E') {

        /* If no side wall, turn & move toward the side we're following */
        if(pos + rotate1(dir) != '#') {
            dir = rotate1(dir);
            pos = pos + dir;
            cost++;
        }
        
        /* If there's a wall in front, turn away from side wall we follow */
        else if(pos + dir == '#') {
            dir = rotate2(dir);
        }
        
        /* Otherwise, move forward */
        else {
            pos = pos + dir;
            cost++;
        }        
    }
        
    return cost;
}

/*
 * Return the shortest path through the maze starting at "pos" and ending
 * at the exit 'E'. Since moving from one location to another always incurs
 * the same edge cost, this problem can be easily solved using a breadth
 * first traversal starting from "pos".
 */
int search(coord pos)
{
    queue<coord> queue;             /* FIFO queue for breadth first search */
    map<const coord, bool> visited; /* Locations already visited */    
    map<const coord, int> cost;     /* Shortest path length to each location */
    
    /* Add starting location to the FIFO queue; cost of 1 counts the 'S' */
    visited[pos] = true;
    cost[pos] = 1;
    queue.push(pos);
    
    /* Keep looping until there are no more locations to visit */
    while(!queue.empty()) {
    
        /* Retrieve the next location from the queue in breadth first order */
        coord pos = queue.front();
        queue.pop();
    
        /* If this is the exit, return with the shortest path length to it */
        if(pos == 'E') {
            return cost[pos];
        }

        /* Explore each of the surrounding neighbors */
        coord dir(1, 0);
        for(int i = 0; i < 4; i++, dir = left(dir)) {
            coord newpos = pos + dir;
        
            /* Skip locations out of bounds, visited, or containing a wall */
            if(!inside(newpos) || visited[newpos] || newpos == '#') {
                continue;
            }

            /* Compute shortest path to this neighbor and add to queue */
            visited[newpos] = true;
            cost[newpos] = cost[pos] + 1;
            queue.push(newpos);
        }
    }
    
    /* If we got here then there is no path from maze start to finish */
    throw "The exit is not reachable";
}

/* Main body of program */
void process(void)
{
    int maze_num, maze_idx;
    
    /* Read how many puzzles are to be analyzed */
    cin >> maze_num;

    /* Process each puzzle separately */
    for(maze_idx = 0; maze_idx < maze_num; maze_idx++) {
        int col_size, row_size;
    
        /* Read in the maze and get initial starting point */
        coord start = parse_input();
        
        /* Compute shortest path to exit (and check that exit is reachable) */
        int shortcost = search(start);
        
        /* Compute cost of following the left and right walls */
        int leftcost  = follow(start, left, right);
        int rightcost = follow(start, right, left);
        
        /* Print the final results */
        cout << leftcost << " " << rightcost << " " << shortcost << endl;
    }
}

/* Run program and print out any exceptions that occur */
int main(void)
{
    /* Throw exceptions on EOF or failed data extraction in >> operator */
    cin.exceptions(ios::eofbit | ios::failbit);
    
    /* Run main body of code */
    try {
        process();
    }
    
    /* Catch any internally generated exceptions */
    catch(char const *e) {
        cerr << "Exception: " << e << endl;
    }
    
    /* Catch unexpected EOF or bad input data */
    catch(ios::failure const &e) {
        cerr << "Unexpected EOF or data type mismatch on input" << endl;
    }

    return 0;
}
