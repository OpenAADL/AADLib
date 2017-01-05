
#ifdef STM32_MAVLINK_H_
#define STM32_MAVLINK_H_

struct mavlink_message_t;

int stm32_mavlink_write_message(const mavlink_message_t* msg);
void stm32_emit_heartbeat();
void stm32_emit_raw_imu(float rates[3], int16_t acc[3]);
void stm32_emit_ping(int seq);

void stm32_recv_message(mavlink_message_t* msg);

#endif /* STM32_MAVLINK_H_ */
