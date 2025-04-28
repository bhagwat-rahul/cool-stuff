This contains key insights during 0 - asic course and improvements that oss eda tools can make imo.

one of the things to do is export your pdk locally and then use a script to make magic with it.
part of the pdk is how std cells in the lib look along with drc rules, when you load magic w a pdk it auto drc checks.
this auto drc check interface can be made better, currently too command heavy and not intuitive enough.
easy way to switch between cross section and std view would also help.
acc to what you want to do you need to create a simulation, this could be enhanced w auto creating sim cmd's or gen'ing diff sim types.
these simulations aren't very good at sim'ing parasitics so maybe actually physically sim on an FPGA in the cloud.
assistant to quickly ref and grep through your pdk is low hanging fruit (index pdk and provide help)
also magic can be config'ed to have the command window as a terminal like window in ide's the single window per thing philosophy is stupid imo.


magic could have better layer picking in the sidebar
vdd is the drain vss is source and in mosfets input current decides whether the silicon that connects source to drain conducts or not.
Circuits are defined with verilog that can be simulated using yosys, the sim uses an intermediate representation since it doesn't have info from your std cells yet.
Then you can synth actual logic from cells of your pdk.

A register in HW (verilog) is just a collection of flip flops configured to store values upto certain lengths.
(8 bit reg will have flip flops to store up to 8 bits).
n-bit register has n flip flops a flip flop is just on/off stored in hw.
flip flops are built with latches.
Latches dont really hold the val for long cz they rely on capacitance which goes out after a while.
This is why we need flip flops.
Ideal flip flop samples immediately with no ambiguity on output and sample instantly on clkedge (i.e every time clock counts and not at an offset).


