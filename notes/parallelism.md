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
(benchmarks could be stuff like comparisons on streams of vec instr's non vec, wall clk time, throughput, etc.)
(power utilisation for diff types or proc types, etc.)

one consideration is, you have to ensure the same instructions are being run on mult data for simd.
for eg. if you have an if else branch that works on a vector, then some elements will have to go via if code path
and others via else, so that doubles the amt of time.
if you have an if else and you structure so that the more popular case takes longer than non popular case to exec,
that can massively slow down stuff. divergent code like this tough to parallelise.
but if you do simd on divergent, try to ensure conditionals are similar performance or if you can make assumptions
like knowing which condition is likelier then make that quicker and not take too long?
simd parallelism is usually done at compile time if explicit or runtime by hw if implicit.

there is also multi threading which would be having multiple register states per core, so that way when on instruction
is waiting on memory to be fetched into cache you just exec other ones in their own reg's

so in hw if you have fetch+decode, exec, memacc/wb(reg's you're execing on) units diff types so far are:-
1. superscalar:- do multiple independent things at once, in hw this means multiple fetch+decode and exec w common mem/wb interface and an out of order instruction co-ordinator.
2. simd:- common fetch/decode/memacc/wb but mult (vector) exec units.
3. multi-core:- just do fully diff things everything duplicated.
4. multi-thread:- has multi mem/wb interface to reduce stall time, common fetch/decode, can have simd like multi exec.

in multi threaded you probably want to have enough threads to account for your longest amt of stall time from slowest memory.
also probably dont want too many since memory takes up larger space than logic and every thread is just replicated regs (memory)
could also do something where instead of serving continuously you always serve unit waiting for longest etc. some consierations to make there.

bringing this all together you can a large dispatcher at the top with all these things mixed in diff quantities and the dispatcher / scheduler just ensures max utlisation provided we have things to do.

one implementation details is that cpu's are always simd never simt and gpu's are usually simt.
simt is just single instruction multiple thread.
a way to think about this is simt would be instantiating a regfile 8 times.
simd would be having every reg in the regfile be 8 vec wide.
in simt, technically each thread has their own prog counters they still do the same thing though (look at warps in gpu's)

usually, still in modern systems we are blocked by the speed of memory, cz even hbm's are 1% of the speed that alu's demand for max throughput.
so usually you're trying to optimise programs for the least amount of mem fetches since that's currently the costliest.
so favor computing things (arithmetic) over loading things (memacc's) if you have a choice.
^ this is for situations where you have tons of things that could be fed to the pipe.

intel ispc compiler gives you some amount of abstraction over having to manually manage threading and simd.
similar to what things like cuda, etc. would do. instead of having to specify simd width's and thread spawning,
you usually define the work that needs to be done, what part is parallelisable, give it a parallelisable impl.
and it will parallelise it.

It runs in 'gangs' so whenever you specify a task it will spawn x gangs and return results once all gangs are done.
ispc code compiles down to .o files so your cpp can call it normally.

Can be tricky to manage race conditions for common vars that need to be updated.
To fix you can use locks, intermediate vec vars, thread pooling, etc.

apart from simd like stuff you could also have parallelism where each parr unit does diff things.
some examples of this are recursive functions where each level down is independent.
there's cilk in c that let's you do this kinda stuff where you can just cilk_spawn and cilk_sync.
not to be confused with fork and join, since fork implies that the work will start asap.
cilk simply says that this work is async do this whenever before i call sync (or implicitly the end of a func)

the underlying implementation could just run things as you wrote them and not do anything parallel,
or run every spawned thing (which in turn could spawn more stuff etc)
if it kept calling every spawned thing there would be work to do in the queue always before sync instead of having to wait.

also, usually when doing parallel stuff you have things like locks and barriers for using shared vars/state.
so a lock on a var ensures other people don't read/write to from it.
and barriers ensure that no more than x things use a resource at the same time.
internally these are implemented using atomics.

these locks/spawns and other constructs will also build dag's (directed acyclic graphs) or dependency graphs that you then need to follow.
a good part of what things like pytorch, etc. do is this.

