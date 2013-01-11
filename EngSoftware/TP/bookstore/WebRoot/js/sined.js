/**
*	Construtor da biblioteca.
*
*	@param contexto - Parâmetro utilizado setar o atributo ctx com o contexto da aplicação. 
*/
function SinedUtil(contexto){
	ctx = contexto;
}
var ctx = null;

/**
* Função responsável por remover letras da string.
**/
SinedUtil.prototype.removeCaracteres = function (str){
	str = new String(str);
	var chrPrt = "0";
	var strRet = "";
	var j = 0;
	for (var i = 0; i < str.length; i++) {
		chrPrt = str.substring(i, i + 1);
		if (chrPrt.match(/\d/)) {
			if (j == 0) {
				strRet = chrPrt;
				j = 1;
			} else {
				strRet = strRet.concat(chrPrt);
			}
		}
	}
	return strRet;
}

SinedUtil.prototype.keyUp = function (elem, evento){
	var key = evento.keyCode;
	if(key == 13){
		$("input[value=OK]").click();
	} 
}

SinedUtil.prototype.applyMask = function applyMask(){
	jQuery(function($){
		$("input[mask=registroconselho]").mask("*******/**");
		$("input[mask=nit]").mask("999.99999.99-9");
		$("input[mask=cat]").mask("9999999999-9/99");
		$("input[mask=cep]").mask("99999-999");
		$("input[mask=cpf]").mask("999.999.999-99");
		$("input[mask=cnpj]").mask("99.999.999/9999-99");
		$("input[mask=cei]").mask("99.999.99999/99");
		$("input[mask=date]").mask("99/99/9999",{alertNotCompleted:"Formato da data inválido.",completed:function(){
			if(!$s.validaData(this.val())) {
				this.val("");
				//this.clearCache();
				this.focus();
			}
		}});
		$("input[mask=timestamp]").mask("99/99/9999 99:99",{alertNotCompleted:"Formato de data e hora inválido.",completed:function(){
			if(!$s.validaTimestamp(this.val())) {
				this.val("");
				//this.clearCache();
				this.focus();
			}
		}});

		$("input[mask=mesano]").mask("99/9999",{completed:function(){
			if(!$s.validaDataMesAno(this.val())) {
				this.val("");
				//this.clearCache();
				this.focus();
			}
		}});
		$("input[mask=telefone]").mask("(99)9999-9999");
		$("input[mask=inscricaoestadual]").mask("999999999999-9");
		$("input[mask=placa]").mask("aaa-9999");
		$("input[mask=percentual]").mask("99",{alertNotCompleted:"Formato de porcentagem inválido.",completed:function(){
			alert($s.toFloat(this.val()));
			if($s.toFloat(this.val()) > 100){
				alert("Valor não pode ser maior que 100%.");
				this.val("");
				this.focus();
			}else if($s.toFloat(this.val()) > -100){
				alert("Valor não pode ser menor que -100%.");
				this.val("");
				this.focus();
			}
		}});
	});
}

SinedUtil.prototype.disableMask = function disableMask(){
	jQuery(function($){
		$("input[mask=cep]").unmask();
		$("input[mask=cpf]").unmask();
		$("input[mask=cnpj]").unmask();
		$("input[mask=date]").unmask();
		$("input[mask=mesano]").unmask();
		$("input[mask=telefone]").unmask();
		$("input[mask=timestamp]").unmask();
		$("input[mask=inscricaoestadual]").unmask();
		$("input[mask=placa]").unmask();
		$("input[mask=percentual]").unmask();
	});
}

/**
 * Formata CPF
 */
SinedUtil.prototype.formataCpf = function(cpf){
	return cpf.substring(0,3) + "." + cpf.substring(3,6) + "." + cpf.substring(6,9) + "-" + cpf.substring(9,11);
}

/**
 * Mostra a janela de avisos
 */
SinedUtil.prototype.showNoticeMessage = function (texto,focus){
	$("#Flash-message").html(texto).addClass("flash_notice").removeClass("flash_alert").show();
	if(focus) this.getElement(focus).focus();
}

/**
 * Esconde a janela de avisos
 */
SinedUtil.prototype.hideNoticeMessage = function (){
	$("#Flash-message").html("").hide();
}

/**
 * Mostra a janela de alert
 */
SinedUtil.prototype.showAlertMessage = function (texto,focus){
	$("#Flash-message").html(texto).addClass("flash_alert").removeClass("flash_notice").show();
	if(focus) this.getElement(focus).focus();
}

/**
 * Esconde a janela de alert
 */
SinedUtil.prototype.hideAlertMessage = function (){
	$("#Flash-message").html("").hide();
}

/**
 * Função responsável por verificar os e-mails
 */
SinedUtil.prototype.checkMail = function (mail){	
    var er = new RegExp(/^[A-Za-z0-9_\-\.]+@[A-Za-z0-9_\-\.]{2,}\.[A-Za-z0-9]{2,}(\.[A-Za-z0-9])?/);
    if(typeof(mail) == "string"){
    	if(mail=="") return true;
        if(er.test(mail)){ return true; }
    } else if(typeof(mail) == "object"){
    	if(mail.value=="") return true;
        if(er.test(mail.value)){ return true; }
	}	    
	return false;
}

/**
 * Retorna o primeiro objeto encontrado com o nome informado.
 */
SinedUtil.prototype.getElementByName = function (name){
	return document.getElementsByName(name)[0];
}

/**
 * Retorna o objeto a partir de um id
 */
SinedUtil.prototype.getElement = function (field){
	return document.getElementById(field);
}

/**
 * Retorna o valor do objeto a partir de um id
 */
SinedUtil.prototype.getElementValue = function (field){
	return this.getElement(field).value;
}

/**
 * Retira a seleção de um componete select ao pressionar a tecla DELETE.
 */
SinedUtil.prototype.limpaCombo = function (evento,select){
    tecla = evento.keyCode;
    if(tecla == 0) tecla = evento.charCode;	    
    if (tecla == 46) {
    	select.selectedIndex = null;
    	select.onchange();
    }
}

/**
 * Verifica se a string é um número
 */
SinedUtil.prototype.isNumber = function (numExp){
	if (numExp != ""){
		if (isNaN(numExp) || (numExp.length == 0)){
			return false;
		}  
	} 
	return true;
}

var ca

/**
 * Verifica se a string é composta apenas de letras
 */
SinedUtil.prototype.isString = function (stringExp){
	var re = new RegExp;
	re = /^(([a-zA-ZÀ-ú -])+)$/;
	if (stringExp != ""){
	  var arr = re.exec(stringExp);
	  if (arr == null){
	  	return false; 
	  }
	}
	return true;
}

/**
 * Verifica se a string é composta por números, espaço e hífen
 */
SinedUtil.prototype.isStringNumber = function (stringExp){
	var er = new RegExp(/([^0-9\- ]+)/);
	if (stringExp != ""){
	  if(er.test(stringExp)){ return false; }
	}return true;
}

/**
 * Esconde a mensagem de carregando
 */
SinedUtil.prototype.hideLoading = function(){
	$("#loadmsg").fadeOut();
}

/**
 * Mostra a mensagem de carregando
 */
SinedUtil.prototype.showLoading = function(){
	$("#loadmsg").fadeIn();
}

/**
 * Mostra o help
 */
SinedUtil.prototype.openHelp = function(taghelp){
	var url = 'http://wiki.w3erp.com.br';
	if(taghelp != null && taghelp != ''){
		url += '/wiki/' + taghelp;
	}
	window.open(url, '_blank');
}

/**
 * Obtém o label do valor selecionado no combo
 */
SinedUtil.prototype.getComboLabelSelected = function(combo){
	return combo.options[combo.selectedIndex].text;
}

/**
 * Obtém o id do valor selecionado no combo
 */
SinedUtil.prototype.getComboIdSelected = function(combo){
	var value = combo.options[combo.selectedIndex].value;
	if(value != "<null>")
		return this.getValueId(value); 
	else
		return value;
}

SinedUtil.prototype.getValueId = function(value){
	return value.substring(value.lastIndexOf("=")+1,value.lastIndexOf("]"));
}

SinedUtil.prototype.getValueIdAutocomplete = function(value){
	return value.substring(value.indexOf("=")+1,value.indexOf(","));
}

SinedUtil.prototype.getIdEntidade = function(entidadeString){
	var id = entidadeString.substring(entidadeString.indexOf("=")+1,entidadeString.indexOf(","));
	var idNumber = parseInt(id); 
	
	if(isNaN(idNumber)){
		id = $s.getValueId(entidadeString);
	}
	
	return id;

}

SinedUtil.prototype.convertFromHTML5Date = function (date){
	if(date==null) return "";
	if(typeof date == "object")  date = this.formatDate(date); 
	log( date.indexOf("-") )
	if(date.indexOf("-") != -1){
        var cleanDateArray = date.split('-');
        return cleanDateArray[2] + "/" + cleanDateArray[1] + "/" + cleanDateArray[0];
    }else
    	return date;
}

SinedUtil.prototype.convertToHTML5Date = function (date){
	 if(!$Neo.device.ipad && !$Neo.device.android)
	 	return date;
	 
	 if(date==null) return "";	
	 if(date.indexOf("/") !== -1){
        var cleanDateArray = date.split('/');
        return cleanDateArray[2] + "-" + cleanDateArray[1] + "-" + cleanDateArray[0];
    }else
    	return date;
}

/**
 * Carrega as máscaras
 */
SinedUtil.prototype.loadMask = function(id){
	$s.disableMask();
	$s.applyMask();
}

/**
 * Mostra a mensagem de carregando
 */
SinedUtil.prototype.clearForm = function(name){
	$("form[name="+name+"] input").each(function(){
		var el = $(this);
		var type = el.attr("type");
		if(type == "text"){
			el.val("");
		}
		else if (type == "date"){
			el.val("");
		} else if (type == "radio") {
			el.val('<null>');
		}
	})		
	$("form[name="+name+"] select").each(function(){
		var el = $(this);
		el.selectOptions('<null>');		
	});
}

SinedUtil.prototype.refreshPage = function(name){
	document.location.reload();
}

SinedUtil.prototype.validationCPF = function(cpf){
var i;
s = cpf;
s = s.replace(/\D/g,"");
var c = s.substr(0,9);
var dv = s.substr(9,2);
var d1 = 0; 
for (i = 0; i < 9; i++){
	d1 += c.charAt(i)*(10-i);
}
if (d1 == 0){
 	return false;
}
d1 = 11 - (d1 % 11);
if (d1 > 9) d1 = 0;
if (dv.charAt(0) != d1){
	return false;
}
d1 *= 2;
for (i = 0; i < 9; i++){
	d1 += c.charAt(i)*(11-i);
}
d1 = 11 - (d1 % 11);
if (d1 > 9) d1 = 0;
if (dv.charAt(1) != d1){
	return false;
}
return true;
}

/**
*	Verifica se um CNPJ é válido.
*/
SinedUtil.prototype.validationCNPJ = function(cnpj){
var numeros, digitos, soma, i, resultado, pos, tamanho, digitos_iguais;
digitos_iguais = 1;
if (cnpj.length < 14 && cnpj.length < 15)
      return false;
for (i = 0; i < cnpj.length - 1; i++)
      if (cnpj.charAt(i) != cnpj.charAt(i + 1))
            {
            digitos_iguais = 0;
            break;
            }
if (!digitos_iguais)
      {
      tamanho = cnpj.length - 2
      numeros = cnpj.substring(0,tamanho);
      digitos = cnpj.substring(tamanho);
      soma = 0;
      pos = tamanho - 7;
      for (i = tamanho; i >= 1; i--)
            {
            soma += numeros.charAt(tamanho - i) * pos--;
            if (pos < 2)
                  pos = 9;
            }
      resultado = soma % 11 < 2 ? 0 : 11 - soma % 11;
      if (resultado != digitos.charAt(0))
            return false;
      tamanho = tamanho + 1;
      numeros = cnpj.substring(0,tamanho);
      soma = 0;
      pos = tamanho - 7;
      for (i = tamanho; i >= 1; i--)
            {
            soma += numeros.charAt(tamanho - i) * pos--;
            if (pos < 2)
                  pos = 9;
            }
      resultado = soma % 11 < 2 ? 0 : 11 - soma % 11;
      if (resultado != digitos.charAt(1))
            return false;
      return true;
      }
else
      return false;
} 


var ftap="3298765432";
var total=0;
var i;
var resto=0;
var numPIS=0;
var strResto="";


SinedUtil.prototype.validationPIS=function(pis){

total=0;
resto=0;
numPIS=0;
strResto="";
	
	pisAux = pis.split('.');
	pisStr = "";
	for(i=0; i < pisAux.length; i++){
		pisStr += pisAux[i];
	}
	numPIS=pisStr;
			
	if (numPIS=="" || numPIS==null)
	{
		return false;
	}
	
	for(i=0;i<=9;i++)
	{
		resultado = (numPIS.slice(i,i+1))*(ftap.slice(i,i+1));
		total=total+resultado;
	}
	
	resto = (total % 11)
	
	if (resto != 0)
	{
		resto=11-resto;
	}
	
	if (resto==10 || resto==11)
	{
		strResto=resto+"";
		resto = strResto.slice(1,2);
	}
	
	if (resto!=(numPIS.slice(10,11)))
	{
		return false;
	}
	
	return true;
}

SinedUtil.prototype.validaTimestamp = function (valor){
	
	var data = valor.substring(0,10);
	var espaco = valor.substring(10,11);
	var hora = valor.substring(11,16);
	
	var erro = false;
	
	if (valor!=""){
	    erro=0;
	    hoje = new Date();
	    anoAtual = hoje.getFullYear();
	    barras = valor.split("/");
	    if (barras.length == 3) {
			dia = barras[0];
			mes = barras[1];
			ano = barras[2];
			resultado = (!isNaN(dia) && (dia > 0) && (dia < 32)) && (!isNaN(mes) && (mes > 0) && (mes < 13)) && (!isNaN(ano) && (ano.length == 4) /*&& (ano <= (anoAtual+200) && ano >= 1900)*/ );
	        if (!resultado)	{
	            erro = false;
	        }
	        // Verifica se o dia é válido para o mês de fevereiro.
			if (mes == 2 && (dia < 1 || dia > 29 || (dia > 28 && (parseInt(ano/4) != ano/4)))) {
				erro = false;
			}
	     } else{
	         erro = false;
	     }
		erro = true;
	}
	
	
	
	
	if(erro && verifica_hora(hora) && espaco == " "){
		return true;
	} else {
		alert("Data e hora inválidas.")
		return false;
	}
}

/*
 * Valida se é uma data válida
 */
SinedUtil.prototype.validaData = function (valor){
	if (valor!=""){
	    erro=0;
	    hoje = new Date();
	    anoAtual = hoje.getFullYear();
	    barras = valor.split("/");
	    if (barras.length == 3) {
			dia = barras[0];
			mes = barras[1];
			ano = barras[2];
			resultado = (!isNaN(dia) && (dia > 0) && (dia < 32)) && (!isNaN(mes) && (mes > 0) && (mes < 13)) && (!isNaN(ano) && (ano.length == 4) /*&& (ano <= (anoAtual+200) && ano >= 1900)*/ );
	        if (!resultado)	{
	            alert("Data inválida.");
	            return false;
	        }
	        // Verifica se o dia é válido para o mês de fevereiro.
			if (mes == 2 && (dia < 1 || dia > 29 || (dia > 28 && (parseInt(ano/4) != ano/4)))) {
				alert("Data inválida.");
				return false;
			}
	     } else{
	         alert("Data inválida.");
	         return false;
	     }
		return true;
	}
	
	return false;
}

/*
 * Valida se é uma data (mês/Ano)
 */
SinedUtil.prototype.validaDataMesAno = function (valor){
	if (valor!=""){
	    erro=0;
	    hoje = new Date();
	    anoAtual = hoje.getFullYear();
	    barras = valor.split("/");
	    if (barras.length == 2) {
			mes = barras[0];
			ano = barras[1];
			resultado = (!isNaN(mes) && (mes > 0) && (mes < 13)) && (!isNaN(ano) && (ano.length == 4) /*&& (ano <= (anoAtual+200) && ano >= 1900)*/ );
	        if (!resultado)	{
	            alert("Data inválida.");
	            return false;
	        }
	        /* Verifica se o dia é válido para o mês de fevereiro.
			if (mes == 2 && (dia < 1 || dia > 29 || (dia > 28 && (parseInt(ano/4) != ano/4)))) {
				alert("Data inválida.");
				return false;
			}*/
	     } else{
	         alert("Data inválida.");
	         return false;
	     }
		return true;
	}
	
	return false;
}


/**
*	Método para verificar se uma data é válida.
*	
*	@return true - se a data for válida.
*			false - se for inválida. 
*/
SinedUtil.prototype.verificaData = function (campo){
	var data = campo.value;
	var situacao = '';
	var incomplete = '';

	if (data.length == 0) {
		return true;
	}

	if (data.length != 10) {
		incomplete = 'true';
	}
	else {
		mes = (data.substring(3,5));
	
		// verifica se o mes e valido
		if (mes < 1 || mes > 12 ) {
			situacao = 'falsa';
		}
		else {
			dia = (data.substring(0,2));

			// Verifica se o dia é válido para cada mês, exceto fevereiro.
			if (dia < 1 || dia > 31 || (dia > 30 && (mes == 4 || mes == 6 || mes == 9 || mes == 11))) {
				situacao = 'falsa';
			}
			
			ano = (data.substring(6,10));
			// Verifica se o dia é válido para o mês de fevereiro.
			if (mes == 2 && (dia < 1 || dia > 29 || (dia > 28 && (parseInt(ano/4) != ano/4)))) {
				situacao = 'falsa';
			}
		}
	}

	if(incomplete == 'true' || situacao == 'falsa'){
		setTimeout(function(){campo.focus()},0);
		campo.value = '';
		return false;
	}
	return true;
}

/**
*	Valida periodo de datas.
*	Verifica se a data inicial é menor que a data final.
*/
SinedUtil.prototype.periodoValido = function(datainicio,datafim){
	if( datainicio != "" && datafim != ""){
		if(parseInt( datainicio.split( "/" )[2].toString() + datainicio.split( "/" )[1].toString() + datainicio.split( "/" )[0].toString() ) 
		> parseInt( datafim.split( "/" )[2].toString() + datafim.split( "/" )[1].toString() + datafim.split( "/" )[0].toString() ))
		{
			return false;
		}
	}
	return true;
}

/**
*	Valida periodo de horas.
*	Verifica se a hora inicial é menor que a hora final.
*/
SinedUtil.prototype.periodoHoraValido = function(horainicio,horafim){
	if( horainicio != "" && horafim != ""){
		if(parseInt( horainicio.split( ":" )[0].toString()) > parseInt( horafim.split( ":" )[0].toString() ))
			return false;
		if(parseInt( horainicio.split( ":" )[1].toString()) > parseInt( horafim.split( ":" )[1].toString() ))
			return false
	}
	return true;
}

SinedUtil.prototype.periodoDataHoraValido = function(inicio,fim){
	var inicioArray = inicio.split(' ');
	var fimArray = fim.split(' ');
		
	if(!$s.periodoValidoOuIgual(inicioArray[0], fimArray[0])){
		return false;
	} else if(inicioArray[0] == fimArray[0]){
		if(!$s.periodoHoraValido(inicioArray[1], fimArray[1])){
			return false;
		}
	}
	
	return true;
}


SinedUtil.prototype.periodoValidoOuIgual = function(datainicio,datafim){
	if( datainicio != "" && datafim != ""){
		if(parseInt( datainicio.split( "/" )[2].toString() + datainicio.split( "/" )[1].toString() + datainicio.split( "/" )[0].toString() ) 
		<= parseInt( datafim.split( "/" )[2].toString() + datafim.split( "/" )[1].toString() + datafim.split( "/" )[0].toString() ))
		{
			return true;
		}
	}
	return false;
}

/**
*	Método para obter a tecla pressionada.
*/
SinedUtil.prototype.getTecla = function(event){
	if(navigator.appName.indexOf("Netscape")!= -1) {
		return event.which;
	}
	else {
		return event.keyCode;
	}
}

/**
 * Cria uma requisição ajax retornando json
 */
SinedUtil.prototype.getJSON = function(url,data,callback){
	 $.ajax({
			type: "POST",
			url: url,
			data: data,
			contentType:"application/x-www-form-urlencoded; charset=UTF-8",
			success: function(data){
					data = eval("(" +data + ")");
					callback(data);
				}
		});
}
/**
 * Cria uma requisição ajax retornando json
 */
SinedUtil.prototype.getJSONSync = function(url,data,callback){
	 $.ajax({
			type: "POST",
			url: url,
			data: data,
			async: false,
			contentType:"application/x-www-form-urlencoded; charset=UTF-8",
			success: function(data){
					data = eval("(" +data + ")");
					callback(data);
				}
		});
}


/**
*	Função para converter um array em um combo. 
*	
*	@param lista - Array a ser convertido.
*	@param nameSelect - nome do combo.
*	@param events - possíveis eventos que um combo possa ter.
*
*	@author Flávio Tavares 
*/
SinedUtil.prototype.createDataModelByList = function(lista,nameSelect,events){
	var text = "";
	var i;
	
	if(!lista || lista.length == 0){
		text = "Lista vazia.";
	}
	var combo = "<select name=\""+nameSelect+"\" "+events+" >";		
		combo += "<option value='<null>'>"+text+"</option>";
	if(lista){
		for(i=0;i<lista.length;i++){
			combo+="<option value='"+lista[i][0]+"' >"+lista[i][1]+"</option>";
		}
	}	
	combo += "</select>";
	return combo;
}

SinedUtil.prototype.toFloat = function (valor) {
	if(typeof valor == "string"){
		valor = valor.replace(new RegExp('\\.', 'gi'),"");
		valor = valor.replace(new RegExp(',', 'gi'),".");
		
		//valor = valor.replace(".","","g");
		//valor = valor.replace(",",".","g");
		var floatNum = parseFloat(valor);
		return floatNum;
	}
	if(typeof valor == "object"){
		var floatNum = valor.value;
		return parseFloat(value);
	}
	return parseFloat(valor);
}

SinedUtil.prototype.toMoney = function (valor) {
	valor = valor.toFixed(2);
	valor = new String(valor);
	valor = valor.replace(".", ",");
	return demaskvalue(valor,true).formatCurrency();
}

SinedUtil.prototype.toDecimal = function (valor) {
	valor = new String(valor);
	valor = valor.replace(".", ",");
	return valor;
}

SinedUtil.prototype.getObjectId = function (texto) {
	texto = texto.substring(texto.lastIndexOf("=")+1,texto.indexOf("]"));
	return texto;
}

SinedUtil.prototype.hideLogo = function () {
	$(".logo > *").html("<img src=\"${ctx}/imagens/sys/back_logo.gif\">");
}

/*
 * Função que some ou aparece com os componentes escolhidos  do filtro, deixando como filtro simples ou avançado.
 * Além disso muda o nome do link do filtro e a imagem que segue ao lado do nome. 
 */
SinedUtil.prototype.mudaFiltro = function (load){
	if($('#filterType').val() != 'null'){
		//So muda valor do filtro caso não esteje dando load na tela
		if(load != true){
			if($('#filterType').val() == 'true'){
				$('#filterType').val(false);
			} else{
				$('#filterType').val(true);
			}
		}

		if($('#filterType').val() == 'true'){
			$('#btn_simples_avancado').text('Filtro Avançado');
			$("#btn_simples_avancado").addClass("btn_simples_avancadoDown");
			$("#btn_simples_avancado").removeClass("btn_simples_avancadoUp");
		} else{
			$('#btn_simples_avancado').text('Filtro Simples');
			$("#btn_simples_avancado").addClass("btn_simples_avancadoUp");
			$("#btn_simples_avancado").removeClass("btn_simples_avancadoDown");
		}
		
		if($('#filterType').val() == 'true'){
			 $("td.ADVANCED").each(function(){
		        $(this).hide();
		    });
		} else if($('#filterType').val() == 'false'){
			 $("td.ADVANCED").each(function(){
		        $(this).show();
		    });
		}
	}
}

/**
 * Retorna um array com todos os inputs que terminam com
 * o sufixo informado.
 *
 * @author: Hugo Ferreira
 */
SinedUtil.prototype.getInputsPorSufixo = function (suffix){
	var texts = document.getElementsByTagName("input");
	var i = 0;
	var j = 0;
	var inicio = 0;
	var arr = new Array();
	
	for (i = 0; i < texts.length; i++){
		inicio = texts[i].name.lenght - suffix.lenght;
		if(texts[i].name.indexOf(suffix, inicio) > 0){
			arr[j] = texts[i];
			j++;
		}
	}
	return arr;	
}

/*
*	Limpa o valor de um elemento html.
*/
SinedUtil.prototype.clearObject = function (object){
	var type = object.type;
	// Combo
	if(type == "select-one"){
		object.selectedIndex = null;
    	object.onchange();
	}
	// Texto
	if(type == "text"){
		object.value = "";
	}
}

/*
*	Verifica se uma string está vazia ou nula.
*/
SinedUtil.prototype.isStringBlank = function (str){
	return str == null || str == ""; 
}

/**
 * Retorna o contexto da aplicação
 */
SinedUtil.prototype.getApplicationContext = function(){
	return ctx;
}

SinedUtil.prototype.maskFloat = function(elem, settings, e) {		
	return $(elem).each(function(){
		var input = $(this);			
		$s.formatMask(input, settings, e);
		
	});
}

/* Método que cancela a propagacao de eventos */
SinedUtil.prototype.preventDefault = function(e) {
	if (e.preventDefault) { //standart browsers
		e.preventDefault()

	} else { // internet explorer
		e.returnValue = false
		
	}
}

/* Metodo que verifica qual o evento que foi acionado e qual tecla que foi precionada para aplicar 
 * a máscara de float
 */
SinedUtil.prototype.formatMask = function(input, settings, e) {
	e = e || window.event;
	
	var k = e.charCode || e.keyCode || e.which;
	if(k == 9){
		return;
	}
	if (k == 8) {
		$s.preventDefault(e);
		var x = input.val().substring(0, input.val().length - 1);
		input.val($s.maskValue(x, settings));
		return false;
	}
	
	if((k < 48 || k > 57)){
		$s.preventDefault(e);
		return true;
	}
	
	var key = String.fromCharCode(k);  // Valor para o código da Chave
	$s.preventDefault(e);
	input.val($s.maskValue(input.val() + key, settings));
}

/* Metodo que implementa a formatacao de mascara no campo input */
SinedUtil.prototype.maskValue = function(v, settings) {
	var a = '';
	var strCheck = '0123456789';
	var len = v.length;
	var t = "";
	
	if (len == 0) {
		t = "0,000";
	}
	
	for(var i = 0; i < len; i++)
		if ((v.charAt(i) != '0') && (v.charAt(i) != settings.decimal)) 
			break;

	for(; i < len; i++) {
		if (strCheck.indexOf(v.charAt(i))!= -1) 
			a += v.charAt(i);
	}
	if(a.length == 0) {
		t = "0,00";
	
	} else if (a.length == 1) {
		t = "0,0" + a;
	
	} else if (a.length == 2) {
		t = "0," + a;
	
	} else {
		var part1 = a.substring(0, a.length - 2);
		var part2 = a.substring(a.length - 2);
		t = part1 + "," + part2;
	
	}
	var p, d = (t = t.split(","))[1].substr(0, 2);
	
	if(a.length <= settings.maxNumber) {
		for(p = (t = t[0]).length; (p -= 2) >= 1;) {
			t = t.substr(0, p) + t.substr(p);
		}
		
		var masc = t + settings.decimal + d + Array(2 - d.length).join(0);			
		return masc;
	}
}

/* Metodo que trata a tecla backspace no IE */
SinedUtil.prototype.backspace = function(elem, settings, e) {	
	var  isIE = (document.all) ? true : false;
	
	if(isIE) {
		var input = $(elem);

		e = e || window.event;
		
		var k = e.charCode || e.keyCode || e.which;
		
		if (k == 8) {
			$s.preventDefault(e);
			var x = input.val().substring(0, input.val().length);
			input.val($s.maskValue(x, settings));
			
			return false;
		}

		var key = String.fromCharCode(k);  // Valor para o código da Chave
		input.val($s.maskValue(input.val() + key, settings));
	}		
}	
	
	
/**
 * Obtém a posição do elemento no datagrid pelo seu nome.
 * Leva em consideração que o nome do objeto contém sua posição entre '[]'.
 * Exemplos: 
 * 		Para um campo com o nome: 'listaDataGrid[10].valor' será retornado 10.
 * 		Para um campo com nome: 'valor' será retornado null.
 * 
 * @param obj - Nome ou próprio objeto
 * @return Posição em que se encontra o objeto.
 */
SinedUtil.prototype.getRowIndex = function(obj){
	var name = "";
	if(typeof obj == "string"){
		name = obj;
	}else if(typeof obj == "object"){
		name = obj.name;
	}
	
	var regex = new RegExp("\\[(\\d+)\\]");
	var index = regex.exec(name);
	
	if(index == null)
		return null;
	else 
		return parseInt(index[1]);
}

/*
 * Caso a data 2 seja maior que a data 1, retorna 1;
 * Caso a data 2 seja menor que a data 1, retorna -1;
 * Caso sejam iguais, retorna 0;
 * Caso ou a data 1 ou a data 2 seja vazia, retorna 2;
 */
SinedUtil.prototype.comparaData = function (data1,data2) {	
	if(data1 == "" || data2 == ""){
		return 2;
	}
	
	if(data1 == data2){
		return 0;
	}
	var splitDt2 = data2.split( "/" );
	var splitDt1 = data1.split( "/" );
	if ( parseInt(splitDt2[2].toString() + splitDt2[1].toString() + splitDt2[0].toString() ) 
			> parseInt( splitDt1[2].toString() + splitDt1[1].toString() + splitDt1[0].toString() ) ){
		//maior	
		return 1;
	} else {
		//menor
		return -1;
	}
}

SinedUtil.prototype.roundNumber = function (num, dec) {
	var result = Math.round(num*Math.pow(10,dec))/Math.pow(10,dec);
	return result;
}

SinedUtil.prototype.urlEscape = function (urlValue) {
	var newUrlValue = '';
	for(var i=0; i < urlValue.length; i++){
		switch(urlValue.charAt(i)){
		case ' ':
		newUrlValue += '%20';
		break;
		case '<':
		newUrlValue += '%3C';
		break;
		case '>':
		newUrlValue += '%3E';
		break;
		case '#':
		newUrlValue += '%23';
		break;
		case '%':
		newUrlValue += '%25';
		break;
		case '{':
		newUrlValue += '%7B';
		break;
		case '}':
		newUrlValue += '%7D';
		break;
		case '|':
		newUrlValue += '%7C';
		break;
		case '\\':
		newUrlValue += '%5C';
		break;
		case '^':
		newUrlValue += '%5E';
		break;
		case '~':
		newUrlValue += '%7E';
		break;
		case ']':
		newUrlValue += '%5B';
		break;
		case '[':
		newUrlValue += '%5D';
		break;
		case '`':
		newUrlValue += '%60';
		break;
		case ';':
		newUrlValue += '%3B';
		break;
		case '/':
		newUrlValue += '%2F';
		break;
		case '?':
		newUrlValue += '%3F';
		break;
		case ':':
		newUrlValue += '%3A';
		break;
		case '@':
		newUrlValue += '%40';
		break;
		case '&':
		newUrlValue += '%26';
		break;
		case '$':
		newUrlValue += '%24';
		break;
		default:
		newUrlValue += urlValue[i];
		}
	}
	return newUrlValue;
}


SinedUtil.prototype.lpad = function(n, length){
	var str = '' + n;
    while (str.length < length) {
        str = '0' + str;
    }
    return str;
}

SinedUtil.prototype.formatDate = function(date){
	var dd = date.getDate();
	var mm = date.getMonth()+1;//January is 0!
	var yyyy = date.getFullYear();
	if(dd<10){dd='0'+dd}
	if(mm<10){mm='0'+mm}
	return dd+"/"+mm+"/"+yyyy;
}
//declara a biblioteca
var $s = new SinedUtil();


////////////////////////////////////////////////////////
//Funções auxiliares na chamada do web service de CEP //
////////////////////////////////////////////////////////
SinedUtil.prototype.showLoadingCep = function(){
	$("#loadingmsg").fadeIn();
}
SinedUtil.prototype.hideLoadingCep = function(){
	$("#loadingmsg").fadeOut();
}
function retornaEndereco() {		
	if (form['cep'].value != '') {
		var c = form['cep'].value;		
		callEndereco('sistema', c, false, -1);			  
	}else {
		alert('Valor de CEP inválido.');
	}
}

function retornaEnderecoModulo(modulo) {	
	if (form['cep'].value != '') {
		var c = form['cep'].value;
		callEndereco(modulo, c, false, -1);			  
	}else {
		alert('Valor de CEP inválido.');
	}
}
function retornaEnderecoModuloEstatico(modulo) {	
	if (form['endereco.cep'].value != '') {
		var c = form['endereco.cep'].value;
		callEnderecoEstatico(modulo, c, false, -1);			  
	}else {
		alert('Valor de CEP inválido.');
	}
}

function retornaEnderecoModuloCurriculo(modulo) {	
	if (form['cep'].value != '') {
		var c = form['cep'].value;
		callEnderecoCurriculo(modulo, c, false, -1);			  
	}else {
		alert('Valor de CEP inválido.');
	}
}

function retornaEnderecoModuloLista(modulo, campoCep, indice) {	
	if (campoCep.value != '') {
		var c = campoCep.value;		
		callEndereco(modulo, c, true, indice);			  
	}else {
		alert('Valor de CEP inválido.');
	}
}

function callEndereco(modulo, cep, lista, indice) {
	if (lista){
		$("#loadingmsg"+indice).fadeIn();		
	}else {
		$s.showLoadingCep();		
	}
	$s.showAlertMessage("Buscando endereço...");
	$.post(ctx + "/" + modulo + "/process/Cep",
		{"ACAO" : "verifySendTo",
		 "cep" : cep},
		function (data) {
			callbackCep(data, modulo, lista, indice);
		}
	);
}
function callEnderecoEstatico(modulo, cep, lista, indice) {
	if (lista){
		$("#loadingmsg"+indice).fadeIn();		
	}else {
		$s.showLoadingCep();		
	}
	$s.showAlertMessage("Buscando endereço...");
	$.post(ctx + "/" + modulo + "/process/Cep",
		{"ACAO" : "verifySendTo",
		 "cep" : cep},
		function (data) {
			callbackCepEstatico(data, modulo, lista, indice);
		}
	);
}
function callEnderecoCurriculo(modulo, cep, lista, indice) {
	if (lista){
		$("#loadingmsg"+indice).fadeIn();		
	}else {
		$s.showLoadingCep();		
	}
	$s.showAlertMessage("Buscando endereço...");
	$.post(ctx + "/" + modulo + "/process/Cep",
		{"ACAO" : "verifySendTo",
		 "cep" : cep},
		function (data) {
			callbackCepCurriculo(data, modulo, lista, indice);
		}
	);
}

function retornaEnderecoModuloListaContato(modulo, campoCep, indice) {	
	if (campoCep.value != '') {
		var c = campoCep.value;		
		callEnderecoContato(modulo, c, true, indice);			  
	}else {
		alert('Valor de CEP inválido.');
	}
}

function callEnderecoContato(modulo, cep, lista, indice) {
	if (lista){
		$("#loadingmsg"+indice).fadeIn();		
	}else {
		$s.showLoadingCep();		
	}
	$s.showAlertMessage("Buscando endereço...");
	$.post(modulo + "/process/Cep",
		{"ACAO" : "verifySendTo",
		 "cep" : cep},
		function (data) {
			callbackCepContato(data, modulo, lista, indice);
		}
	);
}
function callbackCepContato(data, modulo, lista, indice){
	eval(data);
			
	var prefixoLista = 'listaEndereco[' + indice + ']';
	
	var logradouroNomeCampo = lista ? prefixoLista + '.logradouro' : 'endereco.logradouro';
	var complementoNomeCampo = lista ? prefixoLista + '.complemento' : 'endereco.complemento';
	var bairroNomeCampo = lista ? prefixoLista + '.bairro' : 'endereco.bairro';
	var ufNomeCampo = lista ? prefixoLista + '.municipio.uf' : 'municipio.uf';
	
	form[logradouroNomeCampo].value  = logradouro;
	form[bairroNomeCampo].value = bairro;
	form[ufNomeCampo].value = cduf;	
	form[complementoNomeCampo].value = complemento;
	if(cduf!='br.com.linkcom.sined.geral.bean.Uf[cduf=]'){
		$.post(modulo + "/process/Cep",
		   {"ACAO" : "verifyUf",
		   "cduf" : cduf,
		   "cdmunicipio": cdmunicipio},
		   function (data) {
		   		callbackMunicipio(data, lista, indice);
		   }
		);
	}/*else{
		$s.hideAlertMessage();
		alert('Uf e Municípios não encontrados.');
	}*/
	
	if (lista){
		$("#loadingmsg"+indice).fadeOut();		
	}else {
		$s.hideLoadingCep();	
	}
	$s.hideAlertMessage();
}

function callbackCep(data, modulo, lista, indice){
	eval(data);
			
	var prefixoLista = 'listaEndereco[' + indice + ']';
	
	var logradouroNomeCampo = lista ? prefixoLista + '.logradouro' : 'endereco.logradouro';
	var complementoNomeCampo = lista ? prefixoLista + '.complemento' : 'endereco.complemento';
	var bairroNomeCampo = lista ? prefixoLista + '.bairro' : 'endereco.bairro';
	var ufNomeCampo = lista ? prefixoLista + '.municipio.uf' : 'municipio.uf';
	
	form[logradouroNomeCampo].value  = logradouro;
	form[bairroNomeCampo].value = bairro;
	form[ufNomeCampo].value = cduf;	
	form[complementoNomeCampo].value = complemento;
	if(cduf!='br.com.linkcom.sined.geral.bean.Uf[cduf=]'){
		$.post(ctx + "/" + modulo + "/process/Cep",
		   {"ACAO" : "verifyUf",
		   "cduf" : cduf,
		   "cdmunicipio": cdmunicipio},
		   function (data) {
		   		callbackMunicipio(data, lista, indice);
		   }
		);
	}/*else{
		$s.hideAlertMessage();
		alert('Uf e Municípios não encontrados.');
	}*/
	
	if (lista){
		$("#loadingmsg"+indice).fadeOut();		
	}else {
		$s.hideLoadingCep();	
	}
	$s.hideAlertMessage();
}
function callbackCepEstatico(data, modulo, lista, indice){
	eval(data);
			
	var prefixoLista = 'listaEndereco[' + indice + ']';
	
	var logradouroNomeCampo = lista ? prefixoLista + '.logradouro' : 'endereco.logradouro';
	var complementoNomeCampo = lista ? prefixoLista + '.complemento' : 'endereco.complemento';
	var bairroNomeCampo = lista ? prefixoLista + '.bairro' : 'endereco.bairro';
	var ufNomeCampo = lista ? prefixoLista + '.municipio.uf' : 'endereco.municipio.uf';
	
	form[logradouroNomeCampo].value  = logradouro;
	form[bairroNomeCampo].value = bairro;
	form[ufNomeCampo].value = cduf;	
	form[complementoNomeCampo].value = complemento;
	if(cduf!='br.com.linkcom.sined.geral.bean.Uf[cduf=]'){
		$.post(ctx + "/" + modulo + "/process/Cep",
		   {"ACAO" : "verifyUf",
		   "cduf" : cduf,
		   "cdmunicipio": cdmunicipio},
		   function (data) {
		   		callbackMunicipioEstatico(data, lista, indice);
		   }
		);
	}/*else{
		$s.hideAlertMessage();
		alert('Uf e Municípios não encontrados.');
	}*/
	
	if (lista){
		$("#loadingmsg"+indice).fadeOut();		
	}else {
		$s.hideLoadingCep();	
	}
	$s.hideAlertMessage();
}
function callbackCepCurriculo(data, modulo, lista, indice){
	eval(data);
			
	var prefixoLista = 'listaEndereco[' + indice + ']';
	
	var logradouroNomeCampo = lista ? prefixoLista + '.logradouro' : 'logradouro';
	var complementoNomeCampo = lista ? prefixoLista + '.complemento' : 'complemento';
	var bairroNomeCampo = lista ? prefixoLista + '.bairro' : 'bairro';
	var ufNomeCampo = lista ? prefixoLista + '.municipio.uf' : 'municipio.uf';
	
	form[logradouroNomeCampo].value  = logradouro;
	form[bairroNomeCampo].value = bairro;
	form[ufNomeCampo].value = cduf;	
	form[complementoNomeCampo].value = complemento;
	if(cduf!='br.com.linkcom.sined.geral.bean.Uf[cduf=]'){
		$.post(ctx + "/" + modulo + "/process/Cep",
		   {"ACAO" : "verifyUf",
		   "cduf" : cduf,
		   "cdmunicipio": cdmunicipio},
		   function (data) {
		   		callbackMunicipioCurriculo(data, lista, indice);
		   }
		);
	}/*else{
		$s.hideAlertMessage();
		alert('Uf e Municípios não encontrados.');
	}*/
	
	if (lista){
		$("#loadingmsg"+indice).fadeOut();		
	}else {
		$s.hideLoadingCep();	
	}
	$s.hideAlertMessage();
}

function callbackMunicipio(data, lista, indice){	
	eval(data);
	var prefixoLista = 'listaEndereco[' + indice + ']';
	var municipioNomeCampo = lista ? prefixoLista + '.municipio' : 'municipio';
	
	document.forms[0][municipioNomeCampo].innerHTML = '';
	for (i = 0; i < mapa.length; i++) {
		document.forms[0][municipioNomeCampo].options[i] = new Option(mapa[i][1],mapa[i][0]);
	}
	form[municipioNomeCampo].value = cdmunicipioSel;
	$s.hideAlertMessage();
	
	if (lista){
		$("#loadingmsg"+indice).fadeOut();		
	}else {
		$s.hideLoadingCep();		
	}	
	$s.hideAlertMessage();
}
function callbackMunicipioEstatico(data, lista, indice){	
	eval(data);
	var prefixoLista = 'listaEndereco[' + indice + ']';
	var municipioNomeCampo = lista ? prefixoLista + '.municipio' : 'endereco.municipio';
	
	document.forms[0][municipioNomeCampo].innerHTML = '';
	for (i = 0; i < mapa.length; i++) {
		document.forms[0][municipioNomeCampo].options[i] = new Option(mapa[i][1],mapa[i][0]);
	}
	form[municipioNomeCampo].value = cdmunicipioSel;
	$s.hideAlertMessage();
	
	if (lista){
		$("#loadingmsg"+indice).fadeOut();		
	}else {
		$s.hideLoadingCep();		
	}	
	$s.hideAlertMessage();
}
function callbackMunicipioCurriculo(data, lista, indice){	
	eval(data);
	var prefixoLista = 'listaEndereco[' + indice + ']';
	var municipioNomeCampo = lista ? prefixoLista + '.municipio' : 'municipio';
	
	document.forms[0][municipioNomeCampo].innerHTML = '';
	for (i = 0; i < mapa.length; i++) {
		document.forms[0][municipioNomeCampo].options[i] = new Option(mapa[i][1],mapa[i][0]);
	}
	form[municipioNomeCampo].value = cdmunicipioSel;
	$s.hideAlertMessage();
	
	if (lista){
		$("#loadingmsg"+indice).fadeOut();		
	}else {
		$s.hideLoadingCep();		
	}	
	$s.hideAlertMessage();
}


function retornaEnderecoModuloColaborador(modulo) {	
	if (form['endereco.cep'].value != '') {
		var c = form['endereco.cep'].value;
		callEnderecoColaborador(modulo, c, false, -1);			  
	}else {
		alert('Valor de CEP inválido.');
	}
}

function callEnderecoColaborador(modulo, cep, lista, indice) {
	if (lista){
		$("#loadingmsg"+indice).fadeIn();		
	}else {
		$s.showLoadingCep();		
	}
	$s.showAlertMessage("Buscando endereço...");
	$.post(ctx + "/" + modulo + "/process/Cep",
		{"ACAO" : "verifySendTo",
		 "cep" : cep},
		function (data) {
			callbackCepColaborador(data, modulo, lista, indice);
		}
	);
}


function callbackCepColaborador(data, modulo, lista, indice){
	eval(data);
			
	var prefixoLista = 'listaEndereco[' + indice + ']';
	
	var logradouroNomeCampo = lista ? prefixoLista + '.logradouro' : 'endereco.logradouro';
	var complementoNomeCampo = lista ? prefixoLista + '.complemento' : 'endereco.complemento';
	var bairroNomeCampo = lista ? prefixoLista + '.bairro' : 'endereco.bairro';
	var ufNomeCampo = lista ? prefixoLista + '.municipio.uf' : 'endereco.municipio.uf';
	
	form[logradouroNomeCampo].value  = logradouro;
	form[bairroNomeCampo].value = bairro;
	form[ufNomeCampo].value = cduf;	
	form[complementoNomeCampo].value = complemento;
	if(cduf!='br.com.linkcom.sined.geral.bean.Uf[cduf=]'){
		$.post(ctx + "/" + modulo + "/process/Cep",
		   {"ACAO" : "verifyUf",
		   "cduf" : cduf,
		   "cdmunicipio": cdmunicipio},
		   function (data) {
		   		callbackMunicipioColaborador(data, lista, indice);
		   }
		);
	}/*else{
		$s.hideAlertMessage();
		alert('Uf e Municípios não encontrados.');
	}*/
	
	if (lista){
		$("#loadingmsg"+indice).fadeOut();		
	}else {
		$s.hideLoadingCep();	
	}
	$s.hideAlertMessage();
}


function callbackMunicipioColaborador(data, lista, indice){	
	eval(data);
	var prefixoLista = 'listaEndereco[' + indice + ']';
	var municipioNomeCampo = lista ? prefixoLista + '.municipio' : 'endereco.municipio';
	
	document.forms[0][municipioNomeCampo].innerHTML = '';
	for (i = 0; i < mapa.length; i++) {
		document.forms[0][municipioNomeCampo].options[i] = new Option(mapa[i][1],mapa[i][0]);
	}
	form[municipioNomeCampo].value = cdmunicipioSel;
	$s.hideAlertMessage();
	
	if (lista){
		$("#loadingmsg"+indice).fadeOut();		
	}else {
		$s.hideLoadingCep();		
	}	
	$s.hideAlertMessage();
}


function retornaEnderecoModuloCandidato(modulo) {	
	if (form['cep'].value != '') {
		var c = form['cep'].value;
		callEnderecoCandidato(modulo, c, false, -1);			  
	}else {
		alert('Valor de CEP inválido.');
	}
}


function callEnderecoCandidato(modulo, cep, lista, indice) {
	if (lista){
		$("#loadingmsg"+indice).fadeIn();		
	}else {
		$s.showLoadingCep();		
	}
	$s.showAlertMessage("Buscando endereço...");
	$.post(ctx + "/" + modulo + "/process/Cep",
		{"ACAO" : "verifySendTo",
		 "cep" : cep},
		function (data) {
			callbackCepCandidato(data, modulo, lista, indice);
		}
	);
}


function callbackCepCandidato(data, modulo, lista, indice){
	eval(data);
			
	var prefixoLista = 'listaEndereco[' + indice + ']';
	
	var logradouroNomeCampo = lista ? prefixoLista + '.logradouro' : 'logradouro';
	var complementoNomeCampo = lista ? prefixoLista + '.complemento' : 'complemento';
	var bairroNomeCampo = lista ? prefixoLista + '.bairro' : 'bairro';
	var ufNomeCampo = lista ? prefixoLista + '.municipio.uf' : 'municipio.uf';
	
	form[logradouroNomeCampo].value  = logradouro;
	form[bairroNomeCampo].value = bairro;
	form[ufNomeCampo].value = cduf;	
	form[complementoNomeCampo].value = complemento;
	if(cduf!='br.com.linkcom.sined.geral.bean.Uf[cduf=]'){
		$.post(ctx + "/" + modulo + "/process/Cep",
		   {"ACAO" : "verifyUf",
		   "cduf" : cduf,
		   "cdmunicipio": cdmunicipio},
		   function (data) {
		   		callbackMunicipioCandidato(data, lista, indice);
		   }
		);
	}/*else{
		$s.hideAlertMessage();
		alert('Uf e Municípios não encontrados.');
	}*/
	
	if (lista){
		$("#loadingmsg"+indice).fadeOut();		
	}else {
		$s.hideLoadingCep();	
	}
	$s.hideAlertMessage();
}


function callbackMunicipioCandidato(data, lista, indice){	
	eval(data);
	var prefixoLista = 'listaEndereco[' + indice + ']';
	var municipioNomeCampo = lista ? prefixoLista + '.municipio' : 'municipio';
	
	document.forms[0][municipioNomeCampo].innerHTML = '';
	for (i = 0; i < mapa.length; i++) {
		document.forms[0][municipioNomeCampo].options[i] = new Option(mapa[i][1],mapa[i][0]);
	}
	form[municipioNomeCampo].value = cdmunicipioSel;
	$s.hideAlertMessage();
	
	if (lista){
		$("#loadingmsg"+indice).fadeOut();		
	}else {
		$s.hideLoadingCep();		
	}	
	$s.hideAlertMessage();
}

function createLIDataModelByList(lista){
	var text = " ";
	var i;
	if(!lista || lista.length == 0){
		text = "";
	}
	var menu = "";
	if(lista){
		for(i=0;i<lista.length;i++){
			menu +="<li><a href='" + lista[i][0]+ "' title=''>" + lista[i][1] + "</a></li>";
		}
	}
	return menu;
}

function ajaxUpdateAtalho(uri) {
	var action = $('#btnAtalho').hasClass('addAtalho') ? 'add' : 'remove';
	var path = uri.replace(ctx,'');
	
	$.post(ctx + "/sistema/process/GerenciaAtalho", {'ACAO':'ajaxAddOrRemoveAtalho', 'action':action, 'path':path}, 
		function(data){
			eval(data);
			var menuAtalho = createLIDataModelByList(listaAtalho);
			$('#idNavigationAtalhoMenu').html(menuAtalho);
			$('#btnAtalho').toggleClass('addAtalho').toggleClass('remAtalho');
			
			if (action == 'add') {
				$('#btnAtalho').html('Remover atalho');
			}
			else if (action == 'remove') {
				$('#btnAtalho').html('Adicionar atalho');
			}
		}		
	);
}

function log(){
	
	var str = "";
	for(var i=0; i<arguments.length;i++)
		str+=arguments[i] + " :: "	
	//console.log(str);
}


////////////////////////////////$Neo///////////////////////////////////////
$Neo = {
	 
	isValidatingSession: false
};

$Neo.device = {
	ipad: (navigator.platform.toLowerCase().indexOf("ipad") != -1),
	iphone: (navigator.platform.toLowerCase().indexOf("iphone") != -1),
	ipod: (navigator.platform.toLowerCase().indexOf("ipod") != -1),
	ios: this.ipad || this.iphone || this.ipod,
	android: (navigator.platform.toLowerCase().indexOf("android") != -1)
};
	