#ifndef PWMCONTROLLER_HPP
#define PWMCONTROLLER_HPP

/* PWM bases */

// GPIO12 ALT0(PWM0_0) 
// GPIO13 ALT0(PWM0_1) 
// GPIO18 ALT5(PWM0_0) 
// GPIO45 ALT0(PWM0_1) 
#define PWM0_BASE 0x7e20c000   

// GPIO40 ALT0(PWM1_0) 
// GPIO41 ALT0(PWM1_1) 
#define PWM1_BASE 0x7e20c800

/******************************* NOTES ***********************************/
/* - W1C is Write 1 to clear                                             */

/*************************************************************************/

struct PwmCtlStruct
{ 
  /************ FIELD  | SIZE | TYPE | RESET | DETAILS ************/
  unsigned char        : 16;//  N/A    N/A     N/A
  unsigned char MSEN2  : 1; //  RW     0x0     CH2 M/S ENABLE: 0 = PWM, 1 = M/S XMIT
  unsigned char        : 1; //  N/A    N/A     N/A
  unsigned char USEF2  : 1; //  RW     0x0     CH2 FIFO: 0 = DATA REG XMIT, 1 = FIFO XMIT
  unsigned char POLA2  : 1; //  RW     0x0     CH2 POLARITY: 0 = LOW(0), 1 = LOW(1) 
  unsigned char SBIT2  : 1; //  RW     0x0     CH 2 SILENCE BIT
  unsigned char RPTL2  : 1; //  RW     0x0     CH 2 REPEAT LAST DATA(FIFO): 0 = NO/HALT, 1 = YES 
  unsigned char MODE2  : 1; //  RW     0x0     CH2 MODE: 0 = PWM, 1 = SERIALISER
  unsigned char PWEN2  : 1; //  RW     0x0     CH2 ENABLE: 0 = DISABLE, 1 = ENABLE 
  unsigned char MSEN1  : 1; //  RW     0x0     CH1 M/S ENABLE: 0 = PWN, 1 = M/S XMIT
  unsigned char CLRF   : 1; //  W1SC   0x0     CLEAR FIFO: 1 = CLEAR
  unsigned char USEF1  : 1; //  RW     0x0     CH1 FIFO: 0 = DATA REG XMIT, 1 = FIFO XMIT 
  unsigned char POLA1  : 1; //  RW     0x0     CH1 POLARITY: 0 = LOW(0), 1 = LOW(1)
  unsigned char SBIT1  : 1; //  RW     0x0     CH1 SILENCE BIT
  unsigned char RPTL1  : 1; //  RW     0x0     CH 1 REPEAT LAST DATA(FIFO): 0 = NO/HALT, 1 = YES 
  unsigned char MODE1  : 1; //  RW     0x0     CH 1 Mode: 0 = disable, 1 = enable
  unsigned char PWEN1  : 1; //  RW     0x0     PWEN1: 0 = disabled, 0 equals enabled
};

struct PwmStaStruct
{
  /************ FIELD  | SIZE | TYPE | RESET | DETAILS ************/
  unsigned char        : 21; // N/A    N/A     N/A
  unsigned char STA2   : 1;  // RO     0x0     CHANNEL STATE XMIT
  unsigned char STA1   : 1;  // RO     0x0     CHANNEL STATE XMIT
  unsigned char BERR   : 1;  // W1C    0x0     REG WRITE ERR
  unsigned char        : 2;  // N/A    N/A     N/A
  unsigned char GAPO2  : 1;  // W1C    0x0     CHANNEL GAP ERR
  unsigned char GAPO1  : 1;  // W1C    0x0     CHANNEL GAP ERR        
  unsigned char RERR1  : 1;  // W1C    0x0     FIFO READ ERR          
  unsigned char WERR1  : 1;  // W1C    0x0     FIFO WRITE ERR
  unsigned char EMOT1  : 1;  // RO     0x1     FIFO EMPT 
  unsigned char FULL1  : 1;  // RO     0x0     FIFO FULL
};

struct PwmDmacStruct
{
  /************ FIELD  | SIZE | TYPE | RESET | DETAILS ************/
  unsigned char ENAB   : 1;  // RW     0x0     DMA ENABLE
  unsigned char        : 15; // N/A    N/A     N/A
  unsigned char PANIC  : 8;  // RW     0x7     DMA PANIC THRESHOLD
  unsigned char DREQ   : 8;  // RW     0x7     DREQ THRESHOLD
};

struct PwmRngDataStruct
{
  /************ FIELD  | SIZE | TYPE | RESET | DETAILS ************/
  unsigned char RNGCH1 : 32; // RW     0x020  
  unsigned char DATACH1: 32; // RW     0x0     # PULSES IN RANGE
  unsigned char FIFODAT: 32; // WO     0x0     # FIFO WRITE BUFFER
  unsigned char RNGCH2 : 32; // RW     0x020  
  unsigned char DATACH2: 32; // RW     0x0     # PULSES IN RANGE
};

struct PwmStruct
{
  PwmCtlStruct     : 32
  PwmStaStruct     : 32
  PwmDmacStruct    : 32
  PwmRngDataStruct : 160
};

/* Offsets */ 
#define PWM_CTL   0x00          // PWM Control
#define PWM_STA   0x04          // PWM Status
#define PWM_DMAC  0x08          // PWM DMA Configuration
#define PWM_RNG1  0x10          // PWM Channel 1 Range
#define PWM_DAT1  0x14          // PWM Channel 1 Data
#define PWM_FIF1  0x18          // PWM FIFO input
#define PWM_RNG2  0x20          // PWN Channel 2 Range
#define PWM_DAT2  0x24          // PWM Channel 2 Data



class PwmController
{
  public:
  PwmController();

  ~PwmController();

  PwmController(const &PwmController) = delete;

  PwmController operator=(const &rhs) = delete;

  bool validateStructMemorySize();

  private:
  PwmStruct data;

};


#endif /* PWMCONTROLLER_HPP */
