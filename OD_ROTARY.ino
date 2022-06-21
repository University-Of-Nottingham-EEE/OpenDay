/*
  Dimmer- Al Watson 2015
 */
 
/*Define used pins*/
const int LED=1;       
const int CHA=2;
const int CHB=4;

/*Variables*/
int CHA_last_status=LOW, CHA_current_status, pwm=0;
int CHB_last_status=LOW, CHB_current_status; 

// the setup function runs once when you press reset or power the board
void setup() {
  
               pinMode(LED, OUTPUT);  //led pin defined as output
               pinMode(CHA,INPUT);    //Encoder CHA input
               pinMode(CHB,INPUT);    //Encoder CHB input
              }

// the loop function runs over and over again forever
void loop() {
      
              CHA_current_status=digitalRead(CHA);                        //read encoder channel A
                    if (CHA_current_status!=CHA_last_status){             //debounce encoder
                        delay(5);
                        CHA_current_status=digitalRead(CHA);
                    }
                
              CHB_current_status=digitalRead(CHB);                        //read encoder Channel B
            
              if (CHA_current_status==HIGH && CHA_last_status==LOW ){     //Check for change on Channel A
              
                     if(CHB_current_status ==LOW){                        //check for anticlockwise rotation
                          pwm=pwm+10;                                     //increase PWM duty by 10 steps
                          if(pwm>=255) pwm=255;                           //saturate at 255
                     }               
                     else{                                                //otherwise, asssume clockwise 
                         pwm=pwm-10;                                      //decrease PWM duty by 10 steps
                         if(pwm<=0) pwm=0;                                //saturate at 0                             
                     }
         
             }
         
             CHA_last_status=CHA_current_status;                         //record last status of encoder channels
             CHB_last_status=CHB_current_status;
             analogWrite(LED,pwm);                                       //write pwm to led channel 
           }
