<%@ page import="org.neoframework.bookstore.bean.Livrovenda" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="n" uri="neo"%>
<%@ taglib prefix="t" uri="template"%>


<t:tela titulo="Mais vendidos">
	<n:bean name="lista" valueType="<%=Livrovenda.class%>">
	<t:detalhe name="livrovendatrans" showBotaoNovaLinha="false" showBotaoRemover="false" showColunaAcao="false">
		<n:column header="Rank">${index}</n:column>
		<t:property name="livro.idlivro" type="hidden" write="true"/>
		<t:property name="livro.titulo" type="hidden" write="true"/>
		<t:property name="livro.edicao" type="hidden" write="true"/>
		<t:property name="livro.preco" type="hidden" write="true"/>
		
	</t:detalhe>
	</n:bean>
</t:tela>