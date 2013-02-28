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
