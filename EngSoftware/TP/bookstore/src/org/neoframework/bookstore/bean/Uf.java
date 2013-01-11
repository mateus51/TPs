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
@SequenceGenerator(name="sq_uf", sequenceName="sq_uf")
public class Uf {

	protected Integer iduf;
	protected String nome;
	protected Pais pais;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_uf")
	public Integer getIduf() {
		return iduf;
	}
	
	@DescriptionProperty
	public String getNome() {
		return nome;
	}
	
	@JoinColumn(name="idpais")
	@ManyToOne(fetch=FetchType.LAZY)
	public Pais getPais() {
		return pais;
	}
	public void setIduf(Integer iduf) {
		this.iduf = iduf;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public void setPais(Pais pais) {
		this.pais = pais;
	}
	
	
}
