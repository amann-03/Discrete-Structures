#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

typedef struct Graph {
    int n; // Size of the graph
    int** adj; // Adjacency matrix
    char** station_names; // Array of station names
} Graph;

/**
 * This function has been pre-filled. It reads the input testcase 
 * and creates the Graph structure from it.
*/
Graph* create_graph(char input_file_path[]) {
    FILE* f = fopen(input_file_path, "r");
    Graph* g = (Graph*)malloc(sizeof(Graph));
    // Size of graph
    fscanf(f, "%d", &(g->n));
    // Names of stations
    g->station_names = (char**)malloc(g->n * sizeof(char*));
    for(int i = 0; i < g->n; i++) {
        g->station_names[i] = (char*)malloc(100 * sizeof(char));
        fscanf(f, "%s", g->station_names[i]);
    }
    // Adjacency matrix
    g->adj = (int**)malloc(g->n * sizeof(int*));
    for(int i = 0; i < g->n; i++) {
        g->adj[i] = calloc(g->n, sizeof(int));
    }
    int edges;
    fscanf(f, "%d", &edges);
    for(int i = 0; i < edges; i++) {
        int x, y;
        fscanf(f, "%d%d", &x, &y);
        g->adj[x][y] = 1;
        g->adj[y][x] = 1;
    }
    fclose(f);
    return g;
}
// ---------------------------DO NOT MODIFY (End)------------------------------

/**
 * Q.1 
 * Return the number of junctions.
*/
int find_junctions(Graph* g) {
    int junctions = 0;
    for(int i=0; i < g->n; i++){
        int count =0;
        for(int j=0; j < g->n; j++){
            if(g->adj[i][j] == 1){
                count++;
            }
        }
        if(count >= 4){
            junctions++;
        }
    }
    return junctions;
}

bool sheldons_tour(Graph* g, bool SAME_STATION) {
    int even=0;
    int odd=0;
    for(int i=0; i<g->n; i++){
        int degree=0;
        for(int j=0; j<g->n; j++){
            if(g->adj[i][j]==1)degree++;
        }
        if(degree%2 ==0)even++;
        else odd++;
    }
    if(even==g->n){
        if(SAME_STATION)return true;
        else return false;
    }
    else if(odd==2){
        if(!SAME_STATION)return true;
        else return false;
    }
    else{
        return false;
    }
}

int** warshall(Graph* g) {
    // Do not modify or delete pre-filled code!
    int** closure = (int**)malloc(g->n * sizeof(int*));
    for(int i = 0; i < g->n; i++) {
        closure[i] = calloc(g->n, sizeof(int));
    }

    //Code goes here
    int len = g->n;
    for(int i=0; i<g->n; i++){
        for(int j=0;j<g->n; j++){
            closure[i][j] = g->adj[i][j];
        }
    } 

    for(int k=0; k<len; k++){
        for(int i=0; i<len; i++){
            for(int j=0; j<len; j++){
                if(closure[i][k]==1 && closure[k][j]==1){
                    closure[i][j] = 1;
                }
                else{
                    continue;
                }
            }
        }
    }

    //Here, W(n-1) is our transitive closure
    return closure; // Do not modify
}

int find_impossible_pairs(Graph* g) {
    int** closure = warshall(g); // Do not modify
    int count = 0, len = g->n;
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            if(closure[i][j]==0){
                count++;
            }
            else{
                continue;
            }
        }
    }    
    return count/2;  // as same pair of cities are counted twice
}

int find_vital_train_tracks(Graph* g) {

    int org_pair = find_impossible_pairs(g);
    int vital = 0;
    for(int i=0; i<g->n; i++){
        for(int j=0; j<g->n; j++){    
            if(g->adj[i][j]==1){ // once a edge is found, we will delete it and check if reamining graph is still connected or not
                g->adj[j][i]=0;
                g->adj[i][j]=0;
                if(find_impossible_pairs(g) > org_pair){
                    vital++;
                }
                g->adj[j][i]=1;
                g->adj[i][j]=1;
            }
        }
    }
    return vital/2; // coz. we have checked twice for every edge 
}

int* upgrade_railway_stations(Graph* g) { 
    int* upgrades = calloc(g->n, sizeof(int));  // Do not modify

    // Code goes here
    int* arr = calloc(g->n, sizeof(int));
    int front  = -1;
    int  rear = -1;

    int* m_or_r = calloc(g->n, sizeof(int));
    for (int i = 0; i < g->n; ++i) {
        m_or_r[i] = -1;
    }
    
    for (int i = 0; i < g->n; ++i) {
        if (m_or_r[i] == -1) {
            front = 0;
            rear = 0;
            arr[rear++] = i;
            m_or_r[i] = 0;

            while (front != rear) {
                int current = arr[front++];
                for (int j = 0; j < g->n; ++j) {
                    if (g->adj[current][j]) {
                        if (m_or_r[j] == -1) {
                            m_or_r[j] = 1 - m_or_r[current];
                            arr[rear++] = j;
                        } else if (m_or_r[j] == m_or_r[current]) {
                            free(upgrades);
                            free(m_or_r);
                            int* cannot_upgrade = malloc(g->n * sizeof(int));
                            for (int k = 0; k < g->n; ++k) {
                                cannot_upgrade[k] = -1;
                            }
                            free(arr);
                            return cannot_upgrade;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < g->n; ++i) {
        upgrades[i] = m_or_r[i];
    }

    free(m_or_r);
    free(arr);
    return upgrades; // Do not modify
}



int distance(Graph* g, int city_x, int city_y) {
    
    if (city_x == city_y) return 0;

    bool visited[g->n];
    for(int i=0; i<g->n; i++) visited[i] = false;
    visited[city_x] = true;

    int dist[g->n];
    for (int i=0; i<g->n; i++) dist[i] = -1;
    dist[city_x] = 0;

    bool moveon;
    do{
        moveon = false;
        for (int i=0; i<g->n; i++) {
            for (int j=0; j<g->n; j++) {
                if (g->adj[i][j] && visited[i] && !visited[j]) {
                    dist[j] = dist[i] + 1;
                    visited[j] = true;

                    if (j==city_y) return dist[j]; 
                    moveon = true;
                }
            }
        }

    }while(moveon);

    return dist[city_y];
}

int railway_capital(Graph* g) {
    int dist[g->n];
    for(int i=0; i<g->n; i++)
    {
        int sum=0;
        for(int j=0;j<g->n;j++)
        {
            sum+=distance(g,i,j);
        }
        dist[i]=sum;

    }

    int min_dist = dist[0];
    int k=0;
    for(int j=0; j<g->n; j++){
        if(dist[j] < min_dist){
            min_dist = dist[j];
            k = j;
        }
    }
    return k;
}

bool maharaja_express_tour(Graph* g, int source, int current_city, int previous_city, int* visited) {
    for (int i=0; i<g->n; i++){
        if (g->adj[current_city][i]){
            if (i == source && i != previous_city) return true;
            else{
                if (!visited[i]){
                    visited[i] = 1;
                    if(maharaja_express_tour(g, source, i, current_city, visited)) return true;
                }
            }
        }
    }
    return false;
}

bool maharaja_express(Graph* g, int source) {
    int* visited = (int*)malloc(g->n * sizeof(int)); 
    for(int i = 0; i < g->n; i++) {
        visited[i] = 0;
    }
    // Hint: Call the helper function and pass the visited array created here.
    visited[source] = 1;

    for (int i=0; i<g->n; i++){
        if (g->adj[source][i]){
            visited[i] = 1;
            if (maharaja_express_tour(g, source, i, source, visited)) return true;
        }
    }
    return false;
}


int main() {
    char input_file_path[100] = "testcase_2.txt"; // Can be modified
    Graph* g = create_graph(input_file_path); // Do not modify
    
    // code goes here
    // Q.1
    int junctions = find_junctions(g);
    printf("Number of junctions = %d\n",junctions);
    // Q.2
    bool connect1 = sheldons_tour(g,true);
    bool connect2 = sheldons_tour(g,false);

    if(connect1) printf("Sheldon's tour (ending in same city as start) = POSSIBLE.\n");
    else printf("Sheldon's tour (ending in same city as start) = IMPOSSIBLE.\n");
    if(connect2) printf("Sheldon's tour (ending in different city as start) = POSSIBLE.\n");
    else printf("Sheldon's tour (ending in different city as start) = IMPOSSIBLE.\n");
    //Q.3
    int pairs = find_impossible_pairs(g);
    printf("Impossible to travel city pairs = %d\n",pairs);
    //Q.4
    int vitals = find_vital_train_tracks(g);
    printf("Number of vital train tracks = %d\n\n",vitals);
    //Q.5
    printf("RAILWAY STATION UPGRADES.\n");
    int* modify = calloc(g->n, sizeof(int));
    modify = upgrade_railway_stations(g);
    for(int i=0; i<g->n; i++){
        if(modify[i]==1) printf("%s = Restaurant\n",g->station_names[i]);
        else printf("%s = Maintenance Depot\n",g->station_names[i]);
    }
    printf("\n");
    //Q.6
    int dist = distance(g,3,5);
    printf("Distance between %s and %s = %d\n",g->station_names[3],g->station_names[5],dist);
    //Q.7
    int cap = railway_capital(g);
    printf("Railway Capital = %s\n",g->station_names[cap]);
    //Q.8
    int i =2;
    bool tour = maharaja_express(g,i);
    if(tour) printf("Maharaja Express tour starting from %s = POSSIBLE",g->station_names[i]);
    else printf("Maharaja Express tour starting from %s = IMPOSSIBLE",g->station_names[i]);

    return 0;
}

