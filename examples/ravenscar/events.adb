------------------------------------------------------------------------------
--                                                                          --
--                          PolyORB HI COMPONENTS                           --
--                                                                          --
--                               E V E N T S                                --
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
with PolyORB_HI_Generated.Activity; use PolyORB_HI_Generated.Activity;

package body Events is

   -----------------------------
   -- Delegate_External_Event --
   -----------------------------

   procedure Delegate_External_Event
     (Entity                        : Entity_Type;
      External_Interrupt_Depository : Interrupt_Counter)
   is
   begin
      Put_Line ("External Event Server: received an external interrupt");

      --  We record an entry in the Activation_Log buffer. We perform
      --  this by sending a data to the OUT DATA port
      --  'External_Interrupt'.

      Put_Value (Entity,
                 Ravenscar_Example_External_Event_Server_Interface'
                 (External_Interrupt,
                  External_Interrupt_Depository));

      --  Then we report nominal completion of current activation

      Put_Line ("External Event Server: end of sporadic activation.");
   end Delegate_External_Event;

end Events;
