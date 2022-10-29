
#pragma once

#include "board/yBoard.h"
#include "src/lcd/tft/tft_color.h"
#include "1romdata/romdata.h"

extern volatile bool serialPause;

typedef struct
{
  uint32_t SYSCLK_Frequency;  /*!< returns SYSCLK clock frequency expressed in Hz */
  uint32_t HCLK_Frequency;    /*!< returns HCLK clock frequency expressed in Hz */
  uint32_t PCLK1_Frequency;   /*!< returns PCLK1 clock frequency expressed in Hz */
  uint32_t PCLK2_Frequency;   /*!< returns PCLK2 clock frequency expressed in Hz */
  uint32_t USB_Frequency;
  uint32_t SDIO_Frequency;
}RCC_ClocksTypeDef;
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);

#if TRONXY_UI
#if MCU_TYPE == 1
#define	STM32_IDADDR        STM32F1_IDADDR
#define MCU_NAME            "GD32F10X"
#elif MCU_TYPE == 4
#define	STM32_IDADDR        STM32F4_IDADDR
#define MCU_NAME            "GD32F4XX"
#elif defined(STM32F1xx)
#define	STM32_IDADDR        STM32F1_IDADDR
#define MCU_NAME            "STM32F10X"
#elif defined(STM32F4xx)
#define	STM32_IDADDR        STM32F4_IDADDR
#define MCU_NAME            "STM32F4XX"
#endif
#if GREENY
#define MANUFACTURATOR      "GREENY"
#else
#define MANUFACTURATOR      "TRONXY"
#endif
#define TRONXY_SOFT_VERSION  "V2.17.3"

#include "lcd/picdata/ySca_s.h"
#include "lcd/picdata/yBin_s.h"
#include "lcd/picdata/yPic_s.h"

#include "0windows/yIcon.hpp"
#include "0windows/yFigureSd.h"
#include "0windows/yMultiple.hpp"
#include "0windows/yTablet.hpp"
#include "0windows/yVariant.hpp"
#include "0windows/yCircleButton.hpp"
#include "0windows/yWindow.hpp"
#include "0windows/yCompress.h"
#include "4other/yEvent.hpp"

extern volatile bool globalStop,hasExtraSerialCommand;
uint8_t tronxyStop(void);
uint8_t stopEmergency(void);
uint8_t stopMotor(void);
void tronxyPause(void);

void tronxyInit(void);
void tronxyUpdate(void);
void tronxy_config_init(void);
void filamentSensorReset(void);
void screenPopIndex(int index,VoidFun other = nullptr,bool recordLastScreen = true);
uint8_t closePopupMessage(void);
uint8_t screenFilament(void);
void screenKillError(const char*errorInfo1, const char* errorInfo2);
uint8_t screenMain(void);
void turnToTheme(uint8_t theme);
uint8_t screenReadFailAfter(void);
void saveSettingInPrinting(void);
void pauseMotion(void);
void resumeMotion(void);
void moveEAxis(uint8_t e,bool dir);
uint8_t keepEMove(void);
uint8_t screenFactoryReset(void);
uint8_t logScreen(void);
uint8_t showLog(void);
uint8_t autoLevelEnd(void);
void reshowWindow(void);

uint8_t popupFilamentOut(void);
uint8_t screenPopupWaiting(void);
uint8_t popupPowerloss(void);
uint8_t powerlossShutdown(void);
uint8_t popupReadfail(void);
uint8_t popupTooCold(void);
uint8_t popupRecoveryPrint(void);
uint8_t popupInsertSdcard(void);
uint8_t popupZLimitError(void);

uint8_t popupWaitNozzleHeat(void);
uint8_t popupFilamentInsert(void);
uint8_t popupKillError(void);

void title_show_info(const char*str);

#define BUTTON_CLOSE_POPWIN       1
#define BUTTON_RESET              2
#define BUTTON_ERR_CONFIRM        3
#define BUTTON_STOP_PRINT         4
#define BUTTON_FILE_UP            5
#define BUTTON_FILE_DOWN          6
#define BUTTON_LEVEL_STOP         7
#define BUTTON_CONFIRM_ZOFFSET    8
#define BUTTON_CONFIRM_EFACTOR    9
#define BUTTON_EXCHANGE_FIFTH     10
#define BUTTON_BACK_TOOL          11
#define BUTTON_GOTO_TOOL          12
#define BUTTON_GOTO_PRINT         13
#define BUTTON_GOTO_PRINTTOOL     14
#define BUTTON_FILAMENT           15
#define BUTTON_FAN_TO_TOOL        16
#define BUTTON_POPUP2_STOP_PRINT  17
void trigger(yWidget*w,TouchEvent evt);
uint8_t voidTask(void);
extern yWidget *currentScale;
extern yLabel* lbComponents[];
extern yWidget* winComponents1[];
extern yWidget* winComponents2[];

extern uint8_t my_lang,my_theme,buzzer_switch;
extern uint8_t my_test,myui_ready;

extern volatile uint8_t model_light_st;
extern uint8_t extruder_num,
	hotend_num,
	out_extruder,//记录断料的挤出机
	throat_fan,//为0表示不使用喉管风扇,其它值代表喉管风扇在风扇列表中的起始位置
	fifth_mode,
	dir_y_axis,//影响y轴图标形为,如果图标点击后移动方向是反的,则倒转此值
	dir_z_axis,//影响热床Z上下图标形为,如果图标点击后移动方向是反的,则倒转此值
	xy_device_id;

extern uint8_t pin_left_z_endstop, 
	pin_right_z_endstop,
	pin_probe,
	pin_e0_filament,
	pin_e1_filament,
	pin_e2_filament,
	pin_x_stop,
	pin_y_stop,
	pin_x2_stop,
	filament_sensor_state;

extern volatile uint8_t enabled_laser_serial,
	enabled_auto_bed_leveling,
	enabled_filament_sensor,
	enabled_controller_fan,
	enabled_dual_x,
	enabled_dual_z_stop,
	enabled_z_max_home,
	enabled_taoli,
	enabled_need_heat_head,
	enabled_need_heat_bed,
	enabled_fan,
	enabled_light, //使能照明灯,用主板风扇口,必须失能USE_CONTROLLER_FAN
	enabled_only_home_xy,
	enabled_usb,
	enabled_wifi;

extern volatile uint8_t auto_leveling_x_points, auto_leveling_y_points;
extern void (*updateAutoLevel)(int x, int y, float* value);

extern float fifth_e_factor;
extern float pos_x_min,
	pos_x_max,
	pos_y_min,
	pos_y_max,
	pos_z_min,
	pos_z_max,
	pos_x2_min,
	pos_x2_max,
	pause_z_raise,
	auto_leveling_max_err;

extern yWindow *topwin;
extern int touch_x,touch_y;
extern uint32_t logTime,printTotalTime;
extern const char *screen_error1, *screen_error2;
extern xyz_pos_t Probe_Offset;

extern const char* software_version;
extern const char* firmware_name;

#define TASK_SEQUENCE                 0
#define TASK_LOOP                     1
#define LOOPEVT_BASE                  0
#define LOOPEVT_POPUP                 1
#define LOOPEVT_UI_UPDATE             2 //UI更新优先级低于数值更新,这里如果更改,一定要记得改registerTask处作对应
#define LOOPEVT_AFTER_UI_UPDATE       3
extern yEvent yevt,mevt;

#define POPUP_WAITING                 1
#define POPUP_FILAMENTOUT             2
#define POPUP_POWERLOSS               3
#define POPUP_FACTORY_RESET           4
#define POPUP_LEVEL_CONFIRM           5
#define POPUP_READFAIL                6
#define POPUP_RECOVERY_PRINT          7
#define POPUP_FILAMENT_INSERT         8
#define POPUP_KILL_ERROR              9 
#define POPUP_STOP_PRINT              10
#define POPUP_SAVE_HOTENDOFFSET       11
#define POPUP_LOW_TEMPERATURE         12
#define POPUP_WAITNOZZLE_HEAT         13
#define POPUP_LEVEL_OK                14
#define POPUP_LEVEL_NG                15
#define POPUP_COMPLETE_PRINT          16
#define POPUP_OPENFILE_FAIL           17
#define POPUP_DELETE_FILE             18
#define POPUP_INSERT_CARD             19
#define POPUP_DUALZ_LIMIT_ERR         20
#define POPUP_SAVE_OK                 21
#define POPUP_NOSUPPORT               22
#define POPUP_NORMAL_MODE             23
#define POPUP_KEYBOARD                24
#define POPUP_LANGUAGE                25
#define POPUP_RESTART_TO_CALI         26

#if USBHOST_HS_EN
#define NAME_SIGN_USB        "U"
#else
#define NAME_SIGN_USB        "0"
#endif
#if USE_EXTRUDER == 1
#define NAME_SIGN_EXTRUDER   "T"
#elif USE_EXTRUDER == 2
#define NAME_SIGN_EXTRUDER   "B"
#elif USE_EXTRUDER == 3
#define NAME_SIGN_EXTRUDER   "t"
#elif USE_EXTRUDER == 4
#define NAME_SIGN_EXTRUDER   "g"
#else
#error "wrong extruder!"
#endif

#define SHUTDOWN_PERIOD        90000

#define LANG_ENGLISH      0
#define LANG_CHINESE      1
#define LANG_JAPANESE     2
#define LANG_KOREAN       3
#define LANG_RUSSIAN      4
#define LANG_FRENCH       5
#define LANG_GERMAN       6
#define LANG_SPANISH      7
#define LANG_PORTUGUESE   8
enum TronxyPrintStatus
{
	PRINT_IDLE = 0,
	PRINT_AUTO_LEVEL,//在自动调平中
	PRINT_ERROR,

	PRINT_RUNNING,//打印中
	PRINT_RUNNING_HOME,//打印中复位
	PRINT_PAUSE,//暂停
	PRINT_RESUME,//恢复中
	PRINT_ABORTING,//打印退出中

	PRINT_RUNNING_SERIAL,//连机打印
	PRINT_PAUSE_SERIAL,
};
extern volatile TronxyPrintStatus my_print_status;

struct ButtonParam
{
	uint8_t reserve;//对齐保留
	uint8_t paramNumber; //按钮编号
	#if TRONXY_UI == 1
	const uint16_t* nameCn;
	#else
	uint16_t nameCn; //按钮名字-多国语言
	#endif
	const char* nameEn; //按钮名字-英语,如果为nullptr,则显示多国语言
	void (*touch)(yWidget*,TouchEvent);//触发按钮时要执行的动作
	yEventFun next;//触发按钮后,要执行的具体事情
};
struct MessageSt
{
	uint8_t currentIndex;//功能号
	uint8_t buttonNum;//按钮数量,最大不超过4个
	#if TRONXY_UI == 1
	const uint16_t* cn;
	#else
	uint16_t cn; //界面信息-多国语言
	#endif
	const char* en; //界面信息,如果为nullptr,则显示多国语言
	yEventFun after;//执行弹窗后,要执行的动作
	ButtonParam buttonParam[4];//按钮参数
};
extern struct MessageSt messageSt;

enum KEYBOARD_TYPE{
	KEYBOARD_NUMBER,
	KEYBOARD_STRING,
	KEYBOARD_PASSWORD
};
struct KeyboardSt
{
	KEYBOARD_TYPE type;
	yEventFun ok;
};
extern struct KeyboardSt keyboardSt;

#define INDEX_LANG          104
#define INDEX_THEME         (INDEX_LANG + 1)
#define INDEX_BUZZER_SWITCH (INDEX_THEME + 1)
#define INDEX_DUAL_X_MODE   (INDEX_BUZZER_SWITCH + 1)
#define INDEX_CALIBRATION   (INDEX_DUAL_X_MODE + 1)
#define INDEX_FIFTH_EFACTOR (INDEX_CALIBRATION + 12)
#define INDEX_BABYSTEP_ACCUM (INDEX_FIFTH_EFACTOR + 4)
#define INDEX_Z_OFFSET      (INDEX_BABYSTEP_ACCUM + 2)
#define INDEX_HOTEND_OFFSET (INDEX_Z_OFFSET + sizeof(Probe_Offset))
#define INDEX_Z_VALUES      (INDEX_HOTEND_OFFSET + sizeof(xyz_pos_t) + 2)
constexpr int indexzvalue = INDEX_Z_VALUES;

#if HOTENDS && HOTENDS > 2
#error settings parameter position has changed.
#endif

#endif

#define SDPIC_SIGN                0x5AA5A55A
#define SDPIC_ICON_SIZE           80
#define SDPIC_MAIN_SIZE           160
#define SDPIC_MAIN_SIGN           ";gimage:"
#define SDPIC_ICON_SIGN           ";simage:"

#define WIFI_Y_NUM        5
#define WIFI_EXPIRE_TIME  3000
#define WIFI_NAME_MAX     32
#define WIFI_CMD(x,...)   SERIAL_ECHOLNPGM(x,##__VA_ARGS__)
#define WIFI_EXPIRE_RERESH() sta.nextTime = millis() + WIFI_EXPIRE_TIME
enum WIFI_ST
{
    WIFI_ST_IDLE = 0,
    WIFI_ST_SCANNING,
    WIFI_ST_START,
    WIFI_ST_DISCONNECTING,
    WIFI_ST_DISCONNECTED,
    WIFI_ST_CONNECTED,
    WIFI_ST_GETIP
};
enum SOCKET_ST
{
    SOCKET_ST_IDLE = 0,
    SOCKET_GET_IP
};
enum WIFI_EXE
{
	WIFI_EXE_IDLE = 0,
	WIFI_EXE_SCAN_START,
	WIFI_EXE_STOP_START,
	WIFI_EXE_STOP_END,
	WIFI_EXE_LOGIN_START,
	WIFI_EXE_LOGIN_END,
	WIFI_EXE_INFO_START
};
struct WIFI_STA
{
    enum WIFI_ST wifi_st;
	enum SOCKET_ST socket_st;
	enum WIFI_EXE wifi_exe;
	uint8_t scanIndex;
	uint8_t nextPage;
    int rssi;
	uint32_t nextTime;
	char ssid[WIFI_NAME_MAX];
	char password[WIFI_NAME_MAX];
    char ip[WIFI_NAME_MAX];
    char port[WIFI_NAME_MAX];
    char target_ip[WIFI_NAME_MAX];
    char target_port[WIFI_NAME_MAX];
};
extern struct WIFI_STA sta;
extern volatile int use_test;

