# OS_lab2
	操作系统综合实验2：拓展实验8-鼠标驱动和简单的图形接口实现  
	若运行时出现错误“bash: ./run/sh^M: 坏的解释器：没有那个文件或目录”，可参照 https://blog.csdn.net/qq_39314099/article/details/
## 鼠标的驱动
	在x86体系结构下，发生鼠标点击时CPU收到的中断信号为0x2c，编写一个中断处理函数（mouse_interrupt），并将函数的入口地址写道IDT中，可以调用中断处理程序
	~
	extern void mouse_interrupt(void);
	set_trap_gate(0x2c,&mouse_interrupt)
	~
	将函数直接加在keyboard.s中，用汇编语言实现mouse_interrupt
	kernel/chr_drv/keyboard.s
	~
	#include <linux/config.h>
	.globl mouse_interrupt
	mouse_interrupt:
	pushl %eax
	pushl %ebx
	pushl %ecx
	pushl %edx
	push %ds
	
	movl $0x10,%eax
	mov %ax,%ds
	xor %eax,%eax
	inb $0x60,%al
	pushl %eax
	call readmouse

	addl $4,%esp
	movb $0x20,%al
	outb %al,$0xA0 
	outb %al,$0x20
	
	pop %ds
	popl %edx
	popl %ecx
	popl %ebx
	popl %eax
	iret
~
	鼠标对应的数据寄存器端口地址为0x60
### 鼠标终端的捕获
### 键盘控制器 i8042和终端控制器
### 鼠标输入数据的解码
## 显示器的图形工作模式
	
				          
