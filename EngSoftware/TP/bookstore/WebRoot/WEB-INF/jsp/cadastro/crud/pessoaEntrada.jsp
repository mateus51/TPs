<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="n" uri="neo"%>
<%@ taglib prefix="t" uri="template"%>

<t:entrada>
		
	
	<t:janelaEntrada >
		<t:tabelaEntrada columns="1">
			<t:property name="idpessoa"/>
			<t:property name="nome"/>
			<t:property name="dtnascimento"/>
			<n:group columns="3" showBorder="false">
			<t:propertyConfig renderAs="doubleline">
				<t:property name="nacionalidade" label="País" />
				<t:property name="uf"/>
				<t:property name="cidade"/>
				</t:propertyConfig>
			</n:group>
			<t:property name="site"/>
			<t:property name="email"/>
			<t:property name="foto" type="file"/>
		
			
		</t:tabelaEntrada>
	</t:janelaEntrada>
</t:entrada>

<script type="text/javascript">
	function oi(){
		alert('oi');
	}
</script>