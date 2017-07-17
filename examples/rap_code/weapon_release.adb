------------------------------------------------------------------------------
--                                                                          --
--                          PolyORB HI COMPONENTS                           --
--                                                                          --
--                       W E A P O N _ R E L E A S E                        --
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

with Computations;      use Computations;
with PolyORB_HI.Output; use PolyORB_HI.Output;
with PolyORB_HI_Generated.Activity; use PolyORB_HI_Generated.Activity;

package body Weapon_Release is

   --  WCET = 3 Ms

   Var : Integer := 0;

   ------------------------------
   -- On_Manual_Weapon_Release --
   ------------------------------

   procedure On_Manual_Weapon_Release (Entity : Entity_Type) is
   begin
      Put_Line ("Weapon_Release::On_Manual_Weapon_Release: BEGIN");
      Compute_During_N_Times_1ms (3);
      Var := Var + 1;

      if Var mod 11 = 0 then
         Put_Value (Entity,
                    RAP_Code_Weapon_Release_T_Interface'(Port => Do_Relaunch));
      end if;

      Put_Line ("Weapon_Release::On_Manual_Weapon_Release: END");
   end On_Manual_Weapon_Release;

   -----------------
   -- On_Relaunch --
   -----------------

   procedure On_Relaunch (Entity : Entity_Type) is
   begin
      Put_Line ("Weapon_Release::On_Relaunch: BEGIN");
      Put_Value (Entity,
                 RAP_Code_Weapon_Release_T_Interface'(Port => Do_Relaunch));
      Put_Line ("Weapon_Release::On_Relaunch: END");
   end On_Relaunch;

end Weapon_Release;
