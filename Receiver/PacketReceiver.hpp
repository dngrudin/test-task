#pragma once

#include <list>
#include <memory>

#include "Action.hpp"
#include "Buffer.hpp"
#include "IReceiver.hpp"
#include "PacketState.hpp"

class ICallback;

class PacketReceiver final : public IReceiver {
public:
  void receive(const Byte *data, std::size_t size) override;

  void prepare(ICallback *callback);

private:
  template <typename T, typename... Args> Action *createAction(Args &&...args);

  void sendPackage(const Byte *data, std::size_t size) const;

  ICallback *mCallback = nullptr;

  Buffer mBuffer = {};
  PacketState mPacketState = {};

  Action *mCurrentAction = nullptr;
  Action *mBeginAction = nullptr;
  Action *mComplitedAction = nullptr;

  std::list<Action> mActions;
};