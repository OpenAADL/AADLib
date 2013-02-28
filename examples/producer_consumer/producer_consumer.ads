with PolyORB_HI_Generated.Types; use PolyORB_HI_Generated.Types;

package Producer_Consumer is

   procedure Produce_Spg (Data_Source : out Alpha_Type);

   procedure Consume_Spg (Data_Sink   : Alpha_Type);

end Producer_Consumer;
