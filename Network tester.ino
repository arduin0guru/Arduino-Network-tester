#include <UTFT.h>
#include <UTouch.h>
#include <EtherCard.h>
extern uint8_t BigFont[];
extern uint8_t SmallFont[];
UTFT    myGLCD(ILI9325D_16,38,39,40,41); // LCD Pin
UTouch  myTouch( 6, 5, 4, 3, 2); //Touch pin
//int pinOut = 9;  //Speaker Out
int nicCable=8; //Ethernt Cable Sensor
int x, y,z, menu, col1, col2, col3, col4;
char* myTemplate = "";
char result[64] = {};
char count = 0;
char save = false ;
byte Ethernet::buffer[700];
static uint32_t timer;
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

static void gotPinged (byte* ptr) 
{
myGLCD.setColor(255,0,200);
myGLCD.print("                          ",2, 145);
     myTemplate = "Ping:%d.%d.%d.%d";
     sprintf(result, myTemplate, ptr[0],  ptr[1], ptr[2], ptr[3]);
     myGLCD.print(result,2, 145);
     tone(9, 600, 100); //tone
     myGLCD.setColor(255,0,0);
}

void setup()
{
        myGLCD.InitLCD();
	myGLCD.clrScr();       // Clear the screen (black)
	myTouch.InitTouch();
	myGLCD.setFont(BigFont);
	myGLCD.fillScr(0,0,0);               // Clear the screen (Black)

        myGLCD.setColor(0, 255, 0);
        myGLCD.fillRect(0, 0, 319, 19); //Top header
        myGLCD.fillRect(0, 223, 319, 239); //bottom footer
        myGLCD.setColor(255,0,0);
        myGLCD.setBackColor(0,255,0);
        myGLCD.print("Digital Technology", CENTER, 2);
        myGLCD.print("Network Tester", CENTER, 223);	
        
        myGLCD.setColor(255,255,0); 
        myGLCD.setBackColor(0,0,0);
        myGLCD.print("Digital", CENTER, 50);
        myGLCD.print("Technology", CENTER, 80);
	myGLCD.print("Expert", CENTER, 110);
        myGLCD.print("Group", CENTER, 140);	
	myGLCD.print("CopyRight @2015", CENTER,170);
   	
	delay(4000);        //Delay to draw the image
        myGLCD.setColor (0, 0, 0); myGLCD.fillRect (0, 25, 319, 220);// Clear only middle area
        tone(9, 622, 500); //tone Done
        tone(9, 1244, 1000);
        tone(9, 622, 500); 
	Menu1();
	menu=1;
}

//Buttons coordinates
//Menu 1
//Button Static
int x11=10; int y11=50; int x12=150; int y12=100;
//Button DHCP
int x21=160; int y21=50; int x22=300; int y22=100;
//Button RestTP
int x31=10; int y31=110; int x32=150; int y32=160;
//Button Ping
int x41=160; int y41=110; int x42=300; int y42=160;
//Button Save
int x51=10; int y51=170; int x52=150; int y52=210;
//Button home
int x61=260; int y61=170; int x62=300; int y62=210; //x61 default 160

void Menu1()    // MAIN MENU
{
//  myGLCD.clrScr(); // Clear the screen (black)
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0,0,0);myGLCD.setColor(0,0,0);myGLCD.fillRect (0, 25, 319, 220); // Clear the screen (black)
  myGLCD.setColor(0, 0, 255);
  myGLCD.print("Main Menu", CENTER , 25);
  myGLCD.setBackColor(0, 0, 255);
  //BUTTON Static
  button (x11,y11,x12,y12);  myGLCD.print("Static", 35, 67);
  //BUTTON DHCP
  button (x21,y21,x22,y22);  myGLCD.print("DHCP",200, 67);   
  //BUTTON restIP
  button (x31,y31,x32,y32);  myGLCD.print("RestIP",35, 127);     
  //BUTTON Ping
  button (x41,y41,x42,y42);  myGLCD.print("Ping",200, 127);
  //Button Xray
  // button (x51,y51,x52,y52);  myGLCD.print("Xray",40,182);
   //Button Test
 //  button (x61,y61,x62,y62);  myGLCD.print("Test",200,182);
  menu =1; 
}

void Menu2()    //Back MENU
{
    myGLCD.setBackColor(0,0,0); myGLCD.fillRect (0, 25, 319, 220); // Clear the screen (black)
  //BUTTON Save
 //   button (x51,y51,x52,y52);  myGLCD.print("SAVE",40,182);
   //Button Test
    myGLCD.setBackColor(0, 0, 0);
    myGLCD.setColor(255,255, 255);
//  button (x51,y51,x52,y52); myGLCD.print("Home",40,182);  // Button Home
    myGLCD.drawLine (250,190,280,165); //left roof line
    myGLCD.drawLine (310,190,280,165); //right roof line
    myGLCD.drawRect (260,182,300,210); //main squre
    myGLCD.drawRect (275,192,285,210); //door 
    myGLCD.setColor(0,0,0); //Black
    myGLCD.drawLine (261, 182, 299,182); //clear top line

 // button (x61,y61,x62,y62); myGLCD.print("",200,182);   //BUTTON Back
    menu =2;
}

void Menu3()    // Static menu draw
{
   myGLCD.setBackColor(0,0,0);  myGLCD.fillRect (0, 25, 319, 220); // Clear the screen (black)
  //BUTTON Gpro
//  myGLCD.setBackColor(0, 0, 255);
   myGLCD.setColor(255, 255, 255);
    myGLCD.print("+   +   +   +",80, 47); //upper line
    myGLCD.drawRoundRect(75, 40, 105, 70);
    myGLCD.drawRoundRect(135, 40, 165, 70);
    myGLCD.drawRoundRect(200, 40, 230, 70);
    myGLCD.drawRoundRect(265, 40, 295, 70);
    myGLCD.print("-   -   -   -",80, 117); //lower line
    myGLCD.drawRoundRect(75, 110, 105, 140);
    myGLCD.drawRoundRect(135, 110, 165, 140);
    myGLCD.drawRoundRect(200, 110, 230, 140);
    myGLCD.drawRoundRect(265, 110, 295, 140);
    
 //Home Icon
   myGLCD.drawLine (250,190,280,165); //left roof line
    myGLCD.drawLine (310,190,280,165); //right roof line
    myGLCD.drawRect (260,182,300,210); //main squre
    myGLCD.drawRect (275,192,285,210); //door 
    myGLCD.setColor(0,0,0); //Black
    myGLCD.drawLine (261, 182, 299,182);
      //Button Xray
      myGLCD.setBackColor(0, 0, 255);
   button (x51,y51,x52,y52);  myGLCD.print("SAVE",40,182);
  
   menu =3;
} //void menu 3
void Menu4()    //
{
   myGLCD.setBackColor(0,0,0);  myGLCD.fillRect (0, 25, 319, 220); // Clear the screen (black)
  //BUTTON 
   myGLCD.setBackColor(0, 0, 255);
//  button (x51,y51,x52,y52); myGLCD.print("Home",40,182);
  //BUTTON Back
   tone(9, 600, 1000); //tone Done
   button (x61,y61,x62,y62); myGLCD.print("Back",200,182);   
  menu =4;
} //void menu4

void loop()
{
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();

      if (menu == 1)  //Main menu
      {
        if ((y>=y11) && (y<=y12))  // Upper row
        {     
          if ((x>=x11) && (x<=x12))  // Button: 1 Static
          {  
           waitForIt(x11,y11,x12,y12);
            menu =3;
            
          if (menu==3)
           {
             Menu3();
              col1=ether.myip[0]; col2=ether.myip[1]; col3=ether.myip[2]; col4=ether.myip[3];  // IP save to var
              delay(300);

             myGLCD.setBackColor(0, 0, 0); myGLCD.setColor(255,200,0);
             myGLCD.print("IP :   .   .   .   ",2, 80);
               myGLCD.printNumI(col1 , 65 ,80);
               myGLCD.printNumI(col2 , 125 ,80);
               myGLCD.printNumI(col3, 190 ,80);
               myGLCD.printNumI(col4, 255 ,80);
                 
           } //Menu=3
            
          } //button 1
          if ((x>=x21) && (x<=x22))  // Button: 2 DHCP
           {
                waitForIt(x21,y21,x22,y22);
                menu =2;
                Menu2();
             
             myGLCD.setBackColor(0,0,0);
            if (ether.begin(sizeof Ethernet::buffer, mymac,53) == 0)
                myGLCD.print("NIC Failed", LEFT, 25);
              else
              {
                myGLCD.setColor(0,255,0);
                myGLCD.print("NIC OK", LEFT, 25);
               } 
              delay (1000);
              if (digitalRead(nicCable)==HIGH)
                  {
                  myGLCD.print("Cable OK", LEFT, 45);
                  
                      if (!ether.dhcpSetup())
                      {
                        myGLCD.setColor(255,0,0);
                        myGLCD.print("DHCP Failed", RIGHT, 25);
                      }
                    else
                    {
                      myGLCD.setColor(0,255,0);
                      myGLCD.print("DHCP OK", RIGHT, 25);
                            	       
                    }
                         myGLCD.setColor(255,200,0);
                         myTemplate = "IP  :%d.%d.%d.%d";
                         sprintf(result, myTemplate, ether.myip[0],  ether.myip[1],  ether.myip[2],  ether.myip[3]);
                         myGLCD.print(result,2, 70);
                         
                        // ether.myip[0] = col1; ether.myip[1] = col2; ether.myip[2]= col3 ; ether.myip[3] = col4 ; //Save for static IP
                          
                         myTemplate = "GW  :%d.%d.%d.%d";
                         sprintf(result,myTemplate, ether.gwip[0],  ether.gwip[1],  ether.gwip[2],  ether.gwip[3]);
                         myGLCD.print(result,2, 90);
                        
                         myTemplate = "DNS :%d.%d.%d.%d";
                         sprintf(result, myTemplate, ether.dnsip[0],  ether.dnsip[1],  ether.dnsip[2],  ether.dnsip[3]);
                         myGLCD.print(result,2, 110);
                          tone(9, 600, 1000); //tone Done
                }   //Digital read Ether cable
                 
              else
              {
                myGLCD.setColor(255,0,0);  
                myGLCD.print("No Cable", LEFT, 45);
                tone(9, 600, 1000); //tone Done
              }    
           } //Botton 2 DHCP
        }//Upper Botton
        if ((y>=y31) && (y<=y32))  // Lower row
        {     
          if ((x>=x31) && (x<=x32))  // Button:3 Rest IP
               {
                 waitForIt(x31,y31,x32,y32);
                  menu =2;
                  Menu2();
				  
			ether.myip[0] =0; ether.myip[1] =0; ether.myip[2] =0; ether.myip[3] =0; //reset IP
			ether.gwip[0] =0; ether.gwip[1] =0; ether.gwip[2] =0; ether.gwip[3] =0; //reset subnet
			ether.dnsip[0] =0; ether.dnsip[1] =0; ether.dnsip[2] =0; ether.dnsip[3] =0; //reset gateway
                    myGLCD.setBackColor(0,0,0);
                    myGLCD.setColor(255,0,0);
			myGLCD.print("Reset IP ", CENTER, 45);
			myGLCD.setColor(255,200,0);
                   
			myTemplate = "IP  :%d.%d.%d.%d";
			sprintf(result, myTemplate, ether.myip[0],  ether.myip[1],  ether.myip[2],  ether.myip[3]);
			myGLCD.print(result,2, 90);
                     
                     	myTemplate = "GW  :%d.%d.%d.%d";
			sprintf(result,myTemplate, ether.gwip[0],  ether.gwip[1],  ether.gwip[2],  ether.gwip[3]);
			myGLCD.print(result,2, 110);
				  
			myTemplate = "DNS :%d.%d.%d.%d";
			sprintf(result, myTemplate, ether.dnsip[0],  ether.dnsip[1],  ether.dnsip[2],  ether.dnsip[3]);
			myGLCD.print(result,2, 130);

                        tone(9, 622, 1000);
		} //Botton 3
             
          if ((x>=x41) && (x<=x42))  // Button:4 Ping
           { 
               waitForIt(x41,y41,x42,y42);
               menu =2;
               Menu2();
            myGLCD.setBackColor(0,0,0);
            if (ether.begin(sizeof Ethernet::buffer, mymac,53) == 0)
                myGLCD.print("NIC Failed", LEFT, 25);
              else
              {
                myGLCD.setColor(0,255,0);
                myGLCD.print("NIC OK", LEFT, 25);
	      }
              delay (1000);
			   if (digitalRead(nicCable)==HIGH)
				{
				   myGLCD.print("Cable OK", LEFT, 45);
									
						 if (!ether.dhcpSetup())
						  {
							myGLCD.setColor(255,0,0);
							myGLCD.print("DHCP Failed", RIGHT, 25);
							myGLCD.print("DNS Failed", RIGHT, 45);
						  }
						  else
						  {
							myGLCD.setColor(0,255,0);
							myGLCD.print("DHCP OK", RIGHT, 25);
							
                                                          if (!ether.dnsLookup(PSTR("www.google.com")))
							      {
							        myGLCD.setColor(255,0,0);
						        	myGLCD.print("DNS Failed", RIGHT, 45);
							  	ether.parseIp(ether.hisip, "74.125.77.99");
							      }
						        else
							      {
								myGLCD.setColor(0,255,0);
								myGLCD.print("DNS OK", RIGHT, 45);
							      }
						  } //else
						   myGLCD.setColor(0,200,255);
						   myTemplate = "IP  :%d.%d.%d.%d";
						   sprintf(result, myTemplate, ether.myip[0],  ether.myip[1],  ether.myip[2],  ether.myip[3]);
						   myGLCD.print(result,2, 65);
								   
						   myTemplate = "DNS :%d.%d.%d.%d";
						   sprintf(result, myTemplate, ether.dnsip[0],  ether.dnsip[1],  ether.dnsip[2],  ether.dnsip[3]);
						   myGLCD.print(result,2, 85); 
						   
						   myTemplate = "SRV :%d.%d.%d.%d";
						   sprintf(result, myTemplate, ether.hisip[0],  ether.hisip[1],  ether.hisip[2],  ether.hisip[3]);
						   myGLCD.print(result,2, 105);
						
						ether.registerPingCallback(gotPinged); //receive Ping
					timer = -9999999;
					z=0;
				
					while (ether.hisip[0]>0 && z<10) //10 times
						{
							word len = ether.packetReceive(); // go receive new packets
							word pos = ether.packetLoop(len); // respond to incoming pings
           				      if (len > 0 && ether.packetLoopIcmpCheckReply(ether.hisip))
							{
								count = ((micros()- timer)* 0.001) ;
								myGLCD.setColor(0,255,0);
								myGLCD.print("Ping Google>>",2, 125);
								myGLCD.setColor(255,50,50);       
								myGLCD.printNumI(count ,210, 125);
								myGLCD.printNumI(z ,CENTER, 25);
								myGLCD.print("ms",270, 125);
								myGLCD.setColor(0,255,0);
								myGLCD.print("Internet OK", LEFT, 45);
								tone(9, 622, 10); //tone
                                                                ++z;
                                                          } //LEN
                                                          if (digitalRead(nicCable)==HIGH) //check cable
				                                      	z=z;
                                                          else
                                                             {  z=10;myGLCD.setColor(255,0,0);
                                                                myGLCD.print("No Cable    ", LEFT, 45);
                                                                tone(9, 600, 1000); //tone Done
                                                             }
							// ping a remote server once every few seconds
							if (micros() - timer >= 5000000)
							{
    							   myGLCD.print("                                  ",2, 145);// Gotping clear
							   timer = micros();
							   ether.clientIcmpRequest(ether.hisip);
							} //Micros
                                                     //   else 
                                                      //      z=10;		   
						} //Ether.hisip
                                        
                 		   delay(2000);
				   myGLCD.print(" DONE  " ,210, 125);
				   tone(9, 600, 1000); //tone Done
                                } //digital read
			      else 
                        	{
                                 myGLCD.setColor(255,0,0);  
                                 myGLCD.print("No Cable", LEFT, 45);
                                 tone(9, 600, 1000); //tone Done
                                }    
	
      } //Botton 4
} //middle row
} //Main menu 
   if ((y>=y51) && (y<=y52))  // Bottom row
        {     
 //         if ((x>=x51) && (x<=x52))  // Button:5
 //              { 
 //                  waitForIt(x51,y51,x52,y52);
 //                 menu =2;
 //                 Menu2();
 //              }
           if ((x>=x61) && (x<=x62))  // Button:6
                {
                  waitForIt(x61,y61,x62,y62);
                  menu =1;
                  Menu1();
                }
        } //Bottom Row
   
      if (menu==2)
	{
        delay(300);
        if (((y>=y61) && (y<=y62)) && ((x>=x61) && (x<=x62)))// Button: Back
          {     
           if ((x>=x61) && (x<=x62))  // Button: Bac//          
             {     
                waitForIt(x61,y61,x62,y62);
                menu =1;
                Menu1();
             }
            } //Back Button
	  } //Menu2
     if (menu==3)
        {
          delay(40);
        if ((y>=40) && (y<=70)) //++
             {
               tone(9, 600, 20); //tone while touch
             if ((x>=74) && (x<=105))
                 if ((col1>=0) && (col1<255))
                     {col1++;myGLCD.print("   " , 65 ,80);myGLCD.printNumI(col1 , 65 ,80);}
                 else
                     tone(9, 600, 1000); //tone while touch
             if ((x>=135) && (x<=165))
                 if ((col2>=0) && (col2<255))
                      {col2++;myGLCD.print("   " , 125 ,80); myGLCD.printNumI(col2 , 125 ,80);}
                 else
                       tone(9, 600, 1000); //tone while touch
             if ((x>=200) && (x<=230))
                 if ((col3>=0) && (col3<255))
                       {col3++;myGLCD.print("   ", 190 ,80); myGLCD.printNumI(col3, 190 ,80);}
                 else
                       tone(9, 600, 1000); //tone while touch
             if ((x>=265) && (x<=295))
                 if ((col4>=0) && (col4<255))
                       {col4++; myGLCD.print("   ", 255 ,80); myGLCD.printNumI(col4, 255 ,80);}
                 else
                       tone(9, 600, 1000); //tone while touch
             }
          if ((y>=110) && (y<=140)) //-
           {
             tone(9, 600, 20); //tone while touch
             if ((x>=74) && (x<=105))
                 if ((col1>0) && (col1<=255))
                     {col1--;myGLCD.print("   " , 65 ,80); myGLCD.printNumI(col1 , 65 ,80);}
                 else
                     tone(9, 600, 1000); //tone while touch
             if ((x>=135) && (x<=165))
                 if ((col2>0) && (col2<=255))
                      { col2--;myGLCD.print("   " , 125 ,80); myGLCD.printNumI(col2 , 125 ,80); }
                 else
                     tone(9, 600, 1000); //tone while touch
             if ((x>=200) && (x<=230))
                 if ((col3>0) && (col3<=255))
                     {col3--;myGLCD.print("   ", 190 ,80);myGLCD.printNumI(col3, 190 ,80); }
                 else
                     tone(9, 600, 1000); //tone while touch
             if ((x>=265) && (x<=295))
                 if ((col4>0) && (col4<=255))
                     { col4--; myGLCD.print("   ", 255 ,80); myGLCD.printNumI(col4, 255 ,80); }
                 else
                     tone(9, 600, 1000); //tone while touch
            }         
      if (((y>=y51) && (y<=y52)) && ((x>=x51) && (x<=x52))&& menu==3)// Button: save
           {    
              ether.myip[0] = col1; ether.myip[1] = col2; ether.myip[2]= col3 ; ether.myip[3] = col4 ; //Save static IP
              tone(9, 600, 1000);
              x=280;y=180;
              
           }
      /*        if ((x>=x61) && (x<=x62))  // Button: Back
              {     
                waitForIt(x61,y61,x62,y62);
                menu =3;
                Menu3();
              }
    */
        } //menu 3
     
   if (menu==4 )
      {
       delay(300);
        if ((y>=y61) && (y<=y62))  // Button: Back
          {     
            if ((x>=x61) && (x<=x62))  // Button
              {     
                waitForIt(x61,y61,x62,y62);
                menu =1;
                Menu1();
              }
          } //Button back
      } //menu 4
     
    }  //Touch
  }  //While
}  //loop 

void button(int x1, int y1, int x2, int y2) //Draw button
{
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (x1,y1,x2,y2);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1,y1,x2,y2);
  myGLCD.drawRoundRect ((x1+1), (y1+1), (x2-1),( y2-1));
}

void waitForIt(int x1, int y1, int x2, int y2) // Draw a red frame while a button is touched
{
  if (x1==260) //home icon touch
    {
     myGLCD.setColor(255, 0, 0);
     myGLCD.drawLine (250,190,280,165); //left roof line
     myGLCD.drawLine (310,190,280,165); //right roof line
     myGLCD.drawRect (260,182,300,210); //main squre
     myGLCD.drawRect (275,192,285,210); //door 
     myGLCD.setColor(0,0,0); //Black
     myGLCD.drawLine (261, 182, 299,182);
    }
  else //if (menu=3 && x51) //save button
    {
    myGLCD.setColor(255, 0, 0);
    myGLCD.drawRoundRect (x1, y1, x2, y2);
    myGLCD.drawRoundRect ((x1+1), (y1+1), (x2-1),( y2-1)); 
    }
  tone(9, 600, 20); //tone while touch
 
  while (myTouch.dataAvailable())
      myTouch.read();
      delay(400);
      myGLCD.setColor(0, 0, 0); myGLCD.drawRoundRect (x1, y1, x2, y2);// clean screen black
}
