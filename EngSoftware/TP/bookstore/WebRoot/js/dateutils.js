function DateUtil(){}
var $d = new DateUtil();

/**
 * Retorna uma data para base de cálculo com horas.
 * 1 de Janeiro de 1970, 00:00:00,0
 */
DateUtil.prototype.dataBase = function(){
	var date = new Date(1970, 0, 1);
	date.setHours(0);
	date.setMinutes(0);
	date.setSeconds(0);
	date.setMilliseconds(0);
	//alert("base: " + date);
	return date;	
}

/**
* Função responsável calcular a diferença de horas entre duas datas.
* Só deve ser passado como parametro datas somente com valor de hora.
* @return Date
*/
DateUtil.prototype.subtrai = function (date1, date2){
	var time = date2.getTime() - date1.getTime();
	return new Date(time);
}

/**
* Função responsável as horas de duas datas.
* Só deve ser passado como parametro datas somente com valor de hora.
* @return Date
*/
DateUtil.prototype.soma = function (date1, date2){
	var time = date2.getTime() + date1.getTime();
	return new Date(time);
}

/**
 * Converte uma String no formato HH:mm em um date com a hora informada.
 * Exemplo de entrada: "16:30", "09:45", etc..
 * @see #dataBase()
 * @return Date
 */
DateUtil.prototype.parseHour = function(strdate){
	if(typeof strdate != "string"){
		throw "Tipo inválido para o parser.";
	}
	
	var hrsplit = strdate.split(":");
	var date = this.dataBase();
	
	date.setHours(hrsplit[0]);
	date.setMinutes(hrsplit[1]);
	
	return date;
}

Date.prototype.hoursToFloat = function(){
	var h = this.getHours();
	var m = this.getMinutes();
	if(m != 0){
		m /= 60;
	} 
	return h + m; 
}

DateUtil.prototype.hoursFloatToString = function(hoursFloat){
	hoursFloat = "" + hoursFloat;
	var hours = hoursFloat.split(",");
	
	var hora = parseInt(hours[0]);
	if(hora < 10) hora = "0" + hora;
	
	var min = parseFloat(hours[1]) * 6;
	if(min > 100) min /= 10;
	min = parseInt(min);
	if(min < 10) min = "0" + min;
	
	var str = hora + ":" + min;
	return str;
}
