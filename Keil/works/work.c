#include <reg51.h>
#define GPIO_KEY P1
#define GPIO_DIG P0
typedef unsigned char u8;
typedef unsigned int u16;

sbit LSA = P2 ^ 2; //74LS138位选，且01相反，C位最高位
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;
sbit START = P2 ^ 5; //抢答开始键
sbit RESET = P2 ^ 6; //复位键


u8 code duanxuan[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00}; //段选0-F,用于数码管显示，最后1位为空（不亮）
u16 box[] = {16, 16, 16, 16, 16, 16, 16, 16};                                                                                //存放每一位数字
u16 KeyValue;                                                                                                                //用于表示按下的是哪个键
int time;                                                                                                                    //计时

void Delay(u16 i) //延时
{
    while (i--);
}
void Display() //依次显示各位数字，遍历box，根据box里存的各位是什么数字，通过duanxuan来显示
{
    int i;            //f用于表示前7位中是否有非0数
    for (i = 7; i >= 0; i--) //显示前7位，如果一直没有非0数，全是0就不显示，从非0数开始显示
    {
        LSA = 1 - i % 2;
        LSB = 1 - i / 2 % 2;
        LSC = 1 - i / 4 % 2;
        GPIO_DIG = duanxuan[box[i]];
        Delay(50);
        GPIO_DIG = 0x00;
    }
}

void SetTime()
{
    int time_2 = time / 150;
    box[7] = time_2 / 10;
    box[6] = time_2 % 10;
    time--;
}

void Buzz(int i)
{
    BUZ = 1;
    Delay(i);
    BUZ = 0;
}
void KeyDown() //检查按键
{
    KeyValue = 10;
    RESET = 1;
    START = 1;
    GPIO_KEY = 0xff;
    if (RESET == 0)
        KeyValue = 8;
    else if (START == 0)
        KeyValue = 9;
    else if (GPIO_KEY != 0xff)
    {
        switch (GPIO_KEY) //检查按键在第几行
        {
        case (0Xfe):
            KeyValue = 0;
            break;
        case (0xfd):
            KeyValue = 1;
            break;
        case (0Xfb):
            KeyValue = 2;
            break;
        case (0Xf7):
            KeyValue = 3;
            break;
        case (0Xef):
            KeyValue = 4;
            break;
        case (0Xdf):
            KeyValue = 5;
            break;
        case (0Xbf):
            KeyValue = 6;
            break;
        case (0X7f):
            KeyValue = 7;
            break;
        }
    }
}

void main()
{
    int i = 0;
    BUZ = 0;
    while (1)
    {
        //清零
        for (i = 7; i >= 0; i--)
            box[i] = 0;
        Display();
        KeyDown();
        if (KeyValue == 9) //抢答开始
        {
            Buzz(30000);
            time = 4649;
            for (i = 5; i >= 0; i--)
                box[i] = 16;
            while (1) //循环探测，直至有抢答键或复位键按下（开始键多按了，会被无视）
            {
                SetTime();
                Display();
                KeyDown();
                if (KeyValue < 9 || time < 0) //按了复位或超时，9代表开始键
                    break;
            }
            if (KeyValue < 8 && time >= 0) //如果按下的键是抢答键，8代表开始键
            {
                for (i = 5; i >= 0; i--) //前7位不亮
                    box[i] = 16;
                box[0] = KeyValue + 1; //把抢答的选手号显示
                while (1) //有人抢答了，就持续等待复位键被按下
                {
                    Display();
                    KeyDown();
                    if (KeyValue == 8) //8代表复位键
                        break;
                }
            }
        }
        
    }
}
