package org.neoframework.bookstore.bean;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.SequenceGenerator;

import br.com.linkcom.neo.validation.annotation.MaxLength;
import br.com.linkcom.neo.validation.annotation.Required;

@Entity
@SequenceGenerator(name="sq_noticia", sequenceName="sq_noticia")
public class Noticia {
	protected Integer idnoticia;
	protected String titulo;
	protected String texto;
	protected Participantelivro participantelivro;
	protected Pessoa pessoa;
	protected Tiponoticia tiponoticia;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_noticia")
	public Integer getIdnoticia() {
		return idnoticia;
	}
	
	@MaxLength(100)
	public String getTitulo() {
		return titulo;
	}
	
	@Required
	@MaxLength(5000)
	public String getTexto() {
		return texto;
	}
	
	@JoinColumn(name="idparticipantelivro")
	@ManyToOne(fetch=FetchType.LAZY)
	public Participantelivro getParticipantelivro() {
		return participantelivro;
	}

	@JoinColumn(name="idpessoa")
	@ManyToOne(fetch=FetchType.LAZY)
	public Pessoa getPessoa() {
		return pessoa;
	}

	@Required
	@JoinColumn(name="idtiponoticia")
	@ManyToOne(fetch=FetchType.LAZY)
	public Tiponoticia getTiponoticia() {
		return tiponoticia;
	}
	public void setIdnoticia(Integer idnoticia) {
		this.idnoticia = idnoticia;
	}
	public void setTitulo(String titulo) {
		this.titulo = titulo;
	}
	public void setTexto(String texto) {
		this.texto = texto;
	}
	public void setParticipantelivro(Participantelivro participantelivro) {
		this.participantelivro = participantelivro;
	}
	public void setPessoa(Pessoa pessoa) {
		this.pessoa = pessoa;
	}
	public void setTiponoticia(Tiponoticia tiponoticia) {
		this.tiponoticia = tiponoticia;
	}
	
}
