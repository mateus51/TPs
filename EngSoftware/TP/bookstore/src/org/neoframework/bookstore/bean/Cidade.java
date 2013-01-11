package org.neoframework.bookstore.bean;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.SequenceGenerator;

import br.com.linkcom.neo.bean.annotation.DescriptionProperty;

@Entity
@SequenceGenerator(name="sq_cidade", sequenceName="sq_cidade")
public class Cidade {
	protected Integer idcidade;
	protected String nome;
	protected Uf uf;
	
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_cidade")
	public Integer getIdcidade() {
		return idcidade;
	}

	@DescriptionProperty
	public String getNome() {
		return nome;
	}
	
	@JoinColumn(name="iduf")
	@ManyToOne(fetch=FetchType.LAZY)
	public Uf getUf() {
		return uf;
	}
	public void setIdcidade(Integer idcidade) {
		this.idcidade = idcidade;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public void setUf(Uf uf) {
		this.uf = uf;
	}
	
	
}
