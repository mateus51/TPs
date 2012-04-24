COMPILER = g++
OPTIONS = -c -Wall -Wextra -g

all: tiny

tiny: Call.o Proc.o Command.o WriteStr.o Writeln.o Variable.o Context.o VarAssignment.o WriteVar.o Read.o Expression.o IfThenElse.o While.o For.o StringUtils.o Parser.o Program.o main.o
	$(COMPILER) Program.o Command.o main.o WriteStr.o Writeln.o Variable.o Context.o VarAssignment.o WriteVar.o Read.o Expression.o IfThenElse.o While.o For.o Proc.o Call.o StringUtils.o Parser.o -o tiny

main.o: main.cpp
	$(COMPILER) $(OPTIONS) main.cpp

Context.o: Context.cpp
	$(COMPILER) $(OPTIONS) Context.cpp

Variable.o: Variable.cpp
	$(COMPILER) $(OPTIONS) Variable.cpp

Program.o: Program.cpp
	$(COMPILER) $(OPTIONS) Program.cpp

Command.o: Command.cpp
	$(COMPILER) $(OPTIONS) Command.cpp

WriteStr.o: WriteStr.cpp
	$(COMPILER) $(OPTIONS) WriteStr.cpp

WriteVar.o: WriteVar.cpp
	$(COMPILER) $(OPTIONS) WriteVar.cpp

Writeln.o: Writeln.cpp
	$(COMPILER) $(OPTIONS) Writeln.cpp

VarAssignment.o: VarAssignment.cpp
	$(COMPILER) $(OPTIONS) VarAssignment.cpp

Read.o: Read.cpp
	$(COMPILER) $(OPTIONS) Read.cpp

Expression.o: Expression.cpp
	$(COMPILER) $(OPTIONS) Expression.cpp

IfThenElse.o: IfThenElse.cpp
	$(COMPILER) $(OPTIONS) IfThenElse.cpp
	
While.o: While.cpp
	$(COMPILER) $(OPTIONS) While.cpp
	
For.o: For.cpp
	$(COMPILER) $(OPTIONS) For.cpp

Proc.o: Proc.cpp
	$(COMPILER) $(OPTIONS) Proc.cpp

Call.o: Call.cpp
	$(COMPILER) $(OPTIONS) Call.cpp

StringUtils.o: StringUtils.cpp
	$(COMPILER) $(OPTIONS) StringUtils.cpp

Parser.o: Parser.cpp
	$(COMPILER) $(OPTIONS) Parser.cpp

clean:
	rm -f *.o tiny
