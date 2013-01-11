	function reindexCategoria(id, tableid){
		if($("input[tipo=categoria]").length > 0){
			$("input[tipo=categoria][name^=" + tableid + "]").each(function(){
				var index = $s.getRowIndex(this.name);
			
				var tags = $(this).parent().contents();
				$(tags).each(function(){
					if(this.nodeName == "SPAN"){
						this.innerHTML = this.innerHTML.replace(index+1,index,"g");
					}
				});
				
				var nome = $(this).attr("name");
				var tipopessoa = $(this).attr("tipopessoa");
				
				$(form[nome + '_label']).unautocomplete();
				applyAutocompleteCategoria(nome, tipopessoa);
			});
		}
	}
	
	function escolherCategoria(nome, tipopessoa){
		if(document.getElementById('spanSelCategoria' + nome) != null){
			var display = $(document.getElementById('spanSelCategoria' + nome)).css('display');
		
			if(display == '' || display == 'block' || display == 'inline'){
	 			popupCategoria(contextoAutoComplete + '/crm/process/CategoriaTreeView?propriedade=' + nome + '&tipopessoa=' + tipopessoa, 500, 450);
			} else {
				form[nome].value = '<null>';
				form[nome + '_label'].value = '';
				
				$(document.getElementById('spanSelCategoria' + nome)).show();
				$(document.getElementById('spanExcCategoria' + nome)).hide();
				
	 			form[nome].onchange();
	 			$(form[nome + '_label']).removeAttr("readOnly");
	 			applyAutocompleteCategoria(nome, tipopessoa);
			}
		}
	}
	
	function applyAutocompleteCategoria(nome, tipopessoa){
		if(document.getElementById('spanSelCategoria' + nome) != null){
			var display = $(document.getElementById('spanSelCategoria' + nome)).css('display');
			if(display == '' || display == 'block' || display == 'inline'){
				$(form[nome + '_label']).autocomplete(contextoAutoComplete + '/crm/process/CategoriaAutoComplete?tipopessoa=' + tipopessoa, {
					multiple: false,
					matchContains: true,
					formatItem: formatItem,
					formatResult: formatResult,
					max: 100
				}).result(function(event, data, formatted) {
					$(form[nome + '_label']).val(formatted);
					$(form[nome]).val('br.com.linkcom.sined.geral.bean.Categoria[cdcategoria=' + data[1] + ']');
					
					$(document.getElementById('spanSelCategoria' + nome)).hide();
					$(document.getElementById('spanExcCategoria' + nome)).show();
					
			 		form[nome].onchange();
			 		$(form[nome + '_label']).unautocomplete();
			 		$(form[nome + '_label']).attr("readOnly", "true");	 	
				});	
			} else {
				$(form[nome + '_label']).unautocomplete();
			}
		}
	}
	
	function applyCategoria(){
		$("input[tipo=categoria]").each(function(){
			var nome = $(this).attr("name");
			var tipopessoa = $(this).attr("tipopessoa");
			
			applyAutocompleteCategoria(nome, tipopessoa);
			if(form[nome].value == "" || form[nome].value == "<null>"){
				$(form[nome + '_label']).removeAttr("readOnly");
			} else {
				$(form[nome + '_label']).attr("readOnly", "true");
				$(form[nome + '_label']).unautocomplete();
			}
		});
	}

	function popupCategoria(url,width,height){
		$.showAkModal(url,'Categoria',width,height);
	}
					
	$(document).ready(function(){
		applyCategoria();
	});