
#include <iostream>
#include <unistd.h>

#include "Constants.hpp"
#include "DataConverter.hpp"

#include "Client.hpp"

#define DATA_PULL_SIZE 1000
#define SHORT_WAIT_MICROSECONDS (10 * 1000)
#define LONG_WAIT_MICROSECONDS (10 * 1000 * 1000)

Client::Client()
    : mUdpSocket(), mServerHostname(""), mServerPort(0),
      mDataPull1(DATA_PULL_SIZE), mDataPull2(DATA_PULL_SIZE), mMD5() {}

bool Client::init(const std::string &serverHostname, uint16_t serverPort) {
  bool result = false;
  if (mUdpSocket.init()) {
    mServerHostname = serverHostname;
    mServerPort = serverPort;

    mDataPull1.generate();
    mDataPull2.generate();

    result = true;
  }
  return result;
}

void Client::run() {
  size_t packageNumber = 0;
  unsigned char *package = new unsigned char[BUFFER_BYTES];

  sendDataPull(mDataPull1, packageNumber, package);

  usleep(LONG_WAIT_MICROSECONDS);

  sendDataPull(mDataPull2, packageNumber, package);

  delete[] package;
}

void Client::sendDataPull(const DataPull &dataPull, size_t &packageNumber,
                          unsigned char *package) {
  for (size_t i = 0; i < dataPull.count(); ++i) {
    if (i) {
      usleep(SHORT_WAIT_MICROSECONDS);
    }

    packageNumber++;
    const std::vector<int16_t> &data = dataPull.get(i);

    Milliseconds time;
    size_t packageSize = fillPackage(package, packageNumber, data, time);

    if (mUdpSocket.sendData(package, packageSize, mServerHostname,
                            mServerPort) > 0) {
      std::cout << "Send: " << packageNumber << ' ' << time << '\n';
    }
  }
}

size_t Client::fillPackage(unsigned char *package, size_t packageNumber,
                           const std::vector<int16_t> &data,
                           Milliseconds &time) {
  unsigned char *offset = package;
  offset = int64ToBuffer(packageNumber, offset);

  unsigned char *timeOffset = offset;
  offset += TIME_BYTES;

  unsigned char *dataOffset = offset;
  offset =
      int16ArrayToBuffer((const uint16_t *)data.data(), data.size(), offset);

  mMD5.prepare();
  mMD5.update(dataOffset, offset - dataOffset);
  mMD5.final(offset);
  offset += MD5_BYTES;

  time = getCurrentTime();
  int64ToBuffer(time, timeOffset);

  return offset - package;
}