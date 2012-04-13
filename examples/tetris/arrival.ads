package Arrival is
   pragma Elaborate_Body;

   task Manager is         -- Starts the dropping bricks
      pragma Priority(8);
      entry Tick;
      entry Start;
      entry Stop;
   end Manager;

   task Timer is           -- Timing between events
      pragma Priority(6);
      entry Start;
      entry Stop;
   end Timer;

   task Speeder is         -- Picks up the pace after certain time
      pragma Priority(7);
      entry Start;
      entry Stop;
   end Speeder;

end Arrival;
