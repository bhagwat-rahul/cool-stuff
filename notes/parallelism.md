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

