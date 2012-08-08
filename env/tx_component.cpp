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

   // Declare component behaviour
   void behaviour_tx () {
      if (reset == '1') {
         write.write('0');
         data_in.write(0x00);
         
      }
   }

   // Constructor for the tx component
   SC_CTOR (tx_component) {
      SC_METHOD (behaviour_tx);
         sensitive << clk.pos();
   }
};
//-----------------------------------------------------------------------------
