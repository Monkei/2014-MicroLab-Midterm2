#include<REG_MPC82G516.H>

#define uchar unsigned char

// specified pins, you can use other port
#define seven_port P1
#define matrix_row P0
#define check_but P2

sbit C11 = P3^7;
sbit C22 = P3^6;

uchar table[8] = {0xFF, 0xFF, 0x00, 0xFF, 0x06, 0x76, 0x76, 0x70};
uchar count;
int i;

void delay(int ms);
void delay_us(int us);
void show_num();
void detect();
void show_seven(int i);

void main()
{ 
	P3 = P3&0x0F;
	check_but = 0xFF;
	while(1)
	{
		//show_seven(12);
		if(check_but == 0x00)
		{
			while(count)
			{
				int i = 100;
				while(--i)show_num();
				delay(350);
				count--;
			}
			check_but = 0xFF;
		}else detect();
		show_num();
	}
}

void show_seven(int i)
{
	C11  =1;
	C22 = 0;
	seven_port = 0xF0&seven_port;
	seven_port+=i/10;
	delay_us(100);
	C22 =1;
	C11 = 0;
	seven_port = 0xF0&seven_port;
	seven_port+=i%10;
	delay_us(100);
}

void detect()
{
	check_but = 0xEF;
	if(0xEE==check_but)count = 1+P3%16;
	else if(0xED==check_but)count = 2+P3%16;
	else if(0xEB==check_but)count = 3+P3%16;
	else if(0xE7==check_but)count = 4+P3%16;
	
	check_but = 0xDF;
	if(0xDE==check_but)	count = 5+P3%16;
	else if(0xDD==check_but)count = 6+P3%16;
	else if(0xDB==check_but)count = 7+P3%16;
	else if(0xD7==check_but)count = 8+P3%16;
	
	check_but = 0xBF;
	if(0xBE==check_but)	count = 9+P3%16;
	else if(0xBD==check_but)check_but = 0x00;
	else if(0xBB==check_but)check_but = 0x00;
	else if(0xB7==check_but)check_but = 0x00;
}

void show_num()
{
	uchar i = 0;
	while(i<8)
	{
		show_seven(count);
		seven_port &= 0x0F;
		seven_port += i*16;
		matrix_row = table[i++];
		delay_us(350);
	}
	seven_port &= 0x0F;
	seven_port += (--i)*16;
	matrix_row = 0xFF;
}

void delay(int ms)
{
  while(ms--){
		show_seven(count);
    for(i = 0; i< 1000; i++);
	}
}

void delay_us(int us)   
{
	
  while(us--);    
}
