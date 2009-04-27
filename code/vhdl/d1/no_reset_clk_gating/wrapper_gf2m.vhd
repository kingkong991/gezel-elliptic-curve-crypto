library ieee;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
library work;
use work.std_logic_arithext.all;


--datapath entity
entity wrapper_gf2m is
   port(
      A:in std_logic_vector(162 downto 0);
      B:in std_logic_vector(162 downto 0);
      start:in std_logic;
      mode:in std_logic;
      plus_one:in std_logic;
      T:out std_logic_vector(162 downto 0);
      ready:out std_logic;
      RST : in std_logic;
      CLK : in std_logic

   );
end wrapper_gf2m;


--signal declaration
architecture RTL of wrapper_gf2m is
signal reg_start:std_logic;
signal reg_start_wire:std_logic;
signal reg_mode:std_logic;
signal reg_mode_wire:std_logic;
signal reg_plus_one:std_logic;
signal reg_plus_one_wire:std_logic;
signal reg_T:std_logic_vector(162 downto 0);
signal reg_T_wire:std_logic_vector(162 downto 0);
signal reg_m:std_logic;
signal reg_m_wire:std_logic;
signal reg_cycle:std_logic_vector(7 downto 0);
signal reg_cycle_wire:std_logic_vector(7 downto 0);
signal reg_prev_ready:std_logic;
signal reg_prev_ready_wire:std_logic;
signal B_in:std_logic_vector(162 downto 0);
signal B_mux:std_logic;
signal T_in:std_logic_vector(162 downto 0);
signal T_out:std_logic_vector(162 downto 0);
signal T_mux:std_logic_vector(162 downto 0);
signal m_in:std_logic;
signal m_mux:std_logic;
signal m_out:std_logic;
signal sig_ready:std_logic;
signal sig_T_last:std_logic;
signal sig_en_T:std_logic;
signal sig_0:std_logic;
signal sig_1:std_logic;
signal sig_2:std_logic;
signal sig_3:std_logic;
signal sig_4:std_logic;
signal sig_5:std_logic;
signal sig_6:std_logic_vector(7 downto 0);
signal sig_7:std_logic_vector(7 downto 0);
signal sig_8:std_logic_vector(7 downto 0);
signal sig_9:std_logic;
signal sig_10:std_logic;
signal sig_11:std_logic_vector(162 downto 0);
signal sig_12:std_logic;
signal sig_13:std_logic_vector(162 downto 0);
signal sig_14:std_logic_vector(162 downto 0);
signal sig_15:std_logic_vector(162 downto 0);
signal sig_16:std_logic;
signal sig_17:std_logic;
signal sig_18:std_logic;
signal sig_19:std_logic;
signal sig_20:std_logic;
signal sig_21:std_logic_vector(162 downto 0);
signal sig_22:std_logic;
signal sig_23:std_logic;
signal sig_24:std_logic;
signal sig_25:std_logic;
signal sig_26:std_logic;
signal sig_28:std_logic_vector(162 downto 0);
signal sig_29:std_logic_vector(162 downto 0);
signal sig_30:std_logic_vector(162 downto 0);
signal sig_31:std_logic;
signal sig_32:std_logic;
signal sig_33:std_logic;
signal sig_34:std_logic;
signal sig_35:std_logic;
signal sig_36:std_logic;
signal sig_37:std_logic;
signal sig_38:std_logic;
signal T_int:std_logic_vector(162 downto 0);
signal ready_int:std_logic;
signal sig_27:std_logic_vector(163 downto 0);


--component map declaration
component malu
   port(
      T:in std_logic_vector(162 downto 0);
      B:in std_logic_vector(162 downto 0);
      m_in:in std_logic;
      T_n:out std_logic_vector(162 downto 0);
      m_n:out std_logic;
      RST : in std_logic;
      CLK : in std_logic
   );
end component;


begin


   --portmap
   label_malu : malu port map (
         T => T_in,
         B => B_in,
         m_in => m_in,
         T_n => T_out,
         m_n => m_out,
         RST => RST,
         CLK => CLK
      );
   --register updates
   dpREG: process (CLK,RST)
      begin
         if (RST = '1') then
            reg_start <= '0';
            reg_mode <= '0';
            reg_plus_one <= '0';
            reg_T <= (others=>'0');
            reg_m <= '0';
            reg_cycle <= (others=>'0');
            reg_prev_ready <= '0';
         elsif CLK' event and CLK = '1' then
            reg_start <= reg_start_wire;
            reg_mode <= reg_mode_wire;
            reg_plus_one <= reg_plus_one_wire;
            reg_T <= reg_T_wire;
            reg_m <= reg_m_wire;
            reg_cycle <= reg_cycle_wire;
            reg_prev_ready <= reg_prev_ready_wire;

         end if;
      end process dpREG;


   --combinational logics
   dpCMB: process (reg_start,reg_mode,reg_plus_one,reg_T,reg_m,reg_cycle,reg_prev_ready,B_in,B_mux,T_in
,T_out,T_mux,m_in,m_mux,m_out,sig_ready,sig_T_last,sig_en_T,sig_0,sig_1
,sig_2,sig_3,sig_4,sig_5,sig_6,sig_7,sig_8,sig_9,sig_10,sig_11
,sig_12,sig_13,sig_14,sig_15,sig_16,sig_17,sig_18,sig_19,sig_20,sig_21
,sig_22,sig_23,sig_24,sig_25,sig_26,sig_28,sig_29,sig_30,sig_31,sig_32
,sig_33,sig_34,sig_35,sig_36,sig_37,sig_38,T_int,ready_int,A,B
,start,mode,plus_one)
      begin
         reg_start_wire <= reg_start;
         reg_mode_wire <= reg_mode;
         reg_plus_one_wire <= reg_plus_one;
         reg_T_wire <= reg_T;
         reg_m_wire <= reg_m;
         reg_cycle_wire <= reg_cycle;
         reg_prev_ready_wire <= reg_prev_ready;
         B_in <= (others=>'0');
         B_mux <= '0';
         T_in <= (others=>'0');
         T_mux <= (others=>'0');
         m_in <= '0';
         m_mux <= '0';
         sig_ready <= '0';
         sig_T_last <= '0';
         sig_en_T <= '0';
         sig_0 <= '0';
         sig_1 <= '0';
         sig_2 <= '0';
         sig_3 <= '0';
         sig_4 <= '0';
         sig_5 <= '0';
         sig_6 <= (others=>'0');
         sig_7 <= (others=>'0');
         sig_8 <= (others=>'0');
         sig_9 <= '0';
         sig_10 <= '0';
         sig_11 <= (others=>'0');
         sig_12 <= '0';
         sig_13 <= (others=>'0');
         sig_14 <= (others=>'0');
         sig_15 <= (others=>'0');
         sig_16 <= '0';
         sig_17 <= '0';
         sig_18 <= '0';
         sig_19 <= '0';
         sig_20 <= '0';
         sig_21 <= (others=>'0');
         sig_22 <= '0';
         sig_23 <= '0';
         sig_24 <= '0';
         sig_25 <= '0';
         sig_26 <= '0';
         sig_28 <= (others=>'0');
         sig_29 <= (others=>'0');
         sig_30 <= (others=>'0');
         sig_31 <= '0';
         sig_32 <= '0';
         sig_33 <= '0';
         sig_34 <= '0';
         sig_35 <= '0';
         sig_36 <= '0';
         sig_37 <= '0';
         sig_38 <= '0';
         T_int <= (others=>'0');
         ready_int <= '0';
         sig_27 <= "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
         T <= (others=>'0');
         ready <= '0';

         if (start = '1') then
            sig_0 <= '1';
         else
            sig_0 <= '0';
         end if;
         if (sig_0 = '1') then
            sig_1 <= mode;
         else
            sig_1 <= reg_mode;
         end if;
         if (start = '1') then
            sig_2 <= '1';
         else
            sig_2 <= '0';
         end if;
         if (sig_2 = '1') then
            sig_3 <= plus_one;
         else
            sig_3 <= reg_plus_one;
         end if;
         if (start = '1') then
            sig_4 <= '1';
         else
            sig_4 <= '0';
         end if;
         if (sig_ready = '1') then
            sig_5 <= '1';
         else
            sig_5 <= '0';
         end if;
         sig_6 <= unsigned(reg_cycle) + unsigned(conv_std_logic_vector(1,8));
         if (sig_5 = '1') then
            sig_7 <= reg_cycle;
         else
            sig_7 <= sig_6;
         end if;
         if (sig_4 = '1') then
            sig_8 <= conv_std_logic_vector(0,8);
         else
            sig_8 <= sig_7;
         end if;
         if (start = '1') then
            sig_9 <= '1';
         else
            sig_9 <= '0';
         end if;
         if (mode = '0') then
            sig_10 <= '1';
         else
            sig_10 <= '0';
         end if;
         if (sig_10 = '1') then
            sig_11 <= A;
         else
            sig_11 <= conv_std_logic_vector(0,163);
         end if;
         if (sig_ready = '1') then
            sig_12 <= '1';
         else
            sig_12 <= '0';
         end if;
         sig_13 <= m_out & T_out(162 downto 1);
         if (sig_12 = '1') then
            sig_14 <= sig_13;
         else
            sig_14 <= T_out;
         end if;
         if (sig_9 = '1') then
            sig_15 <= sig_11;
         else
            sig_15 <= sig_14;
         end if;
         T_mux <= sig_15;
         T_in <= reg_T;
         sig_20 <= T_mux(0) xor reg_plus_one;
         sig_T_last <= sig_20;
         sig_21 <= T_mux(162 downto 1) & sig_T_last;
         T <= T_int;
         sig_22 <=  not reg_prev_ready;
         sig_23 <=  not reg_mode;
         sig_24 <= sig_23 or A(162);
         sig_25 <= sig_22 and sig_24;
         B_mux <= sig_25;
         if (B_mux = '1') then
            sig_26 <= '1';
         else
            sig_26 <= '0';
         end if;
         sig_28 <= sig_27(162 downto 0);
         if (sig_26 = '1') then
            sig_29 <= sig_28;
         else
            sig_29 <= conv_std_logic_vector(0,163);
         end if;
         sig_30 <= B and sig_29;
         B_in <= sig_30;
         m_in <= reg_m;
         sig_31 <= sig_ready or start;
         sig_32 <=  not sig_31;
         sig_33 <= sig_32 and m_out;
         m_mux <= sig_33;
         if (start = '1') then
            sig_34 <= '1';
         else
            sig_34 <= '0';
         end if;
         if (reg_mode = '0') then
            sig_35 <= '1';
         else
            sig_35 <= '0';
         end if;
         if (unsigned(reg_cycle) <= 161) then
            sig_36 <= '1';
         else
            sig_36 <= '0';
         end if;
         if (sig_36 = '1') then
            sig_37 <= '0';
         else
            sig_37 <= '1';
         end if;
         if (sig_34 = '1') then
            sig_38 <= '0';
         elsif (sig_35 = '1') then
            sig_38 <= '1';
         else
            sig_38 <= sig_37;
         end if;
         sig_ready <= sig_38;
         ready <= ready_int;
         T_int <= sig_21;
         ready_int <= sig_ready;
         reg_mode_wire <= sig_1;
         reg_plus_one_wire <= sig_3;
         reg_cycle_wire <= sig_8;
         reg_T_wire <= T_mux;
         reg_m_wire <= m_mux;
         reg_prev_ready_wire <= sig_ready;
      end process dpCMB;
end RTL;
