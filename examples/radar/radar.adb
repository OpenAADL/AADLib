with PolyORB_HI.Output;

package body Radar is

   use PolyORB_HI.Output;

   type Fake_Position_Index is mod 8;
   --  We use this index to retrieve fake position

   Fake_Positions : constant array (Fake_Position_Index'Range)
     of Target_Position_Impl :=
     ((1, 1), (2, 2), (3, 3), (1, 1), (2, 2), (3, 3), (2, 2), (3, 3));

   Fake_Index : Fake_Position_Index := 0;

   --------------
   -- Receiver --
   --------------

   procedure Receiver
     (Receiver_Out : out Target_Distance;
      Receiver_In : Target_Distance)
   is
      pragma Unreferenced (Receiver_In);
   begin
      Receiver_Out := Fake_Positions (Fake_Index).Rho;
      Put_Line ("Receiver, target is at distance" &
                  Target_Distance'Image (Receiver_Out));
      Fake_Index := Fake_Index + 1;
   end Receiver;

   ----------------
   -- Controller --
   ----------------

   procedure Controller
     (Controller_In : Motor_Position;
      Controller_Out : out Motor_Position)
   is
      pragma Unreferenced (Controller_In);
   begin
      Controller_Out := Fake_Positions (Fake_Index).Theta;
      Put_Line ("Controller, motor is at angular position "
                  & Motor_Position'Image (Controller_Out));
   end Controller;

   --------------
   -- Analyzer --
   --------------

   procedure Analyser
     (From_Receiver : Target_Distance;
      Analyser_Out : out Target_Position_Impl;
      From_Controller : Motor_Position) is
   begin
      Put_Line ("Analyser: target is at distance: "
                  & Target_Distance'Image (From_Receiver)
                  & " at angular position"
                  & Motor_Position'Image (From_Controller));
      Analyser_Out.Rho := From_Receiver;
      Analyser_Out.Theta := From_Controller;
   end Analyser;

   -----------------
   -- Transmitter --
   -----------------

   procedure Transmitter (Entity : Entity_Type) is
      pragma Unreferenced (Entity);
   begin
      Put_Line ("Transmitter");
   end Transmitter;

   -------------------
   -- Display_Panel --
   -------------------

   procedure Display_Panel (Display_In : Target_Position_Impl) is
   begin
      Put_Line ("Display_Panel: target is at ("
                  & Target_Distance'Image (Display_In.Rho) & ","
                  & Motor_Position'Image (Display_In.Theta) & ")");
   end Display_Panel;

end Radar;
