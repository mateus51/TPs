package org.neoframework.bookstore.bean;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.SequenceGenerator;

import br.com.linkcom.neo.validation.annotation.MaxLength;
import br.com.linkcom.neo.validation.annotation.Required;

@Entity
@SequenceGenerator(name="sq_tiponoticia", sequenceName="sq_tiponoticia")
public class Tiponoticia {
	protected Integer idtiponoticia;
	protected String nome;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_tiponoticia")
	public Integer getIdtiponoticia() {
		return idtiponoticia;
	}
	
	@Required
	@MaxLength(50)
	public String getNome() {
		return nome;
	}
	public void setIdtiponoticia(Integer idtiponoticia) {
		this.idtiponoticia = idtiponoticia;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
}
