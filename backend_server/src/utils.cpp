#include "utils.hpp"

void debug_print(std::string msg) {
  if (DEBUG) {
    std::cout << msg << std::endl;
  }
}
