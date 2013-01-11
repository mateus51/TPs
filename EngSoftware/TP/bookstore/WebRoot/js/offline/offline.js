$.extend({
	postJSON: function(url, data, callback) {
		return jQuery.post(url, data, callback, "json");
	}
});

$.extend({
	grepMap: function(obj, fn){
		var keys = $.grep(Object.keys(obj), fn)
		var map = {}
		for(var i=0; i<keys.length; i++)
			map[keys[i]] = obj[keys[i]]
		return map;
	}
});

$.extend({
    keys:    function(obj){
        var a = [];
        $.each(obj, function(k){ a.push(k) });
        return a;
    }
})
 


$Neo = {
	ctx: contextoAutoComplete, 
	isValidatingSession: false
};

$Neo.device = {
	ipad: (navigator.platform.toLowerCase().indexOf("ipad") != -1),
	iphone: (navigator.platform.toLowerCase().indexOf("iphone") != -1),
	ipod: (navigator.platform.toLowerCase().indexOf("ipod") != -1),
	ios: this.ipad || this.iphone || this.ipod,
	android: (navigator.platform.toLowerCase().indexOf("android") != -1)
};
	$Neo.forms={};
	$Neo.forms.toJSON = function(obj, opts){
		opts = $.extend(opts, { convertFromHTML5Date: false, ignoreLists: false });
		log(opts.convertFromHTML5Date)
	     var form = {};
	     obj.find(':input[name][type!=radio]:enabled, :input[name]:checked, input[name][type="hidden"]').each( function() {
	         var self = $(this);
	         var name = self.attr('name');
	         if(opts.ignoreLists && name.indexOf("].")!=-1)
	         	name = name.substr(name.indexOf("].")+2);
			
         	var val = opts.convertFromHTML5Date ? $s.convertFromHTML5Date(self.val()) : self.val();
	         if (form[name]) {
	            form[name] = form[name] + (val != "" ? (',' + val) : "");
	         }
	         else {
	            form[name] = val;
	         }
	     });
	     //log("form", form)
	     return form;
	}; 
	
	$Neo.forms.collectionToJSON = function(collection){
	     var form = {};
	     collection.each( function() {
	         var self = $(this);
	         var name = self.attr('name');
	         var val = self.val();
			 val = val==null ? "<null>" : val;	        
	         if (form[name]) {
	            form[name] = form[name] + ',' + val;
	         }
	         else {
	            form[name] = val;
	         }
	     });
	     return form;
	}; 
		
	$Neo.forms.sendPost = function sendPost(path, parameters) {
         var form = $('<form></form>');

         form.attr("method", "post");
         form.attr("action", path);
         $.each(parameters, function(key, value) {
	         var field = '<input type="hidden" name="'+key+'" value="'+value+'"></input>';
	
	//         field.attr("type", "hidden");
	  //       field.attr("name", key);
	    //     field.attr("value", value);
	
	         form.append($(field));
         });

         // The form needs to be apart of the document in
         // order for us to be able to submit it.
         $(document.body).append(form);
         form.submit();
         form.remove();
     };

	$Neo.forms.toForm = function(json){
		var keys = $.keys(json);
		for(var i=0; i<keys.length; i++){
			var key = keys[i];
			$("[name=" + key + "]").val(json[key]);
		}
	};

$Neo.util = {
	validateSession: function validateSession(){
		if($Neo.isValidatingSession) return false;
		
		var validate = false;
		$Neo.isValidatingSession = true;
		jQuery.ajax({
	        url:    $Neo.ctx+'/pub/ValidateSession',
	        dataType: "json",
	        success: function(result) {
	         	if(result.valid == false){
	         		validate=false;
	         		var win = $(window);
	         		$.showAkModal( $Neo.ctx+'/pub/ValidateSession?ACAO=login',"Login", 600, 300);
	         	}else{
					validate=true;
				}
	        },
	        async:   false
    	});          
		
		return validate;
	},
	
	closeModalValidateSession: function closeModalValidateSession(){
		$Neo.isValidatingSession = false;
		$.akModalRemove();
	}
};
$Neo.init = function(){
	log("ipad " + $Neo.device.ipad)
	if($Neo.device.ipad){
		 $('head').append('<link rel="stylesheet" href="' + $Neo.ctx + '/css/mobile/ipad.css" type="text/css" />');
	}
}
$Neo.init();	


///offline




var PVOffline = {
	isSync: false,
	isPageModalLogin: false,
	isLoadedResources: false,
	doCache: false, 
	init: function(opts){
		$.extend(PVOffline, opts);
		log("init PVOffline6");
		//init dom
		this.dom.statusBarLeft = $("#offlineStatus .left");
		this.dom.statusBarRight = $("#offlineStatus .right");
		this.dom.statusBar = $("#offlineStatus");
		this.dom.messageBar = $("#offlineMessage");
		this.dom.divCache = $("#divCache");
		
		//atribuindo eventos
		//PVOffline.events.onOrientationChange();
		$(window).bind("online", this.events.onOnline);  
		$(window).bind("offline", this.events.onOffline);
		/*$(window.applicationCache).bind('updateready', this.events.onUpdateReady, false);  
		if(window.applicationCache !=null && window.applicationCache.status !=null  && window.applicationCache.status === window.applicationCache.UPDATEREADY) {  
  			this.events.onUpdateReady();  
		} */ 
		
		
		this.events.onLoad(); 
		
		//verificando se a aplicação está online ou offline 
		if(navigator.onLine) PVOffline.events.onOnline(); 
		else PVOffline.events.onOffline();
		
		//ajustes
		if(document.location.href.indexOf('/offline')!=-1){
			$("#btnAtalho").remove();
			$("#btn_help").remove();
		}
		
 		setTimeout("PVOffline.events.trySync()", 10000)
		
	},
	
	 cache: {
	 	filesDownloaded: 0,
	 	totalFiles: 55,
	 	
	 	getPorcentagem: function(){
	 		return Math.round( PVOffline.cache.filesDownloaded/PVOffline.cache.totalFiles*100);
	 	}
	 },
	//elementos padrões da página
	dom:{
		divCache: null,
		statusBar: null,
		statusBarLeft: null,
		statusBarRight: null,
		messageBar: null
	},
	
	//mensagens
	msg: {
		IS_OFFLINE: "Você está offline.",
		IS_ONLINE: "Você está online",
		PV_NAO_SINCRONIZADO: "Existe(m) {qt} Pedido(s) de Venda para ser(em) sincronizado(s). ",
		PV_SINCRONIZADO: "Não existem Pedidos de Venda para serem sincronizados.",
		LOGIN_NAO_EXISTE: "Só é possível acessar o sistema offline caso você já tenha acessado ele anteriormente. No momento os seguintes usuários podem realizar login: \n\n",
		NAO_EXISTEM_USUARIOS: "Só é possível acessar o sistema offline caso você já tenha acessado ele anteriormente. No momento nenhum usuário ainda acessou o sistema nesse navegador."
	}
};
//pacote de dados Offline da aplicação.
PVOffline.store = {
	getUsuarios: function(){return store.get("usuarios");},
	setUsuarios: function(obj){store.set("usuarios", obj);},
	getUsuarioAtual: function(){ 
		var usuarios = PVOffline.store.getUsuarios(); 
		var loginatual = store.get("loginatual");
		for(var o in usuarios){
			if(usuarios[o].login==loginatual)
				return usuarios[o];
		}
	},
	
	setUsuarioAtual: function(cd){ store.set("loginatual", cd) },
	getListaPedidoVenda: function(){return store.get("pvs");},
	addPedidoVenda: function(pvNovo){
		var d = new Date();
		pvNovo.protocolo = pvNovo.protocolo!=null && pvNovo.protocolo=="" ? PVOffline.util.getProtocolo() : pvNovo.protocolo;
		pvNovo.dataPedidoVenda = $s.lpad(d.getDate()) + "/" + $s.lpad(d.getMonth()+1, 2) + "/" + d.getFullYear() ;
		//add cliente
		var clientes = this.getClientes();
		var keys = $.keys(clientes);
		var listaClienteOffline = {};
		for(var i=0; i<keys.length; i++){
			var key = keys[0];
			var cliente = clientes[key]
			var keysCliente = $.keys(cliente);
			for(var j=0; j<keysCliente.length; j++){//pegar propriedade de clientes e enviar
				var propCliente = keysCliente[j];
				pvNovo['listaClienteOffline['+ i + '].' + propCliente] = cliente[propCliente]; 
			}
		}
		
		var pvs = store.get("pvs") || {};
		pvs[pvNovo.protocolo] = pvNovo;
		//if(pvs.length>0)
		 PVOffline.dom.statusBarRight.html( PVOffline.msg.PV_NAO_SINCRONIZADO.replace("{qt}", $.keys(pvs).length) );
		//else PVOffline.dom.statusBarRight.html( PVOffline.msg.PV_SINCRONIZADO );
		store.set("pvs", pvs)
		alert("Seu pedido de venda foi armazenado com sucesso, com o número de protocolo "+pvNovo.protocolo+". Em breve ele será sincronizado.")
		document.location.href = "/w3erp/offline/crud/Pedidovenda?ACAO=criar";//document.location.href=document.location.href;
	},
	
	addCliente: function(clienteNovo){
		var d = new Date();
		clienteNovo.protocolo = clienteNovo.protocolo || PVOffline.util.getProtocolo();
		
		var clientes = store.get("clientes") || {};
		var cpfcnpj = clienteNovo.cnpj=="" ? clienteNovo.cpf : clienteNovo.cnpj;
		//clienteNovo.cdpessoa = cpfcnpj; 
		var listaEndereco = [];
//		for(var i=0; i<clienteNovo.listaEndereco.length; i++){
//			var end = clienteNovo.listaEndereco[i];
//			end.cdendereco = end.cdendereco==null ? Math.round(Math.random()*10000000) : end.cdendereco
//			listaEndereco.push(end);
//		}
//		clienteNovo.listaEndereco = listaEndereco;
		clientes[cpfcnpj] = clienteNovo;
		store.set("clientes", clientes)
		alert("Cliente salvo com sucesso. Em breve ele será sincronizado.")
		try{parent.$.akModalRemove();}catch(e){}
		
	},
	
	removePedidoVenda: function(pv){
		var listaPedidoVendaOld = PVOffline.store.getListaPedidoVenda();
		var listaPedidoVendaNew = $.grepMap(listaPedidoVendaOld, function(it){ return it != pv.protocolo})
		store.set("pvs",  listaPedidoVendaNew);
		PVOffline.dom.statusBarRight.html( PVOffline.msg.PV_NAO_SINCRONIZADO.replace("{qt}", $.keys(listaPedidoVendaNew).length) );
		//document.location.reload(true);
		//if($.keys(listaPedidoVendaNew).length==0)
			//alert("Todos os pedidos de venda foram sincronizados.");
	},
	
	getClientes: function(){
		return store.get("clientes") || {};
	},
	
	getCdclienteConsultar: function(){
		return store.get("cdclienteconsultar");
	},
	
	setCdclienteConsultar: function(cdclienteconsultar){
		store.set("cdclienteconsultar", cdclienteconsultar);
	}
	
};

PVOffline.util = {};
PVOffline.util = {
	getProtocolo: function(){
		var d = new Date();
		return d.getFullYear() + "" + $s.lpad(d.getMonth()+1, 2) + $s.lpad(d.getDate()) + $s.lpad(d.getHours(), 2) + $s.lpad(d.getMinutes(), 2) + PVOffline.store.getUsuarioAtual().codigo 
		// yyyymmddhhmm + cdusuario com 4 digitos;
	},
	
	getPagina: function(dataSource, page){
		if(dataSource.length<50) return dataSource;
		var arr= new Array();
		
		for(var i=0; i< 50; i++){
			var j = (page-1)*50+i;
			if(j+1==dataSource.length)
				break;
			arr.push(dataSource[j])
		}
		log("arr", arr[0].cdmaterial)
		return arr;
	},
	
	getCdMaterialAtual: function(){ return form.codigo.value;},
	
	findForMaterialGrid: function(query){
		return $.grep(parent.PVOffline.entities.material, function(it){
			return it.cdmaterial.toString().indexOf(query)!=-1 || it.referencia.indexOf(query)!=-1 
			|| it.codigoalternativo.indexOf(query)!=-1 || retirarAcento(it.nome.toUpperCase()).indexOf(query)!=-1
		});
	},
	
	getClientes: function(){
		var descricaoCombo = function(){
			this.logradouro = this.logradouro != null ? this.logradouro : "";
			this.numero = this.numero != null ? this.numero : "";
			this.complemento = this.complemento != null ? this.complemento : "";
			this.bairro = this.bairro != null ? this.bairro : "";
			this.cep = this.cep != null ? this.cep : new Cep("");
			this.pontoreferencia = this.pontoreferencia != null ? this.pontoreferencia : "";
			var municipio = this.municipio;
			log(municipio)		
			var nomemunicipio = $.grep(PVOffline.entities.municipio, function(it){return it.cdmunicipio==municipio})[0]
			log("nmmunicipio", nomemunicipio)
			nomemunicipio = this.municipio != null  && nomemunicipio!=null ? ( ", " +  nomemunicipio.nome ) : "";
			var uf = this.municipio.uf
			var nomeuf = this.municipio != null && this.municipio.uf != null ? ( "/ " +  $.grep(PVOffline.entities.uf, function(it){return it.cduf==uf})[0].sigla ) : "";
			var auxcep = this.cep != null && !this.cep.toString() == "" ? " - " + this.cep : "";
			
			var endereco = this.logradouro;
			if (!this.numero=="")
				endereco += ", " + this.numero;
			if (!this.complemento=="")
				endereco += "/ " + this.complemento;
			if (!this.bairro=="")
				endereco += ", " + this.bairro;
			if (!this.pontoreferencia=="")
				endereco += " (" + this.pontoreferencia + ")";
			endereco += nomemunicipio + nomeuf + auxcep;
					
			return endereco;
		}
		
		var clientes = PVOffline.store.getClientes();
		var clientesArr = new Array();
		if(clientes!=null){
			var keys = $.keys(clientes);
			for(var i=0; i< keys.length; i++){
				var cliente = clientes[ keys[i] ]
				var listaEndereco = new Array();
				var loop=true;
				var j=0;
				while(loop){
					var endereco = {};
					if(cliente['listaEndereco['+j+'].enderecotipo']!=null){
						var mun = cliente['listaEndereco['+j+'].municipio'];
						endereco.cdendereco = cliente['listaEndereco['+j+'].cdendereco'];
						endereco.enderecotipo = cliente['listaEndereco['+j+'].enderecotipo'];
						endereco.cep = cliente['listaEndereco['+j+'].cep'];
						endereco.logradouro = cliente['listaEndereco['+j+'].logradouro'];
						endereco.numero = cliente['listaEndereco['+j+'].numero'];
						endereco.bairro = cliente['listaEndereco['+j+'].bairro'];
						endereco.complemento = cliente['listaEndereco['+j+'].complemento'];
						endereco["municipio.uf"] = cliente['listaEndereco['+j+'].municipio.uf'];
						endereco.municipio = mun
						endereco.caixapostal = cliente['listaEndereco['+j+'].caixapostal'];
						endereco.pais = cliente['listaEndereco['+j+'].pais'];
						endereco.pontoreferencia = cliente['listaEndereco['+j+'].pontoreferencia'];
						endereco.distancia = cliente['listaEndereco['+j+'].distancia'];
						endereco.descricao = descricaoCombo.apply(endereco);
						log("endereco", endereco, endereco.cdendereco)
						listaEndereco.push(endereco)
						j++;
					}else{
						loop=false;
					}
						
				}
				clientesArr.push({cdpessoa: cliente.cdpessoa, nome: cliente.nome, listaEndereco: listaEndereco});
			}
		}
		//return clientesArr
		var cdvendedor = PVOffline.store.getUsuarioAtual().cdpessoa;
		var listaClientes = $.grep(PVOffline.entities.cliente, function(cliente){
			return cliente.listaVendedor.length==0 || $.grep(cliente.listaVendedor, function(vendedor){ return vendedor.cdpessoa==cdvendedor});
		});
		
		return $.merge(listaClientes, clientesArr )
	},
	
	getMaterial: function(cdcliente){
		return $.grep(PVOffline.entities.material, function(material){
			return material.listaEmpresa.length==0 || $.grep(material.listaEmpresa, function(empresa){ return empresa.cdpessoa==cdcliente});
		});
	},
	
	loadClienteEntrada : function (cdcliente){
		log("loadClienteEntrada", "cdcliente", cdcliente)
		var cliente = $.grep(this.getClientes(), function(it){ return it.cdpessoa==cdcliente})[0];
		var keys = $.keys(cliente);
		var indexEnderecoAtual = null;
		for(var i=0; i<keys.length; i++){
			var key = keys[i];
			var value = cliente[key];
			if($.isArray(value)){// é a lista de endereoc
				for(var j=0; j<value.length; j++){
					var endereco = value[j];
					$("#listaEndereco_btnNewline").click();
					var keysEnd = $.keys(endereco);
					for(var k=0; k<keysEnd.length; k++){
						var keyEnd = keysEnd[k];
						
						if(keyEnd!="municipio")
							$(form["listaEndereco["+j+"]."+keyEnd]).val(endereco[keyEnd]);
						if(keyEnd=="municipio.uf")	
							$(form["listaEndereco["+j+"]."+keyEnd]).change()
							
					}
				}
			}else{
				$(form[key]).val(value);
			}
		} 
	},
	
	loadPedidoVendaEntrada : function (){
		//log("loadClienteEntrada", "cdcliente", cdcliente)
		var protocolo = store.get("protocoloEdicaoPedidoVenda");
		if(protocolo!=null){
			store.remove("protocoloEdicaoPedidoVenda");
			//var pv = $.grep(PVOffline.store.getListaPedidoVenda(), function(it){ return it.protocolo==protocolo})[0];
			var pv = PVOffline.store.getListaPedidoVenda()[protocolo] ;
			var keys = $.keys(pv);
			var indexEnderecoAtual = null;
			var countListaPedidovendamaterial = -1;
			var countListaPedidovendapagamento = -1;
			
			$(form['prazopagamento']).val( pv['prazopagamento'] );
			//preenchendo material
			for(var i=0; i<keys.length; i++){
				var key = keys[i];
				var value = pv[key];
				$(form[key]).val(value);
				if(key.indexOf('listaPedidovendamaterial')!=-1){
					var index = parseInt(key.substring(25, 26));
					if(countListaPedidovendamaterial<index){
						countListaPedidovendamaterial++;
						$("[name=codigo]").val(pv["listaPedidovendamaterial["+index+"].material.cdmaterial"]);
						$("[name=unidademedida]").val(pv["listaPedidovendamaterial["+index+"].unidademedida"]);
						PVOffline.util.simulateEnter($("[name=codigo]"));
						//$("[name=material]").val(pv["listaPedidovendamaterial["+index+"].material"]);
						//$("[name=material_label]").val('teste');
						//$("[name=material_value]").val( "br.com.linkcom.sined.geral.bean.Material[cdmaterial=" + pv["listaPedidovendamaterial["+index+"].material.cdmaterial"]+ "]" );
						$("[name=valor]").val(pv["listaPedidovendamaterial["+index+"].preco"]);
						$("[name=quantidades]").val(pv["listaPedidovendamaterial["+index+"].quantidade"]);
						$("[name=dtprazoentrega]").val(pv["listaPedidovendamaterial["+index+"].dtprazoentrega"]);

						$("[name=codigo]").click(); recalculaValores()
						incluirMaterial();
						 
						//setTimeout('$("[name=valor]").val($("[name=valor]").val().replace(".", ",")); $("[name=codigo]").click(); recalculaValores()', 100);
						//setTimeout('incluirMaterial();', 200);
						
						
					}
				}
			}
			verificaBotoes('cliente')
			validaCriarPagamento();
			
			
			
			/*
			
			
			
			
			
			$(form['prazopagamento']).val( pv['prazopagamento'] );
			validaCriarPagamento();
			for(var i=0; i<keys.length; i++){
				
				var key = keys[i];
				var value = pv[key];
				
				if(key.indexOf('listaPedidovendamaterial')!=-1){
					var index = parseInt(key.substring(25, 26));
					if(index!=countListaPedidovendamaterial){
						if(countListaPedidovendamaterial!=-1) incluirMaterial();
						countListaPedidovendamaterial++;
						$("name=[listaPedidovendamaterial["+index+"].codigo]").val(pv["listaPedidovendamaterial["+index+"].codigo"]);
						$("name=[listaPedidovendamaterial["+index+"].material]").val(pv["listaPedidovendamaterial["+index+"].material"]);
						$("name=[listaPedidovendamaterial["+index+"].material_label]").val(pv["listaPedidovendamaterial["+index+"].material_label"]);
						$("name=[listaPedidovendamaterial["+index+"].unidademedida]").val(pv["listaPedidovendamaterial["+index+"].unidademedida"]);
						$("name=[listaPedidovendamaterial["+index+"].valor]").val(pv["listaPedidovendamaterial["+index+"].valor"]);
						$("name=[listaPedidovendamaterial["+index+"].quantidade]").val(pv["listaPedidovendamaterial["+index+"].quantidade"]);
						$("name=[listaPedidovendamaterial["+index+"].prazoentrega]").val(pv["listaPedidovendamaterial["+index+"].prazoentrega"]);
						$(form[key]).val(value);
					}
				//}else if(countListaPedidovendamaterial>-1){
				//	incluirMaterial();
				}else{
					$(form[key]).val(value);
				}
				
				
				/*if($.isArray(value)){// é a lista de endereoc
					for(var j=0; j<value.length; j++){
						var endereco = value[j];
						$("#listaEndereco_btnNewline").click();
						var keysEnd = $.keys(endereco);
						for(var k=0; k<keysEnd.length; k++){
							var keyEnd = keysEnd[k];
							
							if(keyEnd!="municipio")
								$(form["listaEndereco["+j+"]."+keyEnd]).val(endereco[keyEnd]);
							if(keyEnd=="municipio.uf")	
								$(form["listaEndereco["+j+"]."+keyEnd]).change()
								
						}
					}
				}else{*/
					//}
				
			
		} 
	},
	
	
	showInfo: function(msg){
		PVOffline.dom.messageBar.css("background-color", "#333");
		$(".message", PVOffline.dom.messageBar).html(msg);
		PVOffline.dom.messageBar.slideDown()
	},
	
	showError: function(msg){
		PVOffline.dom.messageBar.css("background-color", "red");
		$(".message", PVOffline.dom.messageBar).html(msg);
		PVOffline.dom.messageBar.slideDown()
	},
	
	hideError: function(){
		PVOffline.dom.messageBar.slideUp()
	},
	
	hideInfo: function(){
		PVOffline.dom.messageBar.slideUp()
	},
	
	generateCdTemporario: function(){
		var cod = Math.round(Math.random()*10000000)+""
		while(cod.length<7){cod+="0"}
		return cod;
	},
	
	simulateEnter: function($el){
		e = jQuery.Event("keypress");
		e.which = 13;
		e.keyCode = 13;
		$el.trigger(e);
	}
	
			
};

//Pacote dos eventos da aplicação
PVOffline.events = {};
PVOffline.events = {
	forceCache: false,
	doCache: function(force){
		PVOffline.events.forceCache = force;
		if(force || 
		(PVOffline.doCache && navigator.onLine && document.location.href.indexOf("index")!=-1 && (document.location.href.indexOf("comercialguarani")!=-1 || document.location.href.indexOf("192.168.1.111")!=-1 || document.location.href.indexOf("192.168.2.6")!=-1 || document.location.href.indexOf("distribuidor")!=-1)) ){
			log("Fazendo cache", document.location.href)
			PVOffline.dom.divCache.html("<iframe src=\"/w3erp/offline/process/Cache\" style=\"display: none;\"></iframe>");
			//PVOffline.dom.divCache.html("<iframe src=\"/w3erp/offline/process/Cache?t="+new Date().getTime()+ "\" style=\"display: none;\"></iframe>");
		}
	},
	
	trySync: function(){
		var listaPedidoVenda = PVOffline.store.getListaPedidoVenda();
		if(!PVOffline.isPageModalLogin && navigator.onLine && listaPedidoVenda!=null && $.keys(listaPedidoVenda).length>0){
			this.doSync( PVOffline.store.getListaPedidoVenda() );
		}else setTimeout("PVOffline.events.trySync()", 10000)
	
	},
		
	doSync: function(pvs){
		if(document.location.href.indexOf("/pub/Login")==-1 &&  !$Neo.util.validateSession())
			setTimeout("PVOffline.events.trySync()", 10000)
		
		log("isSync", PVOffline.isSync)
		if(PVOffline.isSync) return;
		else PVOffline.isSync = true;
		log("doSYnc");
		try{
			
			var listaPedidoVenda = PVOffline.store.getListaPedidoVenda();
			log("listaPedidoVenda", listaPedidoVenda)
			if(listaPedidoVenda!=null){
				PVOffline.util.showInfo("Sincronizando pedidos de venda offline...")
	    		log("Sincronizando...")
	    		var keys = $.keys(listaPedidoVenda);
				for(var i=0; i< keys.length; i++){
					var pv = listaPedidoVenda[ keys[i] ];
					log("Sincronizando o Pedido de venda com protocolo="+pv.protocolo);
					PVOffline.util.showInfo("Sincronizando o Pedido de venda com protocolo="+pv.protocolo+"...")
					var error = false
					var success = function(json){
						log("doSync init callback")
						if(json.error) alert(json.msg)
						else {
							PVOffline.store.removePedidoVenda(pv);
							if((keys.length-1)==i) {
								alert("Todos os pedidos de venda foram sincronizados com sucesso.");
								store.remove("clientes")
							}
							log("Sincronização finalizada")
							PVOffline.util.showInfo("Pedido de venda com protocolo="+pv.protocolo + " sincronizado.")
							setTimeout("PVOffline.util.hideInfo()", 5000)
						}
						PVOffline.isSync = false;
					};
					
					var error = function(jqXHR, textStatus, errorThrown){
						error =true;
						PVOffline.isSync=false;
						PVOffline.util.showError("Erro ao sincronizar pedido de venda com protocolo="+pv.protocolo + ". Tentando novamente em 10 segundos.")
						setTimeout("PVOffline.util.hideError()", 5000)
					};
					
					
					
					$.ajax({
						type: 'POST',
						url: $Neo.ctx+"/offline/crud/Pedidovenda",
						data: $.extend(pv, {ACAO: 'salvar'}),
						success: success,
						error: error,
						dataType: 'json',
						async: false
					});
				}
			}
			
		}catch(e){
			log("Erro ao efetuar sincronizacao: " + e, "Linha", e.lineNumber);
			PVOffline.isSync=false;
		}
		
		
	},
	
	
	onOnline: function online(){
		log("Estou online");
		//$("#pedidoVendaOffline").hide("slow");
		var pvs = PVOffline.store.getListaPedidoVenda();
		if( document.location.href.indexOf('/offline')==-1){
			 if(pvs==null || (pvs!=null && $.keys(pvs).length==0))
				PVOffline.dom.statusBar.slideUp();
			else PVOffline.dom.statusBar.slideDown()
		}else PVOffline.dom.statusBar.slideDown()
		/*if(pvs!=null && pvs.length>0 && !PVOffline.isSync){
		//	PVOffline.events.doSync(pvs)
		}else{
			PVOffline.dom.statusBar.slideDown();
		}*/
		PVOffline.dom.statusBarLeft.html(PVOffline.msg.IS_ONLINE)//.slideDown();
		PVOffline.events.doAtualizarMsgSincronizacao()
	},
	
	onOffline: function offline(){
		log("Estou offline");
		//$("#pedidoVendaOffline").show("slow");
		//PVOffline.dom.statusBar.slideDown();
		PVOffline.dom.statusBarLeft.html(PVOffline.msg.IS_OFFLINE)
		PVOffline.events.doAtualizarMsgSincronizacao()
		var pvs = PVOffline.store.getListaPedidoVenda();
		if((pvs!=null && pvs.length>0) ||  document.location.href.indexOf('/offline')!=-1){
			PVOffline.dom.statusBar.slideDown();
		}
	},
	
	onOrientationChange: function onOrientationChange(){
		$(window)    
          .bind('orientationchange', function(){
          	log("ochange"+ window.orientation)
                if(window.orientation==0 || window.orientation==180){
                	$.blockUI.defaults.pageMessage = '<h1>Para Exibir a página corretamente, coloque o tablet na posição horizontal</h1>';
					$.blockUI();
                }else{
                	$(".blockUI").remove();
                }
           })
          .trigger('orientationchange'); 
  
	},
	
	doAtualizarMsgSincronizacao: function(){
		var pvs = PVOffline.store.getListaPedidoVenda();
		if(pvs!=null && $.keys(pvs).length>0) PVOffline.dom.statusBarRight.html( PVOffline.msg.PV_NAO_SINCRONIZADO.replace("{qt}", $.keys(pvs).length) );
		else PVOffline.dom.statusBarRight.html( PVOffline.msg.PV_SINCRONIZADO );
	},
	
	onLoad: function(){
		log("teste", window.location.href)
		this.doCache();
		
		$(window).bind('load', function(e) {
			log("load");
			$(window.applicationCache).bind('updateready', function(e) {
			    if (window.applicationCache.status == window.applicationCache.UPDATEREADY) {
			    	window.applicationCache.swapCache();
			      //if (confirm('Houve mudanças nos arquivos do W3ERP. Deseja recarregar?')) {
			  		document.location.href=document.location.href;  
			      //}
			    } else {
			      // Manifest nao modificado
			    }
	  		}, false);
	
		}, false);
	},//end load
	
	onUpdateReady: function onUpdateReady() {  
		//window.applicationCache.swapCache();
  		document.location.href=document.location.href;  
	}, 

  	logEvent: function logEvent(event) {
    	log("Appcache EVENT " + event.type);
    	if(event.type=="error") log("error: " + event);
    	if(!navigator.onLine && (event.type=="cached" || event.type=="error")) PVOffline.isLoadedResources =true;
    	//if(document.location.href.indexOf("index")!=-1){
	    	
	    	if(event.type=="downloading"){
	    		$.blockUI("<h3>Fazendo download do W3erp offline. Por favor, aguarde...</h3>");
	    	}else if(event.type=="cached"){
	    		$.blockUI("<h3>W3erp offline carregado.</h3>");
	    		PVOffline.cache.filesDownloaded=0;
	    		setTimeout("$.unblockUI()", 2000);
	    	}else if(event.type=="error"){
	    		//$.blockUI({ message: "Erro ao fazer download de dados da tela de pedido venda offline.", css: {"background-color": "red"}});
	    		$.blockUI("<h3>Erro ao fazer download do W3erp offline.</h3>");
	    		PVOffline.cache.filesDownloaded=0;
	    		setTimeout("$.unblockUI()", 3000);
	    	}else if(event.type=="noupdate"){
	    		log("Dados da tela de pedido venda offline já estão atualizados.");
	    		if(PVOffline.events.forceCache){
		    		$.blockUI("<h3>Dados da tela de pedido venda offline já estão atualizados.</h3>");
		    	}
	    		setTimeout("$.unblockUI()", 2000);
	    	}else if(event.type=="progress"){
	    		PVOffline.cache.filesDownloaded++;
	    		$.blockUI("<h3>Fazendo download do W3erp offline. "+PVOffline.cache.getPorcentagem()+ "% concluídos. Por favor, aguarde...</h3>");
	    	}
	    //}
    		
  	},
  	
  	doGravarPedido: function(){
  		if(validateVenda()){
  			var pedidovenda = $Neo.forms.toJSON($("form"), {});
  			PVOffline.store.addPedidoVenda(pedidovenda);
  		}
  	},
  	
  	doSalvarCliente: function(){
  		if(validarFormulario()){
  			$.unblockUI()
  			if( form.cnpj.value!="" || form.cpf.value!="" ){
  				
  				$("[name$=cdendereco]").each(function(){
  					$(this).val(PVOffline.util.generateCdTemporario())
  				}); 
  				
  				var cliente = $Neo.forms.toJSON($("form"), {});
  				var existeEndereco = true; 
  				var i=0;
  				while(existeEndereco){
  					var mun = cliente["listaEndereco["+i+"].municipio"];
  					if(mun!=null){
  						cliente["listaEndereco["+i+ "].municipio"] = "br.com.linkcom.sined.geral.bean.Municipio[cdmunicipio=" + mun + "]";
  						i++;
  					}else{
  						existeEndereco = false;
  						break
  					}
  				}
  				//cliente.cdpessoa = cliente.tipopessoa=="PESSOA_FISICA" ? cliente.cpf : cliente.cnpj;
  				cliente.cdpessoa = cliente.cdpessoa!=null ? cliente.cdpessoa : PVOffline.util.generateCdTemporario();
  				
  				PVOffline.store.addCliente(cliente);
  				opener.location.href=opener.location.href;
  				window.close();
 			}else alert("Preencha o CPF/CNPJ do cliente.")
  		}
  		return false
  	},
  	
  	doLogin: function doLogin(){
  		if(navigator.onLine){
  			//alert('online')
  			return true;
  		}else{
  			var login = $("#login").val();
  			var password = $("#password").val()
  			var usuarios = PVOffline.store.getUsuarios();
  			if(usuarios!=undefined){
 				if(usuarios[login]==null) {
 					var usuariosStr = "";
 					for(var i=0; i<usuarios.length;i++) usuariosStr += usuarios[i].login + "\n"; 
 					alert(PVOffline.msg.LOGIN_NAO_EXISTE + usuariosStr);
 				}
 				else{ 
 					log("hashes", usuarios[login], $.md5(login+password));
 				
	  				if( usuarios[login].hash==$.md5(login+password) ){
	  					log("senha bateu")
	  					document.location.href = "/w3erp/offline/crud/Pedidovenda?ACAO=criar";
	  				}else{
	  					log("senha nao bateu")
	  					alert("Senha incorreta.")
	  				}
  				}
			}else{
				alert(PVOffline.msg.NAO_EXISTEM_USUARIOS);
			}
  		}
  		return false;
  	},
  	
  	forcarAtualizacaoCacheArquivos: function(){
  		var atualizar = confirm("Deseja realmente forçar a atualização do cache dos arquivos do W3ERP offline para todos os usuários?")
  		if(atualizar){
  			$.postJSON($Neo.ctx+"/offline/process/Cache", {ACAO: 'forcarAtualizacaoCache'}, function(json){
  				if(!json.error)
  					alert(json.msg);
  			});
  		}
  	}  
};

//cache
PVOffline.entities = {};
