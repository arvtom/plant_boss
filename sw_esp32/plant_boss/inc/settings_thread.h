/**
*  \file    settings_thread.h
*  \brief   This file settings for threads.
*  \author  arvtom
*/

#ifndef SETTINGS_THREAD_H
#define SETTINGS_THREAD_H

/* ---------------------------- Includes ---------------------------- */

/* ---------------------------- Defines ---------------------------- */
#define STACK_THREAD_APP            4096u
#define STACK_THREAD_INPUT          4096u
#define STACK_THREAD_OUTPUT         4096u
#define STACK_THREAD_NETWORK        4096u
#define STACK_THREAD_MEMORY         4096u

#define PRIORITY_THREAD_APP         10u
#define PRIORITY_THREAD_INPUT       10u
#define PRIORITY_THREAD_OUTPUT      10u
#define PRIORITY_THREAD_NETWORK     10u
#define PRIORITY_THREAD_MEMORY      10u

#define SIZE_QUEUE_INPUT_TO_APP         16
#define SIZE_QUEUE_WIFI_TO_APP          1
#define SIZE_QUEUE_MEMORY_TO_APP        1
#define SIZE_QUEUE_APP_TO_WIFI          150
#define SIZE_QUEUE_APP_TO_MEMORY        1

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Public functions ---------------------------- */

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif