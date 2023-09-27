/**
*  \file    settings_thread.h
*  \brief   This file settings for threads.
*  \author  arvtom
*/

#ifndef SETTINGS_THREAD_H
#define SETTINGS_THREAD_H

/* ---------------------------- Includes ---------------------------- */

/* ---------------------------- Defines ---------------------------- */
#define DEBUG_PLANT_BOSS

#ifdef DEBUG_PLANT_BOSS
    #warning DEBUG_PLANT_BOSS flag is enabled
#endif

#define STACK_THREAD_APP                8192u
#define STACK_THREAD_INPUT              8192u
#define STACK_THREAD_OUTPUT             8192u
#define STACK_THREAD_NETWORK            8192u
#define STACK_THREAD_MEMORY             8192u

#define PRIORITY_THREAD_APP             2u
#define PRIORITY_THREAD_INPUT           5u
#define PRIORITY_THREAD_OUTPUT          5u
#define PRIORITY_THREAD_NETWORK         3u
#define PRIORITY_THREAD_MEMORY          4u

#define DELAY_HANDLE_THREAD_APP         100u
#define DELAY_HANDLE_THREAD_INPUT       1u
#define DELAY_HANDLE_THREAD_OUTPUT      1u
#define DELAY_HANDLE_THREAD_NETWORK     1u
#define DELAY_HANDLE_THREAD_MEMORY      1u

#define SIZE_QUEUE_INPUT_TO_APP         16
#define SIZE_QUEUE_WIFI_TO_APP          20
#define SIZE_QUEUE_MEMORY_TO_APP        1
#define SIZE_QUEUE_APP_TO_WIFI          150
#define SIZE_QUEUE_APP_TO_MEMORY        1

/* ---------------------------- Typedefs ---------------------------- */

/* ---------------------------- Public functions ---------------------------- */

/* ---------------------------- Private functions ---------------------------- */

/* ---------------------------- Interrupt callbacks ---------------------------- */

#endif