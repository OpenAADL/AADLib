with PolyORB_HI_Generated.Deployment;
with PolyORB_HI_Generated.Types;

package Radar is

   use PolyORB_HI_Generated.Deployment;
   use PolyORB_HI_Generated.Types;

   procedure Analyser
     (From_Receiver : Target_Distance;
      Analyser_Out : out Target_Position_Impl;
      From_Controller : Motor_Position);

   procedure Receiver
     (Receiver_Out : out Target_Distance;
      Receiver_In : Target_Distance);

   procedure Controller
     (Controller_In : Motor_Position;
      Controller_Out : out Motor_Position);

   procedure Transmitter (Entity : Entity_Type);

   procedure Display_Panel (Display_In : Target_Position_Impl);

end Radar;
