#include "Ant.h"
class Ant;

class Colony
{
public:
  Colony(char *filename);
  ~Colony();
  void selectRoute();    //経路の選択
  void renewPheromone(); //フェロモン量を更新
  void printPheromone(); //フェロモン量を表示

  Field *field;  //採餌行動の場
  Ant **ant;     //コロニーのメンバ
  double **nume; //経路選択確率の分子
};
