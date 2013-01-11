<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="n" uri="neo"%>
<%@ taglib prefix="t" uri="template"%>

<t:listagem showNewLink="false" >
	<t:janelaFiltro> 
		<t:tabelaFiltro showSubmit="true" columns="1">
		
		<n:group columns="3" showBorder="false">
			<t:propertyConfig renderAs="doubleline">
			<t:property name="titulo" style="width:170px" label="T�tulo"/>
			<t:property name="tipoparticipantelivro" label="Participa��o"/>
			<t:property name="participantelivro" label="Participante"/>
		</t:propertyConfig>
		</n:group>
		<n:group columns="2" showBorder="false">
			Edi��o:<BR/>
			<t:propertyConfig renderAs="single">
			<t:property name="edicaode" label="De"/>
			<t:property name="edicaoate" label="At�"/>
			</t:propertyConfig>
		</n:group>
		<n:group columns="2" showBorder="false" >
			<t:propertyConfig renderAs="doubleline">
				<t:property name="anolancamento"/>
				<t:property name="lancamento" label="Lan�amentos"/>
			</t:propertyConfig>
		</n:group>
		</t:tabelaFiltro>
	</t:janelaFiltro>		
	
	<t:janelaResultados>
		<t:tabelaResultados showExcluirLink="false" showConsultarLink="true" showEditarLink="false">
		 
		<t:property name="idlivro"/>
		<t:property name="titulo"/>
		<t:property name="edicao"/>
		<t:property name="genero.nome" label="G�nero"/>
		<t:property name="preco"/>
		<t:property name="ebook.idarquivo" label="E-book"/>
		<t:property name="lancamento"/>
		</t:tabelaResultados>
	</t:janelaResultados>
</t:listagem>