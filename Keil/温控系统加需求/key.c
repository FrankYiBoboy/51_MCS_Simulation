#include <key.h>


void check_key()
{
	uchar rekey = 0;
	if((key1==0)||(key2==0)||(key3==0))
	{
		delay_ms(10);
		if(rekey==0)	
		{
			if(key1==0)    // ��ⰴ��1�Ƿ���
			{
				rekey=1;
				SetFlag++;	// ���ò�����־
				if(SetFlag >= 3) SetFlag = 0;  		// ����1,����2
			}	
			else if(key2 == 0)	//   ��ⰴ��2�Ƿ���
			{
				rekey=1;
				if(SetFlag == 1)      		// ��������1
				{
					if(setL > 0 )
						{
						setL = setL-1;
						}
				}
				else if(SetFlag == 2)			// ��������2
				{
					if(setH > 0)
					{
					setH = setH-1;
					}
				}						
			}else if(key3==0)			// ��ⰴ��3�Ƿ���
			{
				rekey=1;
				if(SetFlag == 1)      // ��������1
				{
					if(setL < 99 )
					{
					setL=setL+1;
					}
				}
				else if(SetFlag==2)	// ��������2
				{
					if(setH < 99 )
					{
					setH=setH+1;
					}
				}				
			}
		}
	}else{
		rekey = 0; 	// ��ֹ���¼�⵽����
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
				pageFlag++;	// ���ò�����־
				if(pageFlag >= 4) pageFlag = 2; 		// ҳ��1 ҳ��2 ҳ��3 ҳ��1�������ɳ���һ��
			}
		}
	}else{
		rekey = 0;
	}
}