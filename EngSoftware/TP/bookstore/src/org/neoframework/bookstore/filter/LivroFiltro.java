package org.neoframework.bookstore.filter;

import org.neoframework.bookstore.bean.Pessoa;
import org.neoframework.bookstore.bean.Tipoparticipantelivro;

import br.com.linkcom.neo.controller.crud.FiltroListagem;

public class LivroFiltro extends FiltroListagem {
	protected String titulo;
	protected Integer edicaode;
	protected Integer edicaoate;
	protected Boolean lancamento;
	protected Tipoparticipantelivro tipoparticipantelivro;
	protected Pessoa participantelivro;
	protected Integer anolancamento;
	
	
	
	public String getTitulo() {
		return titulo;
	}
	public Integer getEdicaode() {
		return edicaode;
	}
	public Integer getEdicaoate() {
		return edicaoate;
	}
	public Boolean getLancamento() {
		return lancamento;
	}
	public Tipoparticipantelivro getTipoparticipantelivro() {
		return tipoparticipantelivro;
	}
	public Pessoa getParticipantelivro() {
		return participantelivro;
	}
	public void setTitulo(String titulo) {
		this.titulo = titulo;
	}
	public void setEdicaode(Integer edicaoDe) {
		edicaode = edicaoDe;
	}
	public void setEdicaoate(Integer edicaoAte) {
		edicaoate = edicaoAte;
	}
	public void setLancamento(Boolean lancamento) {
		this.lancamento = lancamento;
	}
	public void setTipoparticipantelivro(Tipoparticipantelivro tipoparticipantelivro) {
		this.tipoparticipantelivro = tipoparticipantelivro;
	}
	public void setParticipantelivro(Pessoa participantelivro) {
		this.participantelivro = participantelivro;
	}
	public Integer getAnolancamento() {
		return anolancamento;
	}
	public void setAnolancamento(Integer anolancamento) {
		this.anolancamento = anolancamento;
	}
	
	
}
