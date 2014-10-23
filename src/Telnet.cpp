
#include "Telnet.h"

bool  option[] = {  // It's all the telnet option true if arduino accepte the option else false
    false,  // 0  Binary Transmission
    false,  // 1  Echo
    false,  // 2  Reconnnection
    true,   // 3  Suppress Go Ahead
    false,  // 4  Approx Message Size Negotiation
    true,   // 5  Status
    false,  // 6  Timing Mark
    false,  // 7  Remote Controlled Trans and Echo
    false,  // 8  Output Line Width
    false,  // 9  Output Page Size
    false,  // 10 Output Carriage-Return Disposition
    false,  // 11 Output Horizontal Tabstops
    false,  // 12 Output Horizontal Tab Disposition
    false,  // 13 Output Formfeed Disposition
    false,  // 14 Output Vertical Tabstops
    true,   // 15 Output Vertical Tab Disposition
    false,  // 16 Output Linefeed Disposition
    false,  // 17 Extended ASCII
    false,  // 18 Logout
    false,  // 19 Byte Macro
    false,  // 20 Data Entry Terminal
    false,  // 21 SUPDUP
    false,  // 22 SUPDUP Output
    false,  // 23 Send Location
    true,   // 24 Terminal Type
    false,  // 25 End of Record
    false,  // 26 TACACS User Identiﬁcation
    false,  // 27 Output Marking
    false,  // 28 Terminal Location Number
    false,  // 29 TELNET 3270 Regime
    false,  // 30 X3 PAD
    true,   // 31 Negotiate About Window Size
    false,  // 32 Terminal Speed
    true,   // 33 Remote Flow Control
    false,  // 34 Linemode
    false,  // 35 X Display Location
    false,  // 36
    false,  // 37 TELNET Authentication Option
    false,  // 38
    false,  // 39 TELNET Environment Option
};


Telnet::Telnet(IPAddress ip, uint16_t port, byte mac[]){
  byte statut;
  Serial.println("init ethernet");
  Ethernet.begin(mac);
  delay(500);
  Serial.println("connecting...");
  statut = client.connect(ip, port);
  if (statut == 1)
    Serial.println("connected");
  else
    Serial.println("failed");


}

Telnet::Telnet(){

};

char  Telnet::receiveData() {
	if (client.available()){
	  byte data = client.read();    // read byte from server
	  Serial.print(data,HEX);
	  Serial.print(" ");
	  /*if (data == IAC)              // if start of a commande
		command();
	  else                          // if juste a printable caractere
		return data;                // return char
	  */}
	//return (0);
}

int  Telnet::available(){
  return (client.available());
}

void  Telnet::command(){
  byte data = client.read();  // read second byte from the commande
  Serial.print("r: IAC ");
  switch (data) {             // swith with the 4 cmd possible
    case(DO) :
      cmdDo();
      break;
    case(DONT) :
      cmdDont();
      break;
    case(WILL) :
      cmdWill();
      break;
    case(WONT) :
      cmdWont();
      break;
    case(SB) :
      cmdSb();
      break;
  }
}

void  Telnet::cmdDo(){
  byte data = client.read();    // read the third byte
  Serial.print("Do ");
  Serial.println(data, DEC);
  if (option[data])            // if the option is permitted send Will
     sendWill(data);
   else
     sendWont(data);          // else send wont
}

void  Telnet::cmdDont(){
  byte data = client.read();    // read the third byte
  Serial.print("Dont ");
  Serial.println(data, DEC);
  if (!option[data])            // if the option is permitted send Will
     sendWill(data);
   else
     sendWont(data);          // else send wont
}

void  Telnet::cmdWill(){
  byte data = client.read();    // read the third byte
  Serial.print("Will ");
  Serial.println(data, DEC);
}

void  Telnet::cmdWont(){
  byte data = client.read();    // read the third byte
  Serial.print("Wont ");
  Serial.println(data, DEC);
}

void  Telnet::cmdSb(){
  byte data1 = client.read();    // read the third byte
  byte data2 = 0;
  Serial.print("Sb ");
  Serial.print(data1, DEC);
  Serial.print(" ");
  while ((data1 != IAC) && (data2 != SE)){
	data2 = data1;
	data1 = client.read();
	Serial.print(data1);
  }
  Serial.println(" IAC SE");
}


void  Telnet::sendWill(byte option){
  byte data[] = {IAC, WILL, option};
  Serial.print("s: IAC WILL ");
  Serial.println(option, DEC);
  client.write(data,3);
}

void  Telnet::sendWont(byte option){
  byte data[] = {IAC, WONT, option};
  Serial.print("s: IAC WONT ");
  Serial.println(option, DEC);
  client.write(data,3);
}
