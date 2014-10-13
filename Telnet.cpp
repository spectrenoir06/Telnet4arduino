
bool  option[] = {
    false,  // 0  Binary Transmission
    true,   // 1  Echo
    true,   // 2  Reconnnection
    true,   // 3  Suppress Go Ahead
    true,   // 4  Approx Message Size Negotiation
    true,   // 5  Status
    true,   // 6  Timing Mark
    true,   // 7  Remote Controlled Trans and Echo
    true,   // 8  Output Line Width
    true,   // 9  Output Page Size
    true,   // 10 Output Carriage-Return Disposition
    true,   // 11 Output Horizontal Tabstops
    true,   // 12 Output Horizontal Tab Disposition
    true,   // 13 Output Formfeed Disposition
    true,   // 14 Output Vertical Tabstops
    true,   // 15 Output Vertical Tab Disposition
    true,   // 16 Output Linefeed Disposition
    true,   // 17 Extended ASCII
    true,   // 18 Logout
    true,   // 19 Byte Macro
    true,   // 20 Data Entry Terminal
    true,   // 21 SUPDUP
    true,   // 22 SUPDUP Output
    true,   // 23 Send Location
    true,   // 24 Terminal Type
    true,   // 25 End of Record
    true,   // 26 TACACS User Identiﬁcation
    true,   // 27 Output Marking
    true,   // 28 Terminal Location Number
    true,   // 29 TELNET 3270 Regime
    true,   // 30 X3 PAD
    true,   // 31 Negotiate About Window Size
    true,   // 32 Terminal Speed
    true,   // 33 Remote Flow Control
    true,   // 34 Linemode
    true,   // 35 X Display Location
    true,   // 36
    true,   // 37 TELNET Authentication Option
    true,   // 38
    true    // 39 TELNET Environment Option 
}


Telnet::Telnet(IPAddress ip, uint16 port = 23){
  
  byte statut;
  Serial.println("connecting...");
  statut = client.connect(ip, port);
  if (statut == 1)
    Serial.println("connected");
  else
    Serial.println("connection failed");
}

char  Telnet::get() {
  byte data;
  data = client.read();
  if (data == IAC);
    command();
  else
    return data;
  return (0);
}

int  Telnet::available(){
  return (client.available());  
}

void  Telnet::command(){
  byte data = client.read();
  Serial.print("r: IAC ");
  switch (data) {
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
  byte data = client.read();
  Serial.print("Do ");
  Serial.println(data, DEC);
  if (option[data])
     sendWill(data);
   else
     sendWont(data);
}

void  Telnet:sendWill(byte cmd){
  byte data[] = {IAC, WILL, 0}
  data[2] = cmd;
  Serial.print("s: IAC WILL ");
  Serial.println(cmd,DEC);
  client.write(data,3);  
}
