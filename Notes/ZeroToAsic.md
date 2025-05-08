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
Most programs will tell you that you have accidentally created a latch in your circuit.
You usually never want to create a latch and always use flip flops, latches are issues!!!
we can implement debouncing mechanisms when working with external clocks or when we can't trust clock accuracy.
debounce is basically check a signal x number of times before flipping val.
eg. when you press a button the signal kind of bounces a few times between 0 and 1, so just sample a few times
before flipping the count.

2 types of logic:- combinatorial and sequential.
hardware by default is combinatorial (will compute things instantly in a 'stateless' way).
sequential logic is when you need to hold things in memory / need some state.
sequential logic is implemented using combinatorial hw with flip flops to store temporary things.

In verilog we use <= to assign a value to a var (usually read from right to left)
using '=' results in a blocking op which can be unpredictable, therefore <= is used which is non blocking.
For more info [read this about the differences.](https://www.perplexity.ai/search/blocking-vs-non-blocking-assig-RkHCoI1nS_OPGGIdcf.EWg)
some advice:-

```
In Verilog, if you want to create sequential logic use a clocked always block with Nonblocking assignments.
If you want to create combinational logic use an always block with Blocking assignments.
Try not to mix the two in the same always block.
```

Also, if you modify a register in an always clocked block, try not to modify it elsewhere since both happen at the same time.
Just in general be careful of modifying things in loops or ifs and outside.
Could be tough to wrap head around what happens when since code is not procedural but can be at times.

`always_comb begin` in verilog is a better syntax to write `always @(*)begin`.
[Verilog note about always running code](https://chatgpt.com/share/6813f4ca-1850-8000-aec0-12fcf59bf812)

Verification is done to ensure your logic does what you want it to, you can write cover statements and asserts
(much like c programming) to do so, and then you simulate stuff in something like gtkwave or yosys.
This is also pretty command heavy and could be well suited to a GUI.
So things like opening a specific thing in gtkw with a specic config:-
`gtkwave timer/engine_0/trace0.vcd timer.gtkw`

Usually this verif, etc. is done by things like SAT Solvers or SMT Solvers.
Easy way to think about it is like:-
Imagine a man a wolf and a deer on one side of a river, need to get them to other side, but there's safety issues w animals eating each other.
Using your code you define who can eat what and who can't + the end outcome you want and the solver will run a simulation and give you a soln.
Or let you know that there isn't one.
A good opportunity to also have solvers running in the cloud since resource heavy (guessing that's what a lot of prop tools do.)

Why verify? Cz taping chips is expensive!!! Also take a while (few months), so it's good to know things work.

Noticing a lot of back and forth between you code and some kind of waveform / sim viewer where you go around checking if signals are what you want them to be.
Could potentially be automated with some kind of deterministic tool to check the simulation file or an LLM (not trustworthy but to spot quick things.)

