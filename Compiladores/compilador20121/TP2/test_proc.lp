program asdf;
  n, fact : integer;
  
integer PROCEDURE fatorial(value integer:n):
  fact : integer;
begin
  a := 1;
  repeat
    a := a * n;
    n := n - 1
  until n < 2
end
  
  
begin
  read(n);
  fact := fatorial(n);
  write(fact)
end