package org.neoframework.bookstore.dao;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

import org.neoframework.bookstore.bean.Livro;
import org.neoframework.bookstore.bean.Livrovenda;
import org.springframework.jdbc.core.RowMapper;

import br.com.linkcom.neo.persistence.GenericDAO;

public class LivrovendaDAO extends GenericDAO<Livrovenda> {

	public List<Livrovenda> maisvendido(){
		
		String sql = "SELECT liv.idlivro, liv.titulo, liv.preco, liv.edicao,  l.quantidade FROM Livrovenda l  INNER JOIN livro liv on l.idlivro = liv.idlivro GROUP BY liv.idlivro, liv.titulo,         l.quantidade,        liv.preco,         liv.edicao ORDER BY Count(*) * l.quantidade DESC";
		List<Livrovenda> lista = getJdbcTemplate().query(sql, new RowMapper(){
		public Object mapRow(ResultSet rs, int rowNum) throws SQLException{
			Livrovenda bean = new Livrovenda();
			bean.setLivro(new Livro());
			bean.getLivro().setIdlivro(rs.getInt(1));
			bean.getLivro().setTitulo(rs.getString(2));
			bean.getLivro().setPreco(rs.getString(3));
			bean.getLivro().setEdicao(rs.getInt(4));
		
			return bean;
		}
		});
		return lista;
//	return query()
//			.from(Livrovenda.class)
//			.select("livro.idlivro, livro.titulo, livro.preco, livro.edicao")
//			.leftOuterJoin("livrovenda.livro livro", true)
//			.groupBy("livro.idlivro, livro.titulo, livro.preco, livro.edicao")
////			.orderBy("count(*)*livrovenda.quantidade DESC")
//			.list();
		
//		System.out.println(query.getQuery());
//		
//		return query.list();
	}
}
