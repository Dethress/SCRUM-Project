/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
  /* USER CODE END Header */
  /* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct {
    uint8_t row;
    uint8_t col;
} Position;
typedef enum { DIR_NONE = 0, DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT } Dir;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define NROW 12
#define NCOL 16
#define SQ_SIZE 240/NROW
#define TUNNEL_ROW   (NROW/2)
#define TUNNEL_LEFT  0
#define TUNNEL_RIGHT (NCOL-1)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
Dir pacmanDir = DIR_RIGHT;
uint8_t fruitExists = 0;
uint8_t fruitRow = 0;
uint8_t fruitCol = 0;
uint32_t fruitSpawnTimer = 0;
uint32_t fruitDespawnTimer = 0;
uint32_t fruitSpawnInterval = 0;
const uint32_t fruitLifetime = 6000;
const uint16_t fruitColor = LCD_COLOR_MAGENTA;
uint32_t ledTimer = 0;
uint32_t ledBlinkTimer = 0;
uint8_t ledState = 0;
uint8_t lifeLostFlash = 0;
uint32_t lifeLostTimer = 0;
uint8_t lifeLostCount = 0;
uint8_t pacAnimFrame = 0;
uint32_t pacAnimTimer = 0;
const uint32_t pacAnimDuration = 100;
uint8_t freezeActive = 0;
uint32_t freezeTimer = 0;
uint32_t freezeDuration = 3000;
uint8_t powerupRow = 0;
uint8_t powerupCol = 0;
uint8_t powerupExists = 0;
typedef enum { PINKY_CHASE = 0, PINKY_SCATTER = 1 } PinkyMode;
PinkyMode pinkyMode = PINKY_CHASE;
uint32_t pinkyModeTimer = 0;
const uint32_t pinkyModeDuration = 2000;
uint8_t ghostSpeedLevel = 1;
const uint16_t ghostSpeedMs[3] = { 166, 111, 83 };
const uint16_t freezeTimeByDifficulty[3] = { 4000, 3000, 2000 };


#define BTN_DEBOUNCE_MS       20U
#define BTN_REPEAT_DELAY_MS  160U
#define BTN_REPEAT_MS         80U

static Dir     g_btn_last = DIR_NONE;
static uint32_t g_btn_last_change_ms = 0;
static uint32_t g_btn_last_repeat_ms = 0;
static uint32_t g_btn_first_repeat_ms = 0;


#define FRAME_MS_TARGET   33U
static volatile uint32_t g_frame_ms = 0;
static volatile uint32_t g_fps10 = 0;
static uint32_t pinky_timer_ms = 0;


uint8_t livesLeft = 3;
uint8_t paused = 0;
uint8_t gameOverState = 0;

static uint8_t  sel_pressed = 0;
static uint32_t sel_change_ms = 0;
static uint32_t sel_down_start_ms = 0;

uint16_t totalDots = 0;

static const uint8_t walls[NROW][NCOL] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,1,0,0,0,0,1,1,0,0},
  {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
  {0,0,0,1,1,1,1,1,0,1,1,1,1,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,1,0,0,0,0,1,1,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};



__ALIGN_END uint8_t pinkyLeft[776] = {
0x42,0x4d,0x08,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
0x00,0x00,0x13,0x00,0x00,0x00,0x13,0x00,0x00,0x00,0x01,0x00,0x10,0x00,0x00,0x00,
0x00,0x00,0xd0,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1
};
__ALIGN_END uint8_t pinkyRight[776] = {
0x42,0x4d,0x08,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
0x00,0x00,0x13,0x00,0x00,0x00,0x13,0x00,0x00,0x00,0x01,0x00,0x10,0x00,0x00,0x00,
0x00,0x00,0xd0,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,
0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0xd9,0xfc,
0xd9,0xfc,0xd9,0xfc,0xd9,0xfc,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1,
0x45,0xa1,0x45,0xa1,0x45,0xa1,0x45,0xa1
};

uint8_t gameBoard[NROW][NCOL] = { {0} };

uint8_t visitedFields[NROW][NCOL] = { {0} };
Position pacmanPos = { 0, 0 };
Position pinkyPos = { NROW - 1, NCOL - 1 };
JOYState_TypeDef JoyState = JOY_NONE;
uint16_t pointsCounter = 0;

uint8_t gameStatus = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static inline void DoMove(Dir d);
static void HandleInput(uint32_t now_ms);


/* USER CODE BEGIN PFP */
void myRedLedInit(void);
void myLowLevelRedLedInit(void);
int8_t myAdc1Init(void);
uint32_t getSeedValue(void);
void gameSetup(void);
void moveDown(void);
void moveUp(void);
void moveLeft(void);
void moveRight(void);
void movePinky(void);
void myDrawPixel(uint16_t, uint16_t, uint16_t);
void myDrawFullRectangle(uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);
void myDrawFullCircle(uint16_t, uint16_t, uint16_t, uint16_t);
void gameOver(void);
void DrawHeart(uint16_t x, uint16_t y, uint16_t color);
void DrawHUD(void);
void quickRestart(void);
void showPauseBannerInHUD(void);
void clearPauseBannerInHUD(void);
void drawWalls(void);
void loseLifeAndRespawn(void);
void UpdateLED(uint32_t now_ms);
uint8_t difficultyLevel = 1;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */
    uint32_t seed = 0;
    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */
    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */
    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    /* USER CODE BEGIN 2 */
    /* Initialize the LEDs */
    // BSP_LED_Init(LED_GREEN);
    // BSP_LED_Init(LED_ORANGE);
    // BSP_LED_Init(LED_RED);
    // myRedLedInit();
    myLowLevelRedLedInit();
    // BSP_LED_Init(LED_BLUE);

    /* Configure the Key push-button in GPIO Mode */
    // BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

    /*## Initialize the LCD #################################################*/
    if (BSP_LCD_Init() != LCD_OK) {
        BSP_LED_On(LED_RED);
        Error_Handler();
    }

    BSP_LCD_Clear(LCD_COLOR_DARKGRAY);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);



    if (BSP_JOY_Init(JOY_MODE_GPIO) != IO_OK) {
        BSP_LCD_DisplayStringAt(0, 145, (uint8_t*)"ERROR", CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, 160, (uint8_t*)"Joystick cannot be initialized", CENTER_MODE);
        Error_Handler();
    }
    showStartMenu();

    if (myAdc1Init() != HAL_OK) {
        BSP_LCD_DisplayStringAt(0, 145, (uint8_t*)"ERROR", CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, 160, (uint8_t*)"ADC1 cannot be initialized", CENTER_MODE);
        Error_Handler();
    }


    seed = getSeedValue();
    srand(seed);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    gameSetup();
    DrawHUD();

    uint8_t firstFrame = 1;

    while (1) {
        uint32_t frame_start = HAL_GetTick();
        HandleInput(frame_start);
        uint32_t now_ms = HAL_GetTick();
        uint32_t elapsed = now_ms - frame_start;
        if (elapsed < FRAME_MS_TARGET) {
            HAL_Delay(FRAME_MS_TARGET - elapsed);
        }
        g_frame_ms = HAL_GetTick() - frame_start;
        UpdateLED(g_frame_ms);
        pacAnimTimer += g_frame_ms;
        if (pacAnimTimer >= pacAnimDuration) {
            pacAnimFrame = (pacAnimFrame + 1) % 3;
            pacAnimTimer = 0;
        }
        g_fps10 = (g_frame_ms > 0U) ? (10000U / g_frame_ms) : 0U;

        if (!paused && !gameOverState) {
            if (firstFrame) {
                firstFrame = 0;
                pinky_timer_ms = ghostSpeedMs[ghostSpeedLevel];
            }

            pinky_timer_ms += g_frame_ms;

            if (freezeActive) {
                freezeTimer += g_frame_ms;

                if (freezeTimer >= freezeDuration) {
                    freezeActive = 0;
                }
            }
            else {
                pinky_timer_ms += g_frame_ms;
                while (pinky_timer_ms >= ghostSpeedMs[ghostSpeedLevel]) {
                    movePinky();
                    pinky_timer_ms -= ghostSpeedMs[ghostSpeedLevel];
                }
            }
            pinkyModeTimer += g_frame_ms;
            if (pinkyModeTimer >= pinkyModeDuration) {
                pinkyMode = (pinkyMode == PINKY_CHASE) ? PINKY_SCATTER : PINKY_CHASE;
                pinkyModeTimer = 0;
            }
            if (pointsCounter >= totalDots) { gameStatus = 2; gameOver(); }
            if ((pinkyPos.row == pacmanPos.row) && (pinkyPos.col == pacmanPos.col)) {
                loseLifeAndRespawn();
            }
        }
        myDrawFullCircle(
            powerupCol * SQ_SIZE + SQ_SIZE / 2,
            powerupRow * SQ_SIZE + SQ_SIZE / 2,
            SQ_SIZE / 2 - 2,
            LCD_COLOR_GREEN
        );

        if (!paused && !gameOverState) {
            fruitSpawnTimer += g_frame_ms;

            if (!fruitExists && fruitSpawnTimer >= fruitSpawnInterval) {
                fruitSpawnTimer = 0;
                fruitDespawnTimer = 0;

                fruitSpawnInterval = (rand() % 2) ? 15000 : 20000;

                do {
                    fruitRow = rand() % NROW;
                    fruitCol = rand() % NCOL;
                } while (walls[fruitRow][fruitCol] ||
                    (fruitRow == pacmanPos.row && fruitCol == pacmanPos.col) ||
                    (fruitRow == pinkyPos.row && fruitCol == pinkyPos.col));

                fruitExists = 1;

                myDrawFullCircle(
                    fruitCol * SQ_SIZE + SQ_SIZE / 2,
                    fruitRow * SQ_SIZE + SQ_SIZE / 2,
                    SQ_SIZE / 2 - 3,
                    fruitColor
                );
            }

            if (fruitExists) {

                fruitDespawnTimer += g_frame_ms;

                if (pacmanPos.row == fruitRow && pacmanPos.col == fruitCol) {
                    pointsCounter += 25;
                    fruitExists = 0;
                    myDrawFullRectangle(
                        fruitCol * SQ_SIZE + 1,
                        fruitRow * SQ_SIZE + 1,
                        SQ_SIZE - 1, SQ_SIZE - 1,
                        LCD_COLOR_BLACK
                    );
                }
                else if (fruitDespawnTimer >= fruitLifetime) {
                    fruitExists = 0;

                    myDrawFullRectangle(
                        fruitCol * SQ_SIZE + 1,
                        fruitRow * SQ_SIZE + 1,
                        SQ_SIZE - 1, SQ_SIZE - 1,
                        LCD_COLOR_BLACK
                    );
                }
            }
        }
        DrawHUD();

        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
    RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
    RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
    RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
    RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_ADC
        | RCC_PERIPHCLK_USB;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV3;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
        Error_Handler();
    }
    // HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_HSE, RCC_MCODIV_1);
    // __HAL_RCC_PLLI2S_ENABLE();
}

/* USER CODE BEGIN 4 */

void UpdateLED(uint32_t now_ms)
{
    if (lifeLostFlash) {
        lifeLostTimer += now_ms;

        if (lifeLostTimer >= 100) {
            lifeLostTimer = 0;
            ledState ^= 1;
            if (ledState) GPIOD->ODR |= (1 << 3);
            else          GPIOD->ODR &= ~(1 << 3);

            lifeLostCount++;
            if (lifeLostCount >= 10) {
                lifeLostFlash = 0;
                lifeLostCount = 0;
                ledState = 0;
                GPIOD->ODR &= ~(1 << 3);
            }
        }
        return;
    }
    if (freezeActive) {
        ledBlinkTimer += now_ms;
        if (ledBlinkTimer >= 150) {
            ledBlinkTimer = 0;
            ledState ^= 1;
            if (ledState) GPIOD->ODR |= (1 << 3);
            else          GPIOD->ODR &= ~(1 << 3);
        }
        return;
    }
    if (!paused && !gameOverState) {
        ledTimer += now_ms;

        if (ledTimer >= 1000) {
            ledTimer = 0;
            GPIOD->ODR |= (1 << 3);
            HAL_Delay(30);
            GPIOD->ODR &= ~(1 << 3);
        }
        return;
    }
    GPIOD->ODR &= ~(1 << 3);
}


void drawPacmanAnim(uint16_t col, uint16_t row, Dir d, uint8_t frame) {

    uint16_t cx = col * SQ_SIZE + SQ_SIZE / 2;
    uint16_t cy = row * SQ_SIZE + SQ_SIZE / 2;
    uint16_t r = SQ_SIZE / 2 - 1;

    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);

    if (frame == 2) {
        myDrawFullCircle(cx, cy, r, LCD_COLOR_YELLOW);
        return;
    }

    int angleStart, angleEnd;

    if (d == DIR_RIGHT) {
        angleStart = 20 + frame * 10;
        angleEnd = 360 - angleStart;
    }
    else if (d == DIR_LEFT) {
        angleStart = 200 - frame * 10;
        angleEnd = 160 + frame * 10;
    }
    else if (d == DIR_UP) {
        angleStart = 290 - frame * 10;
        angleEnd = 250 + frame * 10;
    }
    else { // DOWN
        angleStart = 110 - frame * 10;
        angleEnd = 70 + frame * 10;
    }

    for (int i = 0;i < 360;i++) {
        if (i < angleStart || i > angleEnd) {
            float rad = i * 0.0174533f;
            int x = cx + r * cosf(rad);
            int y = cy + r * sinf(rad);
            myDrawPixel(x, y, LCD_COLOR_YELLOW);
        }
    }
}

void myRedLedInit(void) {
    GPIO_InitTypeDef gpioInit = { 0 };

    /* Enable the GPIO_LED clock */
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /* Configure the GPIO_LED pin */
    gpioInit.Pin = GPIO_PIN_3;
    gpioInit.Mode = GPIO_MODE_OUTPUT_PP;
    gpioInit.Pull = GPIO_NOPULL;
    gpioInit.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOD, &gpioInit);
    // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, 0);
}


// Function configuring RED LED using registers:
void myLowLevelRedLedInit(void) {
    /* Enable the GPIO_LED clock */
    // Set bit 5 to '1':
    // RCC->APB2ENR |= 0b00000000000000000000000000100000;
    RCC->APB2ENR |= 1 << 5;

    // Configure PD3 as output 2 MHz:
    // Set bit 13 and 12 to '10':
    // GPIOD->CRL = GPIOD->CRL | 0b00000000000000000010000000000000;
    // GPIOD->CRL |= 0b00000000000000000010000000000000;
    GPIOD->CRL |= 1 << 13;
    // GPIOD->CRL |= 0x00002000;
    // GPIOD->CRL &= 0b11111111111111111110111111111111;
    // GPIOD->CRL &=~0b00000000000000000001000000000000;
    GPIOD->CRL &= ~(1 << 12);
    // Configure PD3 as output push/pull:
    // Set bits 15 and 14 to '00':
    GPIOD->CRL &= ~0b00000000000000001100000000000000;
}


// Function initializing ADC1:
int8_t myAdc1Init(void) {
    uint8_t ret = HAL_OK;
    ADC_HandleTypeDef hadc1 = { 0 };
    ADC_ChannelConfTypeDef sConfig = { 0 };

    /** Common configuration */
    hadc1.Instance = ADC1;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    ret = HAL_ADC_Init(&hadc1);
    if (ret != HAL_OK) {
        return ret;
    }

    /** Configure regular channel group */
    sConfig.Channel = ADC_CHANNEL_7;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
    ret = HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    return ret;
}


// Function used to force ADC1 to sample a channel (channel 7 in our case).
// Returns seed necessary to initialize random number generator:
uint32_t getSeedValue(void) {
    uint32_t ret = 0;

    ADC1->CR2 |= 0x00000001;
    // Wait for the ADC to stabilize:
    HAL_Delay(500);
    // Start conversion:
    ADC1->CR2 |= 0x00000001;
    // Wait for end of the conversion:
    while ((ADC1->SR & 0x00000002) == 0);
    ret = (uint32_t)ADC1->DR;
    // Clear the STRT bit:
    ADC1->SR &= ~0x00000010;

    return ret;
}



void gameSetup(void) {
    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);

    for (uint16_t i = 0; i < 240; i += SQ_SIZE) BSP_LCD_DrawHLine(0, i, 320);
    for (uint16_t i = 0; i < 320; i += SQ_SIZE) BSP_LCD_DrawVLine(i, 0, 240);

    totalDots = 0;
    for (uint8_t r = 0; r < NROW; ++r) {
        for (uint8_t c = 0; c < NCOL; ++c) {
            gameBoard[r][c] = 0;
            visitedFields[r][c] = 0;

            if (!walls[r][c]) {
                myDrawPixel(c * SQ_SIZE + SQ_SIZE / 2, r * SQ_SIZE + SQ_SIZE / 2, LCD_COLOR_WHITE);
                totalDots++;
            }
        }
    }

    drawWalls();

    do { pacmanPos.row = rand() % NROW; pacmanPos.col = rand() % NCOL; } while (walls[pacmanPos.row][pacmanPos.col]);
    gameBoard[pacmanPos.row][pacmanPos.col] = 1;
    visitedFields[pacmanPos.row][pacmanPos.col] = 1;
    pointsCounter = 1;
    myDrawFullCircle(SQ_SIZE * pacmanPos.col + SQ_SIZE / 2, SQ_SIZE * pacmanPos.row + SQ_SIZE / 2, SQ_SIZE / 2 - 1, LCD_COLOR_YELLOW);

    do { pinkyPos.row = rand() % NROW; pinkyPos.col = rand() % NCOL; } while (walls[pinkyPos.row][pinkyPos.col] || (pinkyPos.row == pacmanPos.row && pinkyPos.col == pacmanPos.col));
    gameBoard[pinkyPos.row][pinkyPos.col] = 2;
    BSP_LCD_DrawBitmap(pinkyPos.col * SQ_SIZE + 1, pinkyPos.row * SQ_SIZE + 1, pinkyLeft);


    DrawHUD();
    fruitExists = 0;
    fruitSpawnTimer = 0;
    fruitDespawnTimer = 0;
    fruitSpawnInterval = (rand() % 2) ? 15000 : 20000;
    freezeDuration = freezeTimeByDifficulty[difficultyLevel];
}

void showStartMenu(void)
{
    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    BSP_LCD_SetFont(&Font16);

    uint8_t selection = difficultyLevel;
    uint8_t lastSelection = 255;

    while (1) {

        JOYState_TypeDef js = BSP_JOY_GetState();

        if (js == JOY_UP && selection > 0) {
            selection--;
        }
        else if (js == JOY_DOWN && selection < 2) {
            selection++;
        }
        else if (js == JOY_SEL) {

            while (BSP_JOY_GetState() == JOY_SEL) {
                HAL_Delay(10);
            }

            difficultyLevel = selection;
            ghostSpeedLevel = difficultyLevel;
            freezeDuration = freezeTimeByDifficulty[difficultyLevel];

            HAL_Delay(150);
            return;
        }
        BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
        BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"PAC-MAN", CENTER_MODE);
        BSP_LCD_DisplayStringAt(0, 50, (uint8_t*)"SELECT DIFFICULTY", CENTER_MODE);

        if (selection != lastSelection) {

            BSP_LCD_Clear(LCD_COLOR_BLACK);
            BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"PAC-MAN", CENTER_MODE);
            BSP_LCD_DisplayStringAt(0, 50, (uint8_t*)"SELECT DIFFICULTY", CENTER_MODE);

            if (selection == 0) BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
            else                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_DisplayStringAt(0, 100, (uint8_t*)"EASY", CENTER_MODE);

            if (selection == 1) BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
            else                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_DisplayStringAt(0, 130, (uint8_t*)"NORMAL", CENTER_MODE);

            if (selection == 2) BSP_LCD_SetTextColor(LCD_COLOR_RED);
            else                BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
            BSP_LCD_DisplayStringAt(0, 160, (uint8_t*)"HARD", CENTER_MODE);

            lastSelection = selection;
        }

        HAL_Delay(100);
    }
}



void moveUp(void) {
    pacmanDir = DIR_UP;
    uint8_t r2 = (pacmanPos.row == 0) ? (NROW - 1) : (pacmanPos.row - 1);
    uint8_t c2 = pacmanPos.col;
    if (walls[r2][c2]) return;

    myDrawFullRectangle(pacmanPos.col * SQ_SIZE + 1, pacmanPos.row * SQ_SIZE + 1, SQ_SIZE - 1, SQ_SIZE - 1, LCD_COLOR_BLACK);
    gameBoard[pacmanPos.row][pacmanPos.col] = 0;

    pacmanPos.row = r2;
    gameBoard[pacmanPos.row][pacmanPos.col] = 1;

    if (visitedFields[pacmanPos.row][pacmanPos.col] == 0) {
        pointsCounter++;
        visitedFields[pacmanPos.row][pacmanPos.col] = 1;
    }

    if (powerupExists && pacmanPos.row == powerupRow && pacmanPos.col == powerupCol) {
        freezeActive = 1;
        freezeTimer = 0;
        powerupExists = 0;

        myDrawFullRectangle(
            powerupCol * SQ_SIZE + 1,
            powerupRow * SQ_SIZE + 1,
            SQ_SIZE - 1, SQ_SIZE - 1,
            LCD_COLOR_BLACK
        );
    }

    drawPacmanAnim(pacmanPos.col, pacmanPos.row, pacmanDir, pacAnimFrame);
}

void moveDown(void) {
    pacmanDir = DIR_DOWN;
    uint8_t r2 = (pacmanPos.row == NROW - 1) ? 0 : (pacmanPos.row + 1);
    uint8_t c2 = pacmanPos.col;
    if (walls[r2][c2]) return;

    myDrawFullRectangle(pacmanPos.col * SQ_SIZE + 1, pacmanPos.row * SQ_SIZE + 1, SQ_SIZE - 1, SQ_SIZE - 1, LCD_COLOR_BLACK);
    gameBoard[pacmanPos.row][pacmanPos.col] = 0;

    pacmanPos.row = r2;
    gameBoard[pacmanPos.row][pacmanPos.col] = 1;

    if (visitedFields[pacmanPos.row][pacmanPos.col] == 0) {
        pointsCounter++;
        visitedFields[pacmanPos.row][pacmanPos.col] = 1;
    }

    if (powerupExists && pacmanPos.row == powerupRow && pacmanPos.col == powerupCol) {
        freezeActive = 1;
        freezeTimer = 0;
        powerupExists = 0;

        myDrawFullRectangle(
            powerupCol * SQ_SIZE + 1,
            powerupRow * SQ_SIZE + 1,
            SQ_SIZE - 1, SQ_SIZE - 1,
            LCD_COLOR_BLACK
        );
    }


    drawPacmanAnim(pacmanPos.col, pacmanPos.row, pacmanDir, pacAnimFrame);
}

void moveLeft(void) {
    pacmanDir = DIR_LEFT;
    uint8_t r2 = pacmanPos.row;
    uint8_t c2 = pacmanPos.col;

    if (pacmanPos.row == TUNNEL_ROW && pacmanPos.col == TUNNEL_LEFT) {
        c2 = TUNNEL_RIGHT;
    }
    else {
        c2 = (pacmanPos.col == 0) ? (NCOL - 1) : (pacmanPos.col - 1);
    }
    if (walls[r2][c2]) return;

    myDrawFullRectangle(pacmanPos.col * SQ_SIZE + 1, pacmanPos.row * SQ_SIZE + 1, SQ_SIZE - 1, SQ_SIZE - 1, LCD_COLOR_BLACK);
    gameBoard[pacmanPos.row][pacmanPos.col] = 0;

    pacmanPos.col = c2;
    gameBoard[pacmanPos.row][pacmanPos.col] = 1;

    if (visitedFields[pacmanPos.row][pacmanPos.col] == 0) {
        pointsCounter++;
        visitedFields[pacmanPos.row][pacmanPos.col] = 1;
    }
    if (powerupExists && pacmanPos.row == powerupRow && pacmanPos.col == powerupCol) {
        freezeActive = 1;
        freezeTimer = 0;
        powerupExists = 0;

        myDrawFullRectangle(
            powerupCol * SQ_SIZE + 1,
            powerupRow * SQ_SIZE + 1,
            SQ_SIZE - 1, SQ_SIZE - 1,
            LCD_COLOR_BLACK
        );
    }


    drawPacmanAnim(pacmanPos.col, pacmanPos.row, pacmanDir, pacAnimFrame);
}

void moveRight(void) {
    pacmanDir = DIR_RIGHT;
    uint8_t r2 = pacmanPos.row;
    uint8_t c2 = pacmanPos.col;

    if (pacmanPos.row == TUNNEL_ROW && pacmanPos.col == TUNNEL_RIGHT) {
        c2 = TUNNEL_LEFT;
    }
    else {
        c2 = (pacmanPos.col == NCOL - 1) ? 0 : (pacmanPos.col + 1);
    }
    if (walls[r2][c2]) return;

    myDrawFullRectangle(pacmanPos.col * SQ_SIZE + 1, pacmanPos.row * SQ_SIZE + 1, SQ_SIZE - 1, SQ_SIZE - 1, LCD_COLOR_BLACK);
    gameBoard[pacmanPos.row][pacmanPos.col] = 0;

    pacmanPos.col = c2;
    gameBoard[pacmanPos.row][pacmanPos.col] = 1;

    if (visitedFields[pacmanPos.row][pacmanPos.col] == 0) {
        pointsCounter++;
        visitedFields[pacmanPos.row][pacmanPos.col] = 1;
    }

    if (powerupExists && pacmanPos.row == powerupRow && pacmanPos.col == powerupCol) {
        freezeActive = 1;
        freezeTimer = 0;
        powerupExists = 0;

        myDrawFullRectangle(
            powerupCol * SQ_SIZE + 1,
            powerupRow * SQ_SIZE + 1,
            SQ_SIZE - 1, SQ_SIZE - 1,
            LCD_COLOR_BLACK
        );
    }


    drawPacmanAnim(pacmanPos.col, pacmanPos.row, pacmanDir, pacAnimFrame);
}


void movePinky(void) {
    int16_t dr = (int16_t)pacmanPos.row - (int16_t)pinkyPos.row;
    int16_t dc = (int16_t)pacmanPos.col - (int16_t)pinkyPos.col;

    uint8_t r1 = pinkyPos.row;
    uint8_t c1 = pinkyPos.col;

    if (pinkyPos.row == TUNNEL_ROW && pinkyPos.col == TUNNEL_LEFT) {
        pinkyPos.col = TUNNEL_RIGHT;
    }
    else if (pinkyPos.row == TUNNEL_ROW && pinkyPos.col == TUNNEL_RIGHT) {
        pinkyPos.col = TUNNEL_LEFT;
    }

    r1 = pinkyPos.row;
    c1 = pinkyPos.col;

    uint8_t nr, nc;

    if (pinkyMode == PINKY_SCATTER) {
        if (dr < 0)      nr = (r1 == NROW - 1) ? 0 : (r1 + 1);
        else if (dr > 0) nr = (r1 == 0) ? (NROW - 1) : (r1 - 1);
        else             nr = r1;

        if (dc < 0)      nc = (c1 == NCOL - 1) ? 0 : (c1 + 1);
        else if (dc > 0) nc = (c1 == 0) ? (NCOL - 1) : (c1 - 1);
        else             nc = c1;
    }
    else {
        if (dr < 0)      nr = (r1 == 0) ? (NROW - 1) : (r1 - 1);
        else if (dr > 0) nr = (r1 == NROW - 1) ? 0 : (r1 + 1);
        else             nr = r1;

        if (dc < 0)      nc = (c1 == 0) ? (NCOL - 1) : (c1 - 1);
        else if (dc > 0) nc = (c1 == NCOL - 1) ? 0 : (c1 + 1);
        else             nc = c1;
    }

    if (walls[nr][nc]) return;
    myDrawFullRectangle(c1 * SQ_SIZE + 1, r1 * SQ_SIZE + 1, SQ_SIZE - 1, SQ_SIZE - 1, LCD_COLOR_BLACK);
    gameBoard[r1][c1] = 0;
    if (!walls[r1][c1] && visitedFields[r1][c1] == 0) {
        myDrawPixel(c1 * SQ_SIZE + SQ_SIZE / 2, r1 * SQ_SIZE + SQ_SIZE / 2, LCD_COLOR_WHITE);
    }

    pinkyPos.row = nr;
    pinkyPos.col = nc;
    gameBoard[nr][nc] = 2;

    if (nc > c1 || (c1 == NCOL - 1 && nc == 0)) {
        BSP_LCD_DrawBitmap(nc * SQ_SIZE + 1, nr * SQ_SIZE + 1, pinkyRight);
    }
    else {
        BSP_LCD_DrawBitmap(nc * SQ_SIZE + 1, nr * SQ_SIZE + 1, pinkyLeft);
    }
}


/**
  * @brief  Draws a pixel on LCD.
  * @param  posX: X position
  * @param  posY: Y position
  * @param  color: pixel color in RGB mode (5-6-5)
  */
void myDrawPixel(uint16_t posX, uint16_t posY, uint16_t color) {
    uint16_t backup_color = BSP_LCD_GetTextColor();
    BSP_LCD_SetTextColor(color);

    BSP_LCD_DrawHLine(posX, posY, 1);

    BSP_LCD_SetTextColor(backup_color);
}


void myDrawFullRectangle(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint16_t color) {
    uint16_t backup_color = BSP_LCD_GetTextColor();
    BSP_LCD_SetTextColor(color);

    while (Height--) {
        BSP_LCD_DrawHLine(Xpos, Ypos++, Width);
    }

    BSP_LCD_SetTextColor(backup_color);
}


void myDrawFullCircle(uint16_t centerX, uint16_t centerY, uint16_t radius, uint16_t color) {
    int16_t i, j;
    uint16_t backup_color = BSP_LCD_GetTextColor();
    BSP_LCD_SetTextColor(color);

    for (i = (-1) * radius;i <= radius;i++) {
        for (j = (-1) * radius;j <= radius;j++) {
            if ((i * i + j * j) <= radius * radius) {
                BSP_LCD_DrawVLine(centerX + i, centerY + j, (-2) * j);
                break;
            }
        }
    }

    BSP_LCD_SetTextColor(backup_color);
}

void DrawHeart(uint16_t x, uint16_t y, uint16_t color) {
    myDrawFullCircle(x + 5, y + 5, 5, color);
    myDrawFullCircle(x + 11, y + 5, 5, color);
    myDrawFullRectangle(x + 2, y + 8, 12, 6, color);
    myDrawFullRectangle(x + 5, y + 12, 6, 5, color);
    myDrawFullRectangle(x + 7, y + 16, 2, 3, color);
}

void DrawHUD(void) {
    char buf[32];

    myDrawFullRectangle(0, 0, 320, SQ_SIZE - 1, LCD_COLOR_BLACK);

    for (uint8_t i = 0; i < 3; ++i) {
        if (i < livesLeft) {
            DrawHeart(2 + i * 20, 2, LCD_COLOR_RED);
        }
        else {
            DrawHeart(2 + i * 20, 2, LCD_COLOR_DARKGRAY);
        }
    }


    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    snprintf(buf, sizeof(buf), "SCORE: %u", (unsigned)pointsCounter);
    BSP_LCD_DisplayStringAt(80, 4, (uint8_t*)buf, LEFT_MODE);
    snprintf(buf, sizeof(buf), "SPD:%u", (unsigned)ghostSpeedLevel);
    BSP_LCD_DisplayStringAt(200, 4, (uint8_t*)buf, LEFT_MODE);
    if (difficultyLevel == 0)
        BSP_LCD_DisplayStringAt(260, 4, (uint8_t*)"E", LEFT_MODE);
    else if (difficultyLevel == 1)
        BSP_LCD_DisplayStringAt(260, 4, (uint8_t*)"N", LEFT_MODE);
    else
        BSP_LCD_DisplayStringAt(260, 4, (uint8_t*)"H", LEFT_MODE);
    snprintf(buf, sizeof(buf), "%s",
        (pinkyMode == PINKY_CHASE ? "CHASE" : "SCATTER"));
    BSP_LCD_DisplayStringAt(200, 4, (uint8_t*)buf, LEFT_MODE);
    if (freezeActive) {
        BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
        BSP_LCD_DisplayStringAt(260, 4, (uint8_t*)"FREEZE", LEFT_MODE);
    }
}

void drawWalls(void) {
    for (uint8_t r = 0; r < NROW; ++r) {
        for (uint8_t c = 0; c < NCOL; ++c) {
            if (walls[r][c]) {
                myDrawFullRectangle(c * SQ_SIZE + 1, r * SQ_SIZE + 1, SQ_SIZE - 1, SQ_SIZE - 1, LCD_COLOR_BLUE);
            }
        }
    }
}

void quickRestart(void) {
    pointsCounter = 0;
    livesLeft = 3;
    gameStatus = 1;
    paused = 0;
    gameOverState = 0;

    for (uint8_t r = 0; r < NROW; ++r) {
        for (uint8_t c = 0; c < NCOL; ++c) {
            gameBoard[r][c] = 0;
            visitedFields[r][c] = 0;
        }
    }

    gameSetup();

    DrawHUD();

    sel_pressed = 0;
}

void loseLifeAndRespawn(void) {

    fruitExists = 0;
    myDrawFullRectangle(
        fruitCol * SQ_SIZE + 1,
        fruitRow * SQ_SIZE + 1,
        SQ_SIZE - 1, SQ_SIZE - 1,
        LCD_COLOR_BLACK
    );
    fruitSpawnTimer = 0;
    fruitDespawnTimer = 0;
    fruitSpawnInterval = (rand() % 2) ? 15000 : 20000;

    lifeLostFlash = 1;
    lifeLostTimer = 0;
    lifeLostCount = 0;

    myDrawFullRectangle(
        pacmanPos.col * SQ_SIZE + 1,
        pacmanPos.row * SQ_SIZE + 1,
        SQ_SIZE - 1, SQ_SIZE - 1,
        LCD_COLOR_BLACK
    );
    gameBoard[pacmanPos.row][pacmanPos.col] = 0;

    if (!walls[pacmanPos.row][pacmanPos.col] && visitedFields[pacmanPos.row][pacmanPos.col] == 0) {
        myDrawPixel(
            pacmanPos.col * SQ_SIZE + SQ_SIZE / 2,
            pacmanPos.row * SQ_SIZE + SQ_SIZE / 2,
            LCD_COLOR_WHITE
        );
    }

    myDrawFullRectangle(
        pinkyPos.col * SQ_SIZE + 1,
        pinkyPos.row * SQ_SIZE + 1,
        SQ_SIZE - 1, SQ_SIZE - 1,
        LCD_COLOR_BLACK
    );
    gameBoard[pinkyPos.row][pinkyPos.col] = 0;

    if (!walls[pinkyPos.row][pinkyPos.col] && visitedFields[pinkyPos.row][pinkyPos.col] == 0) {
        myDrawPixel(
            pinkyPos.col * SQ_SIZE + SQ_SIZE / 2,
            pinkyPos.row * SQ_SIZE + SQ_SIZE / 2,
            LCD_COLOR_WHITE
        );
    }

    if (livesLeft > 0) livesLeft--;

    if (livesLeft == 0) {
        gameStatus = 0;
        gameOver();
        return;
    }

    freezeActive = 0;
    freezeTimer = 0;
    powerupExists = 0;

    pacAnimFrame = 0;
    pacAnimTimer = 0;

    pinkyMode = PINKY_CHASE;
    pinkyModeTimer = 0;

    do {
        pacmanPos.row = rand() % NROW;
        pacmanPos.col = rand() % NCOL;
    } while (walls[pacmanPos.row][pacmanPos.col]);

    gameBoard[pacmanPos.row][pacmanPos.col] = 1;
    visitedFields[pacmanPos.row][pacmanPos.col] = 1;
    pointsCounter++;

    drawPacmanAnim(pacmanPos.col, pacmanPos.row, DIR_RIGHT, pacAnimFrame);

    do {
        pinkyPos.row = rand() % NROW;
        pinkyPos.col = rand() % NCOL;
    } while (walls[pinkyPos.row][pinkyPos.col] ||
        (pinkyPos.row == pacmanPos.row && pinkyPos.col == pacmanPos.col));

    gameBoard[pinkyPos.row][pinkyPos.col] = 2;
    BSP_LCD_DrawBitmap(
        pinkyPos.col * SQ_SIZE + 1,
        pinkyPos.row * SQ_SIZE + 1,
        pinkyLeft
    );

    DrawHUD();
}



static inline void DoMove(Dir d) {
    switch (d) {
    case DIR_UP:    moveUp();    break;
    case DIR_DOWN:  moveDown();  break;
    case DIR_LEFT:  moveLeft();  break;
    case DIR_RIGHT: moveRight(); break;
    default: break;
    }
}

static Dir MapJoyToDir(JOYState_TypeDef js) {
    switch (js) {
    case JOY_UP:    return DIR_UP;
    case JOY_DOWN:  return DIR_DOWN;
    case JOY_LEFT:  return DIR_LEFT;
    case JOY_RIGHT: return DIR_RIGHT;
    default:        return DIR_NONE;
    }
}


static void HandleInput(uint32_t now_ms) {
    JOYState_TypeDef js = BSP_JOY_GetState();

    if (js == JOY_SEL) {
        if (!sel_pressed) {
            if ((now_ms - sel_change_ms) >= BTN_DEBOUNCE_MS) {
                sel_pressed = 1;
                sel_down_start_ms = now_ms;
                sel_change_ms = now_ms;
            }
        }
    }
    else {
        if (sel_pressed && (now_ms - sel_change_ms) >= BTN_DEBOUNCE_MS) {
            uint32_t held = now_ms - sel_down_start_ms;
            sel_pressed = 0;
            sel_change_ms = now_ms;

            if (held >= 1000U) {
                quickRestart();
                return;
            }
            else {
                if (gameOverState) {
                    quickRestart();
                    return;
                }
                else {
                    paused ^= 1;
                }
            }
        }
    }


    if (paused && !gameOverState) {
        Dir dd = MapJoyToDir(js);
        if (dd == DIR_LEFT && ghostSpeedLevel > 0) ghostSpeedLevel--;
        if (dd == DIR_RIGHT && ghostSpeedLevel < 2) ghostSpeedLevel++;
        return;
    }

    if (gameOverState) {
        return;
    }


    Dir d = MapJoyToDir(js);

    if (d != g_btn_last) {
        g_btn_last_change_ms = now_ms;
        g_btn_last = d;
        g_btn_first_repeat_ms = 0;
        if (d != DIR_NONE) {
            g_btn_last_repeat_ms = 0;
        }
        return;
    }

    if (d == DIR_NONE) {
        g_btn_first_repeat_ms = 0;
        g_btn_last_repeat_ms = 0;
        return;
    }

    if (g_btn_last_repeat_ms == 0) {
        if ((now_ms - g_btn_last_change_ms) >= BTN_DEBOUNCE_MS) {
            DoMove(d);
            g_btn_last_repeat_ms = now_ms;
            g_btn_first_repeat_ms = now_ms;
        }
    }
    else {
        if (g_btn_first_repeat_ms && (now_ms - g_btn_first_repeat_ms) >= BTN_REPEAT_DELAY_MS) {
            DoMove(d);
            g_btn_first_repeat_ms = 0;
            g_btn_last_repeat_ms = now_ms;
        }
        else if (!g_btn_first_repeat_ms) {
            if ((now_ms - g_btn_last_repeat_ms) >= BTN_REPEAT_MS) {
                DoMove(d);
                g_btn_last_repeat_ms = now_ms;
            }
        }
    }
}



void gameOver(void) {
    gameOverState = 1;
    paused = 1;

    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_DisplayStringAt(0, 80, (uint8_t*)"GAME OVER", CENTER_MODE);
    if (gameStatus == 2) {
        BSP_LCD_DisplayStringAt(0, 100, (uint8_t*)"Congratulations. You won!", CENTER_MODE);
    }
    else {
        BSP_LCD_DisplayStringAt(0, 100, (uint8_t*)"Pinky caught you.", CENTER_MODE);
    }
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(0, 120, (uint8_t*)"Press SEL to restart", CENTER_MODE);
}


#if 0
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN) {
    if (GPIO_PIN == IOE_IT_PIN) {
        JoyState = BSP_JOY_GetState();
        switch (JoyState) {
        case JOY_DOWN:  moveDown();  break;
        case JOY_UP:    moveUp();    break;
        case JOY_LEFT:  moveLeft();  break;
        case JOY_RIGHT: moveRight(); break;
        default: break;
        }
    }
}
#endif

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    // BSP_LED_On(LED_RED);
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
       /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

