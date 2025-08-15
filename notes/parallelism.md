# Some notes on parallel processing and exec (some from cs149)

A program is just a list of instructions, cpu's exec these (in order or at least in order of deps)
CPUs exec'ing instructions just means they're changing some underlying *state* (i.e. memory)
caches, drams, etc. are examples of memory. memory is just an array of bytes (with addresses)

to drive in diff's in speed:-
fig's from intel kaby lake
- L1 cache: - 4 clks
- L2 cache: - 10 clks
- L3 cache: - 40 clks
- DRAM    : - 250 clks

can think of caches super-rudimentarily of things that store things when used frequently or last used.
like just remove oldest thing that came into cache to make space for new thing.

We need parallelism cz clock speeds not increasing anymore in last couple decades + work done per clk also not.
not increasing cz somewhat fundamentally constrained by power, since power drives more heat and it's pretty exponential.

one way to parallelise is run instr's not dependent on prev ones parallely, aka superscalar execution
**scalar** exec is one thing at a time **superscalar** is more than one thing (independent instructions parallely)

caches usually have *cache lines*, i.e each cache line can store mem from mult addresses:-
so a 4 byte cache line named 0x4 (address 4) can have data from addr's 0x4, 0x5, 0x6, 0x7
so cache lines are kinda like addressing schemes where how many bytes defines offset

instead of a superscalar processor that just has 2 fetch/decode/exec units you could go multi-core.
so maybe have 2 full processors with their own smaller l1 caches etc. that way each can take less area.
so you would have 2 proc's with 75% of the power of 1 and for parallel stuff do 1.5x as much.

could also be possible to parallelise up the stack in s/w which is interesting.
so for eg. a tensor op that does same stuff on multiple data (simd) it doesn't dispatch stuff to diff cores.
it could just have one powerful core do an op on tons of data, like one instruction to apply a state change
to a bunch of diff memory.

gpu eg. rt4090 has 144 'cores' called, sm's (shared multiprocessors).

some things will have smaller parallel cores and big superscalar / stronger cores so you get a good mix
of single core / parallel perf.

extending on multi-core for simd like stuff, what you can do is just have tons of exec units.
and then the reg's available to them will be a vector of regs, eg:-
logic [8] reg0 instead of logic reg0, so each reg is x wide.

and to use the same in sw what you could do is change all vars that can be simd'ed change them to vec's
and then your for loop iterates over each vector.

so for eg. a 16 core processor w 8 wide exec's each core is 128 things you can do in parallel.
so you could spawn 16 threads each doing 1/16th of the work where each block of work operates on 8 wide vec's

probably good thing to think about how superscalar you want each core to be and run benchmarks.
so eg. do you want 1 core w 128 exec units, 8 cores with 16 exec's or 16 cores w 8 exec's or anything in the middle.
good insight here is non floating point alu units can be super small

(could be fun to write parametized verilog for this and run some benchmarking on sky130pdk/fpga simulations)

