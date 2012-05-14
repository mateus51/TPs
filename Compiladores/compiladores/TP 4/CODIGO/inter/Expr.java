package inter;                 // Arquivo Expr.java
import lexer.*; 
import symbols.*;

public class Expr extends Node {
	public Token op;
	public Type type;
	Expr(Token tok, Type p) { op = tok; type = p; }
	public Expr gen() { return this; }
	public Expr reduce() { return this; }
	public void jumping(int t, int f) { emitjumps(toString(), t, f); }
	public void emitjumps(String test, int t, int f) {
		if( t != 0 && f != 0 ) {
			emit("if " + test + " goto L" + t);
			emit("goto L" + f);
		}
		else if( t != 0 ) emit("if " + test + " goto L" + t);
		else if( f != 0 ) emit("iffalse " + test + " goto L" + f);
		else ;// nada, porque ambos t e f fall through 
		
	}
	public String toString() { 
		return op.toString(); 
	}
}


/*
 * 
 * O m ́todo jumping (linhas 10-15, arquivo Rel.java) come ̧a gerando c ́digo para as subex-
                                                          c          o
    e
press ̃es expr1 e expr2 (linhas 11-22). Depois, ele chama o m ́todo emitjumps definido nas
     o                                                      e
linhas 10-18, arquivo Expr.java, na Se ̧ ̃o ?? Se nem t nem f for o r ́tulo especial 0, ent ̃o
                                       ca                          o                    a
emitjumps executa o seguinte
12)             emit("if " + test + " goto L" + t);                 // Arquivo Expr.java
13)             emit("goto L" + f);
No m ́ximo uma instru ̧ ̃o  ́ gerada se t ou f  ́ o r ́tulo especial 0 (novamente, do arquivo
      a                ca e                    e    o
Expr.java):
15)         else if( t != 0 ) emit("if " + test + " goto L" + t);
16)         else if( f != 0 ) emit("iffalse " + test + " goto L" + f);
17)         else ; // nada, porque ambos t e f fall through

 * 
 * */
