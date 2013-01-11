function imprimirSelecionarConciliacao(listaClasses, valor, label){
	//alert('valor '+valor+'  label '+label+'    listaclasses '+listaClasses);
	//alert(window.top.opener.selecionarCallback);
	if(window.top.selecionarCallback){
		//document.write("dd");
		var ok = false;
		for(i in listaClasses){
			var clazz = listaClasses[i];
			if(clazz == window.top.selecionarCallback.valueType){
				ok = true;
			}
		}

		if(ok){
			document.write("<a href=\"javascript:selecionarConciliacao('"+valor.replace("\'","\\'")+"','"+label.replace("\'","\\'")+"')\">selecionar</a>&nbsp;");				
		}
	}
}

function selecionarConciliacao(valor, label, forcombo){
	var isNN = navigator.appName.indexOf("Netscape")!= -1;
	
	var winTop; 
	
    if (window.opener) {
		winTop = window.opener;
	} else {
		winTop = top;
	}
    
	if(winTop.selecionarCallback){
		if(forcombo){
		
			var callback = winTop.selecionarCallback;
			var callbackcallback = callback.callback;
			var onchangeFunction = callback.valueInput.onchange;
			//callback.valueInput.value = valor;
			//alert(callback.valueInput.name);
			
			var combo = callback.valueInput;
			var options = combo.options;
			var op = new Option(label, valor, false, true);
			var isNN = navigator.appName.indexOf("Netscape")!= -1;
			if(isNN){
				options.add(op);
			} else {
				callbackcallback(label, valor);
			}
				
			//options[options.length++].text = label;
			
			
			//combo.value = valor;
			
			if(onchangeFunction){
				onchangeFunction();
			}

			if(isNN){
				setTimeout('top.close()', 500);
			} else {
				winTop.close();					
			}					
		} else {
			
			var callback = winTop.selecionarCallback;
			var onchangeFunction = callback.labelInput.onchange;
			callback.valueInput.val(valor);
			callback.labelInput.html(label);

					
			if(onchangeFunction){
				onchangeFunction();
				//alert(onchangeFunction);
			}
			callback.button.hide();
			callback.buttonUnselect.show();
			
			if(isNN){
				setTimeout('top.close()', 500);
			} else {
				winTop.close();					
			}

		}
		
	}

}
		