#include <stdlib.h>
#include <stdbool.h>

int maximumSafenessFactor(int** grid, int gridSize, int* gridColSize) {

    int n = gridSize;

    int **dist = (int**)malloc(n * sizeof(int*));
    for(int i=0;i<n;i++){
        dist[i]=(int*)malloc(n*sizeof(int));
        for(int j=0;j<n;j++)
            dist[i][j]=-1;
    }

    int total=n*n;

    int *qx=(int*)malloc(total*sizeof(int));
    int *qy=(int*)malloc(total*sizeof(int));

    int front=0,rear=0;

    // Multi-source BFS initialization
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]==1){
                dist[i][j]=0;
                qx[rear]=i;
                qy[rear]=j;
                rear++;
            }
        }
    }

    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};

    // Multi-source BFS
    while(front<rear){

        int x=qx[front];
        int y=qy[front];
        front++;

        for(int k=0;k<4;k++){

            int nx=x+dx[k];
            int ny=y+dy[k];

            if(nx<0||ny<0||nx>=n||ny>=n)
                continue;

            if(dist[nx][ny]!=-1)
                continue;

            dist[nx][ny]=dist[x][y]+1;

            qx[rear]=nx;
            qy[rear]=ny;
            rear++;
        }
    }

    int low=0,high=2*n;

    while(low<high){

        int mid=(low+high+1)/2;

        if(dist[0][0]<mid || dist[n-1][n-1]<mid){
            high=mid-1;
            continue;
        }

        bool **vis=(bool**)malloc(n*sizeof(bool*));
        for(int i=0;i<n;i++){
            vis[i]=(bool*)calloc(n,sizeof(bool));
        }

        front=rear=0;

        qx[rear]=0;
        qy[rear]=0;
        rear++;
        vis[0][0]=true;

        bool ok=false;

        while(front<rear){

            int x=qx[front];
            int y=qy[front];
            front++;

            if(x==n-1 && y==n-1){
                ok=true;
                break;
            }

            for(int k=0;k<4;k++){

                int nx=x+dx[k];
                int ny=y+dy[k];

                if(nx<0||ny<0||nx>=n||ny>=n)
                    continue;

                if(vis[nx][ny])
                    continue;

                if(dist[nx][ny]<mid)
                    continue;

                vis[nx][ny]=true;

                qx[rear]=nx;
                qy[rear]=ny;
                rear++;
            }
        }

        for(int i=0;i<n;i++)
            free(vis[i]);
        free(vis);

        if(ok)
            low=mid;
        else
            high=mid-1;
    }

    for(int i=0;i<n;i++)
        free(dist[i]);
    free(dist);
    free(qx);
    free(qy);

    return low;
}