package org.neoframework.bookstore.bean;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.SequenceGenerator;

import br.com.linkcom.neo.bean.annotation.DescriptionProperty;
import br.com.linkcom.neo.validation.annotation.MaxLength;
import br.com.linkcom.neo.validation.annotation.Required;

@Entity
@SequenceGenerator(name="sq_genero", sequenceName="sq_genero")
public class Genero {

	protected Integer idgenero;
	protected String nome;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_genero")
	public Integer getIdgenero() {
		return idgenero;
	}
	public void setIdgenero(Integer idgenero) {
		this.idgenero = idgenero;
	}
	
	@MaxLength(50)
	@DescriptionProperty
	@Required
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
}
