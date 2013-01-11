<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="n" uri="neo"%>
<%@ taglib prefix="t" uri="template"%>

<t:entrada>
		
	
	<t:janelaEntrada >
	
		<t:tabelaEntrada >
		<t:propertyConfig disabled="${ACAO == 'consultar'}">
		<t:property name="idlivro"/>
		<t:property name="titulo"/>
		<t:property name="edicao"/>
		<t:property name="genero" label="Gênero"/>
		
		<t:property name="preco"/>
		<t:property name="lancamento"/>
	
		<t:property name="ebook" type="FILE"/>

			<t:property name="listaPessoa"  />
			<t:property name="listaTipoparticipantelivro" />
			</t:propertyConfig>
		</t:tabelaEntrada>
		
	</t:janelaEntrada>
</t:entrada>