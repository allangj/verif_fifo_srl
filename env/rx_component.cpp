//-----------------------------------------------------------------------------
// Name        : tx_component
//
// Inputs      : clk
//               reset
//               data_present
//               data_out
//
// Outputs     : write
//               
// Description : Drives data out of the be writen into the DUT
//-----------------------------------------------------------------------------

//---------------------------------Include Files-------------------------------
#include "systemc.h"
#include <stdlib.h>
//-----------------------------------------------------------------------------

//------------------------------------Defines----------------------------------
#define MAX_DELAY 20 // Rand values, consult possible values
#define MIN_DELAY 5
//-----------------------------------------------------------------------------

//-----------------------------------Data item---------------------------------
// Data structure
class data_t {
   public:
      sc_uint < 8 > data;
      sc_uint < 8 > delay; // Delay between reads
      void generate_values() {
         delay = rand()%(MAX_DELAY-MIN_DELAY)+MIN_DELAY
      }
}
//-----------------------------------------------------------------------------

//------------------------------------Module-----------------------------------
SC_MODULE(rx_component) {
   // Inputs
   sc_in < sc_logic > clk;
   sc_in < sc_logic > reset;
   sc_in < sc_logic > data_present;
   sc_in < sc_lv < 8 > > data_out;
   // Outputs
   sc_out < sc_logic > read;

   // Internal values
   data_t dat; // Data value to store data
   dat.generate_values;

   // Declare component behaviour
   void behaviour_rx () {
      if (reset == '1') {
         read.write('0');
      } else {
         if(data.delay == 0) { // read data from fifo
            read.write('1');
            dat.data = (sc_uint < 8 >)data_in.read(); // may be change and class will not contain data
            if(sent_data == true) {
               // add functionality FIXME send to env data to be added to scoreboard
            }
            // generate a new delay
            dat.generate_values;
         } else {
            if(dat.delay == 1) { //activate read signal and read data next cycle
               read.write('0');
               if (data_present.read() != '0') {
                  sent_data = true;
               }
            }
            data.delay = data.delay - 1;
         }
      }
   }

   // Constructor for the tx component
   SC_CTOR (rx_component) {
      SC_METHOD (behaviour_rx);
         sensitive << clk.pos();
   }
};
//-----------------------------------------------------------------------------
