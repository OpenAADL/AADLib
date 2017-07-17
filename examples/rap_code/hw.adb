------------------------------------------------------------------------------
--                                                                          --
--                          PolyORB HI COMPONENTS                           --
--                                                                          --
--                                   H W                                    --
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
with PolyORB_HI_Generated.Types; use PolyORB_HI_Generated.Types;
with PolyORB_HI_Generated.Activity; use PolyORB_HI_Generated.Activity;

package body HW is

   ---------------
   -- Radar_Job --
   ---------------

   procedure Radar_Job (Entity : Entity_Type) is
      pragma Unreferenced (Entity);
   begin
      Put_Line ("Radar: BEGIN");
      Compute_During_N_Times_1ms (2);
      Put_Line ("Radar: END");
   end Radar_Job;

   -------------
   -- RWR_Job --
   -------------

   procedure RWR_Job (Entity : Entity_Type) is
      pragma Unreferenced (Entity);
   begin
      Put_Line ("RWR: BEGIN");
      Compute_During_N_Times_1ms (20);
      Put_Line ("RWR: END");
   end RWR_Job;

   ----------------
   -- Keyset_Job --
   ----------------

   procedure Keyset_Job (Entity : Entity_Type) is
      W : constant RAP_Int_32 := Get_Value
        (Entity,
         Keyset_H_Port_Type'
           (Waypoint_Steering_Selected)).Waypoint_Steering_Selected_DATA;
      Q : constant RAP_Int_32 := Get_Value
        (Entity,
         Keyset_H_Port_Type'
           (Quantity_Select_Request)).Quantity_Select_Request_DATA;
   begin
      Put_Line ("Keyset: BEGIN");
      Put_Line ("Waypoint_Steering_Selected => " & RAP_Int_32'Image (W));
      Put_Line ("Quantity_Select_Request    => " & RAP_Int_32'Image (Q));
      Compute_During_N_Times_1ms (2);
      Put_Line ("Keyset: END");
   end Keyset_Job;

   -------------
   -- INS_Job --
   -------------

   procedure INS_Job (Entity : Entity_Type) is
      pragma Unreferenced (Entity);
   begin
      Put_Line ("INS: BEGIN");
      Compute_During_N_Times_1ms (2);
      Put_Line ("INS: END");
   end INS_Job;

   -------------
   -- NAV_Job --
   -------------

   procedure NAV_Job (Entity : Entity_Type) is
      pragma Unreferenced (Entity);
   begin
      Put_Line ("INS: BEGIN");
      Compute_During_N_Times_1ms (2);
      Put_Line ("INS: END");
   end NAV_Job;

end HW;
