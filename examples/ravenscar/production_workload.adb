------------------------------------------------------------------------------
--                                                                          --
--                          PolyORB HI COMPONENTS                           --
--                                                                          --
--                  P R O D U C T I O N _ W O R K L O A D                   --
--                                                                          --
--                                 B o d y                                  --
--                                                                          --
--                 Copyright (C) 2009, GET-Telecom Paris.                   --
--                                                                          --
-- PolyORB HI is free software; you  can  redistribute  it and/or modify it --
-- under terms of the GNU General Public License as published by the Free   --
-- Software Foundation; either version 2, or (at your option) any later.    --
-- PolyORB HI is distributed  in the hope that it will be useful, but       --
-- WITHOUT ANY WARRANTY;  without even the implied warranty of              --
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General --
-- Public License for more details. You should have received  a copy of the --
-- GNU General Public  License  distributed with PolyORB HI; see file       --
-- COPYING. If not, write  to the Free  Software Foundation, 51 Franklin    --
-- Street, Fifth Floor, Boston, MA 02111-1301, USA.                         --
--                                                                          --
-- As a special exception,  if other files  instantiate  generics from this --
-- unit, or you link  this unit with other files  to produce an executable, --
-- this  unit  does not  by itself cause  the resulting  executable  to  be --
-- covered  by the  GNU  General  Public  License.  This exception does not --
-- however invalidate  any other reasons why  the executable file  might be --
-- covered by the  GNU Public License.                                      --
--                                                                          --
--                PolyORB HI is maintained by GET Telecom Paris             --
--                                                                          --
------------------------------------------------------------------------------

with Ada.Real_Time; use Ada.Real_Time;

package body Production_Workload is

   --  At elaboration time, this package evaluate the number of fixed
   --  point operation 1.0 / X to consume CPU during 1 millisecond.

   --  We use fixed point types to be compliant with restrictions for
   --  HIgh-Integrity systems (pragma Restriction No_Float).

   type Fixed_12_6 is delta 1.0E-6 digits 12;

   N_Base : constant Positive     := 1_000;
   F_Base : constant Fixed_12_6  := 1.0001;

   --  XMS or X Milli Seconds
   XMS    : constant Time_Span := Milliseconds (1);
   N_XMS  : Positive; --  Is computed at elaboration time

   --------------------------------
   -- Compute_During_N_Times_1ms --
   --------------------------------

   procedure Compute_During_N_Times_1ms (N : Positive) is
      X : Fixed_12_6 := F_Base;
   begin
      for I in 1 .. N_XMS * N loop
         X := 1.0 / X;
      end loop;
   end Compute_During_N_Times_1ms;

begin
   declare
      B : Time;
      --  Begin of the measure

      E : Time;
      --  End od the measure

      X : Fixed_12_6 := F_Base;
   begin

      --  Measure N_Base times the same operation 1/X

      B := Clock;
      for I in 1 .. N_Base loop
         X := 1.0 / X;
      end loop;
      E := Clock;

      --  Calculate the number of operation necessary to consume CPU
      --  during 1 sec.

      N_XMS := Positive ((XMS * N_Base) / (E - B));

      --  Redo the measure to obtain a more precise N_XMS value

      B := Clock;
      for I in 1 .. N_XMS loop
         X := 1.0 / X;
      end loop;
      E := Clock;
      N_XMS := Positive ((XMS * N_XMS) / (E - B));
   end;
end Production_Workload;
