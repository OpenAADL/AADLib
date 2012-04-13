with Wall;
package Bricks is
   pragma Elaborate_Body;

   function Finished return Boolean;

   task Move is            -- User moves bricks according to key pressed
      pragma Priority(5);
      entry Start;
      entry Put(X     : in     Wall.Width;
                Y     : in     Wall.Height;
                Brick : in     Wall.Brick_Type;
                Done  :    out Boolean);
      entry Right;
      entry Left;
      entry Rotation;
      entry Drop(Ok : out Boolean);
      entry Stop;
   end Move;

end Bricks;
