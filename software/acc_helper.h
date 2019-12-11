// acc_helper.h
// For helper functions for hw accerlaotr
// Matthew Davis Fall 2019

// ******************************************************************** 
//                              DEFINES
// ******************************************************************** 

// ******************************************************************** 
// Debug defines
#undef DEBUG 
#undef DEBUG1
#undef DEBUG2
#undef DEBUG_BRAM
#define DEBUG                    // Comment out to turn off debug messages
/* #define DEBUG1                // Comment out to turn off debug messages */
//#define DEBUG2
//#define DEBUG_BRAM

// ******************************************************************** 
// Memomoy Map
#define CDMA                0x70000000
#define BRAM0               0x40000000
#define BRAM1               0x40000000
#define ACC                 0x44000000
#define OCM                 0xFFFC0000

// ******************************************************************** 
// Modes
#define STRING 		    1
#define FILE_MODE	    2
#define TESTBENCH           3

// ******************************************************************** 
// Regs for CDMA
#define CDMACR              0x00
#define CDMASR              0x04
#define CURDESC_PNTR        0x08
#define CURDESC_PNTR_MSB    0x0C
#define TAILDESC_PNTR       0x10
#define TAILDESC_PNTR_MSB   0x14
#define SA                  0x18
#define SA_MSB              0x1C
#define DA                  0x20
#define DA_MSB              0x24
#define BTT                 0x28

// ******************************************************************** 
// Regs for Acclerator
#define CHUNK_SIZE          0x10 // 16 bytes per chunk
#define NUM_CHUNKS          0x14
#define START_ADDR          0x18
#define FIRST_REG           0x00

// ******************************************************************** 
// Device path name for the GPIO device

#define GPIO_TIMER_EN_NUM   0x7             // Set bit 7 to enable timere             
#define GPIO_TIMER_CR       0x43C00000      // Control register
#define GPIO_LED_NUM        0x7
#define GPIO_LED            0x43C00004      // LED register
#define GPIO_TIMER_VALUE    0x43C0000C      // Timer value

// Global vars
static volatile unsigned int det_int=0;     // Global flag that is volatile 
                                            // i.e., no caching

// ***************  Struct for keeping state of program ******************
//

typedef struct program_state {
        char*   aes_string;
        char*   key_string;
        int     mode;
} pstate;


// ************************  FUNCTION PROTOTYPES ***********************
//       
// ************************  Memory Operations   ***********************
// Set Memory Bit Routine
int smb(unsigned int target_addr, unsigned int pin_number, 
        unsigned int bit_val);
// Put Memory (Put value in target_addr)
int pm(unsigned int target_addr, unsigned int value);
// Remove Memory
unsigned int rm( unsigned int target_addr);
// Set address + offset to specific value
unsigned int address_set(unsigned int* virtual_address, int offset, unsigned int value);
// CDMA get data at address + offset
unsigned int dma_get(unsigned int* dma_virtual_address, int offset);
// Poll cdma to wait for transaction to finish
int cdma_sync(unsigned int* dma_virtual_address);
// Signal handler for interrupt
void sighandler(int signo);

// Init state from program args
void init_state(int argc, char* argv[], pstate* state);

// For printing AES values
// Encrypt buffer (128 bits) goes to encrypt
// aes string is returned to be printed
// endian switch to 1 to change endianess
void print_aes(char *aes, uint32_t *encrypt, int endian_switch);

// ************************  Functions for latency testing
unsigned long int_sqrt(unsigned long n);
/* void compute_interrupt_latency_stats( unsigned long   *min_latency_p, */ 
/*                                       unsigned long   *max_latency_p, */ 
/*                                       unsigned long   *average_latency_p, */ 
/*                                       unsigned long   *std_deviation_p, */
/*                                       unsigned long   *intr_latency_measurements; */
/*                                       unsigned int    lp_cnt); */ 


