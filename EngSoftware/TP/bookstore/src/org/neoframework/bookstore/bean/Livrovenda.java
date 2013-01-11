package org.neoframework.bookstore.bean;

import java.util.List;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.SequenceGenerator;
import javax.persistence.Transient;

import org.neoframework.bookstore.types.Money;

import br.com.linkcom.neo.validation.annotation.Required;

@Entity
@SequenceGenerator(name="sq_livrovenda", sequenceName="sq_livrovenda")
public class Livrovenda {
	protected Integer idlivrovenda;
	protected Money preco;
	protected Integer quantidade;
	protected Boolean vendaebook;
	protected Livro livro;
	protected Venda venda;
	
	protected List<Livrovenda> livrovendatrans;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO, generator="sq_livrovenda")
	public Integer getIdlivrovenda() {
		return idlivrovenda;
	}
	
	@Required
	public Money getPreco() {
		return preco;
	}
	
	@Required
	public Integer getQuantidade() {
		return quantidade;
	}
	
	@Required
	public Boolean getVendaebook() {
		return vendaebook;
	}
	
	@Required
	@JoinColumn(name="idlivro")
	@ManyToOne(fetch=FetchType.LAZY)
	public Livro getLivro() {
		return livro;
	}
	
	@Required
	@JoinColumn(name="idvenda")
	@ManyToOne(fetch=FetchType.LAZY)
	public Venda getVenda() {
		return venda;
	}
	public void setIdlivrovenda(Integer idlivrovenda) {
		this.idlivrovenda = idlivrovenda;
	}
	public void setPreco(Money preco) {
		this.preco = preco;
	}
	public void setQuantidade(Integer quantidade) {
		this.quantidade = quantidade;
	}
	public void setVendaebook(Boolean vendaebook) {
		this.vendaebook = vendaebook;
	}
	public void setLivro(Livro livro) {
		this.livro = livro;
	}
	public void setVenda(Venda venda) {
		this.venda = venda;
	}
	@Transient
	public List<Livrovenda> getLivrovendatrans() {
		return livrovendatrans;
	}

	public void setLivrovendatrans(List<Livrovenda> livrovendatrans) {
		this.livrovendatrans = livrovendatrans;
	}
	
	
	
	
}
