#include <SPI.h>             // library allows to communicate with SPI devices
#include <MFRC522.h>        // library for read/write a RFID card or tag (include this in library)
#include <LiquidCrystal.h> // lcd library file

// Pin Definitions 
#define LCD_PIN_RS 3
#define LCD_PIN_E	2
#define LCD_PIN_DB4	14
#define LCD_PIN_DB5	15 
#define LCD_PIN_DB6	16
#define LCD_PIN_DB7	17 
#define SS_PIN 10 //RX slave select
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.


// Global variables and defines

// object initialization
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);

byte card_ID[4]; //card UID size 4byte
byte Name1[4]={0xFA,0x89,0x6C,0x2E};//first UID card
byte Name2[4]={0x6A,0x6E,0x51,0x83};//second UID card

//number of cards you have 
int NumbCard[2];//this array content the number of cards. in my case i have just two cards.
int j=0;        

int const YellowLed=7;
int const GreenLed=6;
int const RedLed=5;
int const Buzzer=4;

String Name;//user name
String Section;//user section
String Branch;//user branch
String USN;//user USN ID
String reg;//user roll number
String Mail;//user college enrolled mail
long Contact;//user contact number
int n ;//The number of card you want to detect (optional)  

void setup() {
   
  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(YellowLed,OUTPUT);
  pinMode(Buzzer,OUTPUT);

  lcd.setCursor(0, 0); //LCD setup with number of columns and rows  
  lcd.begin(16, 2);//lcd characters
  
  digitalWrite(RedLed, HIGH);
  digitalWrite(YellowLed, HIGH);
  digitalWrite(GreenLed, HIGH);
  delay(100);
  
  digitalWrite(Buzzer,HIGH); 
  delay(200);  
  
  lcd.print("RFID");//Print a message to the LCD.
  lcd.setCursor(0, 1); // cursor position change 
  lcd.print("PLEASE WAIT");    
  digitalWrite(Buzzer,LOW);
  delay(10);   
  delay(7000);  
  lcd.clear();
  delay(100);
  
  digitalWrite(YellowLed, LOW);
  digitalWrite(GreenLed, LOW); 
  delay(100);   

  lcd.print("INITIALISATION");
  lcd.setCursor(0, 1); 
  lcd.blink();
  delay(100);  
  lcd.print("PROCESS..");  
  delay(5000);  
  lcd.clear();//clear lcd screen
  delay(100);  
  lcd.noBlink();
  delay(100);

  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  
  Serial.println("CLEARSHEET");                 // clears starting at row 1
  Serial.println("LABEL,Date,Time,Name,USN,reg,Branch,Mail,Section,contact,");// make four columns (Date,Time,[Name:"user name"]line 48 & 52,[Number:"user number"]line 49 & 53)
  delay(1000);
  
  lcd.print("Plx-DAQ SHEET");
  lcd.setCursor(0,1);
  delay(100);  
  lcd.print("LABEL");
  delay(2000);
  lcd.clear();
  delay(500);   //delay 0.5 sec
  lcd.print("CLEARSHEET");  
  delay(2000);

  digitalWrite(RedLed, LOW);
  delay(100);
  digitalWrite(YellowLed, HIGH);
  delay(500);   
  
  lcd.clear();
  delay(100);                  
  lcd.print("PLEASE SCAN YOUR");
  lcd.setCursor(0,1);      
  lcd.print("ID");
  delay(3000);        
           
  Serial.println("Scan PICC to see UID...");
  Serial.println("");

 }
    
void loop() {
  //look for new card
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;//got to start of loop if there is no card present
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//if read card serial(0) returns 1, the uid struct contians the ID of the read card.
 }
 lcd.clear();
 delay(100);        
 lcd.print(" SCAN");
 lcd.setCursor(0,1);                  
 lcd.print("SUCCESSFUL"); 
 delay(3000); 

 digitalWrite(Buzzer,HIGH);
 delay(80);  
 digitalWrite(Buzzer,LOW);
 delay(10); 
 digitalWrite(RedLed, HIGH);
 delay(2000);
 digitalWrite(RedLed, LOW);
 delay(100); 
   
 for (byte i = 0; i < mfrc522.uid.size; i++) {
     card_ID[i] = mfrc522.uid.uidByte[i]; 
     if (card_ID[i] == Name1[i]) {
         Name = "USER_NAME";  // Placeholder for user name       
         Contact = 1234567890;  // Placeholder for user contact number   
         Section = "USER_SECTION";  // Placeholder for user section 
         Branch = "USER_BRANCH";  // Placeholder for user branch  
         USN = "USER_USN";  // Placeholder for user USN ID    
         reg = "USER_REG_ID";  // Placeholder for user registration ID  
         Mail = "USER_EMAIL";  // Placeholder for user college enrolled email ID

         j = 0;  // First number in the NumbCard array : NumbCard[j]
         
         lcd.clear();
         delay(100);
         digitalWrite(GreenLed, HIGH);
         delay(100);       
         lcd.print("NAME: USER_NAME");       
         lcd.setCursor(0, 1);
         delay(100);
         lcd.print("USN: USER_USN");
         delay(1000); 
         digitalWrite(GreenLed, LOW);
         delay(100);         
         lcd.clear();
         delay(100);          
     }  
}

      else if (card_ID[i] == Name2[i]) {
    Name = "USER_NAME2";  // Placeholder for user name
    Contact = 1234567890;  // Placeholder for user contact number
    Section = "USER_SECTION2";  // Placeholder for user section
    Branch = "USER_BRANCH2";  // Placeholder for user branch  
    USN = "USER_USN2";  // Placeholder for user USN ID 
    reg = "USER_REG_ID2";  // Placeholder for user registration ID  
    Mail = "USER_EMAIL2";  // Placeholder for user college enrolled email ID                  
    j = 1;  // Second number in the NumbCard array : NumbCard[j]  

    lcd.clear();
    delay(100);
    digitalWrite(GreenLed, HIGH);
    delay(100);       
    lcd.print("NAME: USER_NAME2");       
    lcd.setCursor(0, 1);
    delay(100);
    lcd.print("USN: USER_USN2");
    delay(1000); 
    digitalWrite(GreenLed, LOW);
    delay(100);         
    lcd.clear();
    delay(100);  
}

      else{
          digitalWrite(GreenLed,LOW);
          digitalWrite(RedLed,HIGH);
          goto cont;//go directly to line 85
     }        
}
      if(NumbCard[j] == 1){//to check if the card already detect
      //if you want to use LCD
      lcd.clear();
      delay(100);      
      lcd.print("CARD ALREADY");
      lcd.setCursor(0, 1);
      lcd.print("DETECTED");           
      delay(3000); 
      
      digitalWrite(GreenLed, HIGH);
      delay(100);      
      digitalWrite(RedLed, HIGH);
      delay(2000);
      digitalWrite(RedLed, LOW);
      delay(100);             
      //Serial.println("Already Exist");
      }
      else{  
      lcd.clear();
      delay(100);      
      lcd.blink();
      delay(100);                   
      lcd.print("SENDING DATE TO");
      lcd.setCursor(0,1);      
      lcd.print("EXCEL..");
      delay(3000);     
      lcd.noBlink();
      delay(100); 
      
      digitalWrite(GreenLed, HIGH);
      delay(100);
                                      
      NumbCard[j] = 1;//put 1 in if you want to detect you are card once: put 2 in if you want to detect you are card twice 
      n++;//(optional)
      Serial.print("DATA,DATE,TIME," + Name);//send the Name to excel
      Serial.print(",");
      Serial.print("" + USN);//send the USN to excel
      Serial.print(",");                
      Serial.print("" + reg);//send the register no to excel
      Serial.print(",");                           
      Serial.print("" + Branch);//send the branch to excel
      Serial.print(",");
      Serial.print("" + Mail);//send the mail to excel
      Serial.print(",");   
      Serial.print("" + Section);//send the section to excel
      Serial.print(",");         
      Serial.println(Contact); //send the contact to excel      
      digitalWrite(GreenLed,HIGH);
      digitalWrite(RedLed,LOW);
      digitalWrite(Buzzer,HIGH);
      delay(80);
      digitalWrite(Buzzer,LOW);
      Serial.println("SAVEWORKBOOKAS,Names/WorkNames");    
      delay(1000); 
         
      digitalWrite(RedLed, HIGH);
      delay(800);
                  
lcd.clear();
delay(100);                  
lcd.print("YOUR ATTENDANCE");
lcd.setCursor(0,1);      
lcd.print("IS RECORDED");
delay(3000);            
}
cont:
delay(1000);
digitalWrite(RedLed,LOW);
digitalWrite(GreenLed,LOW);   
//if you want to close the Excel when all card had detected and save Excel file in Names Folder. in my case i have just 2 card (optional)
//if(n==2){
    
  //  Serial.println("FORCEEXCELQUIT");
 //   }
}

          
