//#pragma once
//標準ヘッダのインクルード
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

class Field
{
public:
  Field(char *fileName);
  ~Field();

  int nodeNum;        //ノード数
  double **distance;  //ノード間距離
  double **pheromone; //エッジのフェロモン量
};