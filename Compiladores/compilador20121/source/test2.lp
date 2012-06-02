program asdf;
  n : integer;
  ret : boolean;
begin
  read(n)
  ret := is_power_of_2(n)
  write(ret)
end

boolean PROCEDURE is_power_of_2(reference integer:v):
  a : integer;
  ret : boolean;
begin
  a := v
  repeat
    a := a / 2
  until a <= 1
  ret := a = 1;
end ret

