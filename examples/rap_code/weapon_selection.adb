------------------------------------------------------------------------------
--                                                                          --
--                          PolyORB HI COMPONENTS                           --
--                                                                          --
--                     W E A P O N _ S E L E C T I O N                      --
--                                                                          --
--                                 B o d y                                  --
--                                                                          --
--                     Copyright (C) 2015 ESA & ISAE.                       --
--                                                                          --
-- PolyORB-HI is free software; you can redistribute it and/or modify under --
-- terms of the  GNU General Public License as published  by the Free Soft- --
-- ware  Foundation;  either version 3,  or (at your option) any later ver- --
-- sion. PolyORB-HI is distributed in the hope that it will be useful, but  --
-- WITHOUT ANY WARRANTY; without even the implied warranty of               --
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                     --
--                                                                          --
-- As a special exception under Section 7 of GPL version 3, you are granted --
-- additional permissions described in the GCC Runtime Library Exception,   --
-- version 3.1, as published by the Free Software Foundation.               --
--                                                                          --
-- You should have received a copy of the GNU General Public License and    --
-- a copy of the GCC Runtime Library Exception along with this program;     --
-- see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see    --
-- <http://www.gnu.org/licenses/>.                                          --
--                                                                          --
--              PolyORB-HI/Ada is maintained by the TASTE project           --
--                      (taste-users@lists.tuxfamily.org)                   --
--                                                                          --
------------------------------------------------------------------------------

with Computations; use Computations;
with PolyORB_HI.Output;       use PolyORB_HI.Output;

package body Weapon_Selection is

   --  WCET = 1 Ms

   ------------------------------
   -- On_Weapon_Select_Request --
   ------------------------------

   procedure On_Weapon_Select_Request (Entity : Entity_Type;
                                       Weapon_Select_Request : RAP_Int_32)
   is
      pragma Unreferenced (Weapon_Select_Request);
      pragma Unreferenced (Entity);
   begin
      Put_Line ("Weapon_Selection::On_Weapon_Select_Request: BEGIN");
      Compute_During_N_Times_1ms (1);
      Put_Line ("Weapon_Selection::On_Weapon_Select_Request: END");
   end On_Weapon_Select_Request;

   --------------------------------
   -- On_Quantity_Select_Request --
   --------------------------------

   procedure On_Quantity_Select_Request
     (Entity : Entity_Type; Quantity_Select_Request : RAP_Int_32)
   is
      pragma Unreferenced (Quantity_Select_Request);
      pragma Unreferenced (Entity);
   begin
      Put_Line ("Weapon_Selection::On_Quantity_Select_Request: BEGIN");
      Compute_During_N_Times_1ms (1);
      Put_Line ("Weapon_Selection::On_Quantity_Select_Request: END");
   end On_Quantity_Select_Request;

   --------------------------------
   -- On_Interval_Select_Request --
   --------------------------------

   procedure On_Interval_Select_Request
     (Entity : Entity_Type; Interval_Select_Request : RAP_Int_32)
   is
      pragma Unreferenced (Interval_Select_Request);
      pragma Unreferenced (Entity);
   begin
      Put_Line ("Weapon_Selection::On_Interval_Select_Request: BEGIN");
      Compute_During_N_Times_1ms (1);
      Put_Line ("Weapon_Selection::On_Interval_Select_Request: END");
   end On_Interval_Select_Request;

   -------------------------
   -- On_Auto_CCIP_Toggle --
   -------------------------

   procedure On_Auto_CCIP_Toggle (Entity : Entity_Type) is
      pragma Unreferenced (Entity);
   begin
      Put_Line ("Weapon_Selection::On_Auto_CCIP_Toggle: BEGIN");
      Compute_During_N_Times_1ms (1);
      Put_Line ("Weapon_Selection::On_Auto_CCIP_Toggle: END");
   end On_Auto_CCIP_Toggle;

end Weapon_Selection;
