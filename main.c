#include<REG_MPC82G516.H>

#define uchar unsigned char
#define uint unsigned int

//sbit done;

#define seven_port P1
#define matrix_row P0
#define check_but P2
#define matrix_col P3

uchar table[8] = {0xFF,0xFF,0x00, 0xFF, 0x06, 0x76, 0x76, 0x70};
// specified pins, you can use other port

void delay(int ms){int i; while(ms--)for(i = 0; i< 1000; i++);}
void delay_us(int us)   {while(us--);    }                                                                 
void show_num();
void detect();

void main()
{ 
	check_but = 0xFF;
	while(1)
	{
		
		if(check_but == 0x00)
		{
			int i = 100;
			while(--i)show_num();
			delay(350);
			seven_port = seven_port - 1;
			
			if(seven_port == 0x00)check_but = 0xFF;
		}else detect();
		show_num();
	}
}

void detect()
{
	check_but = 0xEF;
	if(0xEE==check_but)seven_port = 1;
	else if(0xED==check_but)seven_port = 2;
	else if(0xEB==check_but)seven_port = 3;
	else if(0xE7==check_but)seven_port = 4;
	check_but = 0xDF;
	if(0xDE==check_but)seven_port = 5;
	else if(0xDD==check_but)seven_port = 6;
	else if(0xDB==check_but)seven_port = 7;
	else if(0xD7==check_but)seven_port = 8;
	check_but = 0xBF;
	if(0xBE==check_but)seven_port = 9;
	else if(0xBD==check_but)check_but = 0x00;
	else if(0xBB==check_but)check_but = 0x00;
	else if(0xB7==check_but)check_but = 0x00;
}


void show_num()
{
	uchar i = 0;
	while(i<8)
	{
		matrix_col = i;
		matrix_row = table[i++];
		delay_us(350);
		//delay()
	}
	matrix_col = --i;
	matrix_row = 0xFF;
}
