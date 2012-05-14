#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;


int main( int argc, char *argv[] ){
	string compila = "javac lexer/*.java symbols/*.java inter/*.java parser/*.java teste/*.java";

	system (compila.c_str());
}
