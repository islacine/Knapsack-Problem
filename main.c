#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/***
	Guedouari Mohamed 
	Mestoui Yacine
	TPGO 2CS
	2018/2019
				***/

int max(int a, int b) { return (a > b)? a : b; }

//*****************************************************************************//
// Fonction recursive qui traite le probleme du sac a dos avec un seul critaire
int sac_a_dos2d_recursive(int w, int wt[], int val[], int n){
    if(n==0 || w==0)
    {
        return 0;
    }else
    {
       if(wt[n-1]>w)
        {
            return sac_a_dos2d_recursive(w, wt, val, n-1);
        }else
        {
            return max(val[n-1] + sac_a_dos2d_recursive(w - wt[n-1], wt, val, n-1),
                    sac_a_dos2d_recursive(w, wt, val, n-1));
        }
    }
}


//*****************************************************************************//
// Fonction recursive qui traite le probleme du sac a dos avec deux critaires
int sac_a_dos3d_recursive(int w, int wt[],int v,int vol[], int val[], int n){
    if(n==0 || w==0)
    {
        return 0;
    }else
    {
       if(wt[n-1]>w || vol[n-1]>v )
        {
            return sac_a_dos3d_recursive(w, wt,v,vol,val, n-1);
        }else
        {
            return max(val[n-1] + sac_a_dos3d_recursive(w - wt[n-1], wt,v-vol[n-1],vol, val, n-1),
                    sac_a_dos3d_recursive(w, wt,v,vol, val, n-1));
        }
    }
}


//********************************************************************************//
// Algorithme dynamique qui traite le probleme du sac a dos avec un seul critaire
int sac_a_dos2d_dynamique(int W, int wt[], int val[], int n)
{
   int i, w;
   int **K;

   K = (int **) malloc (sizeof(int **)*(n+1));
   for (int h = 0; h < n+1; h++) 
   {
	K[h] = (int *) malloc(sizeof(int)*(W+1));
   }

   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }

   int res = K[n][W];
   w = W; 
   for (i = n; i > 0 && res > 0; i--) { 
          
       // either the result comes from the top 
       // (K[i-1][w]) or from (val[i-1] + K[i-1] 
       // [w-wt[i-1]]) as in Knapsack table. If 
       // it comes from the latter one/ it means  
       // the item is included. 
       if (res == K[i - 1][w])  
           continue;         
       else { 
  
           // This item is included. 
           printf("%d ", wt[i - 1]); 
              
           // Since this weight is included its  
           // value is deducted 
           res = res - val[i - 1]; 
           w = w - wt[i - 1]; 
       } 
   }
   return K[n][W];
}



//*************************************************************************************//
// Algorithme dynamique qui traite le probleme du sac a dos avec deux critaires
int sac_a_dos3d_dynamique(int W, int wt[],int P,int vol[], int val[], int n)
{
   int i,w,k;
   int ***K;

   K = (int ***) malloc (sizeof(int ***)*(n+1));
   for (int h = 0; h < n+1; h++) 
   {
	K[h] = (int **) malloc(sizeof(int*)*(W+1));
	for (int r = 0; r < (W+1); r++) 
	{
		K[h][r] = (int *) malloc(sizeof(int)*(P+1));
	}
   }

   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           for(k = 0; k <= P ; k++)
            {
                if (i==0 || w==0 || k==0)
                {
                    K[i][w][k] = 0;
                }else if (wt[i-1] <= w && vol[i-1]<=k)
                {
                    K[i][w][k] = max(val[i-1] + K[i-1][w-wt[i-1]][k-vol[i-1]],  K[i-1][w][k]);
                }else
                {
                    K[i][w][k] = K[i-1][w][k];
                }

            }

       }
   }
   int res = K[n][W][P];
   w = W; 
   k = P;
   for (i = n; i > 0 && res > 0; i--) { 
          
       // either the result comes from the top 
       // (K[i-1][w]) or from (val[i-1] + K[i-1] 
       // [w-wt[i-1]]) as in Knapsack table. If 
       // it comes from the latter one/ it means  
       // the item is included. 
       if (res == K[i - 1][w][k])  
           continue;         
       else { 
  
           // This item is included. 
           printf("%d %d \n", wt[i - 1] , vol[i - 1]); 
              
           // Since this weight is included its  
           // value is deducted 
           res = res - val[i - 1]; 
           w = w - wt[i - 1]; 
	   k = k - vol[i - 1]; 
       } 
   }
   return K[n][W][P];
}


//*****************************************************************************//
int main()
{
    int val[] = {6,8,14,6,13,17,10,4,5,11,26,35,02,1,2,7,15,17,30,3};
    int wt[] = {20,30,50,20,40,60,30,10,14,36,72,86,5,3,7,23,49,57,69,12};
    int vol[] = {10,15,25,10,20,30,15,5,7,18,36,43,3,2,4,12,25,29,35,6};
    int V=300;
    int W =520;


    struct timeval tv1, tv2;
    long t;

    int n=sizeof(val)/sizeof(val[0]);

    gettimeofday(&tv1,NULL);
    printf("2d recursive = %d",sac_a_dos2d_recursive(W, wt, val, n));
    gettimeofday(&tv2,NULL);
    t = (tv2.tv_sec - tv1.tv_sec)*1000000 + (tv2.tv_usec - tv1.tv_usec);
    printf("\t\ttemps d'execution = %ld ms\n", t);

    gettimeofday(&tv1,NULL);
    printf("\n2d dynamique = %d",sac_a_dos2d_dynamique(W, wt, val, n));
    gettimeofday(&tv2,NULL);
    t = (tv2.tv_sec - tv1.tv_sec)*1000000 + (tv2.tv_usec - tv1.tv_usec);
    printf("\t\ttemps d'execution = %ld ms\n", t);
	
    gettimeofday(&tv1,NULL);
     printf("\n3d recursive = %d ",sac_a_dos3d_recursive(W, wt,V,vol, val, n));
    gettimeofday(&tv2,NULL);
    t = (tv2.tv_sec - tv1.tv_sec)*1000000 + (tv2.tv_usec - tv1.tv_usec);
    printf("\t\ttemps d'execution = %ld ms\n", t);


    gettimeofday(&tv1,NULL);
    printf("\n3d dynamique = %d ",sac_a_dos3d_dynamique(W,wt,V,vol,val,n));
    gettimeofday(&tv2,NULL);
    t = (tv2.tv_sec - tv1.tv_sec)*1000000 + (tv2.tv_usec - tv1.tv_usec);
    printf("\t\ttemps d'execution = %ld ms\n", t);

    return 0;
}
