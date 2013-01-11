package org.neoframework.bookstore.bean;

import java.util.List;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.OneToMany;
import javax.persistence.SequenceGenerator;
import javax.persistence.Transient;

import br.com.linkcom.neo.bean.annotation.DescriptionProperty;
import br.com.linkcom.neo.bean.annotation.DisplayName;
import br.com.linkcom.neo.validation.annotation.MaxLength;
import br.com.linkcom.neo.validation.annotation.MinValue;
import br.com.linkcom.neo.validation.annotation.Required;

@Entity
@SequenceGenerator(name="sq_livro", sequenceName="sq_livro")
public class Livro {
	protected Integer idlivro;
	protected String titulo;
	protected Boolean lancamento;
	protected Genero genero;
	protected String preco;
	protected Integer anolancamento;
	protected Integer edicao;
	protected Arquivo ebook;
	protected String resumo;
	protected String precoebook;
	
	//transient
	protected Estoque estoque;
	protected Tipoparticipantelivro tipoparticipantelivro;
	protected List<Participantelivro> listaParticipantelivro;
	protected List<Tipoparticipantelivro> listaTipoparticipantelivro;
	protected List<Livrovenda> listaLivrovenda;
	protected List<Pessoa>	listaPessoa;
	protected List<Livro> listalivro;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_livro")
	public Integer getIdlivro() {
		return idlivro;
	}
	
	@DescriptionProperty
	@MaxLength(250)
	@DisplayName("Título")
	@Required
	public String getTitulo() {
		return titulo;
	}
	
	public Boolean getLancamento() {
		return lancamento;
	}
	
	@JoinColumn(name="idgenero")
	@ManyToOne(fetch=FetchType.LAZY)
	@DisplayName("Gênero")
	public Genero getGenero() {
		return genero;
	}
	
	@MinValue(0)
	public String getPreco() {
		return preco;
	}
	
	@Required
	@DisplayName("Ano de lançamento")
	public Integer getAnolancamento() {
		return anolancamento;
	}
	
	@Required
	@DisplayName("Edição")
	public Integer getEdicao() {
		return edicao;
	}
	@JoinColumn(name="idarquivo")
	@ManyToOne(fetch=FetchType.LAZY)
	@DisplayName("E-book")
	public Arquivo getEbook() {
		return ebook;
	}
	@MaxLength(1000)
	public String getResumo() {
		return resumo;
	}
	
	@Transient
	public String getPrecoebook() {
		if(this.preco != null){
			String temp = preco.substring(2);
			Double valor = Double.valueOf(temp);
			valor = valor * 0.6;
			this.setPrecoebook("R$"+valor.toString());
			return precoebook;
		}
		return "R$0,00";
	}
	
	public void setIdlivro(Integer idlivro) {
		this.idlivro = idlivro;
	}
	public void setTitulo(String titulo) {
		this.titulo = titulo;
	}
	public void setLancamento(Boolean lancamento) {
		this.lancamento = lancamento;
	}
	public void setGenero(Genero genero) {
		this.genero = genero;
	}
	public void setPreco(String preco) {
		this.preco = preco;
	}
	public void setAnolancamento(Integer anolancamento) {
		this.anolancamento = anolancamento;
	}
	public void setEdicao (Integer edicao) {
		this.edicao = edicao;
	}
	public void setEbook(Arquivo ebook) {
		this.ebook = ebook;
	}
	public void setResumo(String resumo) {
		this.resumo = resumo;
	}
	public void setPrecoebook(String precoebook) {
		this.precoebook = precoebook;
	}

	
	//transiente
	@Transient
	@JoinColumn(name="idestoque")
	@ManyToOne(fetch=FetchType.LAZY)
	public Estoque getEstoque() {
		return estoque;
	}

	@Transient
	@JoinColumn(name="idtipoparticipantelivro")
	@ManyToOne(fetch=FetchType.LAZY)
	public Tipoparticipantelivro getTipoparticipantelivro() {
		return tipoparticipantelivro;
	}
	
	@OneToMany(mappedBy="livro")
	public List<Participantelivro> getListaParticipantelivro() {
		return listaParticipantelivro;
	}

	public void setEstoque(Estoque estoque) {
		this.estoque = estoque;
	}
	
	public void setTipoparticipantelivro(Tipoparticipantelivro tipoparticipantelivro) {
		this.tipoparticipantelivro = tipoparticipantelivro;
	}

	public void setListaParticipantelivro(
			List<Participantelivro> listaParticipantelivro) {
		this.listaParticipantelivro = listaParticipantelivro;
	}

	@OneToMany(mappedBy="livro")
	public List<Livrovenda> getListaLivrovenda() {
		return listaLivrovenda;
	}

	public void setListaLivrovenda(List<Livrovenda> listaLivrovenda) {
		this.listaLivrovenda = listaLivrovenda;
	}

	@Transient
	@ManyToOne(fetch=FetchType.LAZY)
	public List<Tipoparticipantelivro> getListaTipoparticipantelivro() {
		return listaTipoparticipantelivro;
	}

	public void setListaTipoparticipantelivro(
			List<Tipoparticipantelivro> listaTipoparticipantelivro) {
		this.listaTipoparticipantelivro = listaTipoparticipantelivro;
	}
	@Transient
	@ManyToOne(fetch=FetchType.LAZY)
	public List<Pessoa> getListaPessoa() {
		return listaPessoa;
	}

	public void setListaPessoa(List<Pessoa> listaPessoa) {
		this.listaPessoa = listaPessoa;
	}
	@Transient
	
	public List<Livro> getListalivro() {
		return listalivro;
	}

	public void setListalivro(List<Livro> listalivro) {
		this.listalivro = listalivro;
	}
	
	
	
}
