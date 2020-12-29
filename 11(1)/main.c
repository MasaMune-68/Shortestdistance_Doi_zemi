#include <stdio.h>
#include <stdbool.h>
#define N 9 /* 地点の数 */

int main() /* graph2.datのデータ */
{
  int Distance[N][N]={
      {0,3,-1,5,-1,-1,-1,-1,-1}, /* 1 */
      {3,0,2,-1,4,-1,-1,-1,-1}, /* 2 */
      {-1,2,0,-1,-1,4,-1,-1,-1}, /* 3 */
      {5,1,-1,0,-1,-1,2,3,-1}, /* 4 */
      {-1,4,-1,-1,0,1,-1,-1,-1}, /* 5 */
      {-1,-1,4,-1,1,0,-1,2,5}, /* 6 */
      {-1,-1,-1,2,-1,-1,0,2,-1}, /* 7 */
      {-1,-1,-1,3,-1,2,2,0,4,}, /* 8 */
      {-1,-1,-1,-1,-1,5,-1,4,0} /* 9 */
  };
  
  int nPoint=N;/* 地点の数 */
  int sp;/* 出発地の地点番号 */
  int dp;/* 目的地の地点番号 */
  
  printf("出発地の地点番号を入力してください ==> ");
  scanf("%d",&sp);
  
  printf("目的地の地点番号を入力してください ==> ");
  scanf("%d",&dp);
  

  int sRoute[nPoint];
  int sDist;
  

  int pDist[nPoint];/* 出発地から各地点までの最短距離を設定する配列 */
  int pRoute[nPoint];
  bool pFixed[nPoint];/* 出発地から各地点までの最短距離が確定しているかどうかを識別するための配列 */
  int sPoint,i,j,newDist;
  
  sDist=99999;
  
  for(i=0;i<nPoint;i++){
    sRoute[i]=-1;
    pDist[i]=99999;
    pFixed[i]=false;
  }
  
  pDist[sp]=0;
  
  while(true){ /* 最短経路探索処理 */
    i=0;
    while(i<nPoint){/* 未確定の地点を1つ探す */
      if(pFixed[i]==0){
        break; /* 再内側の繰り返しから抜ける */
      }
      i=i+1;
    }
    
    if(i==nPoint){ /* 出発地から全ての地点までの最短経路が確定していれば */
      break; /* 最短経路探索処理を抜ける */
    }
    
    for(j=i+1;j<nPoint;j++){ /* 最短距離がより短い地点を探す */
      if((pFixed[j]==0) && (pDist[j] < pDist[i])){
        i=j;
      }
    }
    
    sPoint=i;
    pFixed[sPoint]=true; /* 出発地からの最短距離を確定する */
    
    for(j=0;j<nPoint;j++){
      if((Distance[sPoint][j]>0) && (pFixed[j]==0)){
        newDist=pDist[sPoint]+Distance[sPoint][j];
        if(newDist<pDist[j]){
          pDist[j]=newDist;
          pRoute[j]=sPoint;
        }
      }
    }
  }
  
  sDist=pDist[dp];
  j=0;
  i=dp;
  while(i!=sp){
    sRoute[j]=i;
    i=pRoute[i];
    j=j+1;
  }
  sRoute[j]=sp;
  
  /* 表示 */
  printf("出発地から目的地までの最短経路\n");
  for(i=j;i>=0;i--){
    printf("%d,",sRoute[i]);
  }
  printf("\n出発地から目的地までの最短距離sDist = %d\n",sDist);
  
  return 0;
}
