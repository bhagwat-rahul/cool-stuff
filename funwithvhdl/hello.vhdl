-- VHDL stands for VHSIC Hardware Description Language (VHSIC stands for Very High Speed Integrated Circuit)

library ieee; -- Defines how certain keywords behave
use ieee.std_logic_1164.all;

entity example_and is
-- Define interface
port (
input_1: in std_logic;
input_2: in std_logic;
and_result: out std_logic
);
end example_and;

architecture rtl of example_and is -- Begin RTL behavior

signal and_gate : std_logic; -- equivalent of wire / logic in verilog

begin
and_gate <= input_1 and input_2; -- assign and of 1 & 2 to intermediate wire
and_result <= and_gate; -- assign val of intermediate wire to interface
end rtl; -- End RTL behavior
