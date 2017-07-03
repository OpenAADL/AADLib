with STM32.Board; use STM32.Board;

package body Blink is

   Blink_On : Boolean := True;

   procedure Do_Blink is
   begin
      if Blink_On then
         All_LEDs_On;
      else
         All_LEDs_Off;
      end if;
      Blink_On := not Blink_On;
   end Do_Blink;

end Blink;
