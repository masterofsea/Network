from socket import *
from threading import Thread

serverName = "127.0.0.1"
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_DGRAM)
clientSocket.bind(('127.0.0.1', 1421))

def scanf():
while 1:
rawMessage = input()
message = rawMessage.encode("utf8")
clientSocket.sendto(message, (serverName, serverPort))


def printf():
while 1:
modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
finallyMessage = modifiedMessage.decode("utf8")
print(finallyMessage)



scanfThread = Thread(target=scanf)
printfThread = Thread(target=printf)

scanfThread.start()
printfThread.start()


scanfThread.join()
printfThread.join()
clientSocket.close()