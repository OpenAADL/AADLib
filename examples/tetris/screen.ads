package Screen is

  -- simple ANSI terminal emulator
  -- Michael Feldman, The George Washington University
  -- July, 1995

  ScreenHeight : constant Integer := 24;
  ScreenWidth : constant Integer := 80;

  subtype Height is Integer range 1..ScreenHeight;
  subtype Width  is Integer range 1..ScreenWidth;

  type Position is record
    Row   : Height := 1;
    Column: Width := 1;
  end record;

  procedure Beep;

  procedure ClearScreen;

  procedure MoveCursor (To: in Position);

end Screen;
