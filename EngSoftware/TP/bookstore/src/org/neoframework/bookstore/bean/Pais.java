package org.neoframework.bookstore.bean;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.SequenceGenerator;

import br.com.linkcom.neo.bean.annotation.DescriptionProperty;
import br.com.linkcom.neo.bean.annotation.DisplayName;
import br.com.linkcom.neo.validation.annotation.MaxLength;
import br.com.linkcom.neo.validation.annotation.Required;

@Entity
@SequenceGenerator(name = "sq_pais", sequenceName = "sq_pais")
public class Pais {
	
	public static final Pais BRASIL = new Pais(36);
	
	protected Integer idpais;
	protected String nome;
	
	public Pais() {
	}
	
	public Pais(Integer idpais) {
		this.idpais = idpais;
	}
	
	@Id
	@DisplayName("Id")
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_pais")
	public Integer getIdpais() {
		return idpais;
	}
	
	@Required
	@MaxLength(50)
	@DescriptionProperty
	public String getNome() {
		return nome;
	}
	
	public void setIdpais(Integer idpais) {
		this.idpais = idpais;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}

}
