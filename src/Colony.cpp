#include "Colony.h"
#include "Ant.h"

//コンストラクタ
//fileName: データセットのファイル名
Colony::Colony(char *fileName)
{
  int i;

  field = new Field(fileName);
  ant = new Ant *[ANT_NUM];

  for (i = 0; i < ANT_NUM; i++)
  {
    ant[i] = new Ant(this);
  }
  nume = new double *[field->nodeNum];
  for (i = 0; i < field->nodeNum; i++)
  {
    nume[i] = new double[field->nodeNum];
  }
}

//デストラクタ
Colony::~Colony()
{
  int i;

  for (i = 0; i < ANT_NUM; i++)
  {
    delete ant[i];
  }
  delete[] ant;
  for (i = 0; i < field->nodeNum; i++)
  {
    delete[] nume[i];
  }
  delete[] nume;
  delete field;
}

//経路を選択する
void Colony::selectRoute()
{
  int i, j;

  //確率の分子を算出
  for (i = 0; i < field->nodeNum; i++)
  {
    for (j = 1; j < i; j++)
    {
      nume[i][j] = pow(field->pheromone[j][i], PHERO_L) * pow(1 / field->distance[i][j], HEU_L);
    }
    for (j = i + 1; j < field->nodeNum; j++)
    {
      nume[i][j] = pow(field->pheromone[i][j], PHERO_L) * pow(1 / field->distance[i][j], HEU_L);
    }
  }

  //経路を選択する
  for (i = 0; i < ANT_NUM; i++)
  {
    ant[i]->selectRoute();
  }
}

//フェロモン量を更新
void Colony::renewPheromone()
{
  int i, j;

  //蒸発させる
  for (i = 0; i < field->nodeNum; i++)
  {
    for (j = i + 1; j < field->nodeNum; j++)
    {
      field->pheromone[i][j] *= 1 - EVA_R;
    }
  }

  //アリによる追加分を加算する
  for (i = 0; i < ANT_NUM; i++)
  {
    ant[i]->putPheromone();
  }
}

//フェロモン量を表示する
void Colony::printPheromone()
{
  int i, j;

  for (i = 0; i < field->nodeNum; i++)
  {
    for (j = 0; j < field->nodeNum; j++)
    {
      printf("%8.3f", field->pheromone[i][j]);
    }
    printf("\n");
  }
}

//ルートを表示
void Colony::printRoute()
{
  //変数定義
  int i, j, k, now, next, nexttmp;
  double tmpmax;
  int route[field->nodeNum];
  bool flag;

  //初期化
  next = 0;
  for (i = 0; i < field->nodeNum; i++)
  {
    route[i] = -1;
  }

  //フェロモンの結果を走査する
  for (i = 0; i < field->nodeNum; i++)
  {

    now = next;
    route[i] = now;
    tmpmax = 0.0;
    for (j = 0; j < field->nodeNum; j++)
    {
      //配列x軸方向への走査
      if (now <= j)
      {
        //過去のルートを調べる
        flag = false;
        for (k = 0; k < field->nodeNum; k++)
        {
          if (route[k] == j)
          {
            flag = true;
          }
        }
        //過去に通っていないノードのうちフェロモン量が多いものを次のノードに
        if (!flag)
        {
          if (tmpmax < field->pheromone[now][j])
          {
            tmpmax = field->pheromone[now][j];
            nexttmp = j;
          }
        }
      }
      //配列y軸方向への走査
      else
      {
        //過去のルートを調べる
        flag = false;
        for (k = 0; k < field->nodeNum; k++)
        {
          if (route[k] == j)
          {
            flag = true;
          }
        }
        //過去に通っていないノードのうちフェロモン量が多いものを次のノードに
        if (!flag)
        {
          if (tmpmax < field->pheromone[j][now])
          {
            tmpmax = field->pheromone[j][now];
            nexttmp = j;
          }
        }
      }
    }
    //次のノードを確定
    next = nexttmp;
  }
  //ルート表示
  printf("Route : ");
  for (i = 0; i < field->nodeNum; i++)
  {
    printf("%d ->", route[i] + 1);
  }
}