function DataGridUtil (){
	var selectedIndex = null;
} 

/**
 * Acessa o link que tem a classe activation
 */
DataGridUtil.prototype.editarRegistro = function (obj){
	var acv = $(".activation",obj);
	if(acv.size() > 0)
		window.location = $(".activation",obj).attr("href");
}

/**
 * Colore a linha que está o mouse no DG
 */
DataGridUtil.prototype.coloreLinha = function (tabelaId,elementoSelecionado){
	var tabela = document.getElementById(tabelaId);
	var cellRows = tabela.rows;
	
	for(i = 0; i< cellRows.length ; i++){
		cellRows[i].style.backgroundColor = "";
	}
	
	elementoSelecionado.style.backgroundColor = "#ABD5FB";
	this.selectedIndex = elementoSelecionado.rowIndex;
}

/**
 * Controla o evento de entrada
 */
DataGridUtil.prototype.mouseonOverTabela = function (tabelaId,elementoSelecionado){
	if(elementoSelecionado.rowIndex != this.selectedIndex)
		elementoSelecionado.style.backgroundColor = '#CAE3FA';
}

/**
 * Controla o evento de saída
 */
DataGridUtil.prototype.mouseonOutTabela = function (tabelaId,elementoSelecionado){
	if(elementoSelecionado.rowIndex != this.selectedIndex)
		elementoSelecionado.style.backgroundColor = '';
}

DataGridUtil.prototype.changeCheckState = function(){
	var check = $("#selectAll").attr("checked");
	
	$("#tabelaResultados input[type=checkbox][name=selecteditens]").each(function(){
		if(check) $(this).attr("checked",check);
		else $(this).removeAttr("checked");
	});
}

DataGridUtil.prototype.getSelectedValues = function(){
	var selectedValues = "";
	$("#tabelaResultados input[name=selecteditens]:checked").each(function(){
		selectedValues += $(this).val()+",";
	});
	if(selectedValues != ""){
		selectedValues = selectedValues.substr(0,(selectedValues.length -1));
	}
	return selectedValues;
}

DataGridUtil.prototype.getSelectedValuesName = function(nome){
	var selectedValues = "";
	$("input[name=" + nome + "]:checked").each(function(){
		selectedValues += $(this).val()+",";
	});
	if(selectedValues != ""){
		selectedValues = selectedValues.substr(0,(selectedValues.length -1));
	}
	return selectedValues;
}

DataGridUtil.prototype.validateSelectedValues = function(){
	if(this.getSelectedValues() == ""){
		alert("Nenhum item foi selecionado.");
		return false;
	} else {
		if(confirm("Você deseja excluir os itens selecionados?"))
			return true;
		else
			return false;
	}
}

var $dg = new DataGridUtil();