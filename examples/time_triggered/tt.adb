with PolyORB_HI.Output; use PolyORB_HI.Output;

package body TT is

   B0_Cycles : Simple_Type := 0;
   B1_Cycles : Simple_Type := 0;

   -------------
   -- B0_Send --
   -------------

   procedure B0_Send (Out_Value : out Simple_Type) is
   begin
      Out_Value := B0_Cycles;
      Put_Line ("B0: sending: " & Simple_Type'Image (Out_Value));
      B0_Cycles := B0_Cycles + 1;
   end B0_Send;

   ---------------------
   -- B1_Receive_Send --
   ---------------------

   procedure B1_Receive_Send
     (Out_Value : out Simple_Type; In_Value : Simple_Type) is
   begin
      Out_Value := B1_Cycles;
      Put_Line ("B1: received" & Simple_Type'Image (In_Value)
                  & " sending" & Simple_Type'Image (Out_Value));
      B1_Cycles := B1_Cycles + 1;
   end B1_Receive_Send;

   ----------------
   -- B2_Receive --
   ----------------

   procedure B2_Receive (In_Value : Simple_Type) is
   begin
      Put_Line ("B2: received" & Simple_Type'Image (In_Value));
   end B2_Receive;

end TT;
