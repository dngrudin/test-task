
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <stdint.h>

#include "DataPull.hpp"
#include "MD5.hpp"
#include "Time.hpp"
#include "UdpSocket.hpp"

class Client {
public:
  Client();

  bool init(const std::string &serverHostname, uint16_t serverPort);

  void run();

private:
  void sendDataPull(const DataPull &dataPull, size_t &packageNumber,
                    unsigned char *package);
  size_t fillPackage(unsigned char *package, size_t packageNumber,
                     const std::vector<int16_t> &data, Milliseconds &time);

  UdpSocket mUdpSocket;
  std::string mServerHostname;
  uint16_t mServerPort;
  DataPull mDataPull1;
  DataPull mDataPull2;
  MD5 mMD5;
};

#endif // CLIENT_HPP