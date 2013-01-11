<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="n" uri="neo"%>
<%@ taglib prefix="t" uri="template"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
	<head>
		<meta http-equiv="X-UA-Compatible" content="IE=7" />
		
		<link rel="stylesheet" type="text/css" href="${ctx}/flex/history/history.css" />
		
		<link rel="stylesheet" type="text/css" href="${ctx}/resource/js/autocomplete/thickbox.css" />
		<link rel="stylesheet" type="text/css" href="${ctx}/resource/js/autocomplete/jquery.autocomplete.css" />

		<link rel="stylesheet" type="text/css" href="${ctx}/css/app.css" />
		<link rel="stylesheet" type="text/css" href="${ctx}/css/default.css" />
	</head>
	<body onload="autoFieldFocus()" background="${ctx}/imagens/background.png">
	
		<script language="JavaScript">
			var tb_pathToImage = "${ctx}/resource/js/autocomplete/loadingAnimation.gif";
			var contextoAutoComplete = '${ctx}';
		</script>
	
		<script language="JavaScript" src="${ctx}/resource/js/autocomplete/jquery.js"></script>	
		<script language="JavaScript" src="${ctx}/resource/js/autocomplete/jquery.ajaxQueue.js"></script>	
		<script language="JavaScript" src="${ctx}/resource/js/autocomplete/jquery.bgiframe.min.js"></script>	
		<script language="JavaScript" src="${ctx}/resource/js/autocomplete/thickbox-compressed.js"></script>	
		<script language="JavaScript" src="${ctx}/resource/js/autocomplete/jquery.autocomplete.js"></script>	
		<script language="JavaScript" src="${ctx}/resource/js/autocomplete/neo.autocomplete.js"></script>	
		<script type="text/javascript" src="${ctx}/js/tabela.js"></script>
		<script type="text/javascript" src="${ctx}/js/dateutils.js"></script>
		<script type="text/javascript" src="${ctx}/js/jquery.maskedinput-1.1.1.js"></script>
		<script type="text/javascript" src="${ctx}/js/jquery.selectboxes.js"></script>
		<script type="text/javascript" src="${ctx}/js/jquery.serialize.js"></script>
		<script type="text/javascript" src="${ctx}/js/jquery.blockUI.js"></script>
		<script type="text/javascript" src="${ctx}/js/treetable.js"></script>
		<script type="text/javascript" src="${ctx}/js/calendar.js"></script>
		<script type="text/javascript" src="${ctx}/js/dimmer.js"></script>
		<script type="text/javascript" src="${ctx}/js/dimensions.pack.js"></script>
		<script type="text/javascript" src="${ctx}/js/akModal.js"></script>
		<script type="text/javascript" src="${ctx}/js/stringutils.js"></script>
		<script type="text/javascript" src="${ctx}/js/wz_tooltip.js"></script>  
		<script type="text/javascript" src="${ctx}/js/stringutils.js"></script>
		<script type="text/javascript" src="${ctx}/js/contagerencial.js"></script>  
		<script type="text/javascript" src="${ctx}/js/categoria.js"></script>  
		<script type="text/javascript" src="${ctx}/js/tiny_mce/tiny_mce.js"></script>  
		<script type="text/javascript" src="${ctx}/flex/AC_OETags.js"></script>
		<script type="text/javascript" src="${ctx}/flex/history/history.js"></script>
		<script type="text/javascript" src="${ctx}/js/jquery.scrollTo-1.4.2-min.js"></script>
		

		<%-- Bibliotecas para funcionamento dos portlets da página inicial --%>		
		<script type="text/javascript" src="${ctx}/js/portlet/jquery.ui.core.js"></script>
		<script type="text/javascript" src="${ctx}/js/portlet/jquery.ui.widget.js"></script>
		<script type="text/javascript" src="${ctx}/js/portlet/jquery.ui.mouse.js"></script>
		<script type="text/javascript" src="${ctx}/js/portlet/jquery.ui.sortable.js"></script>
		
		<%-- Bibliotecas para funcionamento da ordenação dinâmica das colunas--%>
		<script type="text/javascript" src="${ctx}/js/jquery.dataTables.js"></script>
		<script type="text/javascript" src="${ctx}/js/ColReorder.js"></script>
		<script type="text/javascript" src="${ctx}/js/ColVis.js"></script>
		
		<div align="center">
			<div id="corpo">
				<div class="cabecalho" id="cabecalho" style="display:table;">
					<img src="${ctx}/imagens/logo.png" />
					<div class="containerUsuario">					
						<ul id="navigationUsuario1">
							<li><a href="#">
									Olá, visitante!
								</a>
								<ul class="navigationUsuario2">
									<li>
										<n:link url="" onmouseover="Tip(\"Visualizar carrinho de compras\")">Carrinho de compras</n:link>
									</li>
									<li>
										<n:link url="/logout.jsp" onmouseover="Tip(\"Sair do sistema\")">Sair</n:link>
									</li>
								</ul>
							</li>
						</ul>					
					</div>
				
				</div>	
				<div id="tabs6"  style="width:50px;text-align:center;background: url(${ctx}/imagens/btn1.png)">
					<ul id="navigationUsuario1" >
						
						<li >
						Livros
							<ul class="navigationUsuario2">
								<li>
									<n:link url="/logout.jsp" onmouseover="Tip(\"Sair do sistema\")">Sair</n:link>
								</li>
								<li>
									<n:link url="/logout.jsp" onmouseover="Tip(\"Sair do sistema\")">Sair</n:link>
								</li>
							</ul>
						</li>
						
					</ul>
					
				</div>
				<div id="tabs6" style="width:80px;text-align:center;background: url(${ctx}/imagens/btn2.png)">
					<ul id="navigationUsuario1" >
						
						<li >
						Cadastros
							<ul class="navigationUsuario2">
								<li>
									<n:link url="/logout.jsp" onmouseover="Tip(\"Sair do sistema\")">Sair</n:link>
								</li>
								<li>
									<n:link url="/logout.jsp" onmouseover="Tip(\"Sair do sistema\")">Sair</n:link>
								</li>
							</ul>
						</li>
						
					</ul>
					
				</div>
				<div id="tabs6" style="width:90px;text-align:center;background: url(${ctx}/imagens/btn3.png)">
					<ul id="navigationUsuario1" >
						
						<li >
						Estatísticas
							<ul class="navigationUsuario2">
								<li>
									<n:link url="/logout.jsp" onmouseover="Tip(\"Sair do sistema\")">Sair</n:link>
								</li>
								<li>
									<n:link url="/logout.jsp" onmouseover="Tip(\"Sair do sistema\")">Sair</n:link>
								</li>
							</ul>
						</li>
						
					</ul>
					
				</div>
				<div id="tabs6" style="width:1146px;height:18px;text-align:center;background: url(${ctx}/imagens/btnresto.png)">
					<ul id="navigationUsuario1" >
					</ul>
				</div>
				<div style="width: 100%; ">
				<p style="text-align:center;color:#00ff00;">${execucao!= null ? execucao : "Sem ação"}</p>
				</div>
<!--				<div class="containerUsuario">					-->
<!--					<ul id="navigationUsuario1">-->
<!--						<li><a href="#">-->
<!--								Visitante-->
<!--							</a>-->
<!--							<ul class="navigationUsuario2">-->
<!--								<li>-->
<!--									<a href="#"> Carrinho de compras </a>	-->
<!--								</li>-->
<!--								<li>-->
<!--									<n:link url="/logout.jsp" onmouseover="Tip(\"Sair do sistema\")">Sair</n:link>-->
<!--								</li>-->
<!--							</ul>-->
<!--						</li>-->
<!--					</ul>					-->
<!--				</div>-->
				
				
			</div>
		</div>
	</body>
</html>