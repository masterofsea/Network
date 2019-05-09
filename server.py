from socket import *
from threading import Thread


serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', serverPort))
clientList = list()
currentMessage = None

print("The server is ready to receive")

def receive():
global currentMessage
global clientList
while 1:
currentMessage, clientAddress = serverSocket.recvfrom(2048)
print(currentMessage.decode('utf-8'))
if ((clientAddress in clientList)):
continue
clientList.append(clientAddress)


def transmite():
global currentMessage
global clientList
while 1:
if currentMessage is None:
continue
for client in clientList:
temp = ','.join(map(str,client))
mainMessage = temp + ": " + currentMessage.decode('utf-8')
serverSocket.sendto(mainMessage.encode('utf-8'), client)
currentMessage = None


receiveThread = Thread(target=receive)
transmiteThread = Thread(target=transmite)

receiveThread.start()
transmiteThread.start()


receiveThread.join()
transmiteThread.join()
serverSocket.close()