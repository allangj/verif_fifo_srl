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

   // Declare component behaviour
   void behaviour_rx () {
      if (reset == '1') {
         read.write('0');
      }
   }

   // Constructor for the tx component
   SC_CTOR (rx_component) {
      SC_METHOD (behaviour_rx);
         sensitive << clk.pos();
   }
};
//-----------------------------------------------------------------------------
