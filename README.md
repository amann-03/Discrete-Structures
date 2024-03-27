# Discrete-Structures
Implementation of various Graphs Algorithms 

Function-1 : find_junctions()

❖ Initially we made a variable “junctions” to store the no. of junctions in the railway network. 
❖ Then we ran a nested for loop to go through all the edges. For a particular i (i.e particular 
vertex) we made a “count” variable to store the total edges through that vertex.
❖ After the inner for loop gets terminated we get the total “count” for that vertex.
❖ If the “count” is greater than or equal to 4, we get a junction, and hence incrementing the 
junction variable.
❖ At the end we returned the “junction” variable.

Function-2 : sheldons_tour()

❖ First we made two variables named “even” and “odd”, to store how many vertices are of 
even degree and odd degree.
❖ Then , we ran a nested for-loop to go through every edge. For a particular i(i.e particular 
vertex) we made “degree” variable to store the degree of that particular vertex.
❖ Then after calculating degree of a vertex inside outer for-loop, we checked whether it’s even 
or odd and accordingly incremented either even or odd variable.
❖ Then, using the concept of Euler circuit, we know If all the vertex are of even degree, it’s a 
Euler circuit. And if exactly two vertices are odd , then it’s a Euler path.
❖ If not both, it returns false.

Function-3 : warshall()

❖ Initially, we copied the content of adjacency matrix of graph g into closure matrix by running 
nested for-loop. Also introduced variable “len” to store the no. of vertices .
❖ Then, we ran a three nested for-loop, in which outermost loop accounts for the 
matrix(closure) being modified n times(n is no. of vertex), in accordance with Warshall’s 
algorithm by including 1st vertex as internal vertex in the first modification, 1st and 2nd vertex 
as internal vertex in second modification and finally, all the vertices as internal vertex in last 
modification , which gives us the Transitive Closure of the matrix closure.
❖ The core idea of all for-loops is , in the kth modification , it will assign closure[i][j] = 1 iff
already it was 1 in previous modification or closure[i][k] =1 and closure[k][j]=1 after including 
kth vertex as internal vertex.
❖ This whole idea of warshall’s algorithm gave us the transitive closure, which is our required
solution , in which any entry closure[i][j] = 1 indicates that it is possible to travel from ith 
vertex to jth vertex.
❖ To find impossible pairs, we made a variable “count” to keep the count of impossible pairs.
❖ In That we simply ran two nested for-loops to go through every entry of closure matrix and 
keep incrementing the count whenever closure[i][j]=0 which basically denotes the 
impossible pair.
❖ At last, we would half the value of count as it would have counted twice for closure[i][j]=0 
and closure[j][i]=0 , because we want unique pairs.
❖ So, count/2 gives us the final value of impossible pairs.

Function-4 : find_impossible_pairs()

❖ Basically, here I made a variable “org_pair” which stored the count of no. of unique
impossible pairs in our original graph g.
❖ Then , made a variable named “vital” to keep track of vital edges inside nested for-loops.
❖ Inside nested for-loop, for every we found , we first removed the edge and passed the graph 
with modified matrix and if we get the impossible pairs greater than org_pair, it means that 
edge has created a dysconnectivity and it’s a vital edge and hence incrementing vital by 1.
❖ After that again, we added that edge into our graph, so graph doesn’t gets modified in our 
further iterations.
❖ Again, as we checked for every edge twice we would half the value so one edge doesn’t get 
counted twice in vital.
❖ Finally, vital/2 gives us the final no. of vital edges.

Function-5 : find_vital_train_tracks()

The function aims to decide between two types of upgrades (restaurant or maintenance depot) for 
railway stations, ensuring that adjacent stations have different upgrades.
It initializes arrays to track upgrades (upgrades), support Breadth-First Search (BFS) traversal (arr), 
and mark stations for a specific upgrade type (m_or_r).
BFS is employed for graph traversal, marking stations alternately for restaurants (0) and maintenance 
depots (1) to satisfy the upgrading constraints.
During BFS, if a station is connected to another with the same upgrade type, it signifies an inability to 
meet the constraints, leading to the allocation of a cannot_upgrade array indicating failure.
If no conflicts are detected, the function finalizes the upgrades by copying the upgrade plan from 
m_or_r to upgrades, which is then returned.

Function-6 : upgrade_railway_stations()

❖ First, we checked that if city_x and city_y are same vertices, we returned zero.
❖ Then, we made two arrays – one Boolean array “visited[g->n]” all initialized with false and 
second array “dist[g->n]” which will save the distance of all veritces from the city_x.
❖ Then we made visited[city_x] = true as we will start from them. We ran a do-while loop in 
which we ran a nested for-loop in which it will start travelling for first time when i=city_x 
because only visited[city_x] = true initially. So then we will update the value for dist[j] by 1 as 
it is the first level vertex after city_x and made visited[j] true as it is visited.
❖ Similarly, in the further iterations we will have the second level vertices from city_x and 
distances will be 2 bcoz = 1 + 1(this is of first level vertices) and then we will do visited of 
them also true.
❖ We will keep on doing so and ultimately we will have the whole array dist having the 
distances from the city_x.
❖ So, we will return dist[city_y] which we required i.e. the minimum distance between city_x 
and city_y.
❖ Here, on brief view we have used the concept of Breadth first Search(BFS).

Function-7 : railway_capital()

❖ First of all we create an array “dist” of size n(no. of stations). In this array we are going to 
store the sum of minimum distances corresponding to each station.
❖ We first run a for loop which changes the station for which the sum is required. It traverses 
through all stations in order.
❖ Inside the first for loop we declared the variable “sum” which stores the value of minimum 
distances for every iteration of the outer for loop.
❖ The nested for loop traverses through the different stations and calls the “distance” function 
which it keeps on adding to the “sum” variable.
❖ Now all the minimum distances for all the stations have been entered in the array “dist”.
❖ Now we find the minimum value index of the array by running the array through a for loop.
❖ At the end we are returning the index where the value in minimum.

Function-8 : maharaja_express_tour()

maharaja_express_tour is a recursive function used to check if a valid Maharaja Express tour can be 
conducted starting from a given source city, following the constraints of starting and ending at the 
same city, visiting a new city each day, and not traveling the same track twice.
The function iterates over all cities connected to the current city. If a connected city is the source and 
not the immediate previous city, it indicates a potential return to the source, completing the tour.
A visited array tracks cities already included in the tour, ensuring the train does not revisit any city 
except for returning to the source at the end.
For each city that is connected and not visited, the function recursively calls itself, updating the 
current city, previous city, and visited array to reflect the new state.
If the function can return to the source city from a city that is not its direct predecessor, it indicates a 
successful tour path and returns true.
maharaja_express is the main function that determines which cities can serve as valid starting points 
for the tour.
It initializes a visited array, marking the source city as visited, and iterates over all cities connected to 
the source.
For each connected city, it calls maharaja_express_tour. If the tour is successful (returns true), the 
source city is identified as a valid starting point for the Maharaja Express
