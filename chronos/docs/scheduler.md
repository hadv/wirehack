# Chronos Scheduler Module

## Overview

The scheduler module (`src/modules/sched/`) implements a minimal preemptive multitasking scheduler for RISC-V using context switching and timer interrupts.

## Architecture

### Components

1. **context.h** - Defines the task context structure containing callee-saved registers
2. **switch.S** - Assembly implementation of context switching
3. **sched.c** - C implementation of the scheduler logic
4. **sched.h** - Public API for the scheduler

### Context Structure

The context contains all callee-saved registers according to the RISC-V ABI:
- `ra` (x1) - Return address
- `sp` (x2) - Stack pointer  
- `s0-s11` (x8-x9, x18-x27) - Saved registers

Caller-saved registers (`t*`, `a*`) are not saved as they are preserved by the calling convention.

### Context Switch Implementation

The `swtch()` function in `switch.S` performs the context switch:

```assembly
swtch(context_t **old_ctx, context_t *new_ctx)
```

1. Saves current context (ra, sp, s0-s11) to `*old_ctx`
2. Restores new context from `new_ctx`
3. Returns to the new task via `ret` (jumps to restored `ra`)

### Scheduler Logic

The scheduler implements simple round-robin scheduling between two tasks:

- **Cooperative mode**: Tasks call `schedule_once()` to yield CPU
- **Preemptive mode**: Timer ISR calls `schedule_once()` to force task switches

## Usage

### Initializing the Scheduler

```c
#include "modules/sched/sched.h"

void taskA(void) {
    while (1) {
        // Task A work
    }
}

void taskB(void) {
    while (1) {
        // Task B work
    }
}

void kernel_main(void) {
    // Initialize scheduler with two tasks
    tasks_init(taskA, taskB);
    
    // Setup timer for preemptive scheduling
    clint_timer_init(10000000UL, 10000);  // 10ms ticks
    
    // Jump to first task
    taskA();
}
```

### Timer Integration

For preemptive scheduling, the timer ISR calls `schedule_once()`:

```c
void clint_timer_isr(void) {
    // Re-arm timer
    // ...
    
    // Preemptive task switch
    schedule_once();
}
```

## Implementation Details

### Task Setup

Each task has:
- 4KB stack
- Initialized context with `ra` pointing to task entry function
- Stack pointer aligned to 16-byte boundary

### Bootstrap Process

1. `tasks_init()` sets up both task contexts
2. Kernel jumps directly to `taskA()`
3. Timer interrupts trigger `schedule_once()` to switch between tasks

### Context Switch Flow

```
Current Task
    |
    v
[Timer Interrupt]
    |
    v
clint_timer_isr()
    |
    v
schedule_once()
    |
    v
swtch(&old_ctx, new_ctx)
    |
    +-- Save current context
    |
    +-- Restore new context
    |
    v
[Return to new task]
```

## Testing

The scheduler can be tested in two modes:

### Cooperative Mode

Tasks explicitly call `schedule_once()` to yield:

```c
void taskA(void) {
    for (int i = 0; i < 5; i++) {
        uart_puts("[Task A]\n");
        schedule_once();
    }
}
```

### Preemptive Mode

Timer automatically switches tasks:

```c
void taskA(void) {
    while (1) {
        // Work - will be preempted by timer
        counter_a++;
    }
}
```

## Future Enhancements

- [ ] Support for more than 2 tasks
- [ ] Task priorities
- [ ] Task states (RUNNING, READY, BLOCKED)
- [ ] Sleep/wake mechanisms
- [ ] Mutex and semaphore support
- [ ] Dynamic task creation/deletion
- [ ] Context switch latency measurement

## References

- xv6-riscv scheduler implementation
- RISC-V Calling Convention (ABI)
- RISC-V Privileged Specification (timer interrupts)

