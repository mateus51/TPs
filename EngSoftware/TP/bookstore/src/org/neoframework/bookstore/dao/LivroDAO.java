package org.neoframework.bookstore.dao;

import java.util.List;

import org.neoframework.bookstore.bean.Livro;
import org.neoframework.bookstore.bean.Livrovenda;
import org.neoframework.bookstore.filter.LivroFiltro;
import org.springframework.orm.hibernate3.HibernateTemplate;

import br.com.linkcom.neo.controller.crud.FiltroListagem;
import br.com.linkcom.neo.persistence.GenericDAO;
import br.com.linkcom.neo.persistence.QueryBuilder;

public class LivroDAO extends GenericDAO<Livro> {

	@Override
	public void updateListagemQuery(QueryBuilder<Livro> query, FiltroListagem _filtro) {
		LivroFiltro filtro = (LivroFiltro)_filtro;
		query
			.from(Livro.class)
			.select("livro.idlivro, livro.titulo, livro.edicao, genero.nome, livro.preco, ebook.idarquivo, livro.lancamento ")
			.join("livro.genero genero")
			.leftOuterJoin("livro.ebook ebook");
		
		if(filtro != null){
			query
			.where("livro.edicao >= ?", filtro.getEdicaode())
			.where("livro.edicao <= ?", filtro.getEdicaoate()) 
			.where("livro.lancamento = ?", filtro.getLancamento() != null && filtro.getLancamento()? filtro.getLancamento() : null);
		}
			
		
		if(filtro.getTitulo() != null){
			query
				.whereLikeIgnoreAll("livro.titulo", filtro.getTitulo());
		}
		
		if(filtro.getTipoparticipantelivro() != null){
			query
				.join("livro.listaParticipantelivro listaParticipantelivro")
				.where("listaParticipantelivro.tipoparticipantelivro = ?", filtro.getTipoparticipantelivro());
			if(filtro.getParticipantelivro() != null){
				query
					
					.where("listaParticipantelivro.pessoa = ?", filtro.getParticipantelivro());
			}
			
		}
		else if(filtro.getParticipantelivro() != null){
			query
			.join("livro.listaParticipantelivro listaParticipantelivro")
			.where("listaParticipantelivro.pessoa = ?", filtro.getParticipantelivro());
		}
	System.out.println(query.getQuery());
	}

	public List<Livro> maisvendido(){
		
		
		return query()
				.select("livro.idlivro, livro.titulo, livro.preco, livro.edicao")
				.leftOuterJoin("livro.listaLivrovenda livrovenda")
				.groupBy("livro.idlivro, livro.titulo, livro.preco, livro.edicao")
				.orderBy("count(livro)*livrovenda.quantidade DESC").list();
			
//			System.out.println(query.getQuery());
//			
//			return query.list();
		}
}
