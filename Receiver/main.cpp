#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "ICallback.hpp"
#include "PacketReceiver.hpp"

class BytesCounter final : public ICallback {
public:
  void binaryPacket(const Byte *data, std::size_t size) override { mCountBinaryBytes += size; }

  void textPacket(const Byte *data, std::size_t size) override { mCountTextBytes += size; }

  void print() {
    std::cout << "BinaryBytes=" << mCountBinaryBytes << " TextBytes=" << mCountTextBytes << '\n';
  }

private:
  std::size_t mCountBinaryBytes = 0;
  std::size_t mCountTextBytes = 0;
};

void printBandwidth(double bandwidth) {
  std::cout << "Bandwidth=";
  if (bandwidth > 1024 * 1024 * 1024) {
    std::cout << (bandwidth / (1024 * 1024 * 1024)) << 'G';
  } else if (bandwidth > 1024 * 1024) {
    std::cout << (bandwidth / (1024 * 1024)) << 'M';
  } else if (bandwidth > 1024) {
    std::cout << (bandwidth / 1024) << 'K';
  } else {
    std::cout << bandwidth;
  }
  std::cout << "bit/s\n";
}

int main() {
  PacketReceiver receiver;

  BytesCounter callback;
  receiver.prepare(&callback);

  std::vector<std::vector<Byte>> data;

  {
    std::vector<Byte> bs(1030, 'a');
    data.emplace_back(std::move(bs));
  }

  {
    std::vector<Byte> bs(1000, 'a');
    bs[500] = '\r';
    bs[501] = '\n';
    bs[502] = '\r';
    bs[503] = '\n';
    bs[504] = 0x24;
    bs[505] = 0xA1;
    bs[506] = 0x04;
    bs[507] = 0x00;
    bs[508] = 0x00;
    data.emplace_back(std::move(bs));
  }

  {
    std::vector<Byte> bs(1130, 'a');
    bs[1128] = '\r';
    bs[1129] = '\n';
    data.emplace_back(std::move(bs));
  }

  {
    std::vector<Byte> bs(130, 'a');
    bs[0] = '\r';
    bs[1] = '\n';
    bs[2] = 0x24;
    bs[3] = 0x7F;
    bs[4] = 0x00;
    bs[5] = 0x00;
    bs[6] = 0x00;
    data.emplace_back(std::move(bs));
  }

  std::size_t bytes = 0;
  for (const auto &bs : data) {
    bytes += bs.size();
  }

  const auto start = std::chrono::steady_clock::now();
  for (std::size_t i = 0; i < 30; ++i) {
    for (const auto &bs : data) {
      receiver.receive(bs.data(), bs.size());
    }
  }
  const auto end = std::chrono::steady_clock::now();

  callback.print();

  const std::chrono::duration<double> elapsedSeconds = end - start;
  const auto bandwidth = (30 * bytes * 8) / elapsedSeconds.count();
  printBandwidth(bandwidth);

  return 0;
}