# Berzerk (super version)

My initial design for berzerk (shown here) was not strictly faithful to the arcade. There were some major differences planned:
- Robots detect the player intelligently, and would hold fire until they knew they could hit the player
- Robots would navigate efficiently (shortest path) and avoid wall collisions. 
- Robots would behave statefully, between states such as IDLE, MOVING, SHOOTING, and DEAD
- The game board could be variable size (in terms of wall length/thickness and number of walls in game)
- The game board would have only one exit 

This would have produced a more sophisticated / complex design that probably wouldn't have made too much of a difference in gameplay. I ended up scrapping this and designing a version faithful to the arcade, which is what has been implemented. 

## Game space layout 
- The game space is an W x H grid (3x3 in the example below for simplicity; in the original arcade game it's fixed to 5w x 3h)
 of constant-sized (in terms of pixels) cells.
```
     ————— ————— —————
    |     |     |     |
    |     |     |     |
    |     |     |     |
     ————— ————— —————
    |     |     |     |
    |     |     |     |
    |     |     |     |
     ————— ————— —————
    |     |     |     |
    |     |     |     |
    |     |     |     |
     ————— ————— —————
```
- Note in this drawing that there are 3 horizontal walls per row and 4 per column; similarly, 3 vertical walls per
column, and 4 per row. Here, GRID_WIDTH = 3, GRID_HEIGHT = 3.
- The simplest approach is for all walls to be constant size
- Wall size can be configurable, one setting to control horizontal wall length and vertical wall height
(i.e. how "long" walls are), another to control horizontal wall height and vertical wall length (i.e. how "thick"
they are)
- We can represent walls with two arrays, one for horizontal walls and one for vertical walls
    - Alternative: A collection of Room objects; but this would have to account somehow for rooms sharing walls
    (hard).
    - To support easy collision testing, the arrays can contain SDL_Rect*; nullptr means no wall exists, otherwise
    we can deref the pointer to use it for testing.
    - Game can own a single texture for a vertical wall and for a horizontal wall, and then just repeatedly draw it
    wherever needed.
-  A wall is laid on the border between two rooms and its "thickness" extends into each room equally. A room begins
and ends on the same range of pixels regardless of whether a wall exists at is border or not. Horizontal and
vertical walls may overlap without issue.

How to create SDL_Rect for existing walls for collision testing:
- The only thing we actually need to calculate is a wall's top left corner; we already know its width and height
from configuration, and that's all we need to create an SDL_Rect.
- The middle of the screen is 0,0, and configuration determines how many cells are in the grid, so we can calculate
the top left corner of the entire grid ahead of time.
- We can do the rest using the wall's index in its array.
- Suppose for all notes below that we're using the 3x3 grid above, and the center of it's center room is 0,0 and
each cell is 100px by 100px. So the top left point is -150, 150, top right is 150, 150, etc. Suppose walls are 4px
thick.
- For any vertical wall, its top-left corner has:
    - X = GRID_TOP_LEFT_X + (WALL_LENGTH * (index % GRID_WIDTH + 1)) - (WALL_THICKNESS/2)
    - Y = GRID_TOP_LEFT_Y - (WALL_LENGTH * (index / GRID_WIDTH + 1))
    - Example: SDL_Rect for the topmost, leftmost vertical wall (idx 0)
        - X = -150 + (100 * (0 % 3 + 1)) - (4/2) = -157
        - Y = 150 - (100 * (0 / 3 + 1)) = 150
- For any horizontal wall, its top-left corner has:
    - Y = GRID_TOP_LEFT_Y - (WALL_LENGTH * (index / GRID_WIDTH)) + (WALL_THICKNESS/2)
    - X = GRID_TOP_LEFT_X + (WALL_LENGTH * (index % GRID_WIDTH))
    - Example: SDL_Rect for the bottom-most, rightmost horizontal wall (idx 11):
        - Y =  150 - (100 * (11 / 3)) + (4/2) = 150 - (100 * 3) + 2 = -148
        - X = -150 + (100 * (11 % 3)) = 50

## Grid construction
- First, we ensure that the game space is completely enclosed, but has an exit:
    - Every room on the game space's border has the correct border walls (top rooms have top walls, left rooms
have left walls, etc)
        - A vertical wall with index i is a border wall if:
            - i == 0
            - (i % grid width) == 1 (e.g. vertical wall index 4; left side border)
            - (i % grid width) == (grid width - 1); vertical wall index
    - One (or more) of these is randomly selected to be missing a border wall for the player to escape through
```
         ————— ————— —————
        |                 |
        |                 |
        |                 |

        |                 |
        |                 |
        |                 |

        |                 |
        |                 |
        |                 |
         —————       —————
```
```
         ————— ————— —————
        |                 |
        |   P             |
        |                 |

        |                 |
        |                 |
        |                 |

        |                 |
        |                 |
        |                 |
         —————       —————
```
- Next, we find an escape path from the player's position to the exit; this will be an ordered collection of
rooms/nav points that must be traversed. This path must remain clear so the player can actually escape.
    - If we use a BFS, this path will always be a shortest path, and might be too easy
    - DFS may find a shortest path in some circumstances, or a long one
    - We can try randomly selecting a child node to visit as well; this may not prove any better than DFS in
        gameplay experience
```
         ————— ————— —————
        |                 |
        |   P    X     X  |
        |                 |

        |                 |
        |              X  |
        |                 |

        |                 |
        |        X     X  |
        |                 |
         —————       —————
```
- Now, we can begin adding internal walls to the maze. A wall can only be added as long as it doesn't
intersect the escape path.
    - Vertical walls cannot have escape path nav points on the left and right
    - Horizontal walls cannot have escape path nav points above and below
    - We probably want it configurable how many of the maze's walls (other than those on the escape path)
should be filled in
    - Smaller grids will have fewer navigation options, but larger grids will leave more room for player
decision
```
         ————— ————— —————
        |                 |
        |   P    X     X  |
        |                 |
         ————— —————
        |           |     |
        |           |  X  |
        |           |     |
               —————
        |                 |
        |        X     X  |
        |                 |
         —————       —————
```
- Finally, we can place robots (R) at random locations in the maze
    - We cannot place two robots on top of each other, or on top of the player
    - We probably don't want robots to be tightly clustered in a few rooms; a mostly uniform distribution is
preferable
    - We can place robots in completely blocked off cells, but we don't want to put too many in them since
they pose no threat to the player
```
         ————— ————— —————
        |                 |
        |   P    X     X  |
        |        R        |
         ————— —————
        |  R R      |  R  |
        |        R  |  X  |
        |           |     |
               —————
        |             R   |
        |   R    X     X  |
        |        R        |
         —————       —————
```
- The game is now ready.


## Navigation
Robots will provide their starting position and desired ending position. Grid must return to them an ordered
sequence of (x,y) pairs between which they can safely move. Because this is a uniformly weighted grid, Djikstra's
is equivalent to BFS, but A will probably find paths more effectively than BFS. Berzerk was invented before JPS,
so we don't necessarily need to use it (and I'm hesitant to try given how complex it is).


#### Approach 1: spaced jumps
- Assume a configurable value (say 25 here; should never be larger than half of wall length); robots BFS by checking 25px in each direction (perhaps even diagonal).
- BFS terminates when the desired endpoint is within jump range and the path to it does not intersect with a wall.
- If a considered point puts terminates within character-width of a wall or would cause traversal through a wall, it is not considered valid.
- Walls occur at predictable offsets from the top-left corner of the grid. We test in constant time if a wall falls between two points or is within character width of the termination point.
    - We could also do the sort of "predict collision" style testing from Sprawl; move the rectangle to that position and 
Edge cases:
    - Robot get stuck near a wall and has no valid moves?
        - Not if the jump space is appropriately small; if it's shorter than half of wall length, there will always be at least one direction to move in (i.e. away from walls and into the room)
    - Robot overshoots end target?
        - Not if the termination check is based on "is my target in this room"

#### Approach 2: predetermined nav points per room
- A NavPoint is a pre-determined (x,y) coordinate that a character can be centered at without touching a wall.
    - By "predetermined", we could mean "actually generated and stored", but could also mean some rule for
        reliably predicting nearest NavPoints as though they're stored (i.e. if every NavPoint's x and y are
        multiples of 10).
- A character can safely move from one nav point in a room to another without touching a wall.
- There must be at least one per room, and can be as many as there are valid pixels (i.e. wouldn't cause a wall
    collision) per room.
- Having too few NavPoints per room will result in robots colliding with eachother when navigating.
- Having too many will probably degrade performance, e.g. 16 robots in a maze with 1000 x 1000 available
    nav points (suppose the maze is 2000 x 1500) would require 16 x 10^6 (16 million) operations per frame.
- As long as the code for setting nav points is configurable, we can play with it to optimize performance.
- In this approach, a robot does not need to move only to NavPoints.
    - Suppose NavPoints occur on any point whose x and y are both multiples of 10.
    - A robot might move to (5,2) if it spots the player there.
    - In this approach, navigation should begin by first going to the nearest NavPoint, and end at the NavPoint
    closest to the target.
- We could initialize a uniformly spaced grid of nav points (configurable density), then either remove any
    that are within character width of walls, or not treat them as valid when doing pathfinding.
    - When getting navpoint neighbors, we can test against collision with the 4 walls of the (up to 4) rooms the
    character is in. This will only add constant time complexity to each step of pathfinding.
 - This is very similar to spaced jumps, except here a character must first move to a known nav point and go to the one nearest their target rather than start anywhere and end anywhere.

#### Approach 3: Roadsigns
- What if instead of needing a complete path, robots only needed to know where to go "next", akin to following roadsigns?
- Before the game begins, compute how to get from every room to every other room (this can be done during loading)
- This information would be accessed by robots querying "I am in room X, trying to get to room Y. What is the next room I need to go to?" 
- This should not be very expensive to compute; for a 4x4 maze, each of the 16 rooms would need to determine how to reach every other of the 15 rooms (excluding neighbors, so between 14 and 11 other rooms), and we can probably shave off unnecessary edge case work as well. A recursive BFS that upon finding the target room returns to each caller the next room in the path would probably be sufficient. 
- The robot then picks a random point in the next room that won't result in a collision and navigates to it. 
    - This will minimize (but not prevent) robot collisions. 
    - We could minimize further by having a safeguard feature for every robot movement that if it is on a collision course, it picks a random new heading and moves to that point; this could still deadlock in a few scenarios, but the odds become increasingly small. 

## Progressive Feature plan
1. Game space loads with pre-determined wall layout
1. Character and Robots load at predetermined locations
1. Character can move around
1. Character dies if they touch wall or robot
1. Lives mechanic
1. Character wins if they reach exit
1. Character can shoot one projectile at a time 
1. Sounds on shooting
1. Bullets stop if they hit wall or robot
1. Robots die if they are hit by bullet
1. Robot shoot back if character intersects shooting axis
1. Player dies if hit by bullet
1. Robots can navigate from one place to another without hitting walls or (usually) hitting each other
1. Animations for robots and player
1. Robots "detect" player through walls and seek them out
1. Randomized level layouts
1. Lives UI
1. Random robot sounds
1. Bonus lives if all robots killed
1. Level is completed on exit; entire screen holds and is scrolled, then new level is loaded
1. Evil Otto appears on timer, with "intruder alert"
1. New levels have color with robots
1. Scaling robot difficulty - detection distance
1. Scaling robot difficulty - movement speed
1. Scaling robot difficulty - firing rate / projectile speed
1. Scaling robot difficulty - no friendly fire
1. Scaling robot difficulty - walking into walls 
