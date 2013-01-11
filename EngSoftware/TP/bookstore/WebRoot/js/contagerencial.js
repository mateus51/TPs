	function reindexContagerencial(id, tableid){
		if($("input[tipo=contagerencial]").length > 0){
			$("input[tipo=contagerencial][name^=" + tableid + "]").each(function(){
				var index = $s.getRowIndex(this.name);
			
				var tags = $(this).parent().contents();
				$(tags).each(function(){
					if(this.nodeName == "SPAN"){
						this.innerHTML = this.innerHTML.replace(index+1,index,"g");
					}
				});
				
				var nome = $(this).attr("name");
				var tipooperacao = $(this).attr("tipooperacao");
				
				$(form[nome + '_label']).unautocomplete();
				applyAutocompleteContaGerencial(nome, tipooperacao);
			});
		}
	}
	
	function escolherContaGerencial(nome, tipooperacao){
		if(document.getElementById('spanSelCG' + nome) != null){
			var display = $(document.getElementById('spanSelCG' + nome)).css('display');
		
			if(display == '' || display == 'block' || display == 'inline'){
	 			popupCG(contextoAutoComplete + '/financeiro/process/ContaGerencialTreeView?propriedade=' + nome + '&tipooperacao=' + tipooperacao, 500, 450);
			} else {
				form[nome].value = '<null>';
				form[nome + '_label'].value = '';
				
				$(document.getElementById('spanSelCG' + nome)).show();
				$(document.getElementById('spanExcCG' + nome)).hide();
				
	 			form[nome].onchange();
	 			$(form[nome + '_label']).removeAttr("readOnly");
	 			applyAutocompleteContaGerencial(nome, tipooperacao);
			}
		}
	}
	
	function applyAutocompleteContaGerencial(nome, tipooperacao){
		if(document.getElementById('spanSelCG' + nome) != null){
			var display = $(document.getElementById('spanSelCG' + nome)).css('display');
			if(display == '' || display == 'block' || display == 'inline'){
				$(form[nome + '_label']).autocomplete(contextoAutoComplete + '/financeiro/process/ContaGerencialAutoComplete?tipooperacao=' + tipooperacao, {
					multiple: false,
					matchContains: true,
					formatItem: formatItem,
					formatResult: formatResult,
					max: 100
				}).result(function(event, data, formatted) {
					$(form[nome + '_label']).val(formatted);
					$(form[nome]).val('br.com.linkcom.sined.geral.bean.Contagerencial[cdcontagerencial=' + data[1] + ']');
					
					$(document.getElementById('spanSelCG' + nome)).hide();
					$(document.getElementById('spanExcCG' + nome)).show();
					
			 		form[nome].onchange();
			 		$(form[nome + '_label']).unautocomplete();
			 		$(form[nome + '_label']).attr("readOnly", "true");	 	
				});	
			} else {
				$(form[nome + '_label']).unautocomplete();
			}
		}
	}
	
	function applyContagerencial(){
		$("input[tipo=contagerencial]").each(function(){
			var nome = $(this).attr("name");
			var tipooperacao = $(this).attr("tipooperacao");
			
			applyAutocompleteContaGerencial(nome, tipooperacao);
			if(form[nome].value == "" || form[nome].value == "<null>"){
				$(form[nome + '_label']).removeAttr("readOnly");
			} else {
				$(form[nome + '_label']).attr("readOnly", "true");
				$(form[nome + '_label']).unautocomplete();
			}
		});
	}
	
	$(document).ready(function(){
		applyContagerencial();
	});