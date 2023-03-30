/*
University of Nottingham
Open Day
LED Dimmer Source Code
Written By: Al Watson 2015
Updated By: Alex Ottway, June 2022
 */
 
/*Define used pins*/
const int LED=1;       
const int CHA=2;
const int CHB=4; //Using constants (integer datatype here) for pin numbers makes it easy to update the program if we change a pin allocation in the future.

/*Variables*/
int CHA_last_status=LOW, CHA_current_status; //Here we declare variables for the different parameters we want to store.
int CHB_last_status=LOW, CHB_current_status, pwm=0; //All these variables are integer datatype and we've set the value of 'pwm' to zero.

//The "setup" function runs once when you press reset or power the board
void setup() {
  
               pinMode(LED, OUTPUT);  //led pin defined as output
               pinMode(CHA,INPUT);    //Encoder CHA input
               pinMode(CHB,INPUT);    //Encoder CHB input
              }

//The "loop" function runs over and over again forever
void loop() {
      
              CHA_current_status=digitalRead(CHA);                        //Read encoder channel A
                    if (CHA_current_status!=CHA_last_status){             //Debounce encoder. Mechanical switches need "debouncing". Detect a change, wait (5) milliseconds in our case, 
                        delay(5);                                         //then verify that the change REALLY has happened, and only once!
                        CHA_current_status=digitalRead(CHA);
                    }
                
              CHB_current_status=digitalRead(CHB);                        //Read encoder Channel B
            
              if (CHA_current_status==HIGH && CHA_last_status==LOW ){     //Check for change to HIGH on Channel A
                                                                          //If A has gone HIGH, check line B. If B is LOW then the rotation direction is ANTICLOCKWISE
                                                                          //Check out the graph early in the handout document - follow the traces left-to-right for clockwise rotation
                                                                          //and right-to-left for anticlockwise.
              
                     if(CHB_current_status ==LOW){                        //Check for anticlockwise rotation
                          pwm=pwm+10;                                     //Increase PWM duty by 10 steps
                          if(pwm>=255) pwm=255;                           //Saturate at 255 - don't go higher than that maximum value!
                     }               
                     else{                                                //...otherwise, asssume clockwise 
                         pwm=pwm-10;                                      //Decrease PWM duty by 10 steps
                         if(pwm<=0) pwm=0;                                //Saturate at 0 - don't go lower than that!                            
                     }
         
             }
         
             CHA_last_status=CHA_current_status;                         //Record last status of encoder channels so that we can detect if a change has happened
             CHB_last_status=CHB_current_status;
             analogWrite(LED,pwm);                                       //Write pwm to led channel and set its brightness
           }
