with PolyORB_HI.Output;

package body Msgs is

   use PolyORB_HI.Output;

   --------------------
   -- Welcome_Pinger --
   --------------------

   procedure Welcome_Pinger is
   begin
      Put_Line ("Hello! This is the pinger thread starting");
   end Welcome_Pinger;

   -------------
   -- Recover --
   -------------

   procedure Recover is
   begin
      Put_Line ("Could not send message ! ***");
   end Recover;

end Msgs;
