//  xliCloudObj.h - Xlight cloud variables and functions definitions header

#ifndef xliCloudObj_h
#define xliCloudObj_h

#include "xliCommon.h"
#include "ArduinoJson.h"

// Comment it off if we don't use Particle public cloud
/// Notes:
/// Currently, Particle public cloud supports up to 20 variables and 15 functions.
/// In general situation, we should use publish/subscribe or MQTT.
#define USE_PARTICLE_CLOUD

// Notes: Variable name max length is 12 characters long.
// Cloud variables
#define CLV_SysID               "sysID"           // Can also be a Particle Object
#define CLV_TimeZone            "timeZone"        // Can also be a Particle Object
#define CLV_SysStatus           "sysStatus"       // Can also be a Particle Object
#define CLV_JSONData            "jsonData"        // Can also be a Particle Object
#define CLV_LastMessage         "lastMsg"         // Can also be a Particle Object
#define CLV_SenTemperatur       "senTemp"
#define CLV_SenHumidity         "senHumid"
#define CLV_SenBrightness       "senBright"

// Notes: The length of the funcKey is limited to a max of 12 characters.
// Cloud functions
#define CLF_SetTimeZone         "SetTimeZone"     // Can also be a Particle Object
#define CLF_PowerSwitch         "PowerSwitch"     // Can also be a Particle Object
#define CLF_JSONCommand         "JSONCommand"     // Can also be a Particle Object
#define CLF_JSONConfig          "JSONConfig"      // Can also be a Particle Object
#define CLF_SetCurTime          "SetCurTime"

// Publish topics, notes:
// 1. For Particle cloud the publishing speed is about 1 event per sec.
// 2. The length of the topic is limited to a max of 63 characters.
// 3. The maximum length of data is 255 bytes.
/// Alarm event
#define CLT_NAME_Alarm          "xlc-event-alarm"
#define CLT_TTL_Alarm           1800              // 0.5 hour
/// Sensor data update
#define CLT_NAME_SensorData     "xlc-data-sensor"
#define CLT_TTL_SensorData      RTE_DELAY_PUBLISH
#define CLT_TTL_MotionData      5
/// LOG Message
#define CLT_NAME_LOGMSG          "xlc-event-log"
#define CLT_TTL_LOGMSG           3600              // 1 hour
/// Device status event
#define CLT_NAME_DeviceStatus    "xlc-status-device"
#define CLT_TTL_DeviceStatus     10

//------------------------------------------------------------------
// Xlight CloudObj Class
//------------------------------------------------------------------
class CloudObjClass
{
public:
  // Variables should be defined as public
  String m_SysID;
  String m_SysVersion;    // firmware version
  int m_SysStatus;
  String m_tzString;
  String m_jsonData;
  String m_lastMsg;
  String m_strCldCmd;

  float m_temperature;
  float m_humidity;
  uint16_t m_brightness;
  bool m_motion;
  uint16_t m_gas;
  uint16_t m_dust;
  uint16_t m_smoke;

public:
  CloudObjClass();

  String GetSysID();
  String GetSysVersion();

  virtual int CldSetTimeZone(String tzStr) = 0;
  virtual int CldPowerSwitch(String swStr) = 0;
  virtual int CldJSONCommand(String jsonCmd) = 0;
  virtual int CldJSONConfig(String jsonData) = 0;
  virtual int CldSetCurrentTime(String tmStr) = 0;
  int ProcessJSONString(String inStr);

  BOOL UpdateTemperature(float value);
  BOOL UpdateHumidity(float value);
  BOOL UpdateBrightness(uint8_t nid, uint8_t value);
  BOOL UpdateMotion(uint8_t nid, bool value);
  BOOL UpdateGas(uint8_t nid, uint16_t value);
  BOOL UpdateDust(uint8_t nid, uint16_t value);
  BOOL UpdateSmoke(uint8_t nid, uint16_t value);

  void UpdateJSONData();
  BOOL PublishLog(const char *msg);
  BOOL PublishDeviceStatus(const char *msg);

protected:
  void InitCloudObj();

  StaticJsonBuffer<512> m_jBuf;
  JsonObject *m_jpRoot;
  JsonObject *m_jpData;
  JsonObject *m_jpCldCmd;
};

#endif /* xliCloudObj_h */
