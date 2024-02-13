
#include <stdlib.h>

#include "ProtocolFactory.h"
#include "ProtocolImpl.h"

struct Protocol *createProtocol() {
  ProtocolImpl *protocolImpl = (ProtocolImpl *)malloc(sizeof(ProtocolImpl));
  protocolImpl->commandHandlers = NULL;
  protocolImpl->commandProcessing = NULL;
  protocolImpl->parser = NULL;

  Protocol *protocol = (Protocol *)malloc(sizeof(Protocol));
  protocol->impl = protocolImpl;
  protocol->initProtocol = initProtocol;
  protocol->handleData = handleData;

  return protocol;
}

void deleteProtocol(struct Protocol *protocol) {
  if (protocol != NULL) {
    free(protocol->impl);
    free(protocol);
  }
}
