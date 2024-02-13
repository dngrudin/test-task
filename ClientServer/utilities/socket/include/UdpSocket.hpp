
#ifndef UDP_SOCKET_HPP
#define UDP_SOCKET_HPP

#include <cstddef>
#include <stdint.h>
#include <string>

#include <netinet/in.h>
#include <sys/time.h>

class UdpSocket {
public:
  UdpSocket();
  ~UdpSocket();

  bool init();
  bool bind(uint16_t port);
  bool stop();

  bool waitData(timeval timeout);
  std::size_t readData(unsigned char *dataBuffer, std::size_t sizeBuffer);
  std::size_t sendData(unsigned char *dataBuffer, std::size_t sizeBuffer,
                       const std::string &hostname, uint16_t port);

private:
  int mDescriptor;
  sockaddr_in mAddress;
};

#endif // UDP_SOCKET_HPP