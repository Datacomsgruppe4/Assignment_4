#pragma once
#ifndef TIMER_H
#define TIMER_H
#include <stdbool.h>
#include <stdint.h>

static volatile bool counter_flag = false;
static volatile uint32_t counter = 0;

void timer_init(uint16_t compare_value);
#endif

