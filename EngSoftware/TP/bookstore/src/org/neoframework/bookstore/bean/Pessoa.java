package org.neoframework.bookstore.bean;

import java.sql.Date;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.SequenceGenerator;

import br.com.linkcom.neo.bean.annotation.DescriptionProperty;
import br.com.linkcom.neo.validation.annotation.MaxLength;
import br.com.linkcom.neo.validation.annotation.Required;

@Entity
@SequenceGenerator(name="sq_pessoa", sequenceName="sq_pessoa")
public class Pessoa {
	protected Integer idpessoa;
	protected String nome;
	protected Date dtnascimento;
	protected Pais nacionalidade;
	protected Uf uf;
	protected Cidade cidade;
	protected String site;
	protected String email;
	protected Arquivo foto;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_pessoa")
	public Integer getIdpessoa() {
		return idpessoa;
	}
	
	@DescriptionProperty
	@MaxLength(100)
	@Required
	public String getNome() {
		return nome;
	}
	
	@Required
	public Date getDtnascimento() {
		return dtnascimento;
	}
	
	@Required
	@JoinColumn(name="idpais")
	@ManyToOne(fetch=FetchType.LAZY)
	public Pais getNacionalidade() {
		return nacionalidade;
	}
	

	@JoinColumn(name="iduf")
	@ManyToOne(fetch=FetchType.LAZY)
	public Uf getUf() {
		return uf;
	}
	

	@JoinColumn(name="idcidade")
	@ManyToOne(fetch=FetchType.LAZY)
	public Cidade getCidade() {
		return cidade;
	}
	
	@MaxLength(100)
	public String getSite() {
		return site;
	}
	
	@MaxLength(100)
	public String getEmail() {
		return email;
	}

	@JoinColumn(name="idarquivo")
	@ManyToOne(fetch=FetchType.LAZY)
	public Arquivo getFoto() {
		return foto;
	}
	public void setIdpessoa(Integer idpessoa) {
		this.idpessoa = idpessoa;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public void setDtnascimento(Date dtnascimento) {
		this.dtnascimento = dtnascimento;
	}
	public void setNacionalidade(Pais nacionalidade) {
		this.nacionalidade = nacionalidade;
	}
	public void setUf(Uf uf) {
		this.uf = uf;
	}
	public void setCidade(Cidade cidade) {
		this.cidade = cidade;
	}
	public void setSite(String site) {
		this.site = site;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	public void setFoto(Arquivo foto) {
		this.foto = foto;
	}

}
