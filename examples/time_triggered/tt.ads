with PolyORB_HI_Generated.Types; use PolyORB_HI_Generated.Types;

package TT is

   procedure B0_Send (Out_Value : out Simple_Type);

   procedure B1_Receive_Send (Out_Value : out Simple_Type;
                              In_Value : Simple_Type);

   procedure B2_Receive (In_Value : Simple_Type);

end TT;
