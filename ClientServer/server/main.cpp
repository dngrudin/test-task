
#include <iostream>

#include "Server.hpp"

#define SERVER_PORT 31337

int main() {
  Server server;
  if (server.init(SERVER_PORT)) {
    std::cout << "Server run: port " << SERVER_PORT << '\n';
    server.run();
  } else {
    std::cerr << "Server not initialized\n";
  }

  return 0;
}
