//-----------------------------------------------------------------------------
// Name        : tx_component
//
// Inputs      : clk
//               reset
//               full
//               half_full
//
// Outputs     : write
//             : data_in
//               
// Description : Drives data to the be writen into the DUT
//-----------------------------------------------------------------------------

//---------------------------------Include Files-------------------------------
#include "systemc.h"
#include <scv.h>
#include <stdlib.h>
//-----------------------------------------------------------------------------

//------------------------------------Defines----------------------------------
#define RND_SEED 1 // used to srand(time(NULL)); This must be done in env better to propagate to all and avoid conflicts
#define MAX_NUMBER_DATA 800
#define MIN_NUMBER_DATA 160
#define MAX_DELAY 20 // Rand values, consult possible values
#define MIN_DELAY 5
//-----------------------------------------------------------------------------

//-----------------------------------Data item---------------------------------
// Data structure
class data_t {
   public:
      sc_uint < 8 > data;
      sc_uint < 8 > delay; // Delay between data to be written
      void generate_values() {
         data = rand();
         delay = rand()%(MAX_DELAY-MIN_DELAY)+MIN_DELAY
      }
}
//-----------------------------------------------------------------------------

//------------------------------------Module-----------------------------------
SC_MODULE(tx_component) {
   // Inputs
   sc_in < sc_logic > clk;
   sc_in < sc_logic > reset;
   sc_in < sc_logic > full;
   sc_in < sc_logic > half_full;
   // Outputs
   sc_out < sc_logic > write;
   sc_out < sc_lv < 8 > > data_in;

   // Internal values
   data_t dat; // Data value use
   dat.generate_values;
   sc_uint < 10 > data_num = rand()%(MAX_NUMBER_DATA-MIN_NUMBER_DATA)+MIN_NUMBER_DATA;

   // Declare component behaviour
   void behaviour_tx () {
      if (reset == '1') {
         write.write('0');
         data_in.write(0x00);
      } else {
         while (data_num != 0) { // procedure while still data to send
            if(dat.delay == 0) { // send pkt
               write.write('1');
               data_in.write((sc_lv)dat.data);
               // reduce data number
               data_num = data_num - 1;
               // generate new values
               data.generate_values;
            } else { // reduce delay and wait 1 clk
               write.write('0');
               // reduce delay
               data.delay = data.delay - 1;
            }
         }
      }
   }

   // Constructor for the tx component
   SC_CTOR (tx_component) {
      SC_METHOD (behaviour_tx);
         sensitive << clk.pos();
   }
};
//-----------------------------------------------------------------------------
