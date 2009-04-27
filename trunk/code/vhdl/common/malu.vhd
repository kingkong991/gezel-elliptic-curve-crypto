library ieee;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
library work;
use work.std_logic_arithext.all;


--datapath entity
entity malu is
   port(
      T:in std_logic_vector(162 downto 0);
      B:in std_logic_vector(162 downto 0);
      m_in:in std_logic;
      T_n:out std_logic_vector(162 downto 0);
      m_n:out std_logic;
      RST : in std_logic;
      CLK : in std_logic

   );
end malu;


--signal declaration
architecture RTL of malu is
signal sum:std_logic_vector(162 downto 0);
signal result:std_logic_vector(162 downto 0);
signal sig_zero:std_logic;
signal sig_0:std_logic_vector(162 downto 0);
signal sig_1:std_logic_vector(154 downto 0);
signal sig_2:std_logic;
signal sig_3:std_logic;
signal sig_4:std_logic_vector(155 downto 0);
signal sig_5:std_logic;
signal sig_6:std_logic;
signal sig_7:std_logic_vector(156 downto 0);
signal sig_8:std_logic_vector(1 downto 0);
signal sig_9:std_logic_vector(158 downto 0);
signal sig_10:std_logic;
signal sig_11:std_logic;
signal sig_12:std_logic_vector(159 downto 0);
signal sig_13:std_logic_vector(1 downto 0);
signal sig_14:std_logic_vector(161 downto 0);
signal sig_15:std_logic;
signal sig_16:std_logic;
signal sig_17:std_logic_vector(162 downto 0);
signal sig_18:std_logic_vector(162 downto 0);
signal T_n_int:std_logic_vector(162 downto 0);
signal m_n_int:std_logic;


begin


   --combinational logics
   dpCMB: process (sum,result,sig_zero,sig_0,sig_1,sig_2,sig_3,sig_4,sig_5,sig_6
,sig_7,sig_8,sig_9,sig_10,sig_11,sig_12,sig_13,sig_14,sig_15,sig_16
,sig_17,sig_18,T_n_int,m_n_int,T,B,m_in)
      begin
         sum <= (others=>'0');
         result <= (others=>'0');
         sig_zero <= '0';
         sig_0 <= (others=>'0');
         sig_1 <= (others=>'0');
         sig_2 <= '0';
         sig_3 <= '0';
         sig_4 <= (others=>'0');
         sig_5 <= '0';
         sig_6 <= '0';
         sig_7 <= (others=>'0');
         sig_8 <= (others=>'0');
         sig_9 <= (others=>'0');
         sig_10 <= '0';
         sig_11 <= '0';
         sig_12 <= (others=>'0');
         sig_13 <= (others=>'0');
         sig_14 <= (others=>'0');
         sig_15 <= '0';
         sig_16 <= '0';
         sig_17 <= (others=>'0');
         sig_18 <= (others=>'0');
         T_n_int <= (others=>'0');
         m_n_int <= '0';
         T_n <= (others=>'0');
         m_n <= '0';

         sig_0 <= T xor B;
         sum <= sig_0;
         sig_1 <= conv_std_logic_vector(signed(sum(162 downto 8)),155);
         sig_2 <= sum(7);
         sig_3 <= sig_2 xor m_in;
         sig_4 <= sig_1 & sig_3;
         sig_5 <= sum(6);
         sig_6 <= sig_5 xor m_in;
         sig_7 <= sig_4 & sig_6;
         sig_8 <= conv_std_logic_vector(signed(sum(5 downto 4)),2);
         sig_9 <= sig_7 & sig_8;
         sig_10 <= sum(3);
         sig_11 <= sig_10 xor m_in;
         sig_12 <= sig_9 & sig_11;
         sig_13 <= conv_std_logic_vector(signed(sum(2 downto 1)),2);
         sig_14 <= sig_12 & sig_13;
         sig_15 <= sum(0);
         sig_16 <= sig_15 xor m_in;
         sig_17 <= sig_14 & sig_16;
         result <= sig_17;
         sig_zero <= '0';
         sig_18 <= result(161 downto 0) & sig_zero;
         T_n <= T_n_int;
         m_n <= m_n_int;
         T_n_int <= sig_18;
         m_n_int <= result(162);
      end process dpCMB;
end RTL;
