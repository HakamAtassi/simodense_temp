### FPGA Implementation as an AXI peripheral

The steps described here are for Vivado (tested on version 2020.1 and 2020.2) and the target FPGA board Ultra96, although similar steps can be followed for different boards etc.

There are the following files:

-`SAXI_ip.v` The AXI Slave part of the design. It encapsulates the softcore and is used by the Linux program to communicate with the softcore (mapped at 0x90000000).

-`MAXI_ip.v` The AXI Master part of the design, responsible for filling the last-level cache (LLC) and writing blocks back to main memory through the AXI interconnect. 

-`MAXI_ip_doublewidth.v` The version of `MAXI_ip.v` that uses the "double frequency optimisation" for the interconnect, to provide 256-bit/cycle in our platform from a 128-bit port.

-`caches.v`, `cpu.v`, `custom.v` and `system.v` The Verilog code of the softcore, supporting the sort and merge custom SIMD instructions (see those in folder ``../RTL_and_simulation`` for better comments and documentation). *Note*: these are older versions that potentially miss newer bugfixes, so fetch the updated `caches.v`, `cpu.v`, `custom.v` from ``../RTL_and_simulation`` for new projects.

-`VivadoBlockDiagram.png` and `VivadoAddressEditor.png` Raster images showing indicative settings in Vivado for a ZynqMP-based project. `VivadoBlockDiagram_doublewidth.png` is for the alternative for `VivadoBlockDiagram.png` for the "double frequency optimisation".


#### Steps to generate a bitstream, starting from a new project:

1. Create a new project and select a Zynq UltraScale+ device (ZU3EG SBVA484 -1 is the one in Ultra96). Enter the following to the TCL console to enable implementing large caches in Block Ram `set_param synth.elaboration.rodinMoreOptions "rt::set_parameter var_size_limit 33554432"`.

2. Import the sources through the *File > Import* menu and navigate to find and select the Verilog files from here (`caches.v`, `cpu.v`, `custom.v` and `system.v`). Navigate the sources tab to find them, and for each one tick the checkbox to include them globally in the properties tab. 

3. Click on the *Create Block Design* button and then insert an AXI Interconnect, a Zynq UltraScale MPSoC and a Processor System Reset from the *ADD IP* button (a plus sign). Also right click on the source files for `SAXI_ip.v` and `MAXI_ip.v` (or `MAXI_ip_doublewidth.v` for the double frequency optimisation) and add them to the block diagram one by one. 

For the double frequency optimisation, also add a Clocking Wizard and an AXI Clock Converter. 

4. Remember to set the data width of `S_AXI_HP0_FPD` to 128 through the *Re-customise IP* option of the Zynq UltraScale MPSoC IP. The clock configuration for the default version is 150 MHz for the PL Fabric Clock "PL0", using the divider 10 from the IOPLL clock source, in the Zynq UltraScale+ "Re-customize" dialog. 

For the double frequency optimisation, use a divider of 10, to operate at 300 MHz. In the latter case, set manually the input clock rate to 300 MHz for the primary clock, and one output clock of 150 MHz, at the Clocking Wizard through the corresponding *Re-customise IP* dialog. 

5. Make the appropriate connections to make it look like the image `VivadoBlockDiagram.png`. 

Alternatively for `MAXI_ip_doublewidth.v`, follow this block diagram instead: `VivadoBlockDiagram_doublewidth.png`. The general idea is that the `SAXI_ip.v` and `MAXI_ip_doublewidth.v` operate at 150 MHz, which is a clock generated by the clocking wizard, and their AXI width is 256-bit rather than the 128-bit of the port of the board. Note that the AXI interface of `SAXI_ip.v` is just 32-bit and is just for interfacing with it through Linux, hence the AXI Clock Converter. The AXI Clock Converter can actually be replaced by an AXI Interconnect for easier configuration (or increase the inputs of the currently used AXI interconnect).

6. Find the *Address Editor* tab and map half the memory to the MAXI_ip at 0x40000000, as shown in screenshot `VivadoAddressEditor.png`. The SAXI_ip part is mapped at 0x90000000.

7. Save the changes and then *Generate the bitstream*. Copy it to the filesystem of Ultra96 and load it using the FPGA Manager. Follow the instructions in the folder ``ARM_Linux_Client_for_Ultra96``. 

#### Notes for timing closure:

- Sometimes the tool optimisations worsened timing performance. The only enabled implementation optimisation option in early experiments was phys_opt_design (Post-Route). The latest version with the double frequency optimisation used the default Vivado 2020.2 directives.

- Slight changes in the design can make Vivado's heuristics to perform better. For example, when enabling "Safe Clock Startup" in the "Clocking Wizard" for the double frequency optimisation for changing primitive, sometimes it helps with implementation. 