/*Go to the below link(change the api_key as yours)
  https://api.thingspeak.com/update/?api_key=O3OGQLYCTVZHZ685&field2=0
  https://api.thingspeak.com/channels/198279/fields/4/last?api_key=O3OGQLYCTVZHZ685
*/

#include<SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <stdlib.h>

int temp, con = 0;

SoftwareSerial client(2, 3); //RX, TX
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

int  k = 0;
boolean No_IP = false;
String IP = "";
// replace with your SSID and Password
String ssid = "WIN-GCII0CKRUO7 0159";
String pwd = "golapalli98";
// replace with your channel's thingspeak API key
String apiKey = "KBMFL46G976EG81X";
String channel = "211540";


void check4IP(int t1)
{
  int t2 = millis();
  while (t2 + t1 > millis())
  {
    while (client.available() > 0)
    {
      if (client.find("WIFI GOT IP"))
      {
        No_IP = true;
      }
    }
  }
}
void get_ip()
{
  IP = "";
  char ch = 0;
  while (1)
  {
    client.println("AT+CIFSR");
    while (client.available() > 0)
    {
      if (client.find("STAIP,"))
      {
        delay(1000);
        Serial.print("IP Address:");
        while (client.available() > 0)
        {
          ch = client.read();
          if (ch == '+')
            break;
          IP += ch;
        }
      }
      if (ch == '+')
        break;
    }
    if (ch == '+')
      break;
    delay(1000);
  }
  Serial.print(IP);
  lcd.setCursor(0, 1);
  lcd.print(IP);
  lcd.setCursor(15, 1);
  lcd.print(" ");
}
void connect_wifi(String cmd, int t)
{
  int temp = 0, i = 0;
  while (1)
  {
    Serial.println(cmd);
    client.println(cmd);
    while (client.available())
    {
      if (client.find("OK"))
        i = 8;
    }
    delay(t);
    if (i > 5)
      break;
    i++;
  }
  if (i == 8)
    Serial.println("OK");
  else
    Serial.println("Error");
}
void wifi_init()
{
  String connect_to = "";
  connect_wifi("AT", 100);
  connect_wifi("AT+CWMODE=1", 100);
  connect_wifi("AT+CWQAP", 100);
  connect_wifi("AT+RST", 5000);

  check4IP(5000);
  if (!No_IP)
  {
    lcd.setCursor(0, 0);
    lcd.print("Connecting.....");
    lcd.setCursor(0, 1);
    lcd.print("Please wait.....");
    Serial.println("Connecting Wifi....");
    connect_to = "AT+CWJAP=\"";
    connect_to += ssid;
    connect_to += "\",\"";
    connect_to += pwd;
    connect_to += "\"";
    connect_wifi(connect_to, 4000);
  }
  else
  {
    ;
  }
  lcd.setCursor(0, 0);
  lcd.print("Wifi Connected");
  Serial.println("Wifi Connected");
  get_ip();
}

void sendgetstring(String getStr)
{
  int send_status = 0;

  while (!client.find(">"))
  {
    // send data length
    String strn = "AT+CIPSEND=";
    strn += String(getStr.length() + 1);
    client.println(strn);
    Serial.println(strn);
  }
  client.println(getStr);
  Serial.println(getStr);
  delay(500);
}

void setup()
{
  for (int i = 10; i < 14; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  lcd.begin(16, 2);
  lcd.setCursor(4, 0);
  lcd.print("WELCOME");
  lcd.setCursor(1, 1);
  lcd.print("IoT SMART HOME");
  Serial.begin(9600);
  client.begin(9600);
  wifi_init();
  Serial.println("System is Ready..");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("D1=OFF   D2=OFF ");
  lcd.setCursor(0, 1);
  lcd.print("D3=OFF   D4=OFF ");
}

void connectserver(String ip, String port)
{
  char temp;
  while (con == 0)
  {
    // TCP connection
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += ip;    //184.106.153.149 // api.thingspeak.com
    cmd += "\",";
    cmd += port;
    client.println(cmd);
    Serial.println(cmd);

    if (client.find("CONNECT")) {
      temp = client.read();
      temp = client.read();
      temp = client.read();
      temp = client.read();
      String ok = client.readStringUntil('\n');
      Serial.println("Connection OK");
      con = 1;
    }
    else
    {
      temp = client.read();
      temp = client.read();
      Serial.println("CONNECTING ERROR");
      //return;
    }
  }
}
void loop()
{
  //String load_status;
  char str[50];
  String load_status[5];
  char temp;
  int x[5];

  for (int i = 1; i < 5; i++)
  {
    connectserver("184.106.153.149", "80");
    // prepare GET string
    String getStr = "GET /channels/";
    getStr += channel;
    getStr += "/fields/";
    getStr += i;
    getStr += "/last?api_key=";
    getStr += apiKey;
    sendgetstring(getStr);
    delay(3000);
    while (client.available())
    {
      if (client.find("+IPD,"))
      {
        delay(10);
        int len = client.read() - 48;
        temp = client.read();
        load_status[i] = client.readStringUntil('\r');
      }
    }

    //connect_wifi("AT+CIPCLOSE", 2000);

    client.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
    con = 0;
  }
  for (int a = 1; a < 5; a++)
  {
    if (load_status[a] == "1")
    {
      x[a] = 1;
      if (a == 1)
      {
        lcd.setCursor(3, 0);
        lcd.print("ON ");
      }
      else if (a == 2)
      {
        lcd.setCursor(12, 0);
        lcd.print("ON ");
      }
      else if (a == 3)
      {
        lcd.setCursor(3 , 1);
        lcd.print("ON ");
      }
      else if (a == 4)
      {
        lcd.setCursor(12, 1);
        lcd.print("ON ");
      }
    }
    else
    {
      x[a] = 0;
      if (a == 1)
      {
        lcd.setCursor(3, 0);
        lcd.print("OFF");
      }
      else if (a == 2)
      {
        lcd.setCursor(12, 0);
        lcd.print("OFF");
      }
      else if (a == 3)
      {
        lcd.setCursor(3, 1);
        lcd.print("OFF");
      }
      else if (a == 4)
      {
        lcd.setCursor(12, 1);
        lcd.print("OFF");
      }
    }
    Serial.print(load_status[a]);
    Serial.print("   ");
    Serial.println(x[a]);
    digitalWrite(9 + a, x[a]);
  }
  delay(1000);
}

byte ReadStringUART(char *receive_buffer, char terminator)
{
  byte c;
  byte count = 0;

  while (1)
  {
    *receive_buffer = '\0';

    while (!client.available());
    c = client.read();

    if (c == terminator)
      break;

    count++;
    *receive_buffer++ = c;
  }

  return count;
}
