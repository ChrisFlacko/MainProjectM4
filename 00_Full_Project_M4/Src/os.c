/*
 * os.c
 *
 *  Created on: Jul 15, 2025
 *      Author: chris
 */

#include "os.h"

/* Tasks */
TCB task1;
TCB task2;

TCB *currentTask;

/* Reserve the memory space for the two tasks */
/* Make sure they are 8byte aligned */
__attribute__((aligned(8))) uint32_t u32Task1Stack[STACK_SIZE];
__attribute__((aligned(8))) uint32_t u32Task2Stack[STACK_SIZE];


void Task1Func(void)
{
    for (;;)
    {
    	Hal_GPIO_vOutputEnable(5, GPIO_A);
        // ... do work, maybe wait for tick or event
    }
}

void Task2Func(void)
{
    for (;;)
    {
        Hal_GPIO_vOutputDisable(5, GPIO_A);
        // ... do work, maybe wait for tick or event
    }
}

__attribute__((noreturn)) static void TaskExit(void)
{
    for (;;) { __asm volatile("WFI"); }
}

static uint32_t *task1_top = 0;   // top-of-stack for direct start (Option 1)
static uint32_t *task2_top = 0;   // top-of-stack for direct start (Option 1)

void OS_vInitialStackFrame(void)
{
    // Top of Task1 stack for direct branch startup
    task1_top = (uint32_t*)(((uintptr_t)&u32Task1Stack[STACK_SIZE]) & ~((uintptr_t)0x7));
    task2_top = (uint32_t*)(((uintptr_t)&u32Task2Stack[STACK_SIZE]) & ~((uintptr_t)0x7));

    // Build initial HW frame for Task2 (so first switch INTO Task2 works)
    uint32_t *sp = task2_top;
    sp -= 8;                                 // HW frame
    sp[0] = 0;                               // R0
    sp[1] = 0;                               // R1
    sp[2] = 0;                               // R2
    sp[3] = 0;                               // R3
    sp[4] = 0;                               // R12
    sp[5] = (uint32_t)TaskExit;              // LR if Task2 returns
    sp[6] = ((uint32_t)Task2Func) | 1U;      // PC (Thumb)
    sp[7] = 0x01000000;                      // xPSR (Thumb)

    sp -= 8;                                 // R4..R11 spill area
    for (int i = 0; i < 8; ++i) sp[i] = 0xAAAAAAAA;

    sp = (uint32_t*)(((uintptr_t)sp) & ~((uintptr_t)0x7));
    task2.psp = sp;                          // PSP for Task2 restore in PendSV
}

/*
 * This function initialize the first context of the ROTS
 * Therefore it pops manually the register R4-R11
 * Afterwards, through the "BX LR" instruction the rest of the registers get popped and the executing of the first task is starting
 */
void OS_vStartRTOS(void)
{
    __asm volatile(
        "CPSID   i                  \n"

        // Use PSP in Thread mode
        "MOV     r0, #2             \n"
        "MSR     CONTROL, r0        \n"
        "ISB                        \n"

        // PSP = top of Task1 stack (clean stack for direct start)
        "LDR     r0, =task1_top     \n"
        "LDR     r0, [r0]           \n"
        "MSR     PSP, r0            \n"

        // If Task1 returns, go to TaskExit
        "LDR     r1, =TaskExit      \n"
        "ORR     r1, r1, #1         \n"   // ensure Thumb bit
        "MOV     LR, r1             \n"

        "CPSIE   i                  \n"

        // Branch to Task1 entry (Thumb)
        "LDR     r0, =Task1Func     \n"
        "ORR     r0, r0, #1         \n"
        "BX      r0                 \n"
    );
}

void OS_vAddThreads(void)
{
	task1.nextPt = &task2;
	task2.nextPt = &task1;
	currentTask = &task1;
}

/* By entering, R0-R3, R12, LR and xPSR are automatically saved */
__attribute__((naked)) PendSV_Handler(void)
{
	/* Disable interrupts */
	__asm volatile ("CPSID i");

	/* Load psp for saving r4-r11 */
	__asm("MRS R0, psp");

	/* Saving r4-r11 on the stack of the current task */
	__asm("STMDB R0!, {R4-R11}");

	/* Load the psp of the current task */
	__asm("LDR R1, =currentTask");		// Load address
	__asm("LDR R2, [R1]");				// Load value of the address of R1

	/* Store the new psp (R1) into current stack pointer of the current task (R0) */
	__asm("STR R0, [R2]");

	/* Access the nextPt element by increment the address of the current task by 4. R0 is now the address of the next task */
	/* Load the value of the next Task pointer */
	__asm("LDR R3, [R2, #4]");

	/* Store the next task pointer into the currentTask */
	__asm("STR R3, [R1]");

	/* Load the psp of the next task, which is still in R3 */
	__asm("LDR R0, [R3]");

	/* Pop the registers r4-r11 */
	__asm("LDMIA R0!, {R4-R11}");

	/* Store the next task pointer into the psp */
	__asm("MSR psp, R0");

	/* Enable interrupts */
	__asm volatile ("CPSIE i");

	/* Exit the handler */
	__asm("BX LR");
}
