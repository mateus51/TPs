package org.neoframework.bookstore.bean;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.SequenceGenerator;

@Entity
@SequenceGenerator(name="sq_participantelivro", sequenceName="sq_participantelivro")
public class Participantelivro {
	protected Integer idparticipantelivro;
	protected Livro livro;
	protected Pessoa pessoa;
	protected Tipoparticipantelivro tipoparticipantelivro;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_participantelivro")
	public Integer getIdparticipantelivro() {
		return idparticipantelivro;
	}
	
	@JoinColumn(name="idlivro")
	@ManyToOne(fetch=FetchType.LAZY)
	public Livro getLivro() {
		return livro;
	}
	
	@JoinColumn(name="idpessoa")
	@ManyToOne(fetch=FetchType.LAZY)
	public Pessoa getPessoa() {
		return pessoa;
	}
	
	@JoinColumn(name="idtipoparticipacao")
	@ManyToOne(fetch=FetchType.LAZY)
	public Tipoparticipantelivro getTipoparticipantelivro() {
		return tipoparticipantelivro;
	}
	public void setIdparticipantelivro(Integer idparticipantelivro) {
		this.idparticipantelivro = idparticipantelivro;
	}
	public void setLivro(Livro livro) {
		this.livro = livro;
	}
	public void setPessoa(Pessoa pessoa) {
		this.pessoa = pessoa;
	}
	public void setTipoparticipantelivro(Tipoparticipantelivro tipoparticipantelivro) {
		this.tipoparticipantelivro = tipoparticipantelivro;
	}
	
}
