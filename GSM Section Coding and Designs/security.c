#include<avr/io.h>
#include<util/delay.h>
char ch[]="AT+CMGF=1";
char ch1[]="AT+CMGS=\"7014491563\"";
char ch4[]="Alert!! theft is in the house";
int z;
void serial()
{
UCSRB |= (1<<TXEN) | (1<<RXEN);
UCSRC |=(1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
UBRRL=0x33; 
}
void msg()
{
			UDR='A';
			while(!(UCSRA & (1<<TXC)));
			UCSRA=(1<<TXC);
			_delay_ms(50);
			UDR='T';
			while(!(UCSRA & (1<<TXC)));
			UCSRA=(1<<TXC);
			_delay_ms(50);
			UDR=13;
			while(!(UCSRA & (1<<TXC)));
			UCSRA=(1<<TXC);
			_delay_ms(50);
				_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);
			  _delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);
			for(z=0;ch[z]!='\0';z++)
			{
			UDR=ch[z];
			while(!(UCSRA & (1<<TXC)));
			UCSRA=(1<<TXC);
			_delay_ms(50);
			}
			UDR=13;
			while(!(UCSRA & (1<<TXC)));
			UCSRA=(1<<TXC);
			_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);
			  _delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);

			for(z=0;ch1[z]!='\0';z++)
			{
			UDR=ch1[z];
			while(!(UCSRA & (1<<TXC)));
			UCSRA=(1<<TXC);
			_delay_ms(50);
			}
			
			UDR=13;
			while(!(UCSRA & (1<<TXC)));
			UCSRA=(1<<TXC);
			_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);
			  _delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);


			 for(z=0;ch4[z]!='\0';z++)
			 {
			  UDR=ch4[z];
			  while(!(UCSRA & (1<<TXC)));
			  UCSRA=(1<<TXC);
			  _delay_ms(50);
			  }
			  _delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);
			  _delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);_delay_ms(1000);
			UDR=26;
			while(!(UCSRA & (1<<TXC)));
			UCSRA=(1<<TXC);
}

int main()
{
DDRD=!(1<<5) | !(1<<6) | !(1<<7) | (1<<2)| (1<<3);
DDRC=!(1<<1);
DDRB=(1<<1) | !(1<<6) | (1<<3) | (1<<4);
p:
serial();
PORTB=(1<<0);
while(1)
{
if(!(PIND & (1<<5)))        //on switch
{
while(!(PIND & (1<<5)));
while(PIND & (1<<6))
{
if(!(PIND & (1<<7)))         //mic
{
//PORTD=(1<<2);               //safe current
PORTB=(1<<1) | (1<<3);               // safe buzzer
msg();
goto p;
}
if((PINC & (1<<1)))        //human detection sensor
{
//PORTD=(1<<2);               //safe current
PORTB=(1<<1) | (1<<3);               // safe buzzer
msg();
goto p;
}
if(!(PINB & (1<<6)))         //light sensor check
{
PORTB=(1<<4);
}
else
PORTB=!(1<<4);
}
}
else if(!(PIND & (1<<6)))   //off switch
{
while(!(PIND & (1<<6)));
while(PIND & (1<<5))
{
//PORTD=!(1<<2);               //safe current off
PORTB=!(1<<1) | !(1<<3);               //safe current off buzzer off
}
}
}
}
