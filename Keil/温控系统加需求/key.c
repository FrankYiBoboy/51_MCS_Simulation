#include <key.h>


void check_key()
{
	uchar rekey = 0;
	if((key1==0)||(key2==0)||(key3==0))
	{
		delay_ms(10);
		if(rekey==0)	
		{
			if(key1==0)    // 检测按键1是否按下
			{
				rekey=1;
				SetFlag++;	// 设置参数标志
				if(SetFlag >= 3) SetFlag = 0;  		// 设置1,设置2
			}	
			else if(key2 == 0)	//   检测按键2是否按下
			{
				rekey=1;
				if(SetFlag == 1)      		// 处于设置1
				{
					if(setL > 0 )
						{
						setL = setL-1;
						}
				}
				else if(SetFlag == 2)			// 处于设置2
				{
					if(setH > 0)
					{
					setH = setH-1;
					}
				}						
			}else if(key3==0)			// 检测按键3是否按下
			{
				rekey=1;
				if(SetFlag == 1)      // 处于设置1
				{
					if(setL < 99 )
					{
					setL=setL+1;
					}
				}
				else if(SetFlag==2)	// 处于设置2
				{
					if(setH < 99 )
					{
					setH=setH+1;
					}
				}				
			}
		}
	}else{
		rekey = 0; 	// 防止重新检测到按键
	}
}

void page_key()
{
	uchar rekey = 0;
	if(key4 == 0)
	{
		delay_ms(3000);
		if(rekey==0)
		{
			if(key4 == 0)
			{
				rekey=1;
				pageFlag++;	// 设置参数标志
				if(pageFlag >= 4) pageFlag = 2; 		// 页面1 页面2 页面3 页面1按键仅可出现一次
			}
		}
	}else{
		rekey = 0;
	}
}