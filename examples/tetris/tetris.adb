with Screen, Bricks, Wall, Arrival, Text_IO;
procedure Tetris is
   pragma Priority(4);

   Ch : Character;
   Available : Boolean;
   Ok : Boolean;

begin
   loop

      Screen.ClearScreen;
      Wall.Initialize;
      Screen.MoveCursor((Column => 10, Row => 3));
      Text_IO.Put_Line( " TETRIS Ada " );
      Screen.MoveCursor((Column => 1, Row => 5));
      Text_IO.Put_Line( "2=drop 4=left 5=spin 6=right");

      Bricks.Move.Start;
      Arrival.Manager.Start;
      Arrival.Timer.Start;
      Arrival.Speeder.Start;

      Outer : loop
         loop
            Text_IO.Get_Immediate(Ch, Available);
            exit when Available;
            delay 0.01;
         end loop;
         exit Outer when Bricks.Finished;
         case Ch is
            when '2' => -- Down arrow
               loop
                  select
                     Bricks.Move.Drop(Ok);
                  else
                     Ok := TRUE; -- Keep dropping the brick
                  end select;
                  exit when not Ok;
               end loop;
               delay 1.0;

            when '4' => -- Left arrow
               select
                  Bricks.Move.Left;
               else
                  null;
               end select;

            when '5' => -- blank
               select
                  Bricks.Move.Rotation;
               else
                  null;
               end select;

            when '6' => -- Right arrow
               select
                  Bricks.Move.Right;
               else
                  null;
               end select;

            when others =>
               null;
         end case;
      end loop Outer;

      Arrival.Speeder.Stop;
      Arrival.Timer.Stop;
      Bricks.Move.Stop;
      Arrival.Manager.Stop;

      exit when Ch /= 'Y' and Ch /= 'y';
   end loop;

   Screen.ClearScreen;
   abort Bricks.Move;
   abort Arrival.Timer;
   abort Arrival.Manager;
   abort Arrival.Speeder;

end Tetris;
