/**
 * Extensões para o jQuery
 */
jQuery.fn.extend({
	
	/**
	 * Habilita o elemento corrente
	 */
	enable: function(){
		return this.each(function(){
			var j = $(this);
			j.removeAttr("disabled");
		});
	},
	
	/**
	 * Desabilita o elemento corrente
	 */
	disable: function(){
		return this.each(function(){
			var j = $(this);
			j.attr("disabled","disabled");
		});
	},
	
	/**
	 * Muda o label do elemento corrente.
	 */
	label: function(label){
		var j = $(this);
		var id = j.attr("id");
		
		$("label[for=" + id + "]").each(function(){
			$(this).html(label);	
		});
	}
});