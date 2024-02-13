
#include <stdio.h>

#include "CommandHandlersFactory.h"
#include "CommandProcessingFactory.h"
#include "ParserFactory.h"
#include "ProtocolFactory.h"
#include "ReceiverFactory.h"
#include "UdpSocketFactory.h"

#define SOCK_PORT 31337

int main() {
  struct CommandHandlers *commandHandlers = createCommandHandlers();

  struct CommandProcessing *commandProcessing = createCommandProcessing();

  struct Parser *parser = createParser();

  struct UdpSocket *udpSocket = createUdpSocket();
  int initUdpSocketResult = udpSocket->initSocket(udpSocket);

  struct Protocol *protocol = createProtocol();
  int initProtocolResult =
      protocol->initProtocol(protocol, commandHandlers, commandProcessing, parser);

  struct Receiver *receiver = createReceiver();
  int initReceiverResult = receiver->initReceiver(receiver, udpSocket, protocol);

  if ((initUdpSocketResult == 0) && (initProtocolResult == 0) && (initReceiverResult == 0)) {
    receiver->runReceiver(receiver, SOCK_PORT);

    printf("Run server on port %d\n", SOCK_PORT);

    int c;
    do {
      c = getchar();
    } while (c != 's');

    printf("Stopping server\n");

    receiver->stopReceiver(receiver);
  }

  deleteReceiver(receiver);
  deleteProtocol(protocol);
  deleteUdpSocket(udpSocket);
  deleteParser(parser);
  deleteCommandProcessing(commandProcessing);
  deleteCommandHandlers(commandHandlers);

  return 0;
};