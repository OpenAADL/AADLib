------------------------------------------------------------------------------
--                                                                          --
--                          PolyORB HI COMPONENTS                           --
--                                                                          --
--                         E V E N T _ S O U R C E                          --
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

with PolyORB_HI.Output;             use PolyORB_HI.Output;
with PolyORB_HI_Generated.Types;    use PolyORB_HI_Generated.Types;
with PolyORB_HI_Generated.Activity; use PolyORB_HI_Generated.Activity;

package body Event_Source is

   type Divisor_Type is mod 4;

   Criterion : Natural;
   Divisors  : constant array (Divisor_Type) of Positive := (2, 3, 5, 7);
   Divisor   : Divisor_Type;
   --  Use an arbitrary criterion for the sending of external
   --  interrupts.

   Interrupt_Count : Interrupt_Counter;

   ----------
   -- Init --
   ----------

   procedure Init is
   begin
      Put_Line ("External Events: starting");

      Criterion := 0;
      Divisor   := 0;

      Interrupt_Count := 0;
   end Init;

   ------------------------
   -- New_External_Event --
   ------------------------

   procedure New_External_Event (Entity : Entity_Type) is
   begin
      if Criterion mod Divisors (Divisor) = 0 then
         Divisor := Divisor + 1;
         Interrupt_Count := Interrupt_Count + 1;

         Put_Line ("External Events: send an new event:"
                   & Interrupt_Counter'Image (Interrupt_Count)
                   & ". Next divisor ="
                   & Positive'Image (Divisors (Divisor)));

         --  Send the interrupt to the OUT EVENT DATA port
         --  'External_Interrupt' of the thread.

         Put_Value (Entity,
                    RavenscarExample_External_Event_Source_Interface'
                    (External_Interrupt,
                     Interrupt_Count));
      end if;

      --  Evaluate the sending condition

      Criterion := Criterion + 1;
   end New_External_Event;

end Event_Source;
