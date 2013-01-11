/*
*	Scripts para funcionamento do detalhe Impostos em Gerar Receita
*/

/**
 * Inicializações
 */
$(document).ready(init);
function init(){
	initNota();
}

var nota;
function initNota(){
	nota = document.getElementsByName("nota")[0].value;
	if(nota == "" || nota == "<null>"){
		throw "O Parâmetro Nota não pode ser nulo. A tela não funcionará corretamente.";
	}		
}

var appContext = null;
function getAppContext(){
	if(appContext == null){
		appContext = $sinedCtx.getApplicationContext();
	}
	return appContext;
}


// Funções para manipulação de modal
var openModal = function(){
	$s.hideAlertMessage();
	var params = "?ACAO=criar" + 
				"&INSELECTONE=true" +
				"&clearBase=true" +
				"&imposto=true" +
				"&showListagemLink=false" +
				"&closeOnCancel=true" +
				"&cdNota=" + $s.getValueId(nota);
	window.open(getAppContext() + '/financeiro/crud/Contapagar' + params,'page','toolbar=no,location=no,status=no,menubar=no,resizable=no,width=1000,height=600');
}
function afterSaveDocumento(cddocumento){
	carregaDocumentoInserido(cddocumento);
	$s.showNoticeMessage("Imposto " + cddocumento + " inserido.");
}

function adicionaNovoDocumento(doc){
	document.getElementById('listaDocumento').dataModel[0] = dataModelOriginal[0].replace("<value>",doc.cddocumento, "g");
	document.getElementById('listaDocumento').dataModel[1] = dataModelOriginal[1].replace("<value>",doc.dtvencimento);
	document.getElementById('listaDocumento').dataModel[2] = dataModelOriginal[2].replace("<value>",doc.outrospagamento);
	document.getElementById('listaDocumento').dataModel[3] = dataModelOriginal[3].replace("<value>",doc.descricao);
	document.getElementById('listaDocumento').dataModel[4] = dataModelOriginal[4].replace("<value>",doc.valor);
	document.getElementById('listaDocumento').dataModel[5] = dataModelOriginal[5].replace("<cddocumento>",doc.cddocumento);
	
	newLinelistaDocumento();
}

//Manipulação das linhas do DataGrid
var dataModelOriginal = [
	"<input type=\"hidden\" id=\"\" name=\"listaDocumento[{index}].cddocumento\" value=\"<value>\"   disabled='disabled' class='disabled'/><span id=\"listaDocumento[{index}].cddocumento\"><value></span>", 
	"<input type=\"text\"      id=\"\"      name=\"listaDocumento[{index}].dtvencimento\"      value=\"<value>\" size=\"11\"disabled='disabled' class='disabled'/> ", 
	"<input type=\"text\" name=\"listaDocumento[{index}].outrospagamento\" value=\"<value>\" disabled='disabled' size='30' class='disabled'/>", 
	"<input type=\"text\" name=\"listaDocumento[{index}].descricao\" value=\"<value>\" disabled='disabled' size='30' class='disabled'/>", 
	"<input type=\"text\" name=\"listaDocumento[{index}].valor\" value=\"<value>\" style='text-align: right; ' disabled='disabled' class='disabled'/>", 
	"<button type=\"button\" class=\"excluirdetalhe\" onmouseover=\"Tip('Remover imposto', CLICKCLOSE, true)\" onclick=\"javascript:confirmDelete($(this).attr('cddocumento'),this.id);\" cddocumento=\"<cddocumento>\" id=\"button.excluir[table_id=listaDocumento, indice={indexplus}]\" ><img src=\""+getAppContext()+"/imagens/excluir_detalhe.gif\" ></button>"
];

function confirmDelete(cddocumento, idLista){
	var conf = confirm("Deseja remover esta conta a pagar?");
	if(conf){
		try{
			deleteDocumento(cddocumento);
			excluirLinhaPorNome(idLista,true);
			reindexFormPorNome(idLista, form, 'listaDocumento', true);
		}catch(e){
			alert(e);
			$s.hideLoading();
		}
	}
}


var documento = null;
function carregaDocumentoInserido(cddocumento){
	$s.showLoading();
	$.post(getAppContext() + "/financeiro/crud/Contapagar",
				{'ACAO':'ajaxCarregaDocumento','cddocumento':cddocumento},
				function (data){
					eval(data);
					$s.hideLoading();
					if(!success){
						throw "Problema no Ajax. O documento não pode ser carregado.";
					}
					adicionaNovoDocumento(doc);
				});
}

function deleteDocumento(cddocumento){
	$s.showLoading();
	$.post(getAppContext() + "/financeiro/crud/Contapagar",
				{'ACAO':'deleteDocumento','cddocumento':cddocumento},
				function (data){
					eval(data);
					$s.hideLoading();
					if(!success){
						throw erro;
					}
				});
}
