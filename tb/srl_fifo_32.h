#ifndef __SRL_FIFO_32_H__
#define __SRL_FIFO_32_H__
#include "systemc.h"

class srl_fifo_32 : public sc_foreign_module {
   public:
      // Inputs
      sc_in < sc_logic > clk;
      sc_in < sc_logic > reset;
      sc_in < sc_logic > write;
      sc_in < sc_logic > read;
      sc_in < sc_lv < 8 > > data_in
      // Outputs
      sc_out < sc_logic > full;
      sc_out < sc_logic > half_full;
      sc_out < sc_logic > data_present;
      sc_out < sc_lv < 8 > > data_out;

      srl_fifo_32 (sc_module_name nm) : sc_foreign_module(nm, "srl_fifo_32"),
      clk("clk"),
      reset("reset"),
      write("write"),
      read("read"),
      data_in("data_in"),
      full("full"),
      half_full("half_full"),
      data_present("data_present"),
      data_out("data_out")
      {}

      ~srl_fifo_32() {}
};

#endif
