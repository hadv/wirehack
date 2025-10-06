#include <stdint.h>
#include "context.h"
#include "sched.h"

#define NTASK 2
#define STACK_SIZE 4096

/**
 * Task control block
 */
typedef struct task {
    context_t  ctx;                 // Saved context
    uint8_t    stack[STACK_SIZE];   // Task stack
} task_t;

// Task array and current task index
static task_t tasks[NTASK];
static int cur = 0;

// External assembly function for context switch
extern void swtch(context_t **old_ctx, context_t *new_ctx);

/**
 * Setup a task with its entry point
 * Initializes the task's stack and context so that when we switch to it,
 * it will start executing at the entry function
 */
static void setup_task(task_t *t, task_fn_t entry) {
    // Set stack pointer to top of stack (stacks grow downward)
    // Align to 16-byte boundary as per RISC-V ABI
    uint64_t sp = (uint64_t)(t->stack + STACK_SIZE);
    sp &= ~0xFUL;  // Align to 16 bytes

    // Initialize context: when swtch() returns, it will jump to entry
    t->ctx.ra = (uint64_t)entry;
    t->ctx.sp = sp;

    // Zero all saved registers for cleanliness
    t->ctx.s0 = t->ctx.s1 = t->ctx.s2 = t->ctx.s3 = 0;
    t->ctx.s4 = t->ctx.s5 = t->ctx.s6 = t->ctx.s7 = 0;
    t->ctx.s8 = t->ctx.s9 = t->ctx.s10 = t->ctx.s11 = 0;
}

/**
 * Perform one context switch to the next task
 * This implements simple round-robin scheduling between two tasks
 */
void schedule_once(void) {
    int next = (cur + 1) % NTASK;
    
    // Get pointers to current and next contexts
    context_t *oldp = &tasks[cur].ctx;
    context_t *newp = &tasks[next].ctx;
    
    // Update current task index
    cur = next;
    
    // Perform the context switch
    // Note: swtch takes &oldp (pointer to pointer) so it can save to *oldp
    swtch(&oldp, newp);
}

/**
 * Initialize the scheduler with two tasks
 */
void tasks_init(task_fn_t f0, task_fn_t f1) {
    setup_task(&tasks[0], f0);
    setup_task(&tasks[1], f1);
    cur = 0;  // Start with task 0
}

/**
 * Get the current task ID
 */
int sched_current_task(void) {
    return cur;
}

