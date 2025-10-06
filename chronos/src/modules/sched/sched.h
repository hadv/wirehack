#pragma once
#include <stdint.h>

/**
 * Task function type
 */
typedef void (*task_fn_t)(void);

/**
 * Initialize the scheduler with two tasks
 * @param f0 Function pointer for task 0
 * @param f1 Function pointer for task 1
 */
void tasks_init(task_fn_t f0, task_fn_t f1);

/**
 * Perform one context switch to the next task
 * This is cooperative scheduling - call this to yield CPU
 */
void schedule_once(void);

/**
 * Get the current task ID (0 or 1)
 */
int sched_current_task(void);

