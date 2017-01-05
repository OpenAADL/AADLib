#include <stdbool.h>

#include "stm32f4xx_hal.h"
/*#include <v1.0/common/mavlink.h>*/
#include <mavlink.h>

#include "stm32_mavlink.h"

#include "FreeRTOS.h"

extern UART_HandleTypeDef huart2;

const uint8_t SYSTEM_ID = 1;
const uint8_t COMPONENT_ID = 0;

// size stack should be at least 512

int
stm32_mavlink_write_message(const mavlink_message_t* msg)
{
	uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
	size_t m_length = mavlink_msg_to_send_buffer(buffer, msg);
	return HAL_UART_Transmit(&huart2, buffer, m_length, 500.0);
}

// should be sent at least once by second
void 
stm32_emit_heartbeat()
{
	mavlink_heartbeat_t h;
	mavlink_message_t m;
	h.type = MAV_TYPE_GENERIC;
	h.autopilot = MAV_AUTOPILOT_GENERIC;
	h.base_mode =	MAV_MODE_FLAG_TEST_ENABLED;
	h.system_status = MAV_STATE_ACTIVE;

	mavlink_msg_heartbeat_encode(SYSTEM_ID, COMPONENT_ID, &m, &h);
	stm32_mavlink_write_message(&m);
}

void
stm32_emit_raw_imu(float rates[3], int16_t acc[3], int16_t mag[3])
{
	mavlink_raw_imu_t imu;
	mavlink_message_t m;
	imu.time_usec = xTaskGetTickCount() * portTICK_RATE_MS * 1000;
	imu.xacc = acc[0];
	imu.yacc = acc[1];
	imu.zacc = acc[2];
	imu.xgyro = (int16_t)rates[0];
	imu.ygyro = (int16_t)rates[1];
	imu.zgyro = (int16_t)rates[2];
    	imu.xmag= mag[0]; 
    	imu.ymag= mag[1];
    	imu.zmag= mag[2];


	mavlink_msg_raw_imu_encode(SYSTEM_ID, COMPONENT_ID, &m, &imu);
	stm32_mavlink_write_message(&m);
}

void
stm32_emit_ping(int seq)
{
	mavlink_ping_t ping;
	mavlink_message_t m;
	ping.time_usec = xTaskGetTickCount() * portTICK_RATE_MS * 1000;
	ping.seq = seq;
	ping.target_system = SYSTEM_ID;
	ping.target_component = COMPONENT_ID;

	mavlink_msg_ping_encode(SYSTEM_ID, COMPONENT_ID, &m, &ping);
	stm32_mavlink_write_message(&m);
}

void
stm32_recv_message(mavlink_message_t* msg)
{
	bool got_complete_message = false;
	mavlink_status_t status;

	// read the complete message
	while (!got_complete_message) {
		uint8_t c;
		int err = HAL_UART_Receive(&huart2, &c, 1, 10.0); 
		if (err == HAL_OK)
		{
			got_complete_message = mavlink_parse_char(0, c, msg, &status);
		}
	}
}

void
stm32_emit_attitude(float angles[3], float rates[3])
{
    

	mavlink_attitude_t att; //found in mavlink_msg_attitude.h
	mavlink_message_t m;

	att.time_boot_ms = xTaskGetTickCount() * portTICK_RATE_MS * 1000; /*< Timestamp (milliseconds since system boot)*/
	att.roll = angles[0]; /*< Roll angle (rad, -pi..+pi)*/
	att.pitch = angles[1]; /*< Pitch angle (rad, -pi..+pi)*/
	att.yaw = angles[2]; /*< Yaw angle (rad, -pi..+pi)*/
	att.rollspeed = rates[0]; /*< Roll angular speed (rad/s)*/
	att.pitchspeed = rates[1]; /*< Pitch angular speed (rad/s)*/
	att.yawspeed = rates[2]; /*< Yaw angular speed (rad/s)*/


	//mavlink_msg_attitude_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_attitude_t* attitude)
	mavlink_msg_attitude_encode(SYSTEM_ID, COMPONENT_ID, &m, &att);
	
	stm32_mavlink_write_message(&m);
}
