  signed int direction;
int pwm;
float voltageold;
float currentold;
float measuredvoltage;
float measuredcurrent;
float deltav;
float deltai;
float deltae;
float inc;
float error;
char TXT[6];
char TXT2[6];
char TXT3[6];
float vout=120;
float volt;
float  dutycycle;
unsigned int ADC_Value, Factor;
unsigned long temp;
float L=0.6;
float ML=0.618;
float M=0.636;
float MH=0.654;
float H=0.672;


// LCD module connections
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;
        



void main()
{
     Lcd_Init();
       Lcd_Cmd(_LCD_CLEAR);               // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);

  PORTA = 255;
  TRISA = 255;  
  PORTC = 0;                          // set PORTC to 0
  TRISC = 0;                      // configure PORTA pins as input
  voltageold=0;
  currentold=0;
  pwm=180;
  direction=0.001;
  Factor = 488;                         // Initialize LCD

  PWM1_Init(50000);                    // Initialize PWM1 module at 50KHz
  PWM2_Init(50000);                    // Initialize PWM2 module at 50KHz
  PWM1_Start();                       // start PWM1
  PWM2_Start();


while(1)
{

Lcd_Cmd(_LCD_CLEAR);
measuredvoltage=ADC_Read(0);   /* Read the voltage input from ADC channel 0 */
measuredcurrent =ADC_Read(1);  /* Read the current input from ADC channel 1 */
 volt=measuredvoltage*0.004887585532746;
 volt=volt+33;
  WordToStr(volt,TXT2);
  dutycycle=(vout-volt)/vout*100;

ADC_Value = ADC_Read(1);
ADC_Value = ADC_Value + ADC_Read(1);
ADC_Value = ADC_Value + ADC_Read(1);
ADC_Value = ADC_Value/3;
temp = (ADC_Value-512)*Factor ;
ADC_Value = temp/10;
//Display(ADC_Value);

deltav=measuredvoltage-voltageold;
deltai=measuredcurrent-currentold;

deltae=deltai/deltav;
error=-(measuredcurrent/measuredvoltage);

if(deltav==0)
{
if(deltai==0)
{
  pwm=pwm;
}

else if(deltai>0)
{
pwm++;

}

  else if(deltai<0)
{
pwm--;
}
}

else
{
if(deltae<=L)
{

if (error<=L)
{
  pwm=pwm;
}

else if (error>L && error<=ML)
{
  pwm=pwm+L;
}
else if (error>ML && error<=M)
{
  pwm=pwm+L;
}
else if (error>M && error<=MH)
{
  pwm=pwm+ML;
}
else if (error>MH && error<=H)
{
  pwm=pwm+M;
}
   }
   
   
   
   
   if(deltae>L && deltae<=ML)
{

if (error<=L)
{
  pwm=pwm-L;
}


else if (error>L && error<=ML)
{
  pwm=pwm;
}
else if (error>ML && error<=M)
{
  pwm=pwm+ML;
}
else if (error>M && error<=MH)
{
  pwm=pwm+M;
}
else if (error>MH && error<=H)
{
  pwm=pwm+H;
}
   }
   
   
   

   if(deltae>ML && deltae<=M)
{

if (error<=L)
{
  pwm=pwm-L;
}


else if (error>L && error<=ML)
{
  pwm=pwm-ML;
}
else if (error>ML && error<=M)
{
  pwm=pwm;
}
else if (error>M && error<=MH)
{
  pwm=pwm+MH;
}
else if (error>MH && error<=H)
{
  pwm=pwm+H;
}
   }
   
   
          if(deltae>M && deltae<=MH)
{

   if (error<=L)
{
  pwm=pwm-ML;
}

else if (error>L && error<=ML)
{
  pwm=pwm-M;
}
else if (error>ML && error<=M)
{
  pwm=pwm-MH;
}
else if (error>M && error<=MH)
{
  pwm=pwm;
}
else if (error>MH && error<=H)
{
  pwm=pwm+MH;
}
   }




          if(deltae>MH && deltae<=M)
{

   if (error<=L)
{
  pwm=pwm-M;
}

else if (error>L && error<=ML)
{
  pwm=pwm-MH;
}
else if (error>ML && error<=M)
{
  pwm=pwm-H;
}
else if (error>M && error<=MH)
{
  pwm=pwm-H;
}
else if (error>MH && error<=H)
{
  pwm=pwm;
}
   }

}

voltageold =measuredvoltage;
currentold=measuredcurrent;
PWM1_Set_Duty(pwm);
WordToStr(dutycycle,TXT);
Lcd_Out(1,1,"VOLTAGE=");
Lcd_Out(2,1,"DUTYCYCLE=");
Lcd_Out(2,11,TXT);
Lcd_Out(1,9,TXT2);
  Delay_ms(500);
}
}