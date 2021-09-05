with PolyORB_HI.Output;

package body Pinged is

   use PolyORB_HI.Output;

   --------------
   -- Ping_Spg --
   --------------

   procedure Ping_Spg (Data_Sink : Simple_Type) is
   begin
      Put_Line ("*** PING ***" & Simple_Type'Image (Data_Sink));
   end Ping_Spg;

end Pinged;
