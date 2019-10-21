#ifndef __YM_GURL_AUDIO_DEVICE_YM2612
#define __YM_GURL_AUDIO_DEVICE_YM2612

#include <mbed.h>

/*
 *  REGISTERS & COMMANDS
 */
// HARDWARE COMMANDS
#define YM2612_CMD_SELREG1 0x08
#define YM2612_CMD_WRTREG1 0x0A
#define YM2612_CMD_REDREG1 0x06
#define YM2612_CMD_SELREG2 0x09
#define YM2612_CMD_WRTREG2 0x0B
#define YM2612_CMD_REDREG2 0x07
#define YM2612_CMD_HIGHIMP 0x10
// CHIP PART
#define YM2612_PART_1          0x00
#define YM2612_PART_2          0x01
// COMMON REGISTERS
#define YM2612_REG_LFO         0x22
#define YM2612_REG_LFOENABLE   0x22
#define YM2612_REG_LFOFREQ     0x22
#define YM2612_REG_TIMERAH     0x24
#define YM2612_REG_TIMERAL     0x25
#define YM2612_REG_TIMERB      0x26
#define YM2612_REG_CH36MODE    0x27
#define YM2612_REG_KEYONOFF    0x28
#define YM2612_REG_DACDATA     0x2A
#define YM2612_REG_DACENBL     0x2B
// OP1 REGISTERS
// CH1 REGISTERS
#define YM2612_REG_CH1OP1_DETMUL      0x30
#define YM2612_REG_CH1OP1_DT1         0x30
#define YM2612_REG_CH1OP1_MUL         0x30
#define YM2612_REG_CH1OP1_TL          0x40
#define YM2612_REG_CH1OP1_RATEH       0x50
#define YM2612_REG_CH1OP1_RS          0x50
#define YM2612_REG_CH1OP1_AR          0x50
#define YM2612_REG_CH1OP1_RATEMH      0x60
#define YM2612_REG_CH1OP1_AM          0x60
#define YM2612_REG_CH1OP1_D1R         0x60
#define YM2612_REG_CH1OP1_RATEML      0x70
#define YM2612_REG_CH1OP1_D2R         0x70
#define YM2612_REG_CH1OP1_RATEL       0x80
#define YM2612_REG_CH1OP1_D1L         0x80
#define YM2612_REG_CH1OP1_RR          0x80
#define YM2612_REG_CH1OP1_UNDEF       0x90
// CH2 REGISTERS
#define YM2612_REG_CH2OP1_DETMUL      0x31
#define YM2612_REG_CH2OP1_DT1         0x31
#define YM2612_REG_CH2OP1_MUL         0x31
#define YM2612_REG_CH2OP1_TOTLVL      0x41
#define YM2612_REG_CH2OP1_TL          0x41
#define YM2612_REG_CH2OP1_RATEH       0x51
#define YM2612_REG_CH2OP1_RS          0x51
#define YM2612_REG_CH2OP1_AR          0x51
#define YM2612_REG_CH2OP1_RATEMH      0x61
#define YM2612_REG_CH2OP1_AM          0x61
#define YM2612_REG_CH2OP1_D1R         0x61
#define YM2612_REG_CH2OP1_RATEML      0x71
#define YM2612_REG_CH2OP1_D2R         0x71
#define YM2612_REG_CH2OP1_RATEL       0x81
#define YM2612_REG_CH2OP1_D1L         0x81
#define YM2612_REG_CH2OP1_RR          0x81
#define YM2612_REG_CH2OP1_UNDEF       0x91
// CH3 REGISTERS
#define YM2612_REG_CH3OP1_DETMUL      0x32
#define YM2612_REG_CH3OP1_DT1         0x32
#define YM2612_REG_CH3OP1_MUL         0x32
#define YM2612_REG_CH3OP1_TOTLVL      0x42
#define YM2612_REG_CH3OP1_TL          0x42
#define YM2612_REG_CH3OP1_RATEH       0x52
#define YM2612_REG_CH3OP1_RS          0x52
#define YM2612_REG_CH3OP1_AR          0x52
#define YM2612_REG_CH3OP1_RATEMH      0x62
#define YM2612_REG_CH3OP1_AM          0x62
#define YM2612_REG_CH3OP1_D1R         0x62
#define YM2612_REG_CH3OP1_RATEML      0x72
#define YM2612_REG_CH3OP1_D2R         0x72
#define YM2612_REG_CH3OP1_RATEL       0x82
#define YM2612_REG_CH3OP1_D1L         0x82
#define YM2612_REG_CH3OP1_RR          0x82
#define YM2612_REG_CH3OP1_UNDEF       0x92
// OP2 REGISTERS
// CH1 REGISTERS
#define YM2612_REG_CH1OP2_DETMUL      0x34
#define YM2612_REG_CH1OP2_DT1         0x34
#define YM2612_REG_CH1OP2_MUL         0x34
#define YM2612_REG_CH1OP2_TOTLVL      0x44
#define YM2612_REG_CH1OP2_TL          0x44
#define YM2612_REG_CH1OP2_RATEH       0x54
#define YM2612_REG_CH1OP2_RS          0x54
#define YM2612_REG_CH1OP2_AR          0x54
#define YM2612_REG_CH1OP2_RATEMH      0x64
#define YM2612_REG_CH1OP2_AM          0x64
#define YM2612_REG_CH1OP2_D1R         0x64
#define YM2612_REG_CH1OP2_RATEML      0x74
#define YM2612_REG_CH1OP2_D2R         0x74
#define YM2612_REG_CH1OP2_RATEL       0x84
#define YM2612_REG_CH1OP2_D1L         0x84
#define YM2612_REG_CH1OP2_RR          0x84
#define YM2612_REG_CH1OP2_UNDEF       0x94
// CH2 REGISTERS
#define YM2612_REG_CH2OP2_DETMUL      0x35
#define YM2612_REG_CH2OP2_DT1         0x35
#define YM2612_REG_CH2OP2_MUL         0x35
#define YM2612_REG_CH2OP2_TOTLVL      0x45
#define YM2612_REG_CH2OP2_TL          0x45
#define YM2612_REG_CH2OP2_RATEH       0x55
#define YM2612_REG_CH2OP2_RS          0x55
#define YM2612_REG_CH2OP2_AR          0x55
#define YM2612_REG_CH2OP2_RATEMH      0x65
#define YM2612_REG_CH2OP2_AM          0x65
#define YM2612_REG_CH2OP2_D1R         0x65
#define YM2612_REG_CH2OP2_RATEML      0x75
#define YM2612_REG_CH2OP2_D2R         0x75
#define YM2612_REG_CH2OP2_RATEL       0x85
#define YM2612_REG_CH2OP2_D1L         0x85
#define YM2612_REG_CH2OP2_RR          0x85
#define YM2612_REG_CH2OP2_UNDEF       0x95
// CH3 REGISTERS
#define YM2612_REG_CH3OP2_DETMUL      0x36
#define YM2612_REG_CH3OP2_DT1         0x36
#define YM2612_REG_CH3OP2_MUL         0x36
#define YM2612_REG_CH3OP2_TOTLVL      0x46
#define YM2612_REG_CH3OP2_TL          0x46
#define YM2612_REG_CH3OP2_RATEH       0x56
#define YM2612_REG_CH3OP2_RS          0x56
#define YM2612_REG_CH3OP2_AR          0x56
#define YM2612_REG_CH3OP2_RATEMH      0x66
#define YM2612_REG_CH3OP2_AM          0x66
#define YM2612_REG_CH3OP2_D1R         0x66
#define YM2612_REG_CH3OP2_RATEML      0x76
#define YM2612_REG_CH3OP2_D2R         0x76
#define YM2612_REG_CH3OP2_RATEL       0x86
#define YM2612_REG_CH3OP2_D1L         0x86
#define YM2612_REG_CH3OP2_RR          0x86
#define YM2612_REG_CH3OP2_UNDEF       0x96
// OP3 REGISTERS
// CH1 REGISTERS
#define YM2612_REG_CH1OP3_DETMUL      0x38
#define YM2612_REG_CH1OP3_DT1         0x38
#define YM2612_REG_CH1OP3_MUL         0x38
#define YM2612_REG_CH1OP3_TOTLVL      0x48
#define YM2612_REG_CH1OP3_TL          0x48
#define YM2612_REG_CH1OP3_RATEH       0x58
#define YM2612_REG_CH1OP3_RS          0x58
#define YM2612_REG_CH1OP3_AR          0x58
#define YM2612_REG_CH1OP3_RATEMH      0x68
#define YM2612_REG_CH1OP3_AM          0x68
#define YM2612_REG_CH1OP3_D1R         0x68
#define YM2612_REG_CH1OP3_RATEML      0x78
#define YM2612_REG_CH1OP3_D2R         0x78
#define YM2612_REG_CH1OP3_RATEL       0x88
#define YM2612_REG_CH1OP3_D1L         0x88
#define YM2612_REG_CH1OP3_RR          0x88
#define YM2612_REG_CH1OP3_UNDEF       0x98
// CH2 REGISTERS
#define YM2612_REG_CH2OP3_DETMUL      0x39
#define YM2612_REG_CH2OP3_DT1         0x39
#define YM2612_REG_CH2OP3_MUL         0x39
#define YM2612_REG_CH2OP3_TOTLVL      0x49
#define YM2612_REG_CH2OP3_TL          0x49
#define YM2612_REG_CH2OP3_RATEH       0x59
#define YM2612_REG_CH2OP3_RS          0x59
#define YM2612_REG_CH2OP3_AR          0x59
#define YM2612_REG_CH2OP3_RATEMH      0x69
#define YM2612_REG_CH2OP3_AM          0x69
#define YM2612_REG_CH2OP3_D1R         0x69
#define YM2612_REG_CH2OP3_RATEML      0x79
#define YM2612_REG_CH2OP3_D2R         0x79
#define YM2612_REG_CH2OP3_RATEL       0x89
#define YM2612_REG_CH2OP3_D1L         0x89
#define YM2612_REG_CH2OP3_RR          0x89
#define YM2612_REG_CH2OP3_UNDEF       0x99
// CH3 REGISTERS
#define YM2612_REG_CH3OP3_DETMUL      0x3A
#define YM2612_REG_CH3OP3_DT1         0x3A
#define YM2612_REG_CH3OP3_MUL         0x3A
#define YM2612_REG_CH3OP3_TOTLVL      0x4A
#define YM2612_REG_CH3OP3_TL          0x4A
#define YM2612_REG_CH3OP3_RATEH       0x5A
#define YM2612_REG_CH3OP3_RS          0x5A
#define YM2612_REG_CH3OP3_AR          0x5A
#define YM2612_REG_CH3OP3_RATEMH      0x6A
#define YM2612_REG_CH3OP3_AM          0x6A
#define YM2612_REG_CH3OP3_D1R         0x6A
#define YM2612_REG_CH3OP3_RATEML      0x7A
#define YM2612_REG_CH3OP3_D2R         0x7A
#define YM2612_REG_CH3OP3_RATEL       0x8A
#define YM2612_REG_CH3OP3_D1L         0x8A
#define YM2612_REG_CH3OP3_RR          0x8A
#define YM2612_REG_CH3OP3_UNDEF       0x9A
// OP4 REGISTERS
// CH1 REGISTERS
#define YM2612_REG_CH1OP4_DETMUL      0x3C
#define YM2612_REG_CH1OP4_DT1         0x3C
#define YM2612_REG_CH1OP4_MUL         0x3C
#define YM2612_REG_CH1OP4_TOTLVL      0x4C
#define YM2612_REG_CH1OP4_TL          0x4C
#define YM2612_REG_CH1OP4_RATEH       0x5C
#define YM2612_REG_CH1OP4_RS          0x5C
#define YM2612_REG_CH1OP4_AR          0x5C
#define YM2612_REG_CH1OP4_RATEMH      0x6C
#define YM2612_REG_CH1OP4_AM          0x6C
#define YM2612_REG_CH1OP4_D1R         0x6C
#define YM2612_REG_CH1OP4_RATEML      0x7C
#define YM2612_REG_CH1OP4_D2R         0x7C
#define YM2612_REG_CH1OP4_RATEL       0x8C
#define YM2612_REG_CH1OP4_D1L         0x8C
#define YM2612_REG_CH1OP4_RR          0x8C
#define YM2612_REG_CH1OP4_UNDEF       0x9C
// CH2 REGISTERS
#define YM2612_REG_CH2OP4_DETMUL      0x3D
#define YM2612_REG_CH2OP4_DT1         0x3D
#define YM2612_REG_CH2OP4_MUL         0x3D
#define YM2612_REG_CH2OP4_TOTLVL      0x4D
#define YM2612_REG_CH2OP4_TL          0x4D
#define YM2612_REG_CH2OP4_RATEH       0x5D
#define YM2612_REG_CH2OP4_RS          0x5D
#define YM2612_REG_CH2OP4_AR          0x5D
#define YM2612_REG_CH2OP4_RATEMH      0x6D
#define YM2612_REG_CH2OP4_AM          0x6D
#define YM2612_REG_CH2OP4_D1R         0x6D
#define YM2612_REG_CH2OP4_RATEML      0x7D
#define YM2612_REG_CH2OP4_D2R         0x7D
#define YM2612_REG_CH2OP4_RATEL       0x8D
#define YM2612_REG_CH2OP4_D1L         0x8D
#define YM2612_REG_CH2OP4_RR          0x8D
#define YM2612_REG_CH2OP4_UNDEF       0x9D
// CH3 REGISTERS
#define YM2612_REG_CH3OP4_DETMUL      0x3E
#define YM2612_REG_CH3OP4_DT1         0x3E
#define YM2612_REG_CH3OP4_MUL         0x3E
#define YM2612_REG_CH3OP4_TOTLVL      0x4E
#define YM2612_REG_CH3OP4_TL          0x4E
#define YM2612_REG_CH3OP4_RATEH       0x5E
#define YM2612_REG_CH3OP4_RS          0x5E
#define YM2612_REG_CH3OP4_AR          0x5E
#define YM2612_REG_CH3OP4_RATEMH      0x6E
#define YM2612_REG_CH3OP4_AM          0x6E
#define YM2612_REG_CH3OP4_D1R         0x6E
#define YM2612_REG_CH3OP4_RATEML      0x7E
#define YM2612_REG_CH3OP4_D2R         0x7E
#define YM2612_REG_CH3OP4_RATEL       0x8E
#define YM2612_REG_CH3OP4_D1L         0x8E
#define YM2612_REG_CH3OP4_RR          0x8E
#define YM2612_REG_CH3OP4_UNDEF       0x9E
// CH1-3 REGISTERS
#define YM2612_REG_CH1_FREQL          0xA0
#define YM2612_REG_CH1_FREQH          0xA4
#define YM2612_REG_CH2_FREQL          0xA1
#define YM2612_REG_CH2_FREQH          0xA5
#define YM2612_REG_CH3_FREQL          0xA2
#define YM2612_REG_CH3_FREQH          0xA6
#define YM2612_REG_CH3OP1_FREQL          0xA2
#define YM2612_REG_CH3OP1_FREQH          0xA6
#define YM2612_REG_CH3OP2_FREQL          0xA8
#define YM2612_REG_CH3OP2_FREQH          0xAC
#define YM2612_REG_CH3OP3_FREQL          0xA9
#define YM2612_REG_CH3OP3_FREQH          0xAD
#define YM2612_REG_CH3OP4_FREQL          0xAA
#define YM2612_REG_CH3OP4_FREQH          0xAE
// ALGORITHMS
#define YM2612_REG_CH1_ALGO          0xB0
#define YM2612_REG_CH2_ALGO          0xB1
#define YM2612_REG_CH3_ALGO          0xB2
// STEREOSENSIVITY
#define YM2612_REG_CH1_STEREOSENSIVITY          0xB4
#define YM2612_REG_CH2_STEREOSENSIVITY          0xB5
#define YM2612_REG_CH3_STEREOSENSIVITY          0xB6

/*
 *  FLAGS
 */
#define YM2612_D1R              0x1F
#define YM2612_D2R              0x1F
#define YM2612_D1L              0xF0
#define YM2612_RR               0x0F

#define YM2612_CHANNEL_1        0x00
#define YM2612_CHANNEL_2        0x01
#define YM2612_CHANNEL_3        0x02
#define YM2612_CHANNEL_4        0x03
#define YM2612_CHANNEL_5        0x04
#define YM2612_CHANNEL_6        0x05

#define YM2612_OPERATOR_1       0x00
#define YM2612_OPERATOR_2       0x01
#define YM2612_OPERATOR_3       0x02
#define YM2612_OPERATOR_4       0x03

#define YM2612_OPERATORMASK_1       0x01
#define YM2612_OPERATORMASK_2       0x02
#define YM2612_OPERATORMASK_3       0x04
#define YM2612_OPERATORMASK_4       0x08
#define YM2612_OPERATORMASK_NONE    0x00
#define YM2612_OPERATORMASK_ALL     YM2612_OPERATOR_1 | \
                                    YM2612_OPERATOR_2 | \
                                    YM2612_OPERATOR_3 | \
                                    YM2612_OPERATOR_4

#define YM2612_LFO_ON           0x08
#define YM2612_LFO_OFF          0x00

#define YM2612_LFO_398          0x00
#define YM2612_LFO_556          0x01
#define YM2612_LFO_602          0x02
#define YM2612_LFO_637          0x03
#define YM2612_LFO_688          0x04
#define YM2612_LFO_963          0x05
#define YM2612_LFO_4810         0x06
#define YM2612_LFO_7220         0x07

#define YM2612_CH36_ON          0x40
#define YM2612_CH36_OFF         0x00

#define YM2612_DAC_ON           0xFF
#define YM2612_DAC_OFF          0x00

#define YM2612_FREQ_DETUNE_1    0x00
#define YM2612_FREQ_DETUNE_1PE  0x10
#define YM2612_FREQ_DETUNE_1P2E 0x20
#define YM2612_FREQ_DETUNE_1P3E 0x30
#define YM2612_FREQ_DETUNE_1ME  0x50
#define YM2612_FREQ_DETUNE_1M2E 0x60
#define YM2612_FREQ_DETUNE_1M3E 0x70

#define YM2612_FREQ_MUL_HALF    0x00
#define YM2612_FREQ_MUL_1       0x01
#define YM2612_FREQ_MUL_2       0x02
#define YM2612_FREQ_MUL_3       0x03
#define YM2612_FREQ_MUL_4       0x04
#define YM2612_FREQ_MUL_5       0x05
#define YM2612_FREQ_MUL_6       0x06
#define YM2612_FREQ_MUL_7       0x07
#define YM2612_FREQ_MUL_8       0x08
#define YM2612_FREQ_MUL_9       0x09
#define YM2612_FREQ_MUL_10      0x0A
#define YM2612_FREQ_MUL_11      0x0B
#define YM2612_FREQ_MUL_12      0x0C
#define YM2612_FREQ_MUL_13      0x0D
#define YM2612_FREQ_MUL_14      0x0E
#define YM2612_FREQ_MUL_15      0x0F

#define YM2612_TL_MIN           0x00
#define YM2612_TL_MAX           0x7F

#define YM2612_RS_MIN           0x00
#define YM2612_RS_8             0x00
#define YM2612_RS_4             0x01
#define YM2612_RS_2             0x02
#define YM2612_RS_1             0x03
#define YM2612_RS_MAX           0x03

#define YM2612_AM_ON            0x80
#define YM2612_AM_OFF           0x00

#define YM2612_OP_FEEDBACK      0b111000
#define YM2612_OP_ALGORITHM     0b111

#define YM2612_STEREO_L         0x80
#define YM2612_STEREO_R         0x40
#define YM2612_STEREO_LR        YM2612_STEREO_L | YM2612_STEREO_R

#define YM2612_AMS_0            0x00
#define YM2612_AMS_14           0x01
#define YM2612_AMS_59           0x02
#define YM2612_AMS_118          0x03

#define YM2612_FMS_0            0x00
#define YM2612_FMS_34           0x01
#define YM2612_FMS_67           0x02
#define YM2612_FMS_100          0x03
#define YM2612_FMS_140          0x04
#define YM2612_FMS_200          0x05
#define YM2612_FMS_400          0x06
#define YM2612_FMS_800          0x07


/* A structure representing a ym2612 pin map */
struct ym2612_t {
    PinName dataBus[8];
    PinName commandBus[5];
    PinName clockPin;
};

/* A structure representing a ym2612 command */
struct ym2612cmd_t {
    uint8_t address;
    uint8_t part;
    uint8_t data;
};

#endif

