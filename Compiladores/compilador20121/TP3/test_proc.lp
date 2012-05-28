

























program MyProgram;
a, n, fact : integer;

boolean PROCEDURE fatorial(value integer:n):
  fact : char;
  fa, x : integer;
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