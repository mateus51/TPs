function redirecionaTela(tipo, id){
	switch(tipo)
	{
	case 1:
		redirecionaSolicitacaocompra(id);
		break;
	case 2:
		redirecionaCotacao(id);
		break;
	case 3:
		redirecionaOrdemcompra(id);
		break;
	case 4:
		redirecionaEntrega(id);
		break;
	case 5:
		redirecionaRomaneio(id);
		break;
	case 6:
		redirecionaAgendamento(id);
		break;
	case 7:
		redirecionaContapagar(id);
		break
	case 8:
		redirecionaPlanejamento(id);
		break
	}
}

var appContext = null;
function getAppContext(){
	if(appContext == null){
		appContext = $sinedCtx.getApplicationContext();
	}
	return appContext;
}

function redirecionaSolicitacaocompra(id){
	window.location = getAppContext() + '/suprimento/crud/Solicitacaocompra?ACAO=consultar&cdsolicitacaocompra=' + id;
}

function redirecionaCotacao(id){
	window.location = getAppContext() + '/suprimento/crud/Cotacao?ACAO=consultar&cdcotacao=' + id;
}

function redirecionaOrdemcompra(id){
	window.location = getAppContext() + '/suprimento/crud/Ordemcompra?ACAO=consultar&cdordemcompra=' + id;
}

function redirecionaEntrega(id){
	window.location = getAppContext() + '/suprimento/crud/Entrega?ACAO=consultar&cdentrega=' + id;
}

function redirecionaRomaneio(id){
	window.location = getAppContext() + '/suprimento/crud/Romaneio?ACAO=consultar&cdromaneio=' + id;
}

function redirecionaAgendamento(id){
	window.location = getAppContext() + '/financeiro/crud/Agendamento?ACAO=consultar&cdagendamento=' + id;
}

function redirecionaContapagar(id){
	window.location = getAppContext() + '/financeiro/crud/Contapagar?ACAO=consultar&cddocumento=' + id;
}

function redirecionaPlanejamento(id){
	window.location = getAppContext() + '/projeto/crud/Planejamento?ACAO=consultar&cdplanejamento=' + id;
}

function redirecionaAlterarSenha(){
	window.location = getAppContext() + '/sistema/process/alterasenhausuario';
}