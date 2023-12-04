/*
 * This file is a demo that shows some of the capabilities of HyperVec.
 * 
 * In this example, we create a simple TODO program that organizes your daily tasks :D
 * 
 */

#include "hypervec.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Task_s {
    const char *task_name;
    const char *task_description;
    bool task_done;
} Task_t;

#define get_task_name(i)            \
    (i == 0) ? "Create a library" : \
    (i == 1) ? "Call it Hypervec" : \
    (i == 2) ? "Implement it" :     \
    (i == 3) ? "Publish it" :       \
    (i == 4) ? "Update it" :        \
    "Unknown task"

#define get_task_description(i)                                                                               \
    (i == 0) ? "Create a library that can handle dynamic array operations using the C programming language" : \
    (i == 1) ? "The library we just created needs a name, I guess I can call it HyperVec!" :                  \
    (i == 2) ? "The library still needs to be implemented" :                                                  \
    (i == 3) ? "Now that the library was implemented, we need to publish it" :                                \
    (i == 4) ? "The library has some errors, time to fix them!" :                                             \
    "idk"

static int mark_task_done(Task_t *task) {
    if (NULL == task) {
        return -1;
    }
    (*(Task_t*) task).task_done = true;
    return 0;
}

static void mark_all_tasks_done(void *elem) {
    if (NULL == elem) {
        return;
    }
    (*(Task_t*) elem).task_done = true;
}

static void list_tasks(GVec_t *tasks) {
    printf("------------ My TODO List ------------\n");

    for (size_t i = 0; i < tasks->occupied; i++) {
        Task_t curr_task = *(Task_t*) __gv_get(tasks, i);

        printf("* %s:\n   %s\n   status: [%s]\n",
            curr_task.task_name,
            curr_task.task_description,
            (curr_task.task_done)      ? "DONE" : "NOT DONE",
            (i == tasks->occupied - 1) ? "" : "\n"
        );
    }
    printf("--------------------------------------\n\n");
}

int main(void) {
    printf(HYPERVEC_RELEASE"\n");

    // Create a task vector
    GVec_t tasks = {0};

    // Allocate space for a single task
    gv_alloc(tasks, 1, Task_t);

    // Push 10 new tasks, automatically filling up their respective info
    for (unsigned int i = 0; i < 5; i++) {
        gv_push(tasks, ((Task_t) {
                get_task_name(i),
                get_task_description(i),
                false
            })
        );
    }
    // Mark the first and third tasks as done
    mark_task_done((Task_t*) gv_get(tasks, 0));
    mark_task_done((Task_t*) gv_get(tasks, 2));

    // list all tasks
    list_tasks(&tasks);

    // Mark every task as done
    gv_iter(tasks, mark_all_tasks_done);

    // list all tasks again
    list_tasks(&tasks);

    // Pop a task and print it
    Task_t popped_task;
    gv_pop(tasks, popped_task);

    printf("Popped task:\n");

    printf("* %s:\n   %s\n   status: [%s]\n\n",
        popped_task.task_name,
        popped_task.task_description,
        popped_task.task_done ? "DONE" : "NOT DONE"
    );

    // Free the tasks vector
    gv_free(tasks);

    return 0;
}
