with Text_IO;
with Screen;

package body Bricks is

   Finished_Flag : Boolean := False;

   --------------
   -- Finished --
   --------------

   function Finished return Boolean is
   begin
      return Finished_Flag;
   end Finished;

   Move_X, NX            : Wall.Width;
   Move_Y, NY            : Wall.Height;
   New_Brick, Move_Brick : Wall.Brick_Type;
   Exit_Flag        : Boolean := False;

   ---------
   -- Put --
   ---------

   procedure Put_F (X     : in     Wall.Width;
                    Y     : in     Wall.Height;
                    Brick : in     Wall.Brick_Type;
                    Done  :    out Boolean) is
   begin
      if Wall.Examine(Brick, X, Y) then
         Done := False;
      else
         Done := True;
         Finished_Flag := True;
         Screen.MoveCursor((Column => 10, Row => 12));
         Text_IO.Put_Line ("Try Again [Y/N] ?");
      end if;
      Move_X := X;
      Move_Y := Y;
      Move_Brick := Brick;
   end Put_F;

   ----------------
   -- Move_Right --
   ----------------

   procedure Move_Right is
   begin
      if Move_X < Wall.Width'Last then
         NX := Move_X + 1;
         if Wall.Examine(Move_Brick, NX, Move_Y) then
            Wall.Erase(Move_Brick, Move_X, Move_Y);
            Move_X := NX;
            Wall.Put(Move_Brick, Move_X, Move_Y);
         end if;
      end if;
   end Move_Right;

   ---------------
   -- Move_Left --
   ---------------

   procedure Move_Left is
   begin
      if Wall.Width'First < Move_X then
         NX := Move_X - 1;
         if Wall.Examine(Move_Brick, NX, Move_Y) then
            Wall.Erase(Move_Brick, Move_X, Move_Y);
            Move_X := NX;
            Wall.Put(Move_Brick, Move_X, Move_Y);
         end if;
      end if;
   end Move_Left;

   -----------------
   -- Move_Rotate --
   -----------------

   procedure Move_Rotate is

      ------------
      -- Rotate --
      ------------

      procedure Rotate(Brick     : in     Wall.Brick_Type;
                       New_Brick :    out Wall.Brick_Type) is
         X, Y : Integer;
         B    : Wall.Brick_Type;
      begin
         for I in Brick'range loop
            X := Brick(I).Y + 1;
            Y :=  -(Brick(I).X - 1);
            B(I).X := X;
            B(I).Y := Y;
         end loop;
         New_Brick := B;
      end Rotate;

   begin
      Rotate(Move_Brick, New_Brick);
      if Wall.Examine(New_Brick, Move_X, Move_Y) then
         Wall.Erase(Move_Brick, Move_X, Move_Y);
         Move_Brick := New_Brick;
         Wall.Put(Move_Brick, Move_X, Move_Y);
      end if;
   end Move_Rotate;

   procedure Drop_Brick (Ok: out Boolean) is
   begin
      NY :=  Move_Y + 1;
      if Wall.Examine (Move_Brick, Move_X, NY) then
         Wall.Erase (Move_Brick, Move_X, Move_Y);
         Move_Y := NY;
         Wall.Put (Move_Brick, Move_X, Move_Y);
         Ok := True;
      else
         Wall.Place (Move_Brick, Move_X, Move_Y);
         Ok := False;
         Exit_Flag := True;
      end if;
   end Drop_Brick;

   task body Move is
   begin
      Outer : loop
         accept Start;
         Finished_Flag := False;
     Middle : loop
            Exit_Flag := False;
            accept Put(X     : in     Wall.Width;
                       Y     : in     Wall.Height;
                       Brick : in     Wall.Brick_Type;
                       Done  :    out Boolean) do

               Put_F (X, Y, Brick, Done);
               Wall.Put(Brick, X, Y);
            end Put;
        Inner : loop
                  select
                     accept Right do
                        Move_Right;
                     end Right;
                  or
                     accept Left do
                        Move_Left;
                     end Left;
                  or
                     accept Rotation do
                        Move_Rotate;
                     end Rotation;
                  or
                     accept Drop(Ok : out Boolean) do
                        Drop_Brick (Ok);
                     end Drop;
                  or
                     accept Stop;
                     exit Middle;
                  end select;

                  if Exit_Flag then
                     select
                        accept Drop(Ok : out Boolean) do
                           Ok := FALSE;
                        end Drop;
                     or
                        delay 1.0;
                     end select;
                     exit Inner;
                  end if;
        end loop Inner;
     end loop Middle;
      end loop Outer;
   end Move;

end Bricks;
