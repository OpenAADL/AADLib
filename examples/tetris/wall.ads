package Wall is

   subtype Styles is INTEGER range 1..7;

   type Brick_Section is
      record
         Y, X : Integer;
      end record;

   type Brick_Type is array(1 .. 4) of Brick_Section;

   function Pick ( Style : in Styles ) return Brick_Type;

   subtype Width is Integer range 0 .. 11;
   subtype Height is Integer range 1 .. 21;

   procedure Initialize;

   procedure Put(Brick : in Brick_Type;
                 X     : in Width;
                 Y     : in Height);

   procedure Erase(Brick : in Brick_Type;
                   X     : in Width;
                   Y     : in Height);

   procedure Place(Brick : in Brick_Type;
                   X     : in Width;
                   Y     : in Height);

   function Examine(Brick : in Brick_Type;
                    X     : in Width;
                    Y     : in Height) return Boolean;

   procedure Erase_Lines;

end Wall;
