#include <linux/kernel.h>
#include<asm/io.h>
#include "linux/tty.h"
define memstart 0xA0000
#define memsize 64000
#define cursor_side 3
#define width 320
#define height 200
#define barrier_width 10
//struct message *headd;
//设置图形模式的核心代码（系统调用接口的代码实现）
int volatile jumpp;
int ff=0;
int sys_init_graphics()
{
    int i,j,x,y;
    char *p=0xA0000;
    if(ff==0)
    {
    outb(0x05,0x3CE);
    outb(0x40,0x3CF);	//设定 256 色，且取出方式为移动拼装
    outb(0x06,0x3CE);
    outb(0x05,0x3CF);	//设定显存的地址区域，禁止字符模式
    outb(0x04,0x3C4);
    outb(0x08,0x3C5);	//设定将 4 个显存片连在一起


    outb(0x01,0x3D4);
    outb(0x4F,0x3D5);	//设置 End Horizontal Display 为 79
    outb(0x03,0x3D4);
    outb(0x82,0x3D5);	//设置 Display Enable Skew 为 0

    outb(0x07,0x3D4);
    outb(0x1F,0x3D5);	//设置 Vertical Display End 第 8，9 位为 1 ，0
    outb(0x12,0x3D4);
    outb(0x8F,0x3D5);	//设置 Vertical Display End 的低 7 位为 0x8F
    outb(0x17,0x3D4);
    outb(0xA3,0x3D5);	//设置 SLDIV =1,将 Scanline Clock 除以 2



    outb(0x14,0x3D4);
    outb(0x40,0x3D5);	//设置 DW =1
    outb(0x13,0x3D4);
    outb(0x28,0x3D5);	//设置 Offset=40

    outb(0x0C,0x3D4);
    outb(0x00,0x3D5);
    outb(0x0D,0x3D4);
    outb(0x00,0x3D5);	//将 Start Address 设置为 0xA0000
    ff=1;
    }
    
    
    //在图形模式下绘制鼠标的核心代码
    p=memstart;
    for(i=0;i<memsize;i++) *p++=3;
    //将背景颜色设置成蓝绿色

    x=20;
    y=10;
    for(i=x-cursor_side;i<=x+cursor_side;i++)
        for(j=y-cursor_side;j<=y+cursor_side;j++)
	{
            p=(char *) memstart+j*width+i;
            *p=12;	//鼠标颜色为红色
        }

    return 0;
}

int sys_get_message()
{
	//msgg=headd;
	//if(headd->mid!=1)return;
	//headd=headd->next;
	if(jumpp>0) --jumpp;
	return jumpp;
}

int sys_repaint(int x,int y,int h)
{
	int i,j,w;
	char *p;
	i=x;
	j=y;
	p=0xA0000;
	w=barrier_width;
	if(i+w>=320 || i<20 ) return 0;
	if(i==33 || j==33){
    p=0xA0000;
	for(i=0;i<memsize;i++) *p++=3;
	return 0;
	}
	else if(i==44 || j==44 ){
    p=0xA0000;
	for(i=0;i<memsize;i++) *p++=4;
	return 0;
	}else{
	for(i=x;i<=x+w;i++){	
		for(j=y;j<=y+h;j++){
			p=0xA0000+j*320+i;
			*p=12;
		}
		}
}
	
return 0;
}
