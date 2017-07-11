------------------------------------------------------------------------------
--                                                                          --
--                          PolyORB HI COMPONENTS                           --
--                                                                          --
--                 M P D _ T A C T I C A L _ D I S P L A Y                  --
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
with PolyORB_HI.Output; use PolyORB_HI.Output;

package body MPD_Tactical_Display is

   ---------
   -- Job --
   ---------

   procedure Job (Entity : Entity_Type) is
      pragma Unreferenced (Entity);
   begin
      Put_Line ("MPD_Tactical_Display: BEGIN");
      Compute_During_N_Times_1ms (9);
      Put_Line ("MPD_Tactical_Display: END");
   end Job;

end MPD_Tactical_Display;
