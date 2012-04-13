------------------------------------------------------------------------------
--                                                                          --
--                          PolyORB HI COMPONENTS                           --
--                                                                          --
--                    P R O D U C E R _ C O N S U M E R                     --
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

--  $Id: producer_consumer.adb 6274 2009-03-25 19:56:54Z lasnier $

with PolyORB_HI.Output;
with PolyORB_HI_Generated.Deployment;

package body Producer_Consumer is

   use PolyORB_HI.Output;
   use PolyORB_HI_Generated.Deployment;

   The_Data : Alpha_Type := 1;

   function Get_Node return String;
   --  Return the current node name

   --------------
   -- Get_Node --
   --------------

   function Get_Node return String is
   begin
      return Node_Type'Image (My_Node);
   end Get_Node;

   -----------------
   -- Produce_Spg --
   -----------------

   procedure Produce_Spg (Data_Source : out Alpha_Type) is
   begin
      Data_Source := The_Data;
      The_Data := The_Data + 1;

      Put_Line (Normal, Get_Node
                & ": produced "
                & Alpha_Type'Image (Data_Source));
   end Produce_Spg;

   -----------------
   -- Consume_Spg --
   -----------------

   procedure Consume_Spg (Data_Sink : Alpha_Type) is
   begin
      Put_Line (Normal, Get_Node
                & "                              : consumed "
                & Alpha_Type'Image (Data_Sink));
   end Consume_Spg;
end Producer_Consumer;
