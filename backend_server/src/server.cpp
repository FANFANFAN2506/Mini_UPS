#include <cstdlib>
#include <iostream>

#include "Communicator.hpp"
#include "backend_logic.hpp"
#define HOSTNAME "vcm-30458.vm.duke.edu"
// #define HOSTNAME "vcm-30605.vm.duke.edu"

int main() {
  Communicator comm(HOSTNAME);
  try {
    backend_logic::init_phase(comm);
    backend_logic::operation_phase(comm);
  }
  catch (my_exception & e) {
    std::cout << e.what() << std::endl;
  }
}
