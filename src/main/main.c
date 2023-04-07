#include "../../tests/include/connections.h"
#include "../probability/include/erdos_renyi.h"
#include <time.h>

int main(void) {
  srand(time(NULL));
  connection_test();
  return 0;
}
