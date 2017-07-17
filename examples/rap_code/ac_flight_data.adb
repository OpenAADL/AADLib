------------------------------------------------------------------------------
--                                                                          --
--                          PolyORB HI COMPONENTS                           --
--                                                                          --
--                       A C _ F L I G H T _ D A T A                        --
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

package body AC_Flight_Data is

   A : RAP_Int_32 := 0;

   ---------
   -- Job --
   ---------

   procedure Job (Entity : Entity_Type) is
   begin
      Put_Line ("AC_Flight_Data: BEGIN");
      A := A + 2;
      Put_Line ("AC_Flight_Data: Send Angle_Of_Attack "
                & RAP_Int_32'Image (A));
      Put_Value
        (Entity,
         RAP_Code_AC_Flight_Data_T_Interface'
           (Port                 => Angle_Of_Attack,
            Angle_Of_Attack_DATA => A));

      Compute_During_N_Times_1ms (8);
      Put_Line ("AC_Flight_Data: END");
   end Job;

end AC_Flight_Data;
