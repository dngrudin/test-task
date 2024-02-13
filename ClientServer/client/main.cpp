#include <iostream>

#include "Client.hpp"

#define SERVER_NAME "127.0.0.1"
#define SERVER_PORT 31337

int main() {
  Client client;

  if (client.init(SERVER_NAME, SERVER_PORT)) {
    std::cout << "Client run\n";
    client.run();
  }

  return 0;
}
