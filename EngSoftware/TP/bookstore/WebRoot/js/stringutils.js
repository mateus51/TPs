/*
*	Verifica se uma String termina com determinado sufixo
*	@author Flávio Tavares	
*/
String.prototype.endsWith = function(sufixo){
	var length = this.length;
	var end = this.substring(length-sufixo.length,length);
	return sufixo == end;
}

String.prototype.trim = function(){
	return this.replace(/^\s+|\s+$/g,"");
}

String.prototype.isEmpty = function(){
	return "" == this;
}

String.prototype.isNotEmpty = function(){
	return "" != this;
}