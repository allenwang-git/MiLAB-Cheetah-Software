/*!
 * @file main.cpp
 *
 * The main function parses command line arguments and starts the appropriate
 * driver.
 */

#include <main_helper.h>
#include "Lowlevel_Controller.hpp"

int main(int argc, char** argv) {
  main_helper(argc, argv, new Lowlevel_Controller());
  return 0;
}
