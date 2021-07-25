
#include <main_helper.h>
#include "MiLAB_Spi_Controller.h"

int main(int argc, char** argv) {
  main_helper(argc, argv, new MiLAB_Spi_Controller());
  return 0;
}