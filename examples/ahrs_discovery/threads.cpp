/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#define ARM_MATH_CM4
#include <sys/_stdint.h>

#include "stdint.h"
#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
//#include "diag/Trace.h"
#include "stm32f401_discovery.h"
#include "stm32f401_discovery_accelerometer.h"
#include "stm32f401_discovery_gyroscope.h"
#include "eigen_math.h"
#include "thread.h"
#include "AttitudeEKF.h"
#include "hardware.h"
#include <math.h>

//#include "Vector.hpp"
//#include "Matrix.hpp"
//#include "rotation.h"
#include "AttitudeEKF.h"
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal_conf.h"
#include "magneto.h"
#include <cstring>

//#define printvalue
//#undef printmsg
//#define printatt

#define STACK_SIZE 512
#define QUEUE_SIZE 8
#define TASK_PERIOD 80
#define DELAY_TIME 10
#define GRAVITY_CONST (9.8)

/*uint32_t uwPrescalerValue = 0;
uint32_t uwCapturedValue = 0;*/

float gyro_offsets[3] = { 0.0f, 0.0f, 0.0f };
//float acc_offsets[3] = { 0.0f, 0.0f, 0.0f };
float Gyro_offset_x = 0;
float Gyro_offset_y = 0;
float Gyro_offset_z = 0;

//float Acc_offset_x = 0;
//float Acc_offset_y = 0;
//float Acc_offset_z = 0;


//{x_offset = -0.246328354, y_offset = -0.199297905,
//  z_offset = 0.159586906, x_scale = 1.01862228, y_scale = -0.978195071,
//  z_scale = -1.01253819}

float _accel_scale_x_offset = -0.246328354;
float _accel_scale_y_offset = -0.199297905;
float _accel_scale_z_offset = 0.159586906;

float _accel_scale_x_scale = 1.01862228;
float _accel_scale_y_scale = -0.978195071;
float _accel_scale_z_scale = -1.01253819;


float magneto_offset_x= -0.0129708648;
float magneto_offset_y= -0.00589652592;
float magneto_offset_z= 0.000194669192;


float MeasurementAcc[3];
float MeasurementMag[3];
float MeasurementGyo[3];

float MeasurementAcc_avg[50][3];
float MeasurementMag_avg[50][3];

float MeasurementMag_avg_x[50];
float MeasurementMag_avg_y[50];
float MeasurementMag_avg_z[50];

float MeasurementGyo_avg[50][3];

int16_t MeasureCountAcc = 0;
int16_t MeasureCountMag = 0;
int16_t MeasureCountGyro = 0;



int32_t StartTimeinMs_task1 = 0;
int32_t MaxExecutionTime_task1 = 0;

int32_t StartTimeinMs_task2 = 0;
int32_t MaxExecutionTime_task2 = 0;

int32_t StartTimeinMs_task3 = 0;
int32_t MaxExecutionTime_task3 = 0;

int32_t StartTimeinMs_task4 = 0;
int32_t MaxExecutionTime_task4 = 0;

float _gyro_range_scale, _accel_range_scale, _mag_range_scale;

float accel_offs[3];
float accel_T[3][3];
float accel_ref[6][3] = {
			{9.35700035, 0.409596026, -0.258343101},//DETECT_ORIENTATION_TAIL_DOWN
			{-9.84965706, -0.129855901, -0.0214423873},//DETECT_ORIENTATION_NOSE_DOWN

			{-0.148693681, -10.2114305, 0.114945486}, //DETECT_ORIENTATION_LEFT
			{-0.240513146, 9.81283474, -0.0591412783}, //DETECT_ORIENTATION_RIGHT


			{-0.512399197, -0.185382113, -9.50735664},//DETECT_ORIENTATION_UPSIDE_DOWN
			{-0.235319644, -0.0897782445, 9.82653046},//DETECT_ORIENTATION_RIGHTSIDE_UP

			};




/*	DETECT_ORIENTATION_TAIL_DOWN,
	DETECT_ORIENTATION_NOSE_DOWN,
	DETECT_ORIENTATION_LEFT,
	DETECT_ORIENTATION_RIGHT,
	DETECT_ORIENTATION_UPSIDE_DOWN,
	DETECT_ORIENTATION_RIGHTSIDE_UP,
*/

float calibrate_magneto_x[300] =
{/*{*/-0.0272799991, -0.0271999985, -0.0271199998, -0.0270399991, -0.0267999992, -0.0257599987, -0.0269599985, -0.0268799998, -0.0250399988,
  -0.0255199987, -0.0259999987, -0.0259999987, -0.0271199998, -0.0284799989, -0.0291200001, -0.0300799999, -0.0304799993, -0.0294399988,
  -0.0285599995, -0.0294399988, -0.0289599989, -0.0280799996, -0.0273599997, -0.0264799986, -0.0266399998, -0.0279199984, -0.0271199998,
  -0.0266399998, -0.0267999992, -0.0272799991, -0.0261599999, -0.0260799993, -0.0263199992, -0.0271199998, -0.0257599987, -0.0249600001,
  -0.0235200003, -0.0237600002, -0.0251199994, -0.0253599994, -0.0273599997, -0.0269599985, -0.0273599997, -0.0272799991, -0.0267999992,
  -0.0263199992, -0.0258399993, -0.0260799993, -0.0258399993, -0.0257599987/*}*/,

/*{*/0.0275999997, 0.027759999, 0.0284000002, 0.0288800001, 0.0286400001, 0.0260799993, 0.0248799995, 0.0266399998, 0.0264799986,
  0.0247200001, 0.0242400002, 0.0243199989, 0.0243199989, 0.0239199996, 0.024079999, 0.0237600002, 0.0248799995, 0.0250399988, 0.0250399988,
  0.0253599994, 0.0263199992, 0.0255999994, 0.0271999985, 0.0268799998, 0.0264799986, 0.0262399986, 0.0270399991, 0.027759999, 0.0271199998,
  0.0264799986, 0.0265599992, 0.0261599999, 0.0259199999, 0.0252, 0.0245599989, 0.0243999995, 0.0242400002, 0.0243199989, 0.0243999995,
  0.0247200001, 0.0237600002, 0.0225599986, 0.0220799986, 0.0213599987, 0.0221599992, 0.0231199991, 0.0226399992, 0.0251199994, 0.0258399993,
  0.0248799995/*}*/,
/*{*/0.0111999996, 0.0107199997, 0.0101600001, 0.00759999966, 0.00576000009, 0.0027999999, 0.000959999976, -0.00079999998, -0.0027999999,
  -0.00496000005, -0.00583999977, -0.00751999998, -0.0104, -0.0146399997, -0.0171999987, -0.0191200003, -0.0188800003, -0.0184000004,
  -0.0180799998, -0.0195199996, -0.0197599996, -0.0195199996, -0.0188800003, -0.0153599996, -0.0135199996, -0.0137599995, -0.0117600001,
  -0.00968000013, -0.00312000001, -0.00215999992, 0.00255999994, 0.00695999991, 0.0143200001, 0.0179999992, 0.0189599991, 0.0185599998,
  0.0175999999, 0.0159200002, 0.0139999995, 0.0130399996, 0.0107999993, 0.0092000002, 0.00775999995, 0.00655999966, 0.00543999998,
  0.00472000008, 0.00463999994, 0.00535999984, 0.0110399993, 0.0143999998/*}*/,
/*{*/0.0147199994, 0.0146399997, 0.0135199996, 0.01296, 0.0107999993, 0.00832000002, 0.00487999991, 0.00271999999, -0.00127999997,
  -0.00359999994, -0.00615999987, -0.00647999998, -0.00903999992, -0.0122400001, -0.0142399995, -0.0151999993, -0.0160799995, -0.0141599998,
  -0.0134399999, -0.0142399995, -0.0154399993, -0.0164000001, -0.0171999987, -0.0160799995, -0.0131199993, -0.00751999998, -0.00416000001,
  0.00447999965, 0.00927999988, 0.0143200001, 0.0163199995, 0.0175199993, 0.0157599989, 0.0131199993, 0.0117600001, 0.0103199994,
  0.00895999931, 0.00808000006, 0.00799999945, 0.0104799997, 0.0123999994, 0.0134399999, 0.0141599998, 0.0141599998, 0.0135999992,
  0.0142399995, 0.01456, 0.01456, 0.0139199998, 0.01296/*}*/,
/*{*/0.00671999995, 0.00671999995, 0.00591999991, 0.00751999998, 0.00655999966, 0.00288000004, -0.00231999997, -0.00479999976,
  -0.00567999994, -0.00927999988, -0.0133599993, -0.01712, -0.0179199986, -0.0206399988, -0.0204799995, -0.0186400004, -0.0178399999,
  -0.0138399992, -0.0120000001, -0.0116799995, -0.0175999999, -0.0195199996, -0.0171999987, -0.0139199998, -0.0121599995, -0.0107199997,
  -0.00863999967, -0.00615999987, -0.00567999994, 0.00288000004, 0.01088, 0.0160799995, 0.0187999997, 0.01712, 0.0143200001, 0.0115999999,
  0.0103199994, 0.00975999981, 0.00951999985, 0.0092000002, 0.00855999999, 0.00775999995, 0.00583999977, 0.00463999994, 0.00343999988,
  0.00431999983, 0.00815999974, 0.0123999994, 0.0171999987, 0.0149599994/*}*/,
/*{*/0.0102399997, 0.00983999949, 0.00895999931, 0.00799999945, 0.00639999984, 0.00535999984, 0.00367999985, 0.00151999993, -0.00271999999,
  -0.00367999985, -0.00431999983, -0.0045599998, -0.0092000002, -0.0131999999, -0.0151199996, -0.0140799992, -0.0144799994, -0.0141599998,
  -0.0137599995, -0.00999999978, -0.00823999941, -0.00607999973, -0.00615999987, -0.00751999998, -0.00703999959, -0.00503999973,
  -0.00543999998, -0.00367999985, 0, 0.00135999999, 0.00144000002, 0.00591999991, 0.0111199999, 0.0159999989, 0.0157599989, 0.0136799999,
  0.0114399996, 0.01064, 0.01064, 0.0107999993, 0.0105599994, 0.00935999956, 0.00808000006, 0.00631999969, 0.00487999991, 0.00431999983,
  0.0045599998, 0.00639999984, 0.0104, 0.01088/*}*/};

float calibrate_magneto_y[300] =
{
-0.0204799995, -0.0203200001, -0.0199199989, -0.0186400004, -0.0201599989, -0.0231999997, -0.0252799988, -0.0264799986, -0.02936,
  -0.0283199996, -0.0266399998, -0.0224799998, -0.0164799988, -0.00399999972, 0.00159999996, 0.00679999962, 0.01088, 0.01456, 0.01504,
  0.01064, 0.00743999984, 0.000720000011, -0.00239999988, -0.00600000005, -0.00624000002, 0.00496000005, 0.0149599994, 0.0183199998,
  0.0167199988, 0.0133599993, 0.00327999983, -0.00511999987, -0.0138399992, -0.0154399993, -0.02544, -0.0296799988, -0.0271199998,
  -0.0207199994, -0.0104, -0.00671999995, -0.00392000005, -0.00127999997, -0.000639999984, -0.000720000011, -0.00151999993, -0.00223999983,
  -0.00295999995, -0.00248000002, -0.00263999985, -0.00255999994,
-0.0139999995, -0.0148799997, -0.0159200002, -0.0175199993, -0.0197599996, -0.0245599989, -0.0267199986, -0.023599999, -0.0203200001,
  -0.00591999991, -0.00392000005, -0.00159999996, 0.0027999999, 0.0112799993, 0.0140799992, 0.0155999996, 0.0151199996, 0.0152799999,
  0.0155199999, 0.0144799994, 0.0121599995, 0.0123999994, 0.00535999984, 0.00359999994, 0.000239999994, -0.00399999972, -0.0148, -0.02152,
  -0.0229599997, -0.0234399997, -0.0243199989, -0.023839999, -0.0159200002, -0.00496000005, 0.00271999999, 0.00719999988, 0.0115999999,
  0.0136799999, 0.0153599996, 0.0157599989, 0.0169599988, 0.0148799997, 0.0123199997, 0.00767999981, 0.00223999983, -0.00319999992,
  -0.00496000005, -0.0111999996, -0.0137599995, -0.0209599994,
0.0253599994, 0.0255199987, 0.0255199987, 0.0263199992, 0.0269599985, 0.0271199998, 0.0266399998, 0.0255999994, 0.0258399993,
  0.0255199987, 0.0249600001, 0.0244800001, 0.0250399988, 0.0251199994, 0.0247999988, 0.0251199994, 0.0252799988, 0.0264799986, 0.0268799998,
  0.0268799998, 0.0268799998, 0.0273599997, 0.0271999985, 0.0275999997, 0.0272799991, 0.0265599992, 0.0258399993, 0.0279199984, 0.0292799994,
  0.0283199996, 0.0267999992, 0.0260799993, 0.0255999994, 0.0250399988, 0.0253599994, 0.0255199987, 0.0262399986, 0.0269599985, 0.0279199984,
  0.0279199984, 0.0281599984, 0.027999999, 0.0280799996, 0.0280799996, 0.0283199996, 0.028239999, 0.028239999, 0.0281599984, 0.0266399998,
  0.0259199999,
-0.0363999978, -0.0364799984, -0.0367200002, -0.0368000008, -0.0370399989, -0.0378399976, -0.0383999981, -0.0383199975, -0.0382400006,
  -0.0382400006, -0.0366399996, -0.0361599997, -0.0368000008, -0.0360799991, -0.0359199978, -0.0361599997, -0.0363999978, -0.0367200002,
  -0.0372800007, -0.0376800001, -0.0377600007, -0.0375199988, -0.0368799977, -0.0371199995, -0.0380799994, -0.0387200005, -0.0384799987,
  -0.03816, -0.0371199995, -0.0364799984, -0.0367200002, -0.0368799977, -0.0375199988, -0.0387200005, -0.038879998, -0.039359998,
  -0.0395199992, -0.0396800004, -0.0397599973, -0.0395199992, -0.0391199999, -0.038879998, -0.0387200005, -0.0387200005, -0.0386399999,
  -0.0385599993, -0.0379199982, -0.0375199988, -0.0376800001, -0.0372000001,
0.0055999998, 0.00591999991, 0.0092000002, 0.0122400001, 0.0157599989, 0.0176799987, 0.0186400004, 0.0190399997, 0.0186400004,
  0.0177599993, 0.0149599994, 0.00784000009, 0.00351999979, -0.00463999994, -0.00855999999, -0.0138399992, -0.0167199988, -0.0211199988,
  -0.0227199998, -0.0227199998, -0.0143999998, -0.0135999992, -0.0164799988, -0.0211199988, -0.0227199998, -0.0263999999, -0.027999999,
  -0.0302399993, -0.0288800001, -0.0306399986, -0.0281599984, -0.0240000002, -0.0143200001, -0.00832000002, -0.00295999995, -7.9999998e-05,
  0.00239999988, 0.00319999992, 0.00351999979, 0.00423999969, 0.00472000008, 0.00496000005, 0.0038399999, 0.00239999988, 0.00159999996,
  0.00104, 0.000239999994, -0.00431999983, -0.0155199999, -0.0227199998,
-0.0163199995, -0.0164000001, -0.0174399987, -0.0187999997, -0.0196000002, -0.0208000001, -0.0240000002, -0.0248799995, -0.0222399998,
  -0.0175199993, -0.0202399995, -0.0198400002, -0.0185599998, -0.0164799988, -0.00791999977, -0.00255999994, -0.00079999998, 0.00199999986,
  0.00479999976, 0.00655999966, 0.000720000011, 0.00039999999, 0.00127999997, 0.00104, 0.000319999992, 0.000720000011, -0.000720000011,
  0.00399999972, 0.0038399999, 0.00159999996, 0.00239999988, 0.00303999986, -0.00104, -0.0111199999, -0.0140799992, -0.0131199993,
  -0.0137599995, -0.0135199996, -0.0133599993, -0.0137599995, -0.0144799994, -0.0137599995, -0.0136799999, -0.0138399992, -0.0136799999,
  -0.0137599995, -0.0143200001, -0.0167999994, -0.0171999987, -0.01688
};

float calibrate_magneto_z[300] =
{
	-0.0147199994, -0.0148799997, -0.0152799999, -0.0154399993, -0.0148799997, -0.0136799999, -0.0100799995, -0.00711999973, -0.00335999997,
  0.00431999983, 0.00679999962, 0.01296, 0.0157599989, 0.01712, 0.0155999996, 0.0120799998, 0.00759999966, 0.00223999983, -0.0045599998,
  -0.0102399997, -0.0134399999, -0.0173599999, -0.0185599998, -0.0193600003, -0.019439999, -0.0159999989, -0.00847999938, 0.000239999994,
  0.00631999969, 0.0103199994, 0.0177599993, 0.0195199996, 0.0173599999, 0.0159999989, 0.00935999956, 0.000159999996, -0.0123999994,
  -0.0179999992, -0.0207199994, -0.0208000001, -0.0188800003, -0.0188800003, -0.0183199998, -0.0184799992, -0.019199999, -0.0197599996,
  -0.019679999, -0.019679999, -0.019679999, -0.0198400002,
0.0113599999, 0.0109599996, 0.00944000017, 0.00728000002, 0.00511999987, 0.000879999949, -0.0027999999, -0.00711999973, -0.0125599997,
  -0.0195199996, -0.0195199996, -0.0191200003, -0.0181600004, -0.0127999997, -0.00887999963, -0.00728000002, -0.00399999972, -0.00255999994,
  0.000239999994, 0.00288000004, 0.00535999984, 0.00695999991, 0.0112799993, 0.0123999994, 0.0141599998, 0.0149599994, 0.0121599995,
  0.0055999998, 0.00439999998, 0.00487999991, 0.00407999987, 0.00543999998, 0.0131199993, 0.0161600001, 0.0151199996, 0.0131199993,
  0.0102399997, 0.00775999995, 0.00463999994, 0.00248000002, -0.00583999977, -0.0126399994, -0.0160799995, -0.0197599996, -0.02128,
  -0.0218399987, -0.0219999999, -0.0198400002, -0.0181600004, -0.0151999993,
-0.0152799999, -0.0154399993, -0.0158399995, -0.0158399995, -0.0156800002, -0.0156800002, -0.0160799995, -0.0176799987, -0.0171999987,
  -0.0172799993, -0.0177599993, -0.0172799993, -0.0153599996, -0.0119199995, -0.00968000013, -0.00543999998, -0.00423999969, -0.00159999996,
  -0.00111999991, -0.000159999996, -7.9999998e-05, 0.00295999995, 0.00719999988, 0.0118399998, 0.0137599995, 0.0155999996, 0.0177599993,
  0.0159999989, 0.0151999993, 0.0162399989, 0.0165599994, 0.0151999993, 0.00999999978, 0.00576000009, 0.000959999976, -0.000879999949,
  -0.00295999995, -0.00392000005, -0.00463999994, -0.00591999991, -0.00871999934, -0.0100799995, -0.01064, -0.0111999996, -0.0116799995,
  -0.0116799995, -0.0119199995, -0.0119199995, -0.0120000001, -0.01064,
0.0092000002, 0.00975999981, 0.0103199994, 0.00999999978, 0.01064, 0.0107999993, 0.0110399993, 0.0117600001, 0.0121599995, 0.0120799998,
  0.0130399996, 0.0134399999, 0.0113599999, 0.00863999967, 0.0073599997, 0.00416000001, 0.00159999996, -0.00144000002, -0.00208000001,
  -0.00144000002, -0.00191999995, -0.00271999999, -0.00463999994, -0.00903999992, -0.0113599999, -0.01456, -0.0159200002, -0.0164799988,
  -0.0154399993, -0.0116799995, -0.00832000002, -0.00199999986, 0.000319999992, 0.00271999999, 0.00288000004, 0.00335999997, 0.00431999983,
  0.00479999976, 0.00487999991, 0.00367999985, 0.00215999992, 0.00079999998, -0.000959999976, -0.00144000002, -0.00312000001, -0.00472000008,
  -0.0073599997, -0.00887999963, -0.0103199994, -0.0116799995,
0.0324000008, 0.0319200009, 0.0283199996, 0.0233599991, 0.0188800003, 0.0158399995, 0.0151199996, 0.0148799997, 0.0155999996,
  0.0164799988, 0.0181600004, 0.02152, 0.0231199991, 0.023599999, 0.0236799996, 0.0241599996, 0.0239199996, 0.023839999, 0.0236799996,
  0.0240000002, 0.0247999988, 0.0237600002, 0.0244800001, 0.0241599996, 0.0237600002, 0.0221599992, 0.0219999999, 0.0203999989, 0.02152,
  0.0198400002, 0.019439999, 0.0199999996, 0.0225599986, 0.0249600001, 0.0265599992, 0.0270399991, 0.0271199998, 0.0275999997, 0.027759999,
  0.0271999985, 0.0267199986, 0.0271199998, 0.0275199991, 0.0280799996, 0.0287199989, 0.0290399995, 0.0285599995, 0.0275199991, 0.023839999,
  0.02128,
-0.0276799984, -0.0275999997, -0.0274399985, -0.0267999992, -0.0267999992, -0.0266399998, -0.0251199994, -0.0248799995, -0.02568,
  -0.0271999985, -0.0257599987, -0.0255999994, -0.0249600001, -0.0240000002, -0.0241599996, -0.0240000002, -0.0236799996, -0.0228799991,
  -0.0224799998, -0.0229599997, -0.0251199994, -0.0252799988, -0.0253599994, -0.02568, -0.0255999994, -0.0261599999, -0.0269599985,
  -0.0264799986, -0.0263199992, -0.0269599985, -0.0276799984, -0.0275999997, -0.0272799991, -0.0255199987, -0.0251199994, -0.0263999999,
  -0.0270399991, -0.0273599997, -0.0274399985, -0.0271199998, -0.0272799991, -0.0275199991, -0.027759999, -0.028239999, -0.0286400001,
  -0.0284799989, -0.0284000002, -0.0275999997, -0.0265599992, -0.0265599992

};


float sphere_x=0, sphere_y=0, sphere_z=0, sphere_radius=0;
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

void BSP_MAGNETO_GETXYZ (float* pfData);
void LSM303DLHC_MagInit(LSM303DLHCMag_InitTypeDef *LSM303DLHC_InitStruct);
extern "C" void stm32_emit_attitude(float angles[3], float rates[3]);
extern "C" void  stm32_emit_heartbeat();
extern "C" void stm32_emit_raw_imu(float rates[3], int16_t acc[3], int16_t mag[3]);
/* USER CODE BEGIN PV */

/* USER CODE END PV */




/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */



void filter(float *input, float *current_in, unsigned int *counter, float limit)
{
	float value1 = *input;
	float value2 = *current_in;
	float diff = *input - *current_in;
	if (diff < 0)
		diff = diff * -1;
	if (diff < limit)
	{
		*input = (0.50 * value1) + (0.50 * value2);
		*counter = 0;
	}
	else
	{
		if(*counter < 3)
		{
			*input = *input;
			*counter = *counter + 1;
		}
		else
		{

			*input = *current_in;
			*counter = 0;
		}
	}
}

extern "C"void entryaccelero
    (ahrs__data_types__float32_type_aadl* acc_out_data_x,
    ahrs__data_types__float32_type_aadl* acc_out_data_y,
    ahrs__data_types__float32_type_aadl* acc_out_data_z);

/* EntryAccelero function */
#ifdef __cplusplus
extern "C"void entryaccelero
    (ahrs__data_types__float32_type_aadl* acc_out_data_x,
    ahrs__data_types__float32_type_aadl* acc_out_data_y,
    ahrs__data_types__float32_type_aadl* acc_out_data_z)
#endif
{
        init_hardware();

	// Initialise the xLastWakeTime variable with the current time.
	int16_t tAccValue_int[3];
	float tAccValue[3];

	float tAccValuefloat[3];
	static bool firsttime = false;
	static int i = 0;
	i++;
	if (i==10)
		BSP_LED_On(LED3);
	else if (i>20)
	{
		BSP_LED_Off(LED3);
		i = 0;
	}
/* USER CODE BEGIN 5 */
/* Infinite loop */

	if (firsttime == false)
	{
		_gyro_range_scale = 17.5e-3f / 180.0f * 3.14f;

		_accel_range_scale = 0.061e-3f * 9.80f;
    		//new_scale_g_digit = 0.061e-3f;
    		//LSM303D_ONE_G = 9.80f
		_mag_range_scale = 0.080e-3f;
       		//new_scale_ga_digit = 0.080e-3f
		firsttime = true;
	}

	#ifdef printmsg
	//trace_puts("Accelero\n");
	#endif

	taskDISABLE_INTERRUPTS();
	BSP_ACCELERO_GetXYZ(tAccValue_int);
	taskENABLE_INTERRUPTS();

	tAccValue[0]=tAccValue_int[0]*_accel_range_scale;
	tAccValue[1]=tAccValue_int[1]*_accel_range_scale;
	tAccValue[2]=tAccValue_int[2]*_accel_range_scale;

		*acc_out_data_x=tAccValue[0];
		*acc_out_data_y=tAccValue[1];
		*acc_out_data_z=tAccValue[2];

  /* USER CODE END 5 */
}

/* EntryMagneto function */
#ifdef __cplusplus
extern "C" void entrymagneto
    (ahrs__data_types__float32_type_aadl* mag_out_data_x,
    ahrs__data_types__float32_type_aadl* mag_out_data_y,
    ahrs__data_types__float32_type_aadl* mag_out_data_z)
#endif
{
        init_hardware();

	static int i = 0;
	int32_t execution_time = 0;
	float tMagValue[3]={0, 0, 0};
	i++;
	if (i==10)
		BSP_LED_On(LED4);
	else if (i>20)
	{
		BSP_LED_Off(LED4);
		i = 0;
	}
	// Initialise the xLastWakeTime variable with the current time.
	TickType_t LastWakeTime = xTaskGetTickCount();

        StartTimeinMs_task2 = xTaskGetTickCount();
	/* USER CODE BEGIN 5 */
	/* Infinite loop */

	#ifdef printmsg
	//trace_puts("Magneto\n");
	#endif
	taskDISABLE_INTERRUPTS();
	BSP_MAGNETO_GETXYZ(tMagValue);
	taskENABLE_INTERRUPTS();
	tMagValue[0]=tMagValue[0]*_mag_range_scale;
	tMagValue[1]=tMagValue[1]*_mag_range_scale;
	tMagValue[2]=tMagValue[2]*_mag_range_scale;

		*mag_out_data_x = tMagValue[0];
		*mag_out_data_y = tMagValue[1];
		*mag_out_data_z = tMagValue[2];

	execution_time = xTaskGetTickCount() - StartTimeinMs_task2;

	if( (execution_time) > MaxExecutionTime_task2)
	{
		MaxExecutionTime_task2 = execution_time;
	}
}


/* EntryGyroscope function */
#ifdef __cplusplus
extern "C" void entrygyro
    (ahrs__data_types__float32_type_aadl* gyro_out_data_x,
    ahrs__data_types__float32_type_aadl* gyro_out_data_y,
    ahrs__data_types__float32_type_aadl* gyro_out_data_z)
#endif
{
        init_hardware();

	float tGyroValue[3];

	static int i = 0, count = 0;
	int32_t execution_time = 0;
	static unsigned int countx =0;
	static unsigned int county =0;
	static unsigned int countz =0;

	i++;
	if (i==10)
		BSP_LED_On(LED5);
	else if (i>20)
	{
		BSP_LED_Off(LED5);
		i = 0;
	}
	// Initialise the xLastWakeTime variable with the current time.
	TickType_t LastWakeTime = xTaskGetTickCount();
	StartTimeinMs_task3 = xTaskGetTickCount();
	/* USER CODE BEGIN EntryGyroscope */
	/* Infinite loop */

	#ifdef printmsg
	//trace_puts("Gyro\n");
	#endif
	taskDISABLE_INTERRUPTS();
	BSP_GYRO_GetXYZ(tGyroValue);
	taskENABLE_INTERRUPTS();

	//tGyroValue[0]=tGyroValue[0]*_gyro_range_scale;
	//tGyroValue[1]=tGyroValue[1]*_gyro_range_scale;
	//tGyroValue[2]=tGyroValue[2]*_gyro_range_scale;

	if (MeasureCountGyro < 50)
	{
		MeasurementGyo_avg[MeasureCountGyro][0] = tGyroValue[0];
		MeasurementGyo_avg[MeasureCountGyro][1] = tGyroValue[1];
		MeasurementGyo_avg[MeasureCountGyro][2] = tGyroValue[2];
		MeasureCountGyro = MeasureCountGyro + 1;
	}
	else if (MeasureCountGyro == 50)
	{
		MeasurementGyo[0] = MeasurementGyo_avg[0][0];
		MeasurementGyo[1] = MeasurementGyo_avg[0][1];
		MeasurementGyo[2] = MeasurementGyo_avg[0][2];

		for(count = 1; count < 50; count++)
		{
			MeasurementGyo[0] = (MeasurementGyo[0] + MeasurementGyo_avg[count][0])/2;
			MeasurementGyo[1] = (MeasurementGyo[1] + MeasurementGyo_avg[count][1])/2;
			MeasurementGyo[2] = (MeasurementGyo[2] + MeasurementGyo_avg[count][2])/2;

		}
		Gyro_offset_x=MeasurementGyo[0];
		Gyro_offset_y=MeasurementGyo[1];
		Gyro_offset_z=MeasurementGyo[2];

		MeasureCountGyro = MeasureCountGyro + 1;
	}
	else
	{

		filter(&MeasurementGyo[0], &tGyroValue[0], &countx, 500);
		filter(&MeasurementGyo[1], &tGyroValue[1], &county, 500);
		filter(&MeasurementGyo[2], &tGyroValue[2], &countz, 500);

		*gyro_out_data_x = MeasurementGyo[0];
		*gyro_out_data_y = MeasurementGyo[1];
		*gyro_out_data_z = MeasurementGyo[2];

	}

	execution_time = xTaskGetTickCount() - StartTimeinMs_task3;

	if( (execution_time) > MaxExecutionTime_task3)
	{
		MaxExecutionTime_task3 = execution_time;
	}

  /* USER CODE END EntryGyroscope */
}


float mag_decl = 0.0f;
unsigned char use_moment_inertia = 0;
const unsigned char update_vect[3] = {1, 1, 1};
float dt = TASK_PERIOD / 1000.0f;
float z_k[9] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 9.81f, 0.2f, -0.2f, 0.2f};
float q_rotSpeed = 1e-4f;
float q_rotAcc = 0.08f;
float q_acc = 0.009f;
float q_mag = 0.005f;
float r_gyro = 0.0008f;
float r_accel = 10000.0f;
float r_mag = 100.0f;
const float moment_inertia_J[9] = {0.0018f, 0, 0,   0, 0.0018f, 0,    0, 0, 0.0037f};

float x_aposteriori[12];
float P_aposteriori[144];
float Rot_matrix[9] = {1.f,  0,  0,
							0,  1.f,  0,
							0,  0,  1.f
				 	 	 };		// init: identity matrix
// output euler angles
float euler[3] = {0.0f, 0.0f, 0.0f};
float debugOutput[4] = { 0.0f, 0.0f, 0.0f, 0.0f};

float P_aposteriori_k[144] = {100.f, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
					     0, 100.f,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
					     0,   0, 100.f,   0,   0,   0,   0,   0,   0,   0,   0,   0,
					     0,   0,   0, 100.f,   0,   0,   0,   0,   0,   0,   0,   0,
					     0,   0,   0,   0,  100.f,  0,   0,   0,   0,   0,   0,   0,
					     0,   0,   0,   0,   0, 100.f,   0,   0,   0,   0,   0,   0,
					     0,   0,   0,   0,   0,   0, 100.f,   0,   0,   0,   0,   0,
					     0,   0,   0,   0,   0,   0,   0, 100.f,   0,   0,   0,   0,
					     0,   0,   0,   0,   0,   0,   0,   0, 100.f,   0,   0,   0,
					     0,   0,   0,   0,   0,   0,   0,   0,  0.0f, 100.0f,   0,   0,
					     0,   0,   0,   0,   0,   0,   0,   0,  0.0f,   0,   100.0f,   0,
					     0,   0,   0,   0,   0,   0,   0,   0,  0.0f,   0,   0,   100.0f,
					    }; /**< init: diagonal matrix with big values */
float x_aposteriori_k[12];		/**< states */


float rates[3] = {0, 0, 0};
int16_t  mag[3]= {0, 0, 0};
int16_t  acc_raw[3]= {0, 0, 0};
#ifdef __cplusplus
extern "C" void entryattitude
    (ahrs__data_types__float32_type_aadl acc_in_data_x,
    ahrs__data_types__float32_type_aadl mag_in_data_x,
    ahrs__data_types__float32_type_aadl gyro_in_data_x,
    ahrs__data_types__float32_type_aadl acc_in_data_y,
    ahrs__data_types__float32_type_aadl mag_in_data_y,
    ahrs__data_types__float32_type_aadl gyro_in_data_y,
    ahrs__data_types__float32_type_aadl acc_in_data_z,
    ahrs__data_types__float32_type_aadl mag_in_data_z,
    ahrs__data_types__float32_type_aadl gyro_in_data_z)
#endif
{
	static int i = 0;
	int32_t execution_time = 0;

	i++;
	if (i==10)
		BSP_LED_On(LED6);
	else if (i>20)
	{
		BSP_LED_Off(LED6);
		i = 0;
	}
	StartTimeinMs_task4 = xTaskGetTickCount();

	//char printbuffer[128];
	static bool firsttime=true;
	static int time1Hz=0;


	//float x_in_new = ((xraw_f * _accel_range_scale) - _accel_scale.x_offset) * _accel_scale.x_scale;

	//acc_offsets[0]=Acc_offset_x; - _accel_scale_x_offset) * _accel_scale_x_scale;
	//acc_offsets[1]=Acc_offset_y; - _accel_scale_y_offset) * _accel_scale_y_scale;
	//acc_offsets[2]=Acc_offset_z; - _accel_scale_z_offset) * _accel_scale_z_scale;

	gyro_offsets[0] = Gyro_offset_x;
	gyro_offsets[1] = Gyro_offset_y;
	gyro_offsets[2] = Gyro_offset_z;


	if(firsttime)
	{
		AttitudeEKF_initialize();
		//acc.zero();
		//R_decl.identity();
		//initialize_sensor_data_calib();
		//_gyro_range_scale = 17.5e-3f / 180.0f * 3.14f;

		//_accel_range_scale = 0.061e-3f * 9.80f;
    		//new_scale_g_digit = 0.061e-3f;
    		//LSM303D_ONE_G = 9.80f
		//_mag_range_scale = 0.080e-3f;
       		//new_scale_ga_digit = 0.080e-3f
		firsttime=false;
		return;
	}

	// Initialise the xLastWakeTime variable with the current time.
	TickType_t LastWakeTime = xTaskGetTickCount();

	/* Infinite loop */

	#ifdef printmsg
	//int sdf[3];
	//trace_puts("Attitude\n");
	#endif


/*	z_k[0] =  MeasurementGyro[0] - gyro_offsets[0];
	z_k[1] =  MeasurementGyro[1] - gyro_offsets[1];
	z_k[2] =  MeasurementGyro[2] - gyro_offsets[2];
	z_k[3] = MeasurementAccelero[0] - acc(0);
	z_k[4] = MeasurementAccelero[1] - acc(1);
	z_k[5] = MeasurementAccelero[2] - acc(2);
	z_k[6] = MeasurementMagneto[0];
	z_k[7] = MeasurementMagneto[1];
	z_k[8] = MeasurementMagneto[2];

*/
#if 1

	gyro_in_data_x -= gyro_offsets[0];
	gyro_in_data_y -= gyro_offsets[1];
	gyro_in_data_z -= gyro_offsets[2];
	if (gyro_in_data_x < 50 && gyro_in_data_x>-20) gyro_in_data_x = 0;
	if (gyro_in_data_y < 50 && gyro_in_data_y>-20) gyro_in_data_y = 0;
	if (gyro_in_data_z < 50 && gyro_in_data_z>-20) gyro_in_data_z = 0;


	gyro_in_data_x = (gyro_in_data_x) * _gyro_range_scale;
	gyro_in_data_y = (gyro_in_data_y) * _gyro_range_scale;
	gyro_in_data_z = (gyro_in_data_z) * _gyro_range_scale;



	acc_in_data_x = (acc_in_data_x - _accel_scale_x_offset) * _accel_scale_x_scale;
	acc_in_data_y = (acc_in_data_y - _accel_scale_y_offset) * _accel_scale_y_scale;
	acc_in_data_z = (acc_in_data_z - _accel_scale_z_offset) * _accel_scale_z_scale;

	mag_in_data_x = mag_in_data_x - magneto_offset_x;
	mag_in_data_y = mag_in_data_y - magneto_offset_y;
	mag_in_data_z = mag_in_data_z- magneto_offset_z;

	rates[0]=gyro_in_data_x;
	rates[1]=gyro_in_data_y;
	rates[2]=gyro_in_data_z;

	acc_raw[0]=acc_in_data_x;
	acc_raw[1]=acc_in_data_y;
	acc_raw[2]=acc_in_data_z;

	mag[0]=mag_in_data_x;
	mag[1]=mag_in_data_y;
	mag[2]=mag_in_data_z;

	stm32_emit_raw_imu(rates, acc_raw, mag);

	z_k[0] =  (float)gyro_in_data_x;
	z_k[1] =  (float)gyro_in_data_y;
	z_k[2] =  (float)gyro_in_data_z;
	z_k[3] = (float)acc_in_data_x;
	z_k[4] = (float)acc_in_data_y;
	z_k[5] = (float)acc_in_data_z;
	z_k[6] = (float)mag_in_data_x;
	z_k[7] = (float)mag_in_data_y;
	z_k[8] = (float)mag_in_data_z;
#else
	/* Process the sensor data */

        //Vector<3> vect(gyro_in_data_x, gyro_in_data_y, gyro_in_data_z);
	//vect = _board_rotation * vect;

	//gyro_in_data_x = vect(0);
	//gyro_in_data_y = vect(1);
	//gyro_in_data_z = vect(2);



	/* Process the sensor data */

	z_k[0] =  0;
	z_k[1] =  0;
	z_k[2] =  0;
	z_k[3] = 0;
	z_k[4] = 0;
	z_k[5] = -9.8;
	z_k[6] = 0;
	z_k[7] = 0;
	z_k[8] = 0;

#endif


	AttitudeEKF(false, 		// approx_prediction
			use_moment_inertia,
			update_vect,
			dt,
			z_k,
			q_rotSpeed,
			q_rotAcc,
			q_acc,
			q_mag,
			r_gyro,
			r_accel,
			r_mag,
			moment_inertia_J,

			x_aposteriori,
			P_aposteriori,
			Rot_matrix,
			euler,
			debugOutput);


	if (isfinite(euler[0]) && isfinite(euler[1]) && isfinite(euler[2]))
	{
		memcpy(P_aposteriori_k, P_aposteriori, sizeof(P_aposteriori_k));
		memcpy(x_aposteriori_k, x_aposteriori, sizeof(x_aposteriori_k));

	}
	else
	{
		return;
	}


	rates[0]=(float)x_aposteriori[0];
	rates[1]=(float)x_aposteriori[1];
	rates[2]=(float)x_aposteriori[2];
	stm32_emit_heartbeat();
	stm32_emit_attitude(euler,rates);

	#ifdef printatt
	time1Hz += 1;//TASK_PERIOD;
	if(time1Hz > 10)
	{
		//sprintf(printbuffer, "%f, %f, %f, %d", euler[0], euler[1], euler[2],time1Hz);
		//trace_puts(printbuffer);
		//sprintf(printbuffer, "rollspeed:%f, pitchspeed:%f, yawspeed:%f", x_aposteriori[0], x_aposteriori[1], x_aposteriori[2]);
//		trace_puts(printbuffer);

		time1Hz = 0;
	}
	#endif

	execution_time = xTaskGetTickCount() - StartTimeinMs_task4;

	if( (execution_time) > MaxExecutionTime_task4)
	{
		MaxExecutionTime_task4 = execution_time;
	}

}

#ifdef __cplusplus
extern "C" void BSP_MAGNETO_Init(void)
#endif
{
  LSM303DLHCMag_InitTypeDef LSM303DLHC_InitStructure;


  /* Configure MEMS magnetometer main parameters: temp, working mode, full Scale and Data rate */
  LSM303DLHC_InitStructure.Temperature_Sensor = LSM303DLHC_TEMPSENSOR_DISABLE;
  LSM303DLHC_InitStructure.MagOutput_DataRate =LSM303DLHC_ODR_30_HZ ;
  LSM303DLHC_InitStructure.MagFull_Scale = LSM303DLHC_FS_1_3_GA;
  LSM303DLHC_InitStructure.Working_Mode = LSM303DLHC_CONTINUOS_CONVERSION;
  LSM303DLHC_MagInit(&LSM303DLHC_InitStructure);

}

void BSP_MAGNETO_GETXYZ (float* pfData)
{
  uint8_t buffer[6] = {0};
  uint8_t CTRLB = 0;
  uint16_t Magn_Sensitivity_XY = 0, Magn_Sensitivity_Z = 0;
  uint8_t i =0;

  CTRLB = COMPASSACCELERO_IO_Read(MAG_I2C_ADDRESS, LSM303DLHC_CRB_REG_M);

  buffer[0] = COMPASSACCELERO_IO_Read(MAG_I2C_ADDRESS, LSM303DLHC_OUT_X_H_M);
  buffer[1] = COMPASSACCELERO_IO_Read(MAG_I2C_ADDRESS, LSM303DLHC_OUT_X_L_M);
  buffer[2] = COMPASSACCELERO_IO_Read(MAG_I2C_ADDRESS, LSM303DLHC_OUT_Y_H_M);
  buffer[3] = COMPASSACCELERO_IO_Read(MAG_I2C_ADDRESS, LSM303DLHC_OUT_Y_L_M);
  buffer[4] = COMPASSACCELERO_IO_Read(MAG_I2C_ADDRESS, LSM303DLHC_OUT_Z_H_M);
  buffer[5] = COMPASSACCELERO_IO_Read(MAG_I2C_ADDRESS, LSM303DLHC_OUT_Z_L_M);


  /* Switch the sensitivity set in the CRTLB*/
  switch(CTRLB & 0xE0)
  {
  case LSM303DLHC_FS_1_3_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_1_3Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_1_3Ga;
    break;
  case LSM303DLHC_FS_1_9_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_1_9Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_1_9Ga;
    break;
  case LSM303DLHC_FS_2_5_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_2_5Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_2_5Ga;
    break;
  case LSM303DLHC_FS_4_0_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_4Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_4Ga;
    break;
  case LSM303DLHC_FS_4_7_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_4_7Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_4_7Ga;
    break;
  case LSM303DLHC_FS_5_6_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_5_6Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_5_6Ga;
    break;
  case LSM303DLHC_FS_8_1_GA:
    Magn_Sensitivity_XY = LSM303DLHC_M_SENSITIVITY_XY_8_1Ga;
    Magn_Sensitivity_Z = LSM303DLHC_M_SENSITIVITY_Z_8_1Ga;
    break;
  }

  for(i=0; i<2; i++)
  {
    pfData[i]=(float)((int16_t)(((uint16_t)buffer[2*i] << 8) + buffer[2*i+1])*1)/*/Magn_Sensitivity_XY*/;
  }

  pfData[2]=(float)((int16_t)(((uint16_t)buffer[4] << 8) + buffer[5])*1)/*/Magn_Sensitivity_Z*/;

}



void LSM303DLHC_MagInit(LSM303DLHCMag_InitTypeDef *LSM303DLHC_InitStruct)
{
  uint8_t cra_regm = 0x00, crb_regm = 0x00, mr_regm = 0x00;



  /* Configure MEMS: temp and Data rate */
  cra_regm |= (uint8_t) (LSM303DLHC_InitStruct->Temperature_Sensor | LSM303DLHC_InitStruct->MagOutput_DataRate);

  /* Configure MEMS: full Scale */
  crb_regm |= (uint8_t) (LSM303DLHC_InitStruct->MagFull_Scale);

  /* Configure MEMS: working mode */
  mr_regm |= (uint8_t) (LSM303DLHC_InitStruct->Working_Mode);

  /* Write value to Mag MEMS CRA_REG register */
  COMPASSACCELERO_IO_Write(MAG_I2C_ADDRESS, LSM303DLHC_CRA_REG_M, cra_regm);

  /* Write value to Mag MEMS CRB_REG register */
  COMPASSACCELERO_IO_Write(MAG_I2C_ADDRESS, LSM303DLHC_CRB_REG_M, crb_regm);

  /* Write value to Mag MEMS MR_REG register */
  COMPASSACCELERO_IO_Write(MAG_I2C_ADDRESS, LSM303DLHC_MR_REG_M, mr_regm);
}

/**
  * @brief  Get status for Mag LSM303DLHC data
  * @param  None
  * @retval Data status in a LSM303DLHC Data register
  */
uint8_t LSM303DLHC_MagGetDataStatus(void)
{
  uint8_t tmpreg;

  /* Read Mag STATUS register */
  tmpreg = COMPASSACCELERO_IO_Read(MAG_I2C_ADDRESS, LSM303DLHC_SR_REG_M);

  return tmpreg;
}

void BSP_calibration()
{
	return;
	  float MeasurementGyro[3];
	  float MeasurementGyro_prev[3];
	  int first_time = 0;
	  int i;

	  for(i=0; i < 5000; i++)
	  {
		  BSP_GYRO_GetXYZ(MeasurementGyro);
		  if(first_time == 0)
		  {
			MeasurementGyro_prev[0] = MeasurementGyro[0];
			MeasurementGyro_prev[1] = MeasurementGyro[1];
			MeasurementGyro_prev[2] = MeasurementGyro[2];
			first_time = 1;

		  }
		  for(int j=0; j < 3; j++)
		  {
			  gyro_offsets[j] += (MeasurementGyro_prev[j] - MeasurementGyro[j]);
			  MeasurementGyro_prev[j] = MeasurementGyro[j];
		  }

	  }

	  for(int j=0; j < 3; j++)
	  {
		  gyro_offsets[j] /= i;
	  }
}

/* Code Related to Calibration */
#define FLT_EPSILON 1.1920929e-07F  /* 1E-5 */

#define OK 1

struct accelero_scale
{
	float x_offset;
	float y_offset;
	float z_offset;

	float x_scale;
	float y_scale;
	float z_scale;

}accel_scale;
