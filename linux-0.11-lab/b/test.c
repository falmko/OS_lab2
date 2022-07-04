
#define __LIBRARY__
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#define vga_graph_memstart 0xA0000
#define vga_graph_memsize 64000
#define cursor_side 6
#define vga_width 320
#define vga_height 200

#define x_pos 20
#define y_pos 20
_syscall0(void,init_graphics)

int main(void)
{
	int i=14;
	int j=14;
	char *p=vga_graph_memstart;

	init_graphics();


	for(i=0;i<vga_graph_memsize;i++)
	 *p++ = 3;
	for (i=x_pos-cursor_side;i<=x_pos+cursor_side;i++)
		for(j=y_pos-cursor_side;j<=y_pos+cursor_side;j++)
		{
			p=(char *)vga_graph_memstart+j*vga_width+i;
			*p=12;
		}
}
