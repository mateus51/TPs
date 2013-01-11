package org.neoframework.bookstore.bean;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.SequenceGenerator;

import br.com.linkcom.neo.bean.annotation.DisplayName;
import br.com.linkcom.neo.validation.annotation.MaxLength;
import br.com.linkcom.neo.validation.annotation.Required;

@Entity
@SequenceGenerator(name="sq_critica", sequenceName="sq_critica")
public class Critica {
	protected Integer idcritica;
	protected Pessoa critico;
	protected Livro livro;
	protected String texto;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_critica")
	public Integer getIdcritica() {
		return idcritica;
	}
	
	@JoinColumn(name="idpessoa")
	@ManyToOne(fetch=FetchType.LAZY)
	public Pessoa getCritico() {
		return critico;
	}
	
	@JoinColumn(name="idlivro")
	@ManyToOne(fetch=FetchType.LAZY)
	@Required
	public Livro getLivro() {
		return livro;
	}
	
	@Required
	@DisplayName("Crítica")
	@MaxLength(5000)
	public String getTexto() {
		return texto;
	}
	public void setIdcritica(Integer idcritica) {
		this.idcritica = idcritica;
	}
	public void setCritico(Pessoa critico) {
		this.critico = critico;
	}
	public void setLivro(Livro livro) {
		this.livro = livro;
	}
	public void setTexto(String texto) {
		this.texto = texto;
	}
}
