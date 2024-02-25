#include <cstring>
#include <utility>

#include "Action.hpp"
#include "BinarySizeParsing.hpp"
#include "FindBinaryEnd.hpp"
#include "FindTextEnd.hpp"
#include "ICallback.hpp"
#include "PacketReceiver.hpp"
#include "PakageComplete.hpp"
#include "TypeDetection.hpp"

void PacketReceiver::prepare(ICallback *callback) {
  mCallback = callback;

  mActions.clear();

  auto pakageComplete = createAction<PakageComplete>();
  auto findBinaryEnd = createAction<FindBinaryEnd>(pakageComplete, mPacketState);
  auto binarySizeParsing = createAction<BinarySizeParsing>(findBinaryEnd, mPacketState);
  auto findTextEnd = createAction<FindTextEnd>(pakageComplete, mPacketState);
  auto typeDetection = createAction<TypeDetection>(binarySizeParsing, findTextEnd, mPacketState);

  mBeginAction = typeDetection;
  mComplitedAction = pakageComplete;

  mCurrentAction = mBeginAction;
}

void PacketReceiver::receive(const Byte *data, std::size_t size) {
  if (size == 0 || !data)
    return;

  PayloadRange payloadRange{};

  std::size_t offset = 0;
  while (offset < size) {
    const auto nextAction = mCurrentAction->run(data, size, offset, payloadRange);
    if (nextAction == mComplitedAction) {
      if (mBuffer.getSize()) {
        if (mPacketState.moveBack) {
          mBuffer.moveBack(mPacketState.moveBack);
          mPacketState.moveBack = 0;
        }

        if (payloadRange.isValid()) {
          mBuffer.append(data + payloadRange.begin, payloadRange.end - payloadRange.begin + 1);
        }
        sendPackage(mBuffer.getData(), mBuffer.getSize());
      } else if (payloadRange.isValid()) {
        sendPackage(data + payloadRange.begin, payloadRange.end - payloadRange.begin + 1);
      }

      payloadRange = {};

      mBuffer.reset();
      mPacketState = {};

      mCurrentAction = mBeginAction;
    } else if (nextAction != Action::Continue) {
      mCurrentAction = nextAction;
    }
  }

  if (mPacketState.moveBack) {
    mBuffer.moveBack(mPacketState.moveBack);
    mPacketState.moveBack = 0;
  }

  if (payloadRange.isValid()) {
    mBuffer.append(data + payloadRange.begin, payloadRange.end - payloadRange.begin + 1);
  }
}

void PacketReceiver::sendPackage(const Byte *data, std::size_t size) const {
  if (!mCallback)
    return;

  switch (mPacketState.type) {
  case PacketType::Binary:
    mCallback->binaryPacket(data, size);
    break;

  case PacketType::Text:
    mCallback->textPacket(data, size);
    break;

  default:
    break;
  }
}

template <typename T, typename... Args> Action *PacketReceiver::createAction(Args &&...args) {
  mActions.emplace_back(T{std::forward<Args>(args)...});
  return &mActions.back();
}