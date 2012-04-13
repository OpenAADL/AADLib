with Text_IO;
package body Screen is

  package Int_IO is new Text_IO.Integer_IO (Num => Integer);

  ----------
  -- Beep --
  ----------

  procedure Beep is
  begin
    Text_IO.Put (Item => ASCII.BEL);
  end Beep;

  -----------------
  -- ClearScreen --
  -----------------

  procedure ClearScreen is
  begin
    Text_IO.Put (Item => ASCII.ESC);
    Text_IO.Put (Item => "[2J");
  end ClearScreen;

  ----------------
  -- MoveCursor --
  ----------------

  procedure MoveCursor (To: in Position) is
  begin
    Text_IO.New_Line;
    Text_IO.Put (Item => ASCII.ESC);
    Text_IO.Put ("[");
    Int_IO.Put (Item => To.Row, Width => 1);
    Text_IO.Put (Item => ';');
    Int_IO.Put (Item => To.Column, Width => 1);
    Text_IO.Put (Item => 'f');
  end MoveCursor;

end Screen;
