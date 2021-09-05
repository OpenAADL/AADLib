with PolyORB_HI.Output; use PolyORB_HI.Output;

package body Ping is

   Var   : Simple_Type := 0;

   -----------------
   -- Do_Ping_Spg --
   -----------------

   procedure Do_Ping_Spg (Data_Source : out Simple_Type) is
   begin
      if Var > 100 then
         Var := 0;
      end if;

      Var := Var + 1;

      Data_Source := Var;
      Put_Line ("Sending ORDER: ", Simple_Type'Image (Var));
   end Do_Ping_Spg;

end Ping;
