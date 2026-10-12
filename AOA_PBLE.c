#include <stdio.h>
#include <string.h>

#define MAX 20
#define INF 9999

int graph[MAX][MAX];
int dist[MAX];
int visited[MAX];
int parent[MAX];
char name[MAX][30];

int n = 0, source = -1;

//     Input campus graph 
void inputGraph(){
    int i, j;
    printf("Enter number of locations (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX){
        printf("Invalid number of locations.\n");
        while (getchar() != '\n');
        n = 0;
        source = -1;
        return;
    }

    getchar();

    for (i = 0; i < n; i++){
        printf("Enter location %d: ", i + 1);
        if (fgets(name[i], sizeof(name[i]), stdin) == NULL){
            n = 0;
            source = -1;
            return;
        }

        name[i][strcspn(name[i], "\n")] = '\0';

        if (name[i][0] == '\0'){
            printf("Location name can't be empty.\n");
            n = 0;
            source = -1;
            return;
        }
    }

    printf("\nEnter distances between locations.\n");
    printf("Enter 0 if there is no direct road.\n");
    printf("Enter positive distances only.\n\n");

    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (i == j){
                graph[i][j] = 0;
            }
            else{
                printf("%s to %s: ", name[i], name[j]);

                if (scanf("%d", &graph[i][j]) != 1 || graph[i][j] < 0 || graph[i][j] >= INF){
                    printf("Invalid distance entered.\n");
                    while (getchar() != '\n');
                    n = 0;
                    source = -1;
                    return;
                }

                if (graph[i][j] == 0)
                    graph[i][j] = INF;
            }
        }
    }

    source = 0;
    printf("\nCampus graph entered successfully.\n");
    printf("Default source: %s\n", name[source]);
}

//     Display adjacency matrix 
void displayGraph(){
    int i, j;
    if (n == 0){
        printf("Please enter the campus graph first.\n");
        return;
    }

    printf("\nAdjacency Matrix:\n");

    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (graph[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
}

//     Dijkstra's shortest path algorithm 
void dijkstra(){
    int i, j, min, u;
    for (i = 0; i < n; i++){
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (i = 0; i < n - 1; i++){
        min = INF;
        u = -1;

        for (j = 0; j < n; j++){
            if (!visited[j] && dist[j] < min){
                min = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (j = 0; j < n; j++){
            if (!visited[j] && graph[u][j] != INF && dist[u] + graph[u][j] < dist[j]){
                dist[j] = dist[u] + graph[u][j];
                parent[j] = u;
            }
        }
    }
}

//     Print shortest path recursively 
void printPath(int v){
    if (v == source){
        printf("%s", name[v]);
        return;
    }

    if (parent[v] == -1){
        printf("No Path");
        return;
    }

    printPath(parent[v]);
    printf(" -> %s", name[v]);
}

//     Display shortest paths 
void displayResult(){
    int i;

    if (n == 0 || source == -1){
        printf("Please enter the graph and select a source.\n");
        return;
    }

    dijkstra();

    printf("\nShortest paths from %s:\n\n", name[source]);
    printf("Destination\tDistance\tPath\n");

    for (i = 0; i < n; i++){
        if (i == source)
            continue;

        printf("%s\t\t", name[i]);

        if (dist[i] == INF){
            printf("INF\t\tNo Path\n");
        }
        else{
            printf("%d\t\t", dist[i]);
            printPath(i);
            printf("\n");
        }
    }
}

int main(){
    int choice = 0, s, i;

    do{
        printf("\n===== Campus Navigation =====\n");
        printf("1. Enter campus graph\n");
        printf("2. Display adjacency matrix\n");
        printf("3. Select source location\n");
        printf("4. Run Dijkstra\n");
        printf("5. Display shortest paths\n");
        printf("6. Display distances only\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1){
            printf("Invalid input.\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice){
            case 1:
                inputGraph();
                break;

            case 2:
                displayGraph();
                break;

            case 3:
                if (n == 0){
                    printf("Please enter the graph first.\n");
                    break;
                }

                printf("\nLocations:\n");
                for (i = 0; i < n; i++)
                    printf("%d. %s\n", i + 1, name[i]);

                printf("Select source (1-%d): ", n);

                if (scanf("%d", &s) != 1){
                    printf("Invalid source input.\n");
                    while (getchar() != '\n');
                    break;
                }

                if (s >= 1 && s <= n){
                    source = s - 1;
                    printf("Source selected: %s\n",
                           name[source]);
                }
                else{
                    printf("Invalid source.\n");
                }
                break;

            case 4:
                if (n == 0 || source == -1){
                    printf("Please enter the graph first.\n");
                    break;
                }

                dijkstra();
                printf("\nShortest distances calculated successfully.\n");
                break;

            case 5:
                displayResult();
                break;

            case 6:
                if (n == 0 || source == -1){
                    printf("Please enter the graph first.\n");
                    break;
                }

                dijkstra();

                printf("\nDistance from %s:\n", name[source]);

                for (i = 0; i < n; i++){
                    if (dist[i] == INF)printf("%s : No Path\n", name[i]);
                    else
                        printf("%s : %d\n", name[i], dist[i]);
                }
                break;

            case 7:
                printf("Program ended.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 7);

    return 0;
}
