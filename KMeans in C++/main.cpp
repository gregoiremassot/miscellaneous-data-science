#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

int ManhattanDist(int X1,int X2,int Y1,int Y2);

int main(int argc, char *argv[])
{
    // Initialisation des coordonnées des points et des centres des clusters
    double Xpoint[9] = {0,2,2,8,5,7,6,1,4};
    double Ypoint[9] = {0,10,5,4,8,5,4,2,9};
    double Xcluster[4] = {0,2,5,1};
    double Ycluster[4] = {0,10,8,2};
    int nbPointsCluster[4] = {0};
    int clusterBelonging[9];

    for(int i=1;i<=10;i++)
    {
        memset(nbPointsCluster, 0, sizeof(nbPointsCluster));
        // Calcul du cluster à associer à chaque point
        for(int j =1; j<= 8;j++)
        {
           int minDist = 100;
           for(int k=1;k<=3;k++)
           {
               if(ManhattanDist(Xcluster[k],Xpoint[j],Ycluster[k],Ypoint[j]) < minDist)
               {
                   minDist = ManhattanDist(Xcluster[k],Xpoint[j],Ycluster[k],Ypoint[j]);
                   clusterBelonging[j] = k;
               }
           }
           nbPointsCluster[clusterBelonging[j]]++;
        }
        // Calcul des nouveaux centres des clusters

        memset(Xcluster, 0, sizeof(Xcluster));
        memset(Ycluster, 0, sizeof(Ycluster));
        for(int j=1;j<=8;j++)
        {
            Xcluster[clusterBelonging[j]] +=  Xpoint[j]/nbPointsCluster[clusterBelonging[j]];
            Ycluster[clusterBelonging[j]] +=  Ypoint[j]/nbPointsCluster[clusterBelonging[j]];
        }
    cout << "---Etape " << i << "---" << endl;
    cout << "Nb de points dans chaque cluster" << endl;
    for(int k = 1;k <=3;k++)
    {
        cout << k << " : " << nbPointsCluster[k] << endl;
    }

    cout << "Appartenance aux clusters" << endl;
    for(int j = 1;j <=8;j++)
    {
        cout << j << " : cluster " << clusterBelonging[j] << endl;
    }
    cout << "Coordonnees de chaque cluster" << endl;
    for(int k = 1;k <=3;k++)
    {
        cout << k << " : X : " << Xcluster[k] << " : Y : " << Ycluster[k] << endl;
    }
    cout << endl;
    }

    return 0;
}

int ManhattanDist(int X1,int X2,int Y1,int Y2)
{
    return(abs(X1-X2) + abs(Y1-Y2));
}
