#pragma once

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>

struct DVSevents {
  enum class EventType : uint16_t {
    SPECIAL_EVENT = 0,
    POLARITY_EVENT = 1,
    FRAME_EVENT = 2,
    IMU6_EVENT = 3,
    IMU9_EVENT = 4,
    SPIKE_EVENT = 12,
  };

  struct PolarityEvent {
  uint32_t valid : 1;
  bool polarity : 1;
  uint16_t x : 15;
  uint16_t y : 15;
  uint64_t timestamp : 32;
} __attribute__((packed));

  struct SpecialEvent {
    uint32_t valid : 1;
    uint32_t type : 7;
    uint32_t data : 24;
  } __attribute__((packed));

  struct DynapSEEvent {
    uint32_t valid : 1;
    uint32_t core_id : 5;
    uint32_t chip_id : 6;
    uint32_t neuron_id : 20;
    uint32_t timestamp;
  } __attribute__((packed));

  enum class SpecialEventType : uint8_t {
    TIMESTAMP_WRAP = 0,
    TIMESTAMP_RESET = 1,
    EXTERNAL_INPUT_RISING_EDGE = 2,
    EXTERNAL_INPUT_FALLING_EDGE = 3,
    EXTERNAL_INPUT_PULSE = 4,
    DVS_ROW_ONLY = 5,
    EXTERNAL_INPUT1_RISING_EDGE = 6,
    EXTERNAL_INPUT1_FALLING_EDGE = 7,
    EXTERNAL_INPUT1_PULSE = 8,
    EXTERNAL_INPUT2_RISING_EDGE = 9,
    EXTERNAL_INPUT2_FALLING_EDGE = 10,
    EXTERNAL_INPUT2_PULSE = 11,
    EXTERNAL_GENERATOR_RISING_EDGE = 12,
    EXTERNAL_GENERATOR_FALLING_EDGE = 13,
    APS_FRAME_START = 14,
    APS_FRAME_END = 15,
    APS_EXPOSURE_START = 16,
    APS_EXPOSURE_END = 17,
  };

  struct IMU6Event {
    uint32_t valid : 1;
    uint32_t padding : 31;
    uint32_t timestamp : 32;
    float accel_x;
    float accel_y;
    float accel_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float temp;
  } __attribute__((packed));

  struct IMU9Event {
    uint32_t valid : 1;
    uint32_t padding : 31;
    uint32_t timestamp : 32;
    float accel_x;
    float accel_y;
    float accel_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float temp;
    float comp_x;
    float comp_y;
    float comp_z;
  } __attribute__((packed));

  struct FrameEventHeader {
    uint32_t valid : 1;
    uint32_t channels : 3;
    uint32_t filter : 4;
    uint32_t roi : 7;
    uint32_t reserved : 17;
    uint32_t frame_start;
    uint32_t frame_end;
    uint32_t exposure_start;
    uint32_t exposure_end;
    uint32_t x_length;
    uint32_t y_length;
    uint32_t x_position;
    uint32_t y_position;
  } __attribute__((packed));

  struct FrameEvent {
    FrameEventHeader header;
    std::vector<uint16_t> pixels;
  };

  struct Header {
    EventType eventType;
    uint16_t eventSource;
    uint32_t eventSize;
    uint32_t eventTSOffset;
    uint32_t eventTSOverflow;
    uint32_t eventCapacity;
    uint32_t eventNumber;
    uint32_t eventValid;
  } __attribute__((packed));


  DVSevents() {}
  //DVSevents(const std::string &filename) { load(filename); }

  std::vector<DynapSEEvent> dynapse_events;
  std::vector<IMU6Event> imu6_events;
  std::vector<IMU9Event> imu9_events;
  std::vector<PolarityEvent> polarity_events;
};