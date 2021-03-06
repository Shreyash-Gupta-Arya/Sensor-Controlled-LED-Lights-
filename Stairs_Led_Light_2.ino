#include<FastLED.h>

#define num_led 547
#define led_pin 2
#define sensor_1 8
#define sensor_2 12
#define relay 7
#define buzzer 4

uint8_t hue=0;

CRGB led[num_led];

int x,y;
int sensor_1_value=0 , sensor_2_value=0;
unsigned int current_time, loop_time, time_limit = 60000;
unsigned int current_time_2, loop_time_2, time_limit_2 = 60000;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensor_1,INPUT);
  pinMode(sensor_2,INPUT);
  pinMode(relay,OUTPUT);
  FastLED.addLeds<WS2812B, led_pin,GRB>(led,num_led);
  FastLED.setBrightness(150);
  FastLED.show();
  Serial.begin(9600);
  digitalWrite(relay,HIGH);
  x=0;
  y=0;
 
}

void loop() {
  // put your main code here, to run repeatedly:
 //EVERY_N_MILLISECONDS
  
int i,j;

sensor_1_value = digitalRead(sensor_1);
sensor_2_value = digitalRead(sensor_2);
current_time= millis();
current_time_2=millis();
          
           if( sensor_1_value == LOW && sensor_2_value == HIGH)
                        
                        while(1){
                                sensor_1_value = digitalRead(sensor_1);
                                sensor_2_value = digitalRead(sensor_2);
                                if( sensor_1_value == LOW && sensor_2_value == HIGH){             // Entry loop
                                x=x+1;
                                Serial.print("1 ");
                                Serial.println(x);

                                
                                digitalWrite(relay,LOW);
                                delay(250);
                                loop_time = millis();
                                      for(i=0, j=-3 ; i < num_led ;  hue = hue + 10){           
                                            led[i++] = CHSV( hue,255,100 );
                                            //delay(2);
                                            //FastLED.show();
                                            Serial.println("1 ");
                                            
                                            led[j++] = CHSV( 0,0,100 );
                                            delay(2);
                                            FastLED.show();
                                            
                                            if(i< (num_led/6))
                                                tone(buzzer,800,1000);
                                            else
                                                noTone(buzzer);
                                            
                                            
                                      }
                                      for( ; j < num_led ; j++){
                                            led[j] = CHSV( 0,0,100 );
                                            //delay(2);
                                            //FastLED.show();
                                      }
                                      delay(250);
                                      sensor_1_value = HIGH;
                      
                                }

                            current_time = millis();
                            if( current_time - loop_time >= time_limit ){          // Turnoff light under 1 minute
                                    led[0]=CHSV(20,255,200);
                              
                                    for(i=0,j=-3 ; i<num_led ; i++ , hue=hue+20){
                                          led[i]=CHSV(hue,255,100);
                                          //delay(2);
                                          //FastLED.show(); 
                                          led[j++]= CHSV(hue,255,0);
                                          delay(2);
                                          FastLED.show(); 
                                    } 
                                    for(;j<num_led ;j++){
                                          led[j]=CHSV(25,255,0);
                                          //delay(2);
                                          //FastLED.show();
                                    }
                                    x=0;
                                    delay(250);
                                    digitalWrite(relay,HIGH);
                                    break;
                              }   
                      
                      if( sensor_2_value == LOW && sensor_1_value == HIGH && x!=0){             // Exit loop
                        Serial.print("2 ");       
                        Serial.println(x);
                        
                        delay(50);
                                  loop_time = millis();
                                      for(i=0, j=-3 ; i < num_led ;  hue = hue + 10){
                                            led[i++] = CHSV( hue,255,100 );
                                            //delay(2);
                                            //FastLED.show();
                                        
                                            led[j++] = CHSV( 25,255,100 );
                                            
                                            delay(2);
                                            FastLED.show();
                                            
                                      }
                                      for( ; j < num_led ; j++){
                                            led[j] = CHSV( 25,255,100 );
                                            //delay(2);
                                            //FastLED.show();
                                      }
                                      if(x!=1)
                                          delay(1000);
                        if(x>0){
                            x=x-1;
                            sensor_2_value= HIGH;
                        }
                        if( x==0){
                                   led[0]=CHSV(20,255,200);
                              
                                    for(i=0,j=-3 ; i<num_led ; i++ , hue=hue+20){
                                          led[i]=CHSV(hue,255,100);
                                          //delay(2);
                                          //FastLED.show(); 
                                          led[j++]= CHSV(hue,255,0);
                                          delay(2);
                                          FastLED.show(); 
                                    } 
                                    for(;j<num_led;j++){
                                          led[j]=CHSV(25,255,0);
                                          //delay(2);
                                          //FastLED.show();
                                    }
                                    x=0;
                                    delay(250);
                                    digitalWrite(relay,HIGH);
                                    break;
                          }
                         
                         
                      }
                  }

 current_time_2=millis();                
 if( sensor_1_value == HIGH && sensor_2_value == LOW)

      while(1){  
          sensor_1_value = digitalRead(sensor_1);
          sensor_2_value = digitalRead(sensor_2);  
         if( sensor_1_value == HIGH && sensor_2_value == LOW){          // Entry Loop 2
          y = y+1 ;
          Serial.print("3 ");
          Serial.println(y);

          digitalWrite(relay,LOW);
          delay(500);
          //loop_time_2 = millis();
          loop_time = millis();
          for(i= num_led , j= num_led+3 ; i >= 0 ;  hue = hue + 10){
                   led[i--] = CHSV( hue,255,100 );
                   //delay(2);
                   //FastLED.show();
                                        
                   led[j--] = CHSV( 0,0,100 );
                   delay(2);
                   FastLED.show();
                                            
          }
          for( ; j >=0 ; j--){
                    led[j] = CHSV( 0,0,100 );
                    //delay(2);
                    //FastLED.show();
          }
          delay(250);
          sensor_2_value = HIGH;
         }


                  current_time_2 = millis();
                  if( current_time_2 - loop_time_2 >= time_limit_2 ){             // Turnoff light in 1 minute 2
                  
                        led[0]=CHSV(20,255,200);
                        for(i = num_led , j= num_led+3 ; i >= 0 ;  hue = hue + 20){
                                    led[i--] = CHSV( hue,255,100 );
                                    //delay(2);
                                    //FastLED.show();
                                        
                                    led[j--] = CHSV( hue,255,0 );
                                    delay(2);
                                    FastLED.show();
                                            
                      }
                      for( ; j >=0 ; j--){
                                led[j] = CHSV( 25,255,0 );
                                //delay(2);
                                //FastLED.show();
                      }                       
                       
                       y=0;

                       delay(250);
                       digitalWrite(relay,HIGH);                        
                       break;
                    }

                    
 if( sensor_2_value == HIGH && sensor_1_value == LOW && y!=0){              // Exit loop 2
           Serial.print("4 ");       
           Serial.println(y);
                        
           delay(50);
           loop_time_2 = millis();                    
           for(i = num_led , j= num_led+3 ; i >= 0 ;  hue = hue + 10){
                   led[i--] = CHSV( hue,255,100 );
                   //delay(2);
                   //FastLED.show();
                                        
                   led[j--] = CHSV( 25,255,100 );
                   delay(2);
                   FastLED.show();
                                            
          }
          for( ; j >=0 ; j--){
                    led[j] = CHSV( 25,255,100 );
                    //delay(2);
                    //FastLED.show();
          }
          if( y != 1 )
                       delay(2000);
          if( y > 0 ){
                       y = y-1;
                       sensor_1_value= HIGH;
          }
          if( y==0){
                       led[0]=CHSV(20,255,200);
                        for(i = num_led , j= num_led+3 ; i >= 0 ;  hue = hue + 20){
                                    led[i--] = CHSV( hue,255,100 );
                                    //delay(2);
                                    //FastLED.show();
                                        
                                    led[j--] = CHSV( hue,255,0 );
                                    delay(2);
                                    FastLED.show();
                                            
                      }
                      for( ; j >=0 ; j--){
                                led[j] = CHSV( 25,255,0 );
                                //delay(2);
                                //FastLED.show();
                      }      
                                    
                                   
                       
                        y=0;

                        delay(250);
                        digitalWrite(relay,HIGH);                        
                        break;
            }
                         
      }
  }
  
}
 
