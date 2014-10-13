#ifndef Telnet_h
#define Telnet_h

#define IAC   255
#define DO    253
#define DONT  254
#define WILL  251
#define WONT  252
#define SB    250
#define SE    240

#include <Arduino.h>
#include <Ethernet.h>

class Telnet {
  
private :

  void  sendDo(byte cmd);
  void  sendDont(byte cmd);
  void  sendWill(byte cmd);
  void  sendWont(byte cmd);
  void  sendSB(byte cmd, char *data);
  
  void  cmdDo();
  void  cmdDont();
  void  cmdWill();
  void  cmdWont();
  void  cmdSb();
  
  void  command();
  EthernetClient client;

public :

  Telnet(IPAddress ip, uint16 port = 23);
  char  receiveData();
  void  sendData(char c);
  void  sendData(byte *tab, int len);
};

#endif
