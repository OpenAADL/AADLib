with PolyORB_HI.Output;

package body Producer_Consumer is

   use PolyORB_HI.Output;

   The_Data : Alpha_Type := 1;

   -----------------
   -- Produce_Spg --
   -----------------

   procedure Produce_Spg (Data_Source : out Alpha_Type) is
   begin
      Data_Source := The_Data;
      The_Data := The_Data + 1;
      Put_Line (Normal, " Produced " & Alpha_Type'Image (Data_Source));
   end Produce_Spg;

   -----------------
   -- Consume_Spg --
   -----------------

   procedure Consume_Spg (Data_Sink : Alpha_Type) is
   begin
      Put_Line (Normal, "Consumed " & Alpha_Type'Image (Data_Sink));
   end Consume_Spg;

end Producer_Consumer;
