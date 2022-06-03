#include "Colony.h"
#include "Ant.h"

int main()
{
  int i;
  Colony *colony;
  srand((unsigned int)time(NULL));

  char tmpname[] = "sampledata.csv";
  colony = new Colony(tmpname);
  for (i = 1; i < REPEAT_NUM; i++)
  {
    colony->selectRoute();
    colony->renewPheromone();
  }
  colony->printPheromone();
  colony->printRoute();
  delete colony;

  return 0;
}